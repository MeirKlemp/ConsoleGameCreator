#include "cgcpch.h"
#include "Console.h"

namespace cgc {
  Frame Console::newFrame() const {
    auto [rows, columns] = getSize();
    return Frame(rows, columns);
  }

  void Console::draw(const Frame& newFrame) {
    if (m_frame.size() != newFrame.size()) {
      auto [rows, columns] = newFrame.size();
      m_frame = Frame(rows, columns);
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

  void Console::drawChar(size_t row, size_t column, StyledChar schar) {
    setCursorPosition(row, column);
    schar.print();
  }

  std::unique_ptr<Console> Console::platformConsole() {
#ifdef CGC_WINDOWS
#else
#error "This platform is not supported yet."
#endif
  }
}
