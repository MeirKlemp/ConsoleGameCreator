#pragma once
#include "Event.h"
#include "Core/Debug.h"
#include "Core/Util/Types.h"

namespace cgc {
  class KeyTypedEvent : public Event {
  public:
#ifdef CGC_SUPPORT_UTF8
    KeyTypedEvent(const std::string& utf8Char)
      : m_char(utf8Char), m_ascii(false) {};
    KeyTypedEvent(char ascii) : m_ascii(true) {
      m_char += ascii;
    }
    inline char keyChar() const {
      CGC_ASSERT(isAscii(), "This character is not ascii.")
      return m_char[0];
    }
    inline const std::string& keyCharUtf8() const { return m_char; }
    inline bool isAscii() const { return m_ascii; }
  private:
    bool m_ascii;
#else
    KeyTypedEvent(char ascii)
      : m_char(ascii) {
    }
    inline char keyChar() const { return m_char; }
#endif
  private:
    CGC_CHAR m_char;
  };
}
