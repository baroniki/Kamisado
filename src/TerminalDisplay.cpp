#include "TerminalDisplay.h"

#include <iostream>

void TerminalDisplay::DisplayText(std::string& s, const Kamisado::SpaceColor& color) {
    color_text(s, color);
    std::cout << s << std::endl;
}

void TerminalDisplay::DisplayBoard(const Kamisado::Board& board) {
    for (int y = 0; y < Kamisado::BOARD_HEIGHT; ++y) {
        for (int i = 0; i < 3; ++i) {
            if ( i == 1 ) { std::cout << y << " "; }
            else { std::cout << "  "; }

            for (int x = 0; x < Kamisado::BOARD_WIDTH; ++x) {
                Kamisado::BoardSpace space = board[y][x];
                std::string space_str = "       ";
                if ( !space.IsEmpty() && i == 1 ) {
                    space_str = space.m_Occupier->m_PlayerColor == Kamisado::PlayerColor::GOLD ? "   G   " : "   B   ";
                    color_text(space_str, space.m_Occupier->m_TowerColor, space.m_SpaceColor);
                }
                else {
                    color_text(space_str, space.m_SpaceColor);
                }

                std::cout << space_str << std::flush;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "  ";
    for (int x = 0; x < Kamisado::BOARD_WIDTH; ++x) {
        std::cout << "   " << x << "   ";
    }
    std::cout << std::endl;
}

void TerminalDisplay::DisplayPrompt(const std::string& prompt, std::string& response) {
    std::cout << prompt << std::endl;
    std::cin >> response;
}

void TerminalDisplay::ClearTerminal() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void TerminalDisplay::color_text(std::string& to_color, const Kamisado::SpaceColor& text_color, const Kamisado::SpaceColor& bg_color) {
    std::string text_color_code = text_color == bg_color ? BLACK_COLOR_CODE : text_color_map.find(text_color)->second;
    std::string bg_color_code = bg_color_map.find(bg_color)->second;

    to_color = text_color_code + bg_color_code + to_color + RESET_COLOR_CODE;
}

void TerminalDisplay::color_text(std::string& to_color, const Kamisado::SpaceColor& bg_color) {
    std::string bg_color_code = bg_color_map.find(bg_color)->second;

    to_color = bg_color_code + to_color + RESET_COLOR_CODE;
}