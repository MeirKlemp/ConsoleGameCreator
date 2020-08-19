#pragma once
#include "Debug.h"
#include "Util/Types.h"

#include "Platform/Console.h"
#include "Time.h"
#include "Rendering/Frame.h"

#include "Core/Events/KeyPressedEvent.h"
#include "Core/Events/KeyTypedEvent.h"
#include "Core/Events/MouseClickedEvent.h"
#include "Core/Events/MouseMovedEvent.h"
#include "Core/Events/MouseScrolledEvent.h"
#include "Core/Events/WindowResizedEvent.h"

namespace cgc {
  class Application;
  class ScriptableGameObject;

  class GameObject {
  public:
    virtual ~GameObject() = default;
    Application& application();
    Console& console();
    const Time& time();

    template<class T>
    void addGameObject(T& gameobject) {
      gameobject.parent = this;
      m_gameObjects.push_back(std::make_unique<ScriptableGameObject>(gameobject));
      m_gameObjects[m_gameObjects.size() - 1]->start();
    }

    template<class T>
    void addGuiObject(T& gameobject) {
      gameobject.parent = this;
      m_guiObjects.push_back(std::make_unique<ScriptableGameObject>(gameobject));
      m_guiObjects[m_guiObjects.size() - 1]->start();
    }

  protected:
    GameObject() = default;

  protected:
    std::vector<std::unique_ptr<ScriptableGameObject>> m_gameObjects;
    std::vector<std::unique_ptr<ScriptableGameObject>> m_guiObjects;

  private:
    GameObject* parent = nullptr;

    friend class ScriptableGameObject;
  };

  class ScriptableGameObject {
  public:
    template<class T>
    ScriptableGameObject(T& gameobject) : m_gameobject((GameObject&)gameobject) {
      if constexpr (has_start<T>::value) {
        m_start = [this] { ((T&)m_gameobject).start(); };
      }
      if constexpr (has_update<T, void, Frame&>::value) {
        m_update = [this](Frame& frame) { ((T&)m_gameobject).update(frame); };
      }
      if constexpr (has_updateGui<T, void, Frame&>::value) {
        m_updateGui = [this](Frame& frame) { ((T&)m_gameobject).updateGui(frame); };
      }
      if constexpr (has_end<T>::value) {
        m_end = [this] { ((T&)m_gameobject).end(); };
      }
      if constexpr (has_keyPressed<T, void, KeyPressedEvent&>::value) {
        m_keyPressed = [this](KeyPressedEvent& e) { return ((T&)m_gameobject).keyPressed(e); };
      }
      if constexpr (has_keyTyped<T, void, KeyTypedEvent&>::value) {
        m_keyTyped = [this](KeyTypedEvent& e) { return ((T&)m_gameobject).keyTyped(e); };
      }
      if constexpr (has_mouseClicked<T, void, MouseClickedEvent&>::value) {
        m_mouseClicked = [this](MouseClickedEvent& e) { return ((T&)m_gameobject).mouseClicked(e); };
      }
      if constexpr (has_mouseMoved<T, void, MouseMovedEvent&>::value) {
        m_mouseMoved = [this](MouseMovedEvent& e) { return ((T&)m_gameobject).mouseMoved(e); };
      }
      if constexpr (has_mouseScrolled<T, void, MouseScrolledEvent&>::value) {
        m_mouseScrolled = [this](MouseScrolledEvent& e) { return ((T&)m_gameobject).mouseScrolled(e); };
      }
      if constexpr (has_windowResized<T, void, WindowResizedEvent&>::value) {
        m_windowResized = [this](WindowResizedEvent& e) { return ((T&)m_gameobject).windowResized(e); };
      }
    }

    ScriptableGameObject(const ScriptableGameObject& rhs)
      : ScriptableGameObject(rhs.m_gameobject) {}

    inline void start() {
      if (m_start) m_start();
    }
    void update(Frame& frame);
    void end();
    void onEvents(std::vector<std::shared_ptr<Event>>& events);

  private:
    std::function<void()> m_start;
    std::function<void(Frame&)> m_update;
    std::function<void(Frame&)> m_updateGui;
    std::function<void()> m_end;
    std::function<bool(KeyPressedEvent&)> m_keyPressed;
    std::function<bool(KeyTypedEvent&)> m_keyTyped;
    std::function<bool(MouseClickedEvent&)> m_mouseClicked;
    std::function<bool(MouseMovedEvent&)> m_mouseMoved;
    std::function<bool(MouseScrolledEvent&)> m_mouseScrolled;
    std::function<bool(WindowResizedEvent&)> m_windowResized;

    GameObject& m_gameobject;

    friend class GameObject;

  private:
    CGC_FUNCTION_CHECK(start, void)
    CGC_FUNCTION_CHECK(update, void)
    CGC_FUNCTION_CHECK(updateGui, void)
    CGC_FUNCTION_CHECK(end, void)
    CGC_FUNCTION_CHECK(keyPressed, bool)
    CGC_FUNCTION_CHECK(keyTyped, bool)
    CGC_FUNCTION_CHECK(mouseClicked, bool)
    CGC_FUNCTION_CHECK(mouseMoved, bool)
    CGC_FUNCTION_CHECK(mouseScrolled, bool)
    CGC_FUNCTION_CHECK(windowResized, bool)
  };
}
