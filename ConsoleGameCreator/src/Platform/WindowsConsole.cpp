#include "cgcpch.h"

#if CGC_WINDOWS
#include "WindowsConsole.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/KeyTypedEvent.h"
#include "Core/Events/MouseClickEvent.h"

namespace cgc {
  WindowsConsole::WindowsConsole() {
    // Get the handles for input and output.
	m_hout = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hin = GetStdHandle(STD_INPUT_HANDLE);

    setCursorVisible(false);

    // Make console not selectable by user.
    SetConsoleMode(m_hin, ENABLE_EXTENDED_FLAGS);

    // Enable windows input and mouse input after enabled extended flags.
    SetConsoleMode(m_hin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
  }

  std::vector<std::shared_ptr<Event>> WindowsConsole::events() {
	DWORD eventsCount;
	GetNumberOfConsoleInputEvents(m_hin, &eventsCount);

    std::vector<std::shared_ptr<Event>> events;
	PINPUT_RECORD buffer = new INPUT_RECORD[eventsCount];
	ReadConsoleInput(m_hin, buffer, eventsCount, &eventsCount);

	for (unsigned int i = 0; i < eventsCount; i++) {
		switch (buffer[i].EventType) {
		case KEY_EVENT:
		{
          auto& keyEvent = buffer[i].Event.KeyEvent;
          // KeyEvent
          std::shared_ptr<Event> event = std::make_shared<KeyEvent>(
            (Keys)keyEvent.wVirtualKeyCode,
            keyEvent.bKeyDown,
            keyEvent.dwControlKeyState & CAPSLOCK_ON,
            keyEvent.dwControlKeyState & NUMLOCK_ON,
            keyEvent.dwControlKeyState & SCROLLLOCK_ON,
            keyEvent.dwControlKeyState & LEFT_ALT_PRESSED,
            keyEvent.dwControlKeyState & RIGHT_ALT_PRESSED,
            keyEvent.dwControlKeyState & LEFT_CTRL_PRESSED,
            keyEvent.dwControlKeyState & RIGHT_CTRL_PRESSED,
            keyEvent.dwControlKeyState & SHIFT_PRESSED);

          events.push_back(event);

          // KeyTypedEvent
          if (keyEvent.bKeyDown && std::iswprint(keyEvent.uChar.UnicodeChar)) {
            std::shared_ptr<Event> event = std::make_shared<KeyTypedEvent>(keyEvent.uChar.UnicodeChar);
            events.push_back(event);
          }
          break;
		}
		case MOUSE_EVENT:
        {
          auto& mouseEvent = buffer[i].Event.MouseEvent;
          if (mouseEvent.dwEventFlags & MOUSE_MOVED) {
            
          }
          else if (mouseEvent.dwEventFlags & MOUSE_WHEELED) {

          }
          else if (mouseEvent.dwEventFlags & MOUSE_HWHEELED) {

          }
          else { // Mouse pressed or released a button (including double click).
            std::shared_ptr<Event> event;

            // Finds the button state that have been changed;
            for (size_t i = 0; i < 5; i++) {
              uint8_t bit = 0b1 << i;
              if ((mouseEvent.dwButtonState & bit) != (m_lastMouseEvent.dwButtonState & bit)) {
                event = std::make_shared<MouseClickEvent>
                  (MouseButtons(i + 1), mouseEvent.dwButtonState & bit,
                    mouseEvent.dwEventFlags & DOUBLE_CLICK,
                    mouseEvent.dwMousePosition.Y, mouseEvent.dwMousePosition.X);
                break;
              }
            }

            events.push_back(event);
          }

          m_lastMouseEvent = mouseEvent;
          break;
        }
		case WINDOW_BUFFER_SIZE_EVENT: // unimplemented
		default:
			break;
		}
	}

	delete[] buffer;
	return events;
  }

  std::u16string WindowsConsole::getTitle() const {
	TCHAR ctitle[MAX_PATH];
	GetConsoleTitle(ctitle, MAX_PATH);
	std::wstring wtitle = ctitle;
	return std::u16string(wtitle.begin(), wtitle.end());
  }
  void WindowsConsole::setTitle(const std::u16string& title) {
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
