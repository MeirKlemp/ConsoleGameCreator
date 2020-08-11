#pragma once
#include "Event.h"
#include "Core/Keys.h"

namespace cgc {
  class KeyEvent : public Event {
  public:
    KeyEvent(Keys key, bool keyDown,
      bool capsPressed, bool numlockPressed, bool scrollPressed,
      bool leftAltPressed, bool rightAltPressed,
      bool leftControlPressed, bool rightControlPressed,
      bool shiftPressed);

    Keys key() const;
    bool keyDown() const;
    bool keyUp() const;
    bool capslock() const;
    bool numlock() const;
    bool scrollLock() const;
    bool alt() const;
    bool leftAlt() const;
    bool rightAlt() const;
    bool control() const;
    bool leftControl() const;
    bool rightControl() const;
    bool shift() const;
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
