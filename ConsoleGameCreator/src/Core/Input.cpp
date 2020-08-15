#include "cgcpch.h"
#include "Input.h"

#define NOT_CLICKED 0
#define NOT_PRESSED 0
#define DOWN 1
#define UP 2

namespace cgc {
  void Input::onEvents(std::vector<std::shared_ptr<Event>>& events) {
    s_vertical = 0;
    s_horizontal = 0;

    for (Keys key; !s_keysReleased.empty(); s_keysReleased.pop()) {
      key = s_keysReleased.front();
      s_keysMap[key] = NOT_PRESSED;
    }
    for (MouseButtons button; !s_mouseReleased.empty(); s_mouseReleased.pop()) {
      button = s_mouseReleased.front();
      s_mouseClickedMap[button] = NOT_CLICKED;
    }
    for (char keyChar; !s_notTyped.empty(); s_notTyped.pop()) {
      keyChar = s_notTyped.front();
      s_typedMap[keyChar] = false;
    }
#ifdef CGC_SUPPORT_UTF8
    for (std::string utf8; !s_notTypedUtf8.empty(); s_notTypedUtf8.pop()) {
      utf8 = s_notTypedUtf8.front();
      s_typedMapUtf8[utf8] = false;
    }
#endif

    for (auto pevent : events) {
      Event::dispatch<KeyPressedEvent>(*pevent, onKeyPressed);
      Event::dispatch<KeyTypedEvent>(*pevent, onKeyTyped);
      Event::dispatch<MouseClickedEvent>(*pevent, onMouseClicked);
      Event::dispatch<MouseMovedEvent>(*pevent, onMouseMoved);
      Event::dispatch<MouseScrolledEvent>(*pevent, onMouseScrolled);
    }
  }

  bool Input::keyPressed(Keys key) {
    return s_keysMap[key];
  }
  bool Input::keyDown(Keys key) {
    return s_keysMap[key] == DOWN;
  }
  bool Input::keyUp(Keys key) {
    return s_keysMap[key] == UP;
  }

  bool Input::keyTyped(char keyChar) {
    return s_typedMap[keyChar];
  }
#if CGC_SUPPORT_UTF8
  bool Input::keyTyped(const std::string& keyCharUtf8) {
    return s_typedMapUtf8[keyCharUtf8] || s_typedMap[keyCharUtf8[0]];
  }
#endif

  bool Input::mouseButtonClicked(MouseButtons button) {
    return s_mouseClickedMap[button];
  }
  bool Input::mouseButtonDown(MouseButtons button) {
    return s_mouseClickedMap[button] == DOWN;
  }
  bool Input::mouseButtonUp(MouseButtons button) {
    return s_mouseClickedMap[button] == UP;
  }
  bool Input::mouseButtonDoubleClick(MouseButtons button) {
    return s_mouseDoubleClickedMap[button];
  }

  std::pair<size_t, size_t> Input::mousePosition() {
    return std::make_pair(s_row, s_column);
  }
  size_t Input::mouseRow() {
    return s_row;
  }
  size_t Input::mouseColumn() {
    return s_column;
  }

  int Input::verticalScroll() {
    return s_vertical;
  }
  int Input::horizontalScroll() {
    return s_horizontal;
  }

  bool Input::onKeyPressed(KeyPressedEvent& e) {
    if (e.keyDown()) {
      s_keysMap[e.key()] = DOWN;
    }
    else {
      s_keysMap[e.key()] = UP;
      s_keysReleased.push(e.key());
    }
    return false;
  }
  bool Input::onKeyTyped(KeyTypedEvent& e) {
#ifdef CGC_SUPPORT_UTF8
    if (e.isAscii()) {
      s_typedMap[e.keyChar()] = true;
      s_notTyped.push(e.keyChar());
    }
    else {
      s_typedMapUtf8[e.keyCharUtf8()] = true;
      s_notTypedUtf8.push(e.keyCharUtf8());
    }
#else
    s_typedMap[e.keyChar()] = true;
    s_notTyped.push(e.keyChar());
#endif
    return false;
  }
  bool Input::onMouseClicked(MouseClickedEvent& e) {
    if (e.buttonDown()) {
      s_mouseClickedMap[e.mouseButton()] = DOWN;
    }
    else {
      s_mouseClickedMap[e.mouseButton()] = UP;
      s_mouseReleased.push(e.mouseButton());
    }

    if (e.doubleClick()) {
      s_mouseDoubleClickedMap[e.mouseButton()] = true;
    }
    else {
      s_mouseDoubleClickedMap[e.mouseButton()] = false;
    }
    return false;
  }
  bool Input::onMouseMoved(MouseMovedEvent& e) {
    s_row = e.row();
    s_column = e.column();
    return false;
  }
  bool Input::onMouseScrolled(MouseScrolledEvent& e) {
    s_vertical = e.vertical();
    s_horizontal = e.horizontal();
    return false;
  }

  std::queue<Keys> Input::s_keysReleased;
  std::queue<MouseButtons> Input::s_mouseReleased;
  std::queue<char> Input::s_notTyped;

  std::unordered_map<Keys, int8_t> Input::s_keysMap;
  std::unordered_map<MouseButtons, int8_t> Input::s_mouseClickedMap;
  std::unordered_map<MouseButtons, bool> Input::s_mouseDoubleClickedMap;
  std::unordered_map<char, bool> Input::s_typedMap;

  size_t Input::s_row = 0;
  size_t Input::s_column = 0;
  int Input::s_vertical = 0;
  int Input::s_horizontal = 0;

#ifdef CGC_SUPPORT_UTF8
  std::queue<std::string> Input::s_notTypedUtf8;
  std::unordered_map<std::string, bool> Input::s_typedMapUtf8;
#endif
}