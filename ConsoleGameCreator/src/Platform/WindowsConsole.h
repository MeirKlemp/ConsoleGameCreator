#pragma once

#if CGC_WINDOWS
#include "Console.h"

namespace cgc {
  class WindowsConsole : public Console {
  public:
    WindowsConsole();

    virtual std::vector<std::shared_ptr<Event>> events() const override;
    virtual std::string getTitle() const override;
    virtual void setTitle(const std::string& title) override;
    virtual std::pair<size_t, size_t> getSize() const override;
    virtual void setSize(size_t rows, size_t columns) override;
    virtual std::pair<size_t, size_t> getCursorPosition() const override;
    virtual void setCursorPosition(size_t row, size_t column) override;
    virtual void setCursorVisible(bool visible) override;

  private:
  private:
    void* m_hout, *m_hin;
  };
}
#endif
