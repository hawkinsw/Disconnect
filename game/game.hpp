#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
#include <vector>

class GamePiece {
public:
  enum class Type {
    Red, Yellow
  };
  virtual std::string toString() = 0;
  virtual Type type() const = 0;
};

class RedGamePiece : public GamePiece {
public:
  std::string toString() { return "Red"; }
  Type type() const { return GamePiece::Type::Red; }
};

class YellowGamePiece : public GamePiece {
public:
  std::string toString() { return "Yellow"; }
  Type type() const  { return GamePiece::Type::Yellow; }
};

class GameBoard {
public:
  static const int Width{7};
  static const int Height{6};

  bool isFilled(int row, int column) const {
    return !!m_game_board[row][column];
  }
  void setPosition(GamePiece::Type gpt, int row, int column) {
    if (gpt == GamePiece::Type::Red) {
      m_game_board[row][column] = std::make_shared<RedGamePiece>();
    } else  {
      m_game_board[row][column] = std::make_shared<YellowGamePiece>();
    }
  }
  auto getPosition(int row, int column) {
    return m_game_board[row][column];
  }

  std::vector<int> scorePlay(int row, int column, const GamePiece &gp);

  friend std::ostream &operator<<(std::ostream &os, const GameBoard &gb);
private:
  std::vector<std::vector<std::shared_ptr<GamePiece>>> m_game_board =
      std::vector<std::vector<std::shared_ptr<GamePiece>>>(
          6, std::vector<std::shared_ptr<GamePiece>>(7, nullptr));
};
#endif