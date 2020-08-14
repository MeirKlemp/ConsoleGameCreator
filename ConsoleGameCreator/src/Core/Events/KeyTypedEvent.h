#pragma once
#include "Event.h"
#include "Core/Debug.h"

namespace cgc {
  class KeyTypedEvent : public Event {
  public:
    KeyTypedEvent(const std::string& utf8)
      : m_utf8(utf8), m_ascii(false) {};
    KeyTypedEvent(char ascii) : m_ascii(true) {
      m_utf8 += ascii;
    }
    inline char keyChar() const {
      CGC_ASSERT(isAscii(), "This character is not ascii.")
      return m_utf8[0];
    }
    inline const std::string& keyCharUtf8() const { return m_utf8; }
    inline bool isAscii() const { return m_ascii; }
    inline bool isUtf8() const { return !m_ascii; }
  private:
    std::string m_utf8;
    bool m_ascii;
  };
}
