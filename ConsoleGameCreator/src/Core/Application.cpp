#include "cgcpch.h"
#include "Application.h"
#include "Input.h"

namespace cgc {
  Application::Application() {
    m_console = Console::platformConsole();
  }

  Application::~Application() {
  }

  void Application::run() {
    running = true;
    m_time.start();
    m_gameobject->start();

    while (running) {
      m_time.update();

      Frame frame = m_console->newFrame();
      std::vector<std::shared_ptr<Event>> events = m_console->events();

      Input::onEvents(events);

      m_gameobject->onEvents(events);
      m_gameobject->update(frame);

      m_console->draw(frame);
    }

    m_gameobject->end();
  }
  void Application::close() {
    running = false;
  }

  Console& Application::console() {
    return *m_console;
  }

  const Time& Application::time() const {
    return m_time;
  }

  Application* Application::s_instance = new Application();

  Application* Application::get() {
    return s_instance;
  }
}
