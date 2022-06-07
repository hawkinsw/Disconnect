#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <GameController.hpp>
#include <memory>

MainWindow::MainWindow(std::shared_ptr<GameController> gc)
    : QMainWindow(nullptr), ui(new Ui::MainWindow), m_gc(gc) {
  ui->setupUi(this);
  SetupBoardArray();
}

void MainWindow::SetupBoardArray(){
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

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_makePlayButton_clicked() {
    int column{0};
    bool ok{false};
    static bool red_turn{true};
    column = ui->playedColumn->currentText().toInt(&ok) - 1;
    assert(ok);

    std::shared_ptr<GamePiece> piece{nullptr};
    if (red_turn) {
        piece = std::make_shared<RedPiece>();
    } else {
        piece = std::make_shared<YellowPiece>();
    }
    m_gc->playPiece(piece, column);
    red_turn = !red_turn;

    render();
}
