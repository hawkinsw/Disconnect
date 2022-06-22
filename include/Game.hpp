#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
#include <vector>

class GamePiece {
public:
  enum class Type { Red, Yellow };
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
  Type type() const { return GamePiece::Type::Yellow; }
};

class PlayScore {
public:
  PlayScore(int left, int down_left, int down, int down_right, int right)
      : m_left{left}, m_down_left{down_left}, m_down{down},
        m_down_right{down_right}, m_right{right} {}

  int leftScore() const { return m_left; }
  int rightScore() const { return m_right; }
  int downRightScore() const { return m_down_right; }
  int downLeftScore() const { return m_down_left; }
  int downScore() const { return m_down; }

private:
  int m_left{0}, m_down_left{0}, m_down{0}, m_down_right{0}, m_right{0};
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
    } else {
      m_game_board[row][column] = std::make_shared<YellowGamePiece>();
    }
  }
  auto getPosition(int row, int column) { return m_game_board[row][column]; }

  PlayScore scorePlay(int row, int column, const GamePiece &gp);

  friend std::ostream &operator<<(std::ostream &os, const GameBoard &gb);

private:
  std::vector<std::vector<std::shared_ptr<GamePiece>>> m_game_board =
      std::vector<std::vector<std::shared_ptr<GamePiece>>>(
          6, std::vector<std::shared_ptr<GamePiece>>(7, nullptr));
};
#endif