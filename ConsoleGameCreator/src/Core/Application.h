#pragma once

namespace cgc {
  class Application {
  public:
    static Application* get();

    virtual ~Application();
    void run();
  private:
    Application();
  private:
    static Application* instance;
  };
}

