#pragma once

#include "KamisadoStructs.h"

#include <map>
#include <string>

class TerminalDisplay {
public:
    static void DisplayBoard(const Kamisado::Board& board);
    static void DisplayPrompt(const std::string& prompt, std::string& response);
    static void DisplayText(std::string& prompt, const Kamisado::SpaceColor& color);
    static void ClearTerminal();
    static void color_text(std::string& to_color, const Kamisado::SpaceColor& text_color, const Kamisado::SpaceColor& bg_color);
    static void color_text(std::string& to_color, const Kamisado::SpaceColor& bg_color);
};

const std::string RESET_COLOR_CODE = "\033[0m";
const std::string BLACK_COLOR_CODE = "\033[30m";

const std::map<Kamisado::SpaceColor, std::string> text_color_map = {
    { Kamisado::SpaceColor::ORANGE, "\033[38;2;255;165;0m" },
    { Kamisado::SpaceColor::RED, "\033[38;2;255;0;0m" },
    { Kamisado::SpaceColor::GREEN, "\033[38;2;0;255;0m" },
    { Kamisado::SpaceColor::PINK, "\033[38;2;255;192;203m" },
    { Kamisado::SpaceColor::YELLOW, "\033[38;2;255;255;0m" },
    { Kamisado::SpaceColor::BLUE, "\033[38;2;0;0;255m" },
    { Kamisado::SpaceColor::PURPLE, "\033[38;2;128;0;128m" },
    { Kamisado::SpaceColor::BROWN, "\033[38;2;139;69;19m" }
};

const std::map<Kamisado::SpaceColor, std::string> bg_color_map = {
    { Kamisado::SpaceColor::ORANGE, "\033[48;2;255;165;0m" },
    { Kamisado::SpaceColor::RED, "\033[48;2;255;0;0m" },
    { Kamisado::SpaceColor::GREEN, "\033[48;2;0;255;0m" },
    { Kamisado::SpaceColor::PINK, "\033[48;2;255;192;203m" },
    { Kamisado::SpaceColor::YELLOW, "\033[48;2;255;255;0m" },
    { Kamisado::SpaceColor::BLUE, "\033[48;2;0;0;255m" },
    { Kamisado::SpaceColor::PURPLE, "\033[48;2;128;0;128m" },
    { Kamisado::SpaceColor::BROWN, "\033[48;2;139;69;19m" }
};