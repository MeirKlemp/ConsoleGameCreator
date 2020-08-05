#include "cgcpch.h"
#include "Application.h"

namespace cgc {
  Application* Application::s_instance = new Application();

  Application* Application::get() {
    return s_instance;
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
