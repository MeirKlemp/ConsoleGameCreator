#include "cgcpch.h"
#include "Time.h"
#include "Debug.h"

namespace cgc {
  Time::Time()
    : m_start(0), m_lastFrame(0), m_deltaMS(0){ }

  void Time::start() {
    using namespace std::chrono;
    auto duration = system_clock::now().time_since_epoch();
    m_start = duration_cast<milliseconds>(duration).count();
  }
  void Time::update() {
    auto _now = time();
    m_deltaMS = _now - m_lastFrame;
    m_lastFrame = _now;
  }

  uint64_t Time::time() const {
    CGC_ASSERT(m_start != 0, "Time didn't start yet.")

    using namespace std::chrono;
    auto duration = system_clock::now().time_since_epoch();
    auto now = duration_cast<milliseconds>(duration).count();
    return now - m_start;
  }
  uint64_t Time::deltaTimeMS() const {
    return m_deltaMS;
  }
  float Time::deltaTimeS() const {
    return m_deltaMS / 1000.0f;
  }

  void Time::sleep(uint64_t ms) {
    using namespace std::this_thread;
    using namespace std::chrono;
    sleep_for(milliseconds(ms));
  }
}
