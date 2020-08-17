#pragma once
#include "Debug.h"

namespace cgc {
  class Application;
  class Console;
  class Time;
  class Frame;
  class Event;
  class ScriptableGameObject;

  class KeyPressedEvent;
  class KeyTypedEvent;
  class MouseClickedEvent;
  class MouseMovedEvent;
  class MouseScrolledEvent;
  class WindowResizedEvent;

  class GameObject {
  public:
    virtual ~GameObject() = default;
    Application& application();
    Console& console();
    const Time& time();

    void destroy();

    template<class T, class... Args>
    void addGameObject(Args&... args) {
      ScriptableGameObject go;
      go.bind<T>(args...);
      go.start();
      go.m_gameobject->parent = this;
      m_gameObjects.push_back(std::move(go));
    }

    template<class T, class... Args>
    void addGuiObject(Args&... args) {
      ScriptableGameObject gui;
      gui.bind<T>(args...);
      gui.start();
      gui.m_gameobject->parent = this;
      m_guiObjects.push_back(std::move(gui));
    }

  protected:
    GameObject() = default;

  protected:
    std::vector<ScriptableGameObject> m_gameObjects;
    std::vector<ScriptableGameObject> m_guiObjects;

  private:
    GameObject* parent = nullptr;

    friend class ScriptableGameObject;
  };

  class ScriptableGameObject {
  public:
    ScriptableGameObject() = default;
    ScriptableGameObject(const ScriptableGameObject& rhs)
      : m_initGameObject(rhs.m_initGameObject), m_deleteGameObject(rhs.m_deleteGameObject),
        m_start(rhs.m_start), m_update(rhs.m_update), m_end(rhs.m_end), m_gameobject(nullptr) {}
    ScriptableGameObject(ScriptableGameObject&& rhs) noexcept
      : ScriptableGameObject(rhs) {
      m_gameobject = rhs.m_gameobject;
      rhs.m_deleteGameObject = nullptr;
    }
    ~ScriptableGameObject() {
      if (m_deleteGameObject) m_deleteGameObject();
    }

    ScriptableGameObject& operator=(const ScriptableGameObject& rhs);
    ScriptableGameObject& operator=(ScriptableGameObject&& rhs) noexcept;

    template<class T, class... Args>
    void bind(Args&... args) {
      m_initGameObject = [this, &args...] { m_gameobject = new T(args...); };
      m_deleteGameObject = [this] { delete (T*)m_gameobject; };
      m_start = [this] { ((T*)m_gameobject)->start(); };
      m_update = [this](Frame& frame) { ((T*)m_gameobject)->update(frame); };
      m_updateGui = [this](Frame& frame) { ((T*)m_gameobject)->updateGui(frame); };
      m_end = [this] { ((T*)m_gameobject)->end(); };
      m_keyPressed = [this](KeyPressedEvent& e) { return ((T*)m_gameobject)->keyPressed(e); };
      m_keyTyped = [this](KeyTypedEvent& e) { return ((T*)m_gameobject)->keyTyped(e); };
      m_mouseClicked = [this](MouseClickedEvent& e) { return ((T*)m_gameobject)->mouseClicked(e); };
      m_mouseMoved = [this](MouseMovedEvent& e) { return ((T*)m_gameobject)->mouseMoved(e); };
      m_mouseScrolled = [this](MouseScrolledEvent& e) { return ((T*)m_gameobject)->mouseScrolled(e); };
      m_windowResized = [this](WindowResizedEvent& e) { return ((T*)m_gameobject)->windowResized(e); };
    }

    inline void start() {
      CGC_ASSERT(!m_gameobject, "GameObject already started")
      CGC_ASSERT(m_initGameObject, "Didn't bind a GameObject")

      if (!m_gameobject) m_initGameObject();
      if (m_start) m_start();
    }
    void update(Frame& frame);
    void end();
    void onEvents(std::vector<std::shared_ptr<Event>>& events);

  private:
    std::function<void()> m_initGameObject;
    std::function<void()> m_deleteGameObject;
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

    GameObject* m_gameobject = nullptr;

    friend class GameObject;
  };
}
