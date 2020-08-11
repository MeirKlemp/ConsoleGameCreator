#include "cgcpch.h"
#include "MouseClickEvent.h"

namespace cgc {
  MouseClickEvent::MouseClickEvent(MouseButtons mouseButton, bool down, bool doubleClick, uint32_t row, uint32_t column)
    : m_button(mouseButton), m_down(down), m_double(doubleClick), m_row(row), m_column(column) { }

  bool MouseClickEvent::buttonDown() const {
    return m_down;
  }
  bool MouseClickEvent::buttonUp() const {
    return !m_down;
  }

  bool MouseClickEvent::doubleClick() const {
      return m_double;
  }

  MouseButtons MouseClickEvent::mouseButton() const {
    return m_button;
  }

  uint32_t MouseClickEvent::row() const {
    return m_row;
  }
  uint32_t MouseClickEvent::column() const {
    return m_column;
  }
  std::pair<uint32_t, uint32_t> MouseClickEvent::position() const {
    return std::make_pair(m_row, m_column);
  }
}