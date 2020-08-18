#pragma once
#include "Platform/Console.h"
#include "Time.h"
#include "GameObject.h"

namespace cgc {
  class Application {
  public:
    virtual ~Application();

    void run();
    void close();

    Console& console();
    const Time& time() const;

    template<class T, class... Args>
    inline void setGameObject(Args&... args) {
      m_gameobject.bind<T>(args...);
      if (running) m_gameobject.start();
    }

    static Application* get();
  private:
    Application();
  private:
    bool running = false;
    std::unique_ptr<Console> m_console;
    ScriptableGameObject m_gameobject;
    Time m_time;

    static Application* s_instance;
  };
}

