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
    for (char16_t keyChar; !s_notTyped.empty(); s_notTyped.pop()) {
      keyChar = s_notTyped.front();
      s_typedMap[keyChar] = false;
    }
    for (MouseButtons button; !s_mouseReleased.empty(); s_mouseReleased.pop()) {
      button = s_mouseReleased.front();
      s_mouseClickedMap[button] = NOT_CLICKED;
    }

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

  bool Input::keyTyped(char16_t keyChar) {
    return s_typedMap[keyChar];
  }

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
    s_typedMap[e.keyChar()] = true;
    s_notTyped.push(e.keyChar());
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
  std::queue<char16_t> Input::s_notTyped;
  std::queue<MouseButtons> Input::s_mouseReleased;

  std::unordered_map<Keys, int8_t> Input::s_keysMap;
  std::unordered_map<char16_t, bool> Input::s_typedMap;
  std::unordered_map<MouseButtons, int8_t> Input::s_mouseClickedMap;
  std::unordered_map<MouseButtons, bool> Input::s_mouseDoubleClickedMap;

  size_t Input::s_row = 0;
  size_t Input::s_column = 0;
  int Input::s_vertical = 0;
  int Input::s_horizontal = 0;
}