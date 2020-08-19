#include <cgc.h>

class SandBox : public cgc::GameObject {
public:
  void start() {
    console().setTitle("SandBox");

    directionX = rand() % 2 == 0 ? -1 : 1;
    directionY = rand() % 2 == 0 ? -1 : 1;
    row = 10;
    column = 50;

    border.setBorder(cgc::StyledChar('#', cgc::Style(cgc::Colors::red, cgc::Colors::green)));
    addGameObject(border);
  }
  void update(cgc::Frame& frame) {
    frame.write(row, column, print, style);

    if (time().time() - lastMove > 100) {
      if (row + directionY == 0 || row + directionY == border.rows() - 1) {
        directionY *= -1;
        style.foreground = cgc::Color(rand() % 256, rand() % 256, rand() % 256);
      }
      if (column + directionX == 0 || column + directionX == border.columns() - print.size()) {
        directionX *= -1;
        style.foreground = cgc::Color(rand() % 256, rand() % 256, rand() % 256);
      }

      row += directionY;
      column += directionX;
      lastMove = time().time();
    }
  }

  bool windowResized(cgc::WindowResizedEvent & e) {
    border.setSize(e.rows(), e.columns());
    console().setCursorVisible(false);
    return false;
  }
private:
  cgc::Border border;
  cgc::Style style;
  std::string print = "Sandbox Project";
  uint64_t lastMove = 0;
  size_t row = 1, column = 1;
  int directionX = 1;
  int directionY = 1;
};

int main() {
  srand(time(NULL));
  cgc::Application* app = cgc::Application::get();
  SandBox test;
  app->setGameObject(test);
  app->run();
  delete app;
}

