#pragma once
#include "Core/Rendering/Frame.h"
#include "Core/Events/Event.h"

namespace cgc {
  class Console {
  public:
    virtual ~Console() = default;

    virtual Frame newFrame() const;
    virtual void draw(const Frame& newFrame);

    virtual std::vector <std::shared_ptr<Event>> events() = 0;
    virtual std::string getTitle() const = 0;
    virtual void setTitle(const std::string& title) = 0;
    virtual std::pair<size_t, size_t> getSize() const = 0;
    virtual void setSize(size_t rows, size_t columns) = 0;
    virtual std::pair<size_t, size_t> getCursorPosition() const = 0;
    virtual void setCursorPosition(size_t row, size_t column) = 0;
    virtual void setCursorVisible(bool visible) = 0;

    static std::unique_ptr<Console> platformConsole();
  private:
    virtual void drawChar(size_t row, size_t column, const StyledChar& schar);
  private:
    Frame m_frame;
  };
}
