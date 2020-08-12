#pragma once
#include "Event.h"
#include "Core/MouseButtons.h"

namespace cgc {
  class MouseClickedEvent : public Event {
  public:
    MouseClickedEvent(MouseButtons mouseButton, bool down, bool doubleClick, size_t row, size_t column)
      : m_button(mouseButton), m_down(down), m_double(doubleClick), m_row(row), m_column(column) { }

    inline bool buttonDown() const { return m_down; }
    inline bool buttonUp() const { return !m_down; }
    inline bool doubleClick() const { return m_double; }
    inline MouseButtons mouseButton() const { return m_button; }
    inline size_t row() const { return m_row; }
    inline size_t column() const { return m_column; }
    inline std::pair<size_t, size_t> position() const
      { return std::make_pair(m_row, m_column); }
  private:
    MouseButtons m_button;
    bool m_down;
    bool m_double;
    size_t m_row, m_column;
  };
}
