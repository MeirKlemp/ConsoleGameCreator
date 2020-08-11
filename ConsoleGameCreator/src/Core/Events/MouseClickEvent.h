#pragma once
#include "Event.h"
#include "Core/MouseButtons.h"

namespace cgc {
  class MouseClickEvent : public Event {
  public:
    MouseClickEvent(MouseButtons mouseButton, bool down, bool doubleClick, uint32_t row, uint32_t column);

    bool buttonDown() const;
    bool buttonUp() const;
    bool doubleClick() const;
    MouseButtons mouseButton() const;
    uint32_t row() const;
    uint32_t column() const;
    std::pair<uint32_t, uint32_t> position() const;
  private:
    MouseButtons m_button;
    bool m_down;
    bool m_double;
    uint32_t m_row, m_column;
  };
}
