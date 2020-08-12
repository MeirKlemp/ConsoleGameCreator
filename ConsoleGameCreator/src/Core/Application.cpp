#include "cgcpch.h"
#include "Application.h"
#include "Events/MouseClickedEvent.h"
#include "Events/MouseMovedEvent.h"
#include "Events/MouseScrolledEvent.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyTypedEvent.h"

namespace cgc {
  Application::Application() {
    m_console = Console::platformConsole();
  }

  Application::~Application() {
  }

  void Application::run() {
    running = true;
    m_time.start();

    while (running) {
      m_time.update();

      Frame frame = m_console->newFrame();
      std::vector<std::shared_ptr<Event>> events = m_console->events();

      for (auto pevent : events) {
        Event& event = *pevent;
        Event::dispatch<MouseClickedEvent>(event, [](MouseClickedEvent& e)->bool {
          Console& console = Application::get()->console();
          console.setTitle(fmt::format(u"Mouse Clicked: button({5}), down({0}), up({1}), double({2}), row({3}), col({4})",
            e.buttonDown(), e.buttonUp(), e.doubleClick(), e.row(), e.column(), e.mouseButton()));
          return true;
        });
        Event::dispatch<MouseMovedEvent>(event, [](MouseMovedEvent& e)->bool {
          Console& console = Application::get()->console();
          console.setTitle(fmt::format(u"Mouse Moved: row({0}), col({1})", e.row(), e.column()));
          return true;
        });
        Event::dispatch<MouseScrolledEvent>(event, [](MouseScrolledEvent& e)->bool {
          Console& console = Application::get()->console();
          console.setTitle(fmt::format(u"Mouse Scrolled: vertical({}), horizontal({})", e.vertical(), e.horizontal()));
          return true;
        });
        Event::dispatch<KeyPressedEvent>(event, [](KeyPressedEvent& e)->bool {
          Console& console = Application::get()->console();
          console.setTitle(
            fmt::format(u"Key Pressed: keyCode({0}), keyDown({1}), keyUp({2}), capslock({3}), "
                        u"numlock({4}), scrollLock({5}), alt({6}), leftAlt({7}), rightAlt({8}), "
                        u"control({9}), leftControl({10}), rightControl({11}), shift({12})",
            e.key(), e.keyDown(), e.keyUp(), e.capslock(), e.numlock(), e.scrollLock(), e.alt(),
            e.leftAlt(), e.rightAlt(), e.control(), e.leftControl(), e.rightControl(), e.shift()));
          return true;
        });
        Event::dispatch<KeyTypedEvent>(event, [](KeyTypedEvent& e)->bool {
          Console& console = Application::get()->console();
          console.setTitle(fmt::format(u"Key Typed: KeyChar({})", e.keyChar()));
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

  const Time& Application::time() const {
    return m_time;
  }

  Application* Application::s_instance = new Application();

  Application* Application::get() {
    return s_instance;
  }
}
