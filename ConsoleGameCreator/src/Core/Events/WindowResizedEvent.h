#pragma once
#include "cgcpch.h"
#include "Event.h"

namespace cgc {
  class WindowResizedEvent : public Event {
  public:
    WindowResizedEvent(size_t rows, size_t columns, size_t lastRows, size_t lastColumns)
      : m_rows(rows), m_columns(columns), m_lastRows(lastRows), m_lastColumns(lastColumns) {}

    inline std::pair<size_t, size_t> size() const {
      return std::make_pair(m_rows, m_columns);
    }
    inline size_t rows() const { return m_rows; }
    inline size_t columns() const { return m_columns; }

    inline std::pair<size_t, size_t> lastSize() const {
      return std::make_pair(m_lastRows, m_lastColumns);
    }
    inline size_t lastRows() const { return m_lastRows; }
    inline size_t lastColumns() const { return m_lastColumns; }

    inline std::pair<int64_t, int64_t> delta() const {
      return std::make_pair(m_rows - m_lastRows, m_columns - m_lastColumns);
    }

  private:
    size_t m_rows, m_columns;
    size_t m_lastRows, m_lastColumns;
  };
}
