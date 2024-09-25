#pragma once

#include <memory>
#include <array>
#include <map>
#include <string>

namespace Kamisado {

enum SpaceColor { 
    ORANGE, 
    RED, 
    GREEN, 
    PINK, 
    YELLOW, 
    BLUE, 
    PURPLE, 
    BROWN 
};

const std::string COLORS_STRING = "ORANGE, RED, GREEN, PINK, YELLOW, BLUE, PURPLE, BROWN";

const std::map<SpaceColor, std::string> SpaceColorString {
    { SpaceColor::ORANGE, "ORANGE"},
    { SpaceColor::RED, "RED"},
    { SpaceColor::GREEN, "GREEN"},
    { SpaceColor::PINK, "PINK"},
    { SpaceColor::YELLOW, "YELLOW"},
    { SpaceColor::BLUE, "BLUE"},
    { SpaceColor::PURPLE, "PURPLE"},
    { SpaceColor::BROWN, "BROWN"},
};
const std::map<std::string, SpaceColor> StringSpaceColor {
    { "ORANGE", SpaceColor::ORANGE },
    { "RED", SpaceColor::RED },
    { "GREEN", SpaceColor::GREEN },
    { "PINK", SpaceColor::PINK },
    { "YELLOW", SpaceColor::YELLOW },
    { "BLUE", SpaceColor::BLUE },
    { "PURPLE", SpaceColor::PURPLE },
    { "BROWN", SpaceColor::BROWN }
};

enum PlayerColor {
    GOLD,
    BLACK
};

const std::map<PlayerColor, std::string> PlayerColorString {
    { PlayerColor::GOLD, "GOLD" },
    { PlayerColor::BLACK, "BLACK" }
};
const std::map<std::string, PlayerColor> StringPlayerColor {
    { "GOLD", PlayerColor::GOLD },
    { "BLACK", PlayerColor::BLACK }
};

constexpr int BOARD_HEIGHT = 8;
constexpr int BOARD_WIDTH = 8;
const std::array<std::array<SpaceColor, BOARD_WIDTH>, BOARD_HEIGHT> BOARD_LAYOUT = {{
    {   SpaceColor::BROWN, SpaceColor::PURPLE, SpaceColor::BLUE, SpaceColor::YELLOW,
        SpaceColor::PINK, SpaceColor::GREEN, SpaceColor::RED, SpaceColor::ORANGE },
    {   SpaceColor::GREEN, SpaceColor::BROWN, SpaceColor::YELLOW, SpaceColor::RED,
        SpaceColor::PURPLE, SpaceColor::PINK, SpaceColor::ORANGE, SpaceColor::BLUE },
    {   SpaceColor::RED, SpaceColor::YELLOW, SpaceColor::BROWN, SpaceColor::GREEN,
        SpaceColor::BLUE, SpaceColor::ORANGE, SpaceColor::PINK, SpaceColor::PURPLE },
    {   SpaceColor::YELLOW, SpaceColor::BLUE, SpaceColor::PURPLE, SpaceColor::BROWN,
        SpaceColor::ORANGE, SpaceColor::RED, SpaceColor::GREEN, SpaceColor::PINK },
    {   SpaceColor::PINK, SpaceColor::GREEN, SpaceColor::RED, SpaceColor::ORANGE,
        SpaceColor::BROWN, SpaceColor::PURPLE, SpaceColor::BLUE, SpaceColor::YELLOW },
    {   SpaceColor::PURPLE, SpaceColor::PINK, SpaceColor::ORANGE, SpaceColor::BLUE,
        SpaceColor::GREEN, SpaceColor::BROWN, SpaceColor::YELLOW, SpaceColor::RED },
    {   SpaceColor::BLUE, SpaceColor::ORANGE, SpaceColor::PINK, SpaceColor::PURPLE,
        SpaceColor::RED, SpaceColor::YELLOW, SpaceColor::BROWN, SpaceColor::GREEN },
    {   SpaceColor::ORANGE, SpaceColor::RED, SpaceColor::GREEN, SpaceColor::PINK,
        SpaceColor::YELLOW, SpaceColor::BLUE, SpaceColor::PURPLE, SpaceColor::BROWN }
}};

struct BoardCoord {
    int x, y;
    bool IsValid() const { return x >= 0 && x <= BOARD_WIDTH && y >= 0 && y <= BOARD_HEIGHT; };
};

struct Tower {
    PlayerColor m_PlayerColor;
    SpaceColor m_TowerColor;
    BoardCoord m_Coords;

    Tower(const PlayerColor player, const SpaceColor space, const BoardCoord coord)
        :   m_PlayerColor(player),
            m_TowerColor(space),
            m_Coords(coord) {};

    void UpdateCoords(const BoardCoord& c) {
        m_Coords.x = c.x;
        m_Coords.y = c.y;
    }
};


struct BoardSpace {
    SpaceColor m_SpaceColor;
    std::shared_ptr<Tower> m_Occupier;

    BoardSpace() : m_SpaceColor(SpaceColor::ORANGE), m_Occupier(nullptr) {}

    bool IsEmpty() {
        return m_Occupier == nullptr;
    }
};

using Board = std::array<std::array<BoardSpace, 8>, 8>;

};