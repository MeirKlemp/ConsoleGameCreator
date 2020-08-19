#pragma once
#include "Core/GameObject.h"
#include "Core/Util/Types.h"

namespace cgc {
  class Border : public GameObject {
  public:
    inline bool inBounds(size_t row, size_t column) const {
      return row >= m_row && row < m_rows + m_row &&
        column >= m_column && column < m_columns + m_column;
    }
    inline StyledChar border() const { return m_border; }
    inline StyledChar fill() const { return m_fill; }
    inline std::pair<size_t, size_t> location() const { return std::make_pair(m_row, m_column); }
    inline std::pair<size_t, size_t> size() const { return std::make_pair(m_rows, m_columns); }
    inline size_t row() const { return m_row; }
    inline size_t column() const { return m_column; }
    inline size_t rows() const { return m_rows; }
    inline size_t columns() const { return m_columns; }

    inline void setBorder(StyledChar chr) {
      m_border = chr;
    }
    inline void setFill(StyledChar chr) {
      m_fill = chr;
    }
    inline void setLocation(size_t row, size_t column) {
      m_row = row;
      m_column = column;
    }
    inline void setSize(size_t rows, size_t columns) {
      m_rows = rows;
      m_columns = columns;
    }
    inline void setRow(size_t row) { m_row = row; }
    inline void setColumn(size_t column) { m_column = column; }
    inline void setRows(size_t rows) { m_rows = rows; }
    inline void setColumns(size_t columns) { m_columns = columns; }

    void update(Frame& frame) {
      for (size_t r = 0; r < m_rows; r++) {
        if (m_row + r >= frame.rows()) continue;

        for (size_t c = 0; c < m_columns; c++) {
          if (m_column + c >= frame.columns()) continue;

          if (r == 0 || r == m_rows - 1 ||
            c == 0 || c == m_columns - 1) {
            frame.set(m_row + r, m_column + c, m_border);
          }
          else if (filling) {
            frame.set(m_row + r, m_column + c, m_fill);
          }
        }
      }
    }

  public:
    bool filling = false;
  private:
    StyledChar m_border = '#';
    StyledChar m_fill;
    size_t m_row = 0, m_column = 0;
    size_t m_rows = 0, m_columns = 0;
  };
}
