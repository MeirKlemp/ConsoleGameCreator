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
    time.start();

    while (running) {
      time.update();

      Frame frame = m_console->newFrame();
      std::vector<std::shared_ptr<Event>> events = m_console->events();

      m_console->draw(frame);
    }
  }
  void Application::close() {
    running = false;
  }

  Console& Application::console() {
    return *m_console;
  }

  Application* Application::s_instance = new Application();

  Application* Application::get() {
    return s_instance;
  }
}
