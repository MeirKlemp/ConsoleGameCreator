#include "cgcpch.h"
#include "Console.h"
#include "WindowsConsole.h"

namespace cgc {
  Frame Console::newFrame() const {
    auto [rows, columns] = getSize();
    return Frame(rows, columns);
  }

  void Console::draw(const Frame& newFrame) {
    if (m_frame.size() != newFrame.size()) {
      auto [rows, columns] = newFrame.size();
      m_frame.setSize(rows, columns);
    }

    for (size_t r = 0; r < m_frame.rows(); r++) {
      for (size_t c = 0; c < m_frame.columns(); c++) {
        if (m_frame.get(r, c) != newFrame.get(r, c)) {
          m_frame.set(r, c, newFrame.get(r, c));
          drawChar(r, c, newFrame.get(r, c));
        }
      }
    }
  }

  void Console::clear() {
    auto [rows, columns] = getSize();

    for (size_t r = 0; r < rows; r++) {
      for (size_t c = 0; c < columns; c++) {
        m_frame.set(r, c, ' ');
        drawChar(r, c, ' ');
      }
    }
  }

  void Console::drawChar(size_t row, size_t column, const StyledChar& schar) {
    setCursorPosition(row, column);
    schar.print();
  }

  std::unique_ptr<Console> Console::platformConsole() {
#ifdef CGC_WINDOWS
    return std::make_unique<WindowsConsole>();
#else
#error "This platform is not supported yet."
#endif
  }
}
