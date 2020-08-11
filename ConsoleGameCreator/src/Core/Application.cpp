#include "cgcpch.h"
#include "Application.h"
#include "Events/MouseClickEvent.h"

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

      for (auto pevent : events) {
        Event& event = *pevent;
        Event::dispatch<MouseClickEvent>(event, [](MouseClickEvent& e)->bool {
          Console& console = Application::get()->console();
          console.setTitle(fmt::format(u"Mouse Clicked: button({5}), down({0}), up({1}), double({2}), row({3}), col({4})",
            e.buttonDown(), e.buttonUp(), e.doubleClick(), e.row(), e.column(), e.mouseButton()));
          return true;
        });
      }

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
