#include "Game.hpp"

std::ostream &operator<<(std::ostream &os, const GameBoard &gb) {
  for (int row{GameBoard::Height - 1}; row >= 0; row--) {
    for (int col{0}; col < GameBoard::Width; col++) {
      auto v = gb.m_game_board[row][col];
      if (!v) {
        os << "x ";
        continue;
      }
      if (v->type() == GamePiece::Type::Red) {
        os << "R ";
      } else if (v->type() == GamePiece::Type::Yellow) {
        os << "Y ";
      }
    }
    os << "\n";
  }
  return os;
}

PlayScore GameBoard::scorePlay(int row, int col, const GamePiece &gp) {
  int right{0};
  int left{0};
  int down{0};
  int down_right{0};
  int down_left{0};

  for (int i{1}; i <= 4 && col - i >= 0; i++) {
    if (m_game_board[row][col - i] &&
        m_game_board[row][col - i]->type() == gp.type()) {
      left++;
    } else {
      break;
    }
  }
  for (int i{1}; i <= 4 && col + i < GameBoard::Width; i++) {
    if (m_game_board[row][col + i] &&
        m_game_board[row][col + i]->type() == gp.type()) {
      right++;
    } else {
      break;
    }
  }

  for (int i{1}; i <= 4 && col - i >= 0 && row - i >= 0; i++) {
    if (m_game_board[row - i][col - i] &&
        m_game_board[row - i][col - i]->type() == gp.type()) {
      down_left++;
    } else {
      break;
    }
  }

  for (int i{1}; i <= 4 && col + i < GameBoard::Width && row - i >= 0; i++) {
    if (m_game_board[row - i][col + i] &&
        m_game_board[row - i][col + i]->type() == gp.type()) {
      down_right++;
    } else {
      break;
    }
  }

  for (int i{1}; i <= 4 && row - i >= 0; i++) {
    if (m_game_board[row - i][col] &&
        m_game_board[row - i][col]->type() == gp.type()) {
      down++;
    } else {
      break;
    }
  }

  return PlayScore(left, down_left, down, down_right, right);
}
