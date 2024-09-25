#include "KamisadoGame.h"
#include <format>

KamisadoGame::KamisadoGame() : m_CurrentTower(nullptr) {
    // set board spaces
    for ( int y = 0; y < Kamisado::BOARD_HEIGHT; ++y ) {
        for ( int x = 0; x < Kamisado::BOARD_WIDTH; ++x ) {
            m_Board[y][x].m_SpaceColor = Kamisado::BOARD_LAYOUT[y][x];
        }
    }

    // set board towers
    for ( int x = 0; x < Kamisado::BOARD_WIDTH; ++x ) {
        // create tower for gold and black player
        Kamisado::BoardCoord black_coord = {x, Kamisado::BOARD_HEIGHT-1};
        Kamisado::BoardCoord gold_coord = {x, 0};
        Kamisado::SpaceColor black_color = m_Board[black_coord.y][black_coord.x].m_SpaceColor;
        Kamisado::SpaceColor gold_color = m_Board[gold_coord.y][gold_coord.x].m_SpaceColor;
        auto black_tower = std::make_shared<Kamisado::Tower>(Kamisado::PlayerColor::BLACK, black_color, black_coord);
        auto gold_tower = std::make_shared<Kamisado::Tower>(Kamisado::PlayerColor::GOLD, gold_color, gold_coord);

        // insert gold and black player tower into board and tower array
        m_Board[black_coord.y][black_coord.x].m_Occupier = black_tower;
        m_Board[gold_coord.y][gold_coord.x].m_Occupier = gold_tower;
        m_BlackTowers[black_color] = black_tower;
        m_GoldTowers[gold_color] = gold_tower;
    }
}

KamisadoGame::~KamisadoGame() {

}

void KamisadoGame::PlayOnTerminal() {
    // decide first player
    Kamisado::PlayerColor turn_color = HandlePrompt<Kamisado::PlayerColor>(
        "Who goes first? [GOLD, BLACK]: ", 
        [](const Kamisado::PlayerColor& c) {
            return true; // if parser is successful then value is valid
        },
        [](const std::string& s) {
            return Kamisado::StringPlayerColor.at(s);
    });

    // first player decides which tower tower to move
    const std::string prompt = std::format("{} player, select a tower to move [{}]", 
        Kamisado::PlayerColorString.at(turn_color), Kamisado::COLORS_STRING);
    Kamisado::SpaceColor tower_color = HandlePrompt<Kamisado::SpaceColor>(
        prompt,
        [](const Kamisado::SpaceColor& c) {
            return true; // if parser is successful then value is valid
        },
        [](const std::string& s) {
            return Kamisado::StringSpaceColor.at(s);
    });

    m_CurrentTower = turn_color == Kamisado::PlayerColor::GOLD ? m_GoldTowers[tower_color] : m_BlackTowers[tower_color];

    while ( m_CurrentTower != nullptr ) {
        Turn();
    }

    TerminalDisplay::ClearTerminal();
    TerminalDisplay::DisplayBoard(m_Board);
    std::string winmsg = std::format("{} wins!", Kamisado::PlayerColorString.at(m_Winner));
    TerminalDisplay::DisplayText(winmsg, Kamisado::SpaceColor::GREEN);
}

void KamisadoGame::Turn() {
    // get coordinates for current player to move to, confirm it is a valid move
    std::string prompt = std::format(
        "{} player, select a coordinate to move {} tower on coordinates {},{} (y,x): ",
        Kamisado::PlayerColorString.at(m_CurrentTower->m_PlayerColor),
        Kamisado::SpaceColorString.at(m_CurrentTower->m_TowerColor),
        m_CurrentTower->m_Coords.y,
        m_CurrentTower->m_Coords.x);

    Kamisado::BoardCoord coord = HandlePrompt<Kamisado::BoardCoord>(
        prompt,
        [this](const Kamisado::BoardCoord& c) {
            return c.IsValid() && ValidTowerMove(c);
        },
        [](const std::string& s) {
            Kamisado::BoardCoord coords{0,0};
            
            coords.y = std::stoi(s.substr(0,1));
            coords.x = std::stoi(s.substr(2, 1));

            return coords;
        }
    );

    MoveCurrentTower(coord);
}


