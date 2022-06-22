#include "Game.hpp"
#include <iostream>

bool simple_right_test(bool debug = false) {
  GameBoard gb{};
  gb.setPosition(GamePiece::Type::Red, 2, 3);
  gb.setPosition(GamePiece::Type::Red, 2, 4);
  gb.setPosition(GamePiece::Type::Red, 2, 5);
  if (debug) {
    std::cout << gb << "\n";
  }
  auto score{gb.scorePlay(2, 2, RedGamePiece{})};
  if (score.rightScore() == 3 && score.leftScore() == 0 &&
      score.downLeftScore() == 0 && score.downScore() == 0 &&
      score.downRightScore() == 0) {
    return true;
  }
  return false;
}

bool simple_left_test(bool debug = false) {
  GameBoard gb{};
  gb.setPosition(GamePiece::Type::Red, 2, 3);
  gb.setPosition(GamePiece::Type::Red, 2, 4);
  gb.setPosition(GamePiece::Type::Red, 2, 5);
  if (debug) {
    std::cout << gb << "\n";
  }
  auto score{gb.scorePlay(2, 6, RedGamePiece{})};
  if (score.rightScore() == 0 && score.leftScore() == 3 &&
      score.downLeftScore() == 0 && score.downScore() == 0 &&
      score.downRightScore() == 0) {
    return true;
  }
  return false;
}

bool simple_down_left_test(bool debug = false) {
  GameBoard gb{};
  gb.setPosition(GamePiece::Type::Red, 2, 3);
  gb.setPosition(GamePiece::Type::Red, 1, 2);
  gb.setPosition(GamePiece::Type::Red, 0, 1);
  if (debug) {
    std::cout << gb << "\n";
  }
  auto score{gb.scorePlay(3, 4, RedGamePiece{})};
  if (score.rightScore() == 0 && score.leftScore() == 0 &&
      score.downLeftScore() == 3 && score.downScore() == 0 &&
      score.downRightScore() == 0) {
    return true;
  }
  return false;
}

bool simple_down_test(bool debug = false) {
  GameBoard gb{};
  gb.setPosition(GamePiece::Type::Red, 3, 3);
  gb.setPosition(GamePiece::Type::Red, 2, 3);
  gb.setPosition(GamePiece::Type::Red, 1, 3);
  if (debug) {
    std::cout << gb << "\n";
  }
  auto score{gb.scorePlay(4, 3, RedGamePiece{})};
  if (score.rightScore() == 0 && score.leftScore() == 0 &&
      score.downLeftScore() == 0 && score.downScore() == 3 &&
      score.downRightScore() == 0) {
    return true;
  }
  return false;
}

bool simple_down_right_test(bool debug = false) {
  GameBoard gb{};
  gb.setPosition(GamePiece::Type::Red, 3, 3);
  gb.setPosition(GamePiece::Type::Red, 2, 4);
  gb.setPosition(GamePiece::Type::Red, 1, 5);
  if (debug) {
    std::cout << gb << "\n";
  }
  auto score{gb.scorePlay(4, 2, RedGamePiece{})};
  if (score.rightScore() == 0 && score.leftScore() == 0 &&
      score.downLeftScore() == 0 && score.downScore() == 0 &&
      score.downRightScore() == 3) {
    return true;
  }
  return false;
}

#define RUN_TEST(test_name, debug)                                             \
  do {                                                                         \
    if (!test_name(debug)) {                                                   \
      std::cout << #test_name " failed\n";                                     \
    } else {                                                                   \
      std::cout << #test_name " succeeded\n";                                  \
    }                                                                          \
  } while (false);

int main() {
  bool debug{false};
  RUN_TEST(simple_right_test, debug)
  RUN_TEST(simple_left_test, debug)
  RUN_TEST(simple_down_left_test, debug)
  RUN_TEST(simple_down_test, debug)
  RUN_TEST(simple_down_right_test, debug)
  return 0;
}