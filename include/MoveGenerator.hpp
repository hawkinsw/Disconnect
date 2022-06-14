#ifndef MOVEGENERATOR_HPP
#define MOVEGENERATOR_HPP

#include "GameController.hpp"

class MoveGenerator {
  public:
    MoveGenerator(const GameBoard gb, std::shared_ptr<GamePiece> gp): m_Gb{gb}, m_piece{gp} {};
    std::pair<int, int> Generate();

  private:
    GameBoard m_Gb{};
    std::shared_ptr<GamePiece> m_piece;
};
#endif