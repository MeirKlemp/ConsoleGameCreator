#pragma once
#include "Event.h"
#include "Core/Keys.h"

namespace cgc {
  class KeyPressedEvent : public Event {
  public:
    KeyPressedEvent(Keys key, bool keyDown,
      bool capsPressed, bool numlockPressed, bool scrollLockPressed,
      bool leftAltPressed, bool rightAltPressed,
      bool leftControlPressed, bool rightControlPressed,
      bool shiftPressed)
      : m_key(key), m_down(keyDown), m_caps(capsPressed),
      m_num(numlockPressed), m_scroll(scrollLockPressed),
      m_lalt(leftAltPressed), m_ralt(rightAltPressed),
      m_lctrl(leftControlPressed), m_rctrl(rightControlPressed),
      m_shift(shiftPressed) { }

    inline Keys key() const { return m_key; }
    inline bool keyDown() const { return m_down; }
    inline bool keyUp() const { return !m_down; }
    inline bool capslock() const { return m_caps; }
    inline bool numlock() const { return m_num; }
    inline bool scrollLock() const { return m_scroll; }
    inline bool alt() const { return m_lalt || m_ralt; }
    inline bool leftAlt() const { return m_lalt; }
    inline bool rightAlt() const { return m_ralt; }
    inline bool control() const { return m_lctrl || m_rctrl; }
    inline bool leftControl() const { return m_lctrl; }
    inline bool rightControl() const { return m_rctrl; }
    inline bool shift() const { return m_shift; }
  private:
    Keys m_key;
    bool m_down;
    bool m_caps;
    bool m_num;
    bool m_scroll;
    bool m_lalt, m_ralt;
    bool m_lctrl, m_rctrl;
    bool m_shift;
  };
}
