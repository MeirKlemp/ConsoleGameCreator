#include "cgcpch.h"
#include "Application.h"

namespace cgc {
  Application* Application::instance = new Application();

  Application* Application::get() {
    return instance;
  }

  Application::Application() {
#ifdef CGC_WINDOWS
#else
#error "Working only for windows at this point."
#endif
  }

  Application::~Application() {

  }

  void Application::run() {
    while (true);
  }
}
