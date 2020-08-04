#pragma once
#include <cgcpch.h>
#include <Core/Debug.h>
#include <fmt/format.h>

namespace cgc {
  template <size_t t_rows, size_t t_columns>
  class Frame {
  public:
    Frame(char16_t defaultChar = ' ') {
      for (size_t r = 0; r < rows(); r++) {
        for (size_t c = 0; c < columns(); c++) {
          buffer[r][c] = defaultChar;
        }
      }
    }

    constexpr size_t rows() {
      return t_rows;
    }
    constexpr size_t columns() {
      return t_columns;
    }
    constexpr size_t length() {
      return t_rows * t_columns;
    }

    const char16_t* operator[](size_t row) const {
      CGC_ASSERT(row < t_rows, "row is out of bounds.");
      return buffer[row];
    }
    char16_t* operator[](size_t row) {
      CGC_ASSERT(row < t_rows, "row is out of bounds.");
      return buffer[row];
    }

    template <class... Args>
    void writef(size_t row, size_t column, const std::u16string& str, Args&& ...args) {
      CGC_ASSERT(row < t_rows, "row is out of bounds.");
      CGC_ASSERT(column < t_columns, "column is out of bounds.");

      std::u16string formatted = fmt::format(str, args...);
      write(row, column, formatted);
    }
    
    void write(size_t row, size_t column, const std::u16string& str) {
      CGC_ASSERT(row < t_rows, "row is out of bounds.");
      CGC_ASSERT(column < t_columns, "column is out of bounds.");

      size_t maxColLen = t_columns - column;
      size_t maxLen = length() - row * t_columns + column;
      std::u16string towrite = str.substr(0, wrapping ? maxLen : maxColLen);
      memcpy(buffer[row] + column, towrite.c_str(), towrite.length() * sizeof(char16_t));
    }
  public:
    bool wrapping = false;
  private:
    char16_t buffer[t_rows][t_columns];
  };
}

