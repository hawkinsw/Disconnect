#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlabel.h"
#include <GameController.hpp>
#include <QMainWindow>
#include <memory>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(std::shared_ptr<GameController> controller);
  ~MainWindow();
  std::shared_ptr<QLabel> getChipAt(int row, int col) const {
    return m_board_array[row][col];
  }
  void render();

private slots:
  void on_makePlayButton_clicked();

private:
  Ui::MainWindow *ui;
  std::vector<std::vector<std::shared_ptr<QLabel>>> m_board_array =
      std::vector<std::vector<std::shared_ptr<QLabel>>>(
          6, std::vector<std::shared_ptr<QLabel>>(7));
  std::shared_ptr<GameController> m_gc{nullptr};
  void SetupBoardArray();
};
#endif // MAINWINDOW_H
