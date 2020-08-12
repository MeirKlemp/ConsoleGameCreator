#pragma once
#include "Event.h"

namespace cgc {
  class MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(size_t row, size_t column)
      : m_row(row), m_column(column) {}

    inline size_t row() const { return m_row; }
    inline size_t column() const { return m_column; }
    inline std::pair<size_t, size_t> position() const
      { return std::make_pair(m_row, m_column); }
  private:
    size_t m_row, m_column;
  };
}
