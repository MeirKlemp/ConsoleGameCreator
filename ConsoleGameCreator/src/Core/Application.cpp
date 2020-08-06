#include "cgcpch.h"
#include "Application.h"

namespace cgc {
  Application::Application() {
    m_console = Console::platformConsole();
  }

  Application::~Application() {
  }

  void Application::run() {
    running = true;
    while (running) {
      Frame frame = m_console->newFrame();

      Style style(Colors::azure, Colors::green_yellow, Emphasis::underline);
      frame.write(0, 0, u"Hello, world", style);

      m_console->draw(frame);
    }
  }
  void Application::end() {
    running = false;
  }

  const Console& Application::console() const {
    return *m_console;
  }

  Application* Application::s_instance = new Application();

  Application* Application::get() {
    return s_instance;
  }
}
