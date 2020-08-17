#include <cgc.h>

class Test : public cgc::GameObject {
public:
  void start() {
  }
  void update(cgc::Frame& frame) {
  }
  void updateGui(cgc::Frame& frame) {
  }
  bool keyPressed(cgc::KeyPressedEvent& e) {
    return false;
  }
  bool keyTyped(cgc::KeyTypedEvent& e) {
    return false;
  }
  bool mouseClicked(cgc::MouseClickedEvent& e) {
    return false;
  }
  bool mouseMoved(cgc::MouseMovedEvent& e) {
    return false;
  }
  bool mouseScrolled(cgc::MouseScrolledEvent& e) {
    return false;
  }
  bool windowResized(cgc::WindowResizedEvent& e) {
    return false;
  }
  void end() {
  }
};

int main() {
  cgc::Application* app = cgc::Application::get();
  app->setGameObject<Test>();
  app->run();
  delete app;
}