bool KamisadoGame::ValidTowerMove(const Kamisado::BoardCoord& coords) const {
    // check if coordinates are in vertical or diagonal path from current tower coordinates
    auto current_tower_coords = m_CurrentTower->m_Coords;

    bool vertical_path = false, diagonal_path = false;
    if ( m_CurrentTower->m_PlayerColor == Kamisado::PlayerColor::GOLD ) {
        vertical_path = current_tower_coords.x == coords.x && current_tower_coords.y < coords.y;
        diagonal_path = std::abs(coords.x - current_tower_coords.x) == coords.y - current_tower_coords.y
                                && current_tower_coords.y < coords.y;
    }
    else {
        vertical_path = current_tower_coords.x == coords.x && current_tower_coords.y > coords.y;
        diagonal_path = std::abs(current_tower_coords.x - coords.x) == current_tower_coords.y - coords.y
                                && current_tower_coords.y > coords.y;
    }

    if ( !vertical_path && !diagonal_path ) return false;

    // check if path to new coordinates is blocked
    int d_x = current_tower_coords.x > coords.x ? -1 : 1;
    int x = diagonal_path ? current_tower_coords.x + d_x : current_tower_coords.x;
    for ( int y = current_tower_coords.y+1; y <= coords.y; ++y ) {
        if ( m_Board[y][x].m_Occupier != nullptr ) return false;
        x += diagonal_path ? d_x : 0;
    }

    return true;
}

void KamisadoGame::MoveCurrentTower(const Kamisado::BoardCoord& coords) {
    // check for winner
    if ( m_CurrentTower->m_PlayerColor == Kamisado::PlayerColor::GOLD && coords.y == Kamisado::BOARD_HEIGHT - 1 ) {
        m_Winner = Kamisado::PlayerColor::GOLD;
        m_CurrentTower = nullptr;
        return;
    }
    else if ( m_CurrentTower->m_PlayerColor == Kamisado::PlayerColor::BLACK && coords.y == 0) {
        m_Winner = Kamisado::PlayerColor::BLACK;
        m_CurrentTower = nullptr;
        return;
    }

    // update board state and tower coordinates
    m_Board[m_CurrentTower->m_Coords.y][m_CurrentTower->m_Coords.x].m_Occupier = nullptr;
    m_Board[coords.y][coords.x].m_Occupier = m_CurrentTower;
    m_CurrentTower->UpdateCoords(coords);

    // update tower pointer for next turn
    Kamisado::SpaceColor next_tower = m_Board[coords.y][coords.x].m_SpaceColor;
    m_CurrentTower = m_CurrentTower->m_PlayerColor == Kamisado::PlayerColor::GOLD ?
        m_BlackTowers[next_tower] : m_GoldTowers[next_tower];

    // check if new tower is blocked and update state + turn accordingly
    // last player moves tower based on color blocked tower is on
    if ( !IsCurrentTowerBlocked() ) return;

    auto new_coords = m_CurrentTower->m_Coords;
    next_tower = m_Board[new_coords.y][new_coords.x].m_SpaceColor;
    m_CurrentTower = m_CurrentTower->m_PlayerColor == Kamisado::PlayerColor::GOLD ?
        m_BlackTowers[next_tower] : m_GoldTowers[next_tower];

    // if next tower is blocked too, last player loses
    if ( !IsCurrentTowerBlocked() ) return;

    m_Winner = m_CurrentTower->m_PlayerColor;
    m_CurrentTower = nullptr;
}

bool KamisadoGame::IsCurrentTowerBlocked() const {
    Kamisado::BoardCoord c1,c2,c3;
    auto coord = m_CurrentTower->m_Coords;
    if ( m_CurrentTower->m_PlayerColor == Kamisado::PlayerColor::GOLD ) {
        c1 = {coord.x == 0 ? 0 : coord.x - 1, coord.y + 1};
        c2 = {coord.x, coord.y + 1};
        c3 = {coord.x == Kamisado::BOARD_WIDTH-1 ? Kamisado::BOARD_WIDTH-1 : coord.x + 1,coord.y + 1};
    }
    else {
        c1 = {coord.x == 0 ? 0 : coord.x - 1, coord.y - 1};
        c2 = {coord.x, coord.y - 1};
        c3 = {coord.x == Kamisado::BOARD_WIDTH-1 ? Kamisado::BOARD_WIDTH-1 : coord.x + 1,coord.y - 1};
    }

    return  m_Board[c1.y][c1.x].m_Occupier != nullptr &&
            m_Board[c2.y][c2.x].m_Occupier != nullptr &&
            m_Board[c3.y][c3.x].m_Occupier != nullptr;
}