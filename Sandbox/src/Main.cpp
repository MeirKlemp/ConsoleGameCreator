#include <cgc.h>

class Test : public cgc::GameObject {
public:
  void update(cgc::Frame& frame) {
    frame.write(0, 0, "It is working!!!");
  }
};

int main() {
  cgc::Application* app = cgc::Application::get();
  app->setGameObject<Test>();
  app->run();
  delete app;
}

