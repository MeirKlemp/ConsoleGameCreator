#pragma once
#include "cgcpch.h"

namespace cgc {
  class Time {
  public:
    Time();
    virtual ~Time() = default;

    void start();
    void update();
    uint64_t time() const;
    uint64_t deltaTimeMS() const;
    float deltaTimeS() const;

    static void sleep(uint64_t ms);
  private:
    uint64_t m_start;
    uint64_t m_lastFrame;
    uint64_t m_deltaMS;
  };
}

