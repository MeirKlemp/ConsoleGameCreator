#pragma once
#include "Core/Rendering/StyledChar.h"
#include "Core/Debug.h"

#include <fmt/format.h>

namespace cgc {
  class Frame {
  public:
    Frame(size_t rows = 0, size_t columns = 0, const StyledChar& defaultChar = ' ');
    Frame(const Frame& rhs);
    Frame(Frame&& rhs) noexcept;
    virtual ~Frame();

    size_t rows() const;
    size_t columns() const;

    std::pair<size_t, size_t> size() const;
    void setSize(size_t rows, size_t columns, const StyledChar& defaultChar = ' ');

    Frame& operator=(const Frame& rhs);
    Frame& operator=(Frame&& rhs) noexcept;

    StyledChar get(size_t row, size_t column) const;
    void set(size_t row, size_t column, const StyledChar& val);

    size_t write(size_t row, size_t column, const std::string& str, Style style = Style());

    typedef std::vector<std::pair<std::string, Style>> StyledStrings;
    size_t write(size_t row, size_t column, const StyledStrings& strings);

    template <class... Args>
    size_t writef(size_t row, size_t column, const std::string& str, Style style, Args&&... args) {
      CGC_ASSERT(row < m_rows, "row is out of bounds.");
      CGC_ASSERT(column < m_columns, "column is out of bounds.");

      std::string formatted = fmt::format(str, args...);
      return write(row, column, formatted, style);
    }
  private:
    size_t strToBuffer(size_t row, size_t column, const std::string& str, Style style);
    void setBuffer(const StyledChar& defaultChar);
    void setBuffer(StyledChar** buffer);
    void setBuffer(const Frame& frame, const StyledChar& defaultChar);
    void deleteBuffer();
  public:
    bool wrapping = false;
  private:
    size_t m_rows, m_columns;
    StyledChar** m_buffer;
  };
}
