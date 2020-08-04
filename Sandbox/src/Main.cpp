#include <cgc.h>

int main() {
  cgc::Application* app = cgc::Application::get();
  app->run();
  delete app;
}
