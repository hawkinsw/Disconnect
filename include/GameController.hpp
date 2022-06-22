#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <iostream>
#include <memory>
#include <qpixmap.h>
#include <string>
#include <vector>
#include "Game.hpp"

class RenderableGamePiece {
public:
  virtual std::string toString() = 0;
  virtual QPixmap toPixmap() = 0;
  virtual GamePiece::Type toType() = 0;
};

class RenderableRedPiece : public RenderableGamePiece {
  std::string toString() { return game_piece.toString(); }
  QPixmap toPixmap() { return QPixmap(QString::fromUtf8(":/assets/connect-four-red.png"));}
  GamePiece::Type toType() { return game_piece.type(); };
  private:
    RedGamePiece game_piece;
};

class RenderableYellowPiece : public RenderableGamePiece {
  std::string toString() { return game_piece.toString(); }
  QPixmap toPixmap() { return QPixmap(QString::fromUtf8(":/assets/connect-four-yellow.png"));}
  GamePiece::Type toType() { return game_piece.type(); };
  private:
    YellowGamePiece game_piece;
};

class GameController {
public:
  auto getPosition(int row, int column) {
    return m_renderable_game_board[row][column];
  }

  auto getActiveGameboard() {
    return m_active_gb;
  }

  bool playPiece(std::shared_ptr<RenderableGamePiece> gp, int column) {
    int row{0};
    for (; row < GameBoard::Height; row++) {
      if (m_active_gb.isFilled(row, column)) {
        break;
      }
    }

    if (row == 0) {
      return false;
    }

    row--;
    m_active_gb.setPosition(gp->toType(), row, column);
    m_renderable_game_board[row][column] = gp;

    std::cout << "Putting a " << gp->toString() << " at the " << row
              << " row and the " << column << " column.\n";

    return true;
  }

private:
  GameBoard m_active_gb{};
  std::vector<std::vector<std::shared_ptr<RenderableGamePiece>>> m_renderable_game_board =
      std::vector<std::vector<std::shared_ptr<RenderableGamePiece>>>(
          6, std::vector<std::shared_ptr<RenderableGamePiece>>(7, nullptr));
};
#endif