#pragma once
#include "Platform/Console.h"

namespace cgc {
  class Application {
  public:
    virtual ~Application();

    void run();
    void end();

    const Console& console() const;

    static Application* get();
  private:
    Application();
  private:
    bool running = false;
    std::unique_ptr<Console> m_console;

    static Application* s_instance;
  };
}

