#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <iostream>
#include <memory>
#include <qpixmap.h>
#include <string>
#include <vector>

class GamePiece {
public:
  virtual std::string toString() = 0;
  virtual QPixmap toPixmap() = 0;
};

class RedPiece : public GamePiece {
  std::string toString() { return "Red"; }
  QPixmap toPixmap() { return QPixmap(QString::fromUtf8(":/assets/connect-four-red.png"));}
};

class YellowPiece : public GamePiece {
  std::string toString() { return "Yellow"; }
  QPixmap toPixmap() { return QPixmap(QString::fromUtf8(":/assets/connect-four-yellow.png"));}
};

class GameBoard {
public:
  bool isFilled(int row, int column) const {
    return !!m_game_board[row][column];
  }
  void setPosition(std::shared_ptr<GamePiece> gp, int row, int column) {
    m_game_board[row][column] = gp;
  }
  auto getPosition(int row, int column) {
    return m_game_board[row][column];
  }

private:
  std::vector<std::vector<std::shared_ptr<GamePiece>>> m_game_board =
      std::vector<std::vector<std::shared_ptr<GamePiece>>>(
          6, std::vector<std::shared_ptr<GamePiece>>(7, nullptr));
};

class GameController {
public:
  auto getPosition(int row, int column) {
    return m_active_gb.getPosition(row, column);
  }

  bool playPiece(std::shared_ptr<GamePiece> gp, int column) {
    int row{0};
    for (; row < 6; row++) {
      if (m_active_gb.isFilled(row, column)) {
        break;
      }
    }

    if (row == 0) {
      return false;
    }

    row--;
    m_active_gb.setPosition(gp, row, column);

    std::cout << "Putting a " << gp->toString() << " at the " << row
              << " row and the " << column << " column.\n";

    return true;
  }

private:
  GameBoard m_active_gb{};
};

#endif