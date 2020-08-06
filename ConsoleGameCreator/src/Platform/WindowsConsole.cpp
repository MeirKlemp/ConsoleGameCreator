#include "cgcpch.h"

#if CGC_WINDOWS
#include "WindowsConsole.h"
#include <Windows.h>

namespace cgc {
  WindowsConsole::WindowsConsole() {
    // Get the handles for input and output.
	m_hout = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hin = GetStdHandle(STD_INPUT_HANDLE);

    setCursorVisible(false);

    // Make console not selectable by user.
    DWORD prev_mode;
    GetConsoleMode(m_hin, &prev_mode); 
    SetConsoleMode(m_hin, ENABLE_EXTENDED_FLAGS | 
        (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
  }

  std::string WindowsConsole::getTitle() const {
	TCHAR ctitle[MAX_PATH];
	GetConsoleTitle(ctitle, MAX_PATH);
	std::wstring wtitle = ctitle;
	return std::string(wtitle.begin(), wtitle.end());
  }
  void WindowsConsole::setTitle(const std::string& title) {
	std::wstring wtitle(title.begin(), title.end());
	SetConsoleTitle(wtitle.c_str());
  }

  std::pair<size_t, size_t> WindowsConsole::getSize() const {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(m_hout, &info);

    auto [left, top, right, bottom] = info.srWindow;
    size_t rows = (size_t)bottom - top;
    size_t columns = (size_t)right - left;

    return std::make_pair(rows, columns);
  }
  void WindowsConsole::setSize(size_t rows, size_t columns) {
    // TODO: Fix resizing window and buffer
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(m_hout, &info);

    info.srWindow.Bottom = info.srWindow.Top + rows;
    info.srWindow.Right = info.srWindow.Left + columns;
    info.dwSize = { (SHORT)columns, (SHORT)rows };

    SetConsoleWindowInfo(m_hout, TRUE, &info.srWindow);
    SetConsoleScreenBufferSize(m_hout, info.dwSize);
  }

  std::pair<size_t, size_t> WindowsConsole::getCursorPosition() const {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(m_hout, &info);
    auto [column, row] = info.dwCursorPosition;
    return std::make_pair(row, column);
  }
  void WindowsConsole::setCursorPosition(size_t row, size_t column) {
	COORD pos = { (SHORT)column, (SHORT)row };
	SetConsoleCursorPosition(m_hout, pos);
  }

  void WindowsConsole::setCursorVisible(bool visible) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(m_hout, &cursorInfo);
    if (cursorInfo.bVisible == visible) return;
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(m_hout, &cursorInfo);
  }
}
#endif
