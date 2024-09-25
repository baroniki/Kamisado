#pragma once
#include <array>
#include <functional>

#include "KamisadoStructs.h"
#include "TerminalDisplay.h"

class KamisadoGame {
public:
    KamisadoGame();
    ~KamisadoGame();

    void PlayOnTerminal();

private:
    // data members
    Kamisado::Board m_Board;
    std::array<std::shared_ptr<Kamisado::Tower>, Kamisado::BOARD_WIDTH> m_GoldTowers;
    std::array<std::shared_ptr<Kamisado::Tower>, Kamisado::BOARD_WIDTH> m_BlackTowers;

    std::shared_ptr<Kamisado::Tower> m_CurrentTower;
    Kamisado::PlayerColor m_Winner;

    // helper functions
    void Turn();

    bool ValidTowerMove(const Kamisado::BoardCoord& coord) const;
    bool IsCurrentTowerBlocked() const;
    void MoveCurrentTower(const Kamisado::BoardCoord& coord);

    Kamisado::SpaceColor ParseSpaceColor(const std::string& prompt) const;

    template <typename T>
    T HandlePrompt(const std::string& prompt, std::function<bool(const T&)> validator, std::function<T(std::string&)> parser) const {
        std::string response = "";
        T parsed_response;
        while (true) {
            TerminalDisplay::DisplayBoard(m_Board);
            TerminalDisplay::DisplayPrompt(prompt, response);
            TerminalDisplay::ClearTerminal();

            try {
                parsed_response = parser(response);
                if ( !response.empty() && validator(parsed_response) )
                    return parsed_response;
            } catch (...) { /* do nothing: ask prompt again */ }
        }
    }

};