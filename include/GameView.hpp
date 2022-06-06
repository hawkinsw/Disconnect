#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <memory>
#include <mainwindow.h>

class GameView {
  private:
    std::weak_ptr<MainWindow> m_window{};
  public:
    GameView(std::shared_ptr<MainWindow> window): m_window{std::weak_ptr<MainWindow>(window)} {}
    void render();
};

#endif