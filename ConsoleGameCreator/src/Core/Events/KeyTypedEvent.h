#pragma once
#include "Event.h"

namespace cgc {
  class KeyTypedEvent : public Event {
  public:
    KeyTypedEvent(char16_t ch) : m_ch(ch) {};
    char16_t keyChar() const { return m_ch; }
  private:
    char16_t m_ch;
  };
}
