#include "cgcpch.h"
#include "KeyEvent.h"

namespace cgc {
  KeyEvent::KeyEvent(Keys key, bool keyDown, bool capsPressed, bool numlockPressed, bool scrollPressed, bool leftAltPressed, bool rightAltPressed, bool leftControlPressed, bool rightControlPressed, bool shiftPressed)
    : m_key(key), m_down(keyDown), m_caps(capsPressed),
      m_num(numlockPressed), m_scroll(scrollPressed),
      m_lalt(leftAltPressed), m_ralt(rightAltPressed),
      m_lctrl(leftControlPressed), m_rctrl(rightControlPressed),
      m_shift(shiftPressed) { }
  
  Keys KeyEvent::key() const {
    return m_key;
  }

  bool KeyEvent::keyDown() const {
    return m_down;
  }
  bool KeyEvent::keyUp() const {
    return !m_down;
  }

  bool KeyEvent::capslock() const {
    return m_caps;
  }
  bool KeyEvent::numlock() const {
    return m_num;
  }
  bool KeyEvent::scrollLock() const {
    return m_scroll;
  }

  bool KeyEvent::alt() const {
    return m_lalt || m_ralt;
  }
  bool KeyEvent::leftAlt() const {
    return m_lalt;
  }
  bool KeyEvent::rightAlt() const {
    return m_ralt;
  }

  bool KeyEvent::control() const {
    return m_lctrl || m_rctrl;
  }
  bool KeyEvent::leftControl() const {
    return m_lctrl;
  }
  bool KeyEvent::rightControl() const {
    return m_rctrl;
  }

  bool KeyEvent::shift() const {
    return m_shift;
  }
}