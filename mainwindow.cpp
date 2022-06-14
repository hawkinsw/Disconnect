#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.hpp"
#include <GameController.hpp>
#include <MoveGenerator.hpp>
#include <memory>

MainWindow::MainWindow(std::shared_ptr<GameController> gc)
    : QMainWindow(nullptr), ui(new Ui::MainWindow), m_gc(gc) {
  ui->setupUi(this);
  SetupBoardArray();
}

void MainWindow::SetupBoardArray() {
#include "gameboard_init.hpp"
}

void MainWindow::render() {
  for (int row = 0; row < 6; row++) {
    for (int column = 0; column < 7; column++) {
      auto piece = m_gc->getPosition(row, column);
      if (!piece) {
        continue;
      }
      m_board_array[row][column]->setPixmap(piece->toPixmap());
    }
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_makePlayButton_clicked() {
  int column{0};
  bool ok{false};
  static bool red_turn{true};
  column = ui->playedColumn->currentText().toInt(&ok) - 1;
  assert(ok);

  std::shared_ptr<RenderableGamePiece> piece{nullptr};
  if (red_turn) {
    piece = std::make_shared<RenderableRedPiece>();
  } else {
    piece = std::make_shared<RenderableYellowPiece>();
  }
  m_gc->playPiece(piece, column);
  red_turn = !red_turn;

  // Now, we are going to take out the user's valuation formula, and use that to
  // calculate the best play!

  std::shared_ptr<RenderableGamePiece> auto_piece{nullptr};
  std::shared_ptr<GamePiece> auto_game_piece{nullptr};
  if (red_turn) {
    auto_piece = std::make_shared<RenderableRedPiece>();
    auto_game_piece = std::make_shared<RedGamePiece>();
  } else {
    auto_piece = std::make_shared<RenderableYellowPiece>();
    auto_game_piece = std::make_shared<YellowGamePiece>();
  }

  

  MoveGenerator mg{m_gc->getActiveGameboard(), auto_game_piece};
  auto autoplay = mg.Generate();

  std::cout << auto_piece->toString()
            << " is going to automatically play into column "
            << std::get<0>(autoplay) << "\n";

  m_gc->playPiece(auto_piece, std::get<0>(autoplay));
  render();

  red_turn = !red_turn;
}
