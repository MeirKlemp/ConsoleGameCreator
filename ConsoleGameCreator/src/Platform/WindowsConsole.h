#pragma once

#if CGC_WINDOWS
#include "Console.h"

#include <Windows.h>

namespace cgc {
  class WindowsConsole : public Console {
  public:
    WindowsConsole();

    virtual std::vector<std::shared_ptr<Event>> events() override;
    virtual std::string getTitle() const override;
    virtual void setTitle(const std::string& title) override;
    virtual std::pair<size_t, size_t> getSize() const override;
    virtual void setSize(size_t rows, size_t columns) override;
    virtual std::pair<size_t, size_t> getCursorPosition() const override;
    virtual void setCursorPosition(size_t row, size_t column) override;
    virtual void setCursorVisible(bool visible) override;
    virtual bool isCursorVisible() override;

  private:
    void keyboardEvents(const KEY_EVENT_RECORD& keyEvent, std::vector<std::shared_ptr<Event>>& events);
    void mouseEvents(const MOUSE_EVENT_RECORD& mouseEvent, std::vector<std::shared_ptr<Event>>& events);
    void windowResizedEvent(std::vector<std::shared_ptr<Event>>& events);

  private:
    HANDLE m_hout, m_hin;
    MOUSE_EVENT_RECORD m_lastMouseEvent;

    size_t m_lastRows, m_lastColumns;
  };
}
#endif
