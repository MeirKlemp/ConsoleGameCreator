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

      Style style(Colors::red, Colors::green_yellow, Emphasis::underline);
      frame.writef(0, 0, u"time(ms): {}", style, time.time());
      frame.writef(1, 0, u"fps: {:.2f}", style, 1 / time.deltaTimeS());
      frame.writef(2, 0, u"dt(ms): {}", style, time.deltaTimeMS());

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
