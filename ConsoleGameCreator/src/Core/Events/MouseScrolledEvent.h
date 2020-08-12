#pragma once
#include "Event.h"

namespace cgc {
  class MouseScrolledEvent : public Event {
  public:
    MouseScrolledEvent(int vertical, int horizontal)
      : m_vertical(vertical), m_horizontal(horizontal) { }

    inline int vertical() const { return m_vertical; }
    inline int horizontal() const { return m_horizontal; }
  private:
    int m_vertical, m_horizontal;
  };
}
