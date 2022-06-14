#include <iostream>
#include "game.hpp"

int main() {
  GameBoard gb{};

  gb.setPosition(GamePiece::Type::Red, 0, 0);
  gb.setPosition(GamePiece::Type::Red, 1, 1);
  gb.setPosition(GamePiece::Type::Red, 2, 2);
  gb.setPosition(GamePiece::Type::Red, 2, 4);
  gb.setPosition(GamePiece::Type::Red, 1, 5);
  gb.setPosition(GamePiece::Type::Red, 0, 6);
  gb.setPosition(GamePiece::Type::Red, 3, 0);
  gb.setPosition(GamePiece::Type::Red, 3, 6);
  gb.setPosition(GamePiece::Type::Red, 0, 3);
  gb.setPosition(GamePiece::Type::Red, 1, 3);
  gb.setPosition(GamePiece::Type::Red, 2, 3);
  std::cout << gb << "\n";
  auto scores{gb.scorePlay(3, 3, RedGamePiece{})};
  std::cout << "left: " << scores[0] << "\n";
  std::cout << "down_left: " << scores[1] << "\n";
  std::cout << "down: " << scores[2] << "\n";
  std::cout << "down_right: " << scores[3] << "\n";
  std::cout << "right: " << scores[4] << "\n";
  std::cout << "Done.\n";
}