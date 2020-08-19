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

    template<class T>
    inline void setGameObject(T& gameobject) {
      m_gameobject.reset(new ScriptableGameObject(gameobject));
      if (running) m_gameobject->start();
    }

    static Application* get();
  private:
    Application();
  private:
    bool running = false;
    std::unique_ptr<Console> m_console;
    std::unique_ptr<ScriptableGameObject> m_gameobject;
    Time m_time;

    static Application* s_instance;
  };
}

