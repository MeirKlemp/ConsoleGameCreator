#pragma once
#include "Platform/Console.h"
#include "Time.h"

namespace cgc {
  class Application {
  public:
    virtual ~Application();

    void run();
    void close();

    Console& console();
    const Time& time() const;

    static Application* get();
  private:
    Application();
  private:
    bool running = false;
    std::unique_ptr<Console> m_console;
    Time m_time;

    static Application* s_instance;
  };
}

