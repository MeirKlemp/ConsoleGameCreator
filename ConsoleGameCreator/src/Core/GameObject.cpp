#include "cgcpch.h"
#include "GameObject.h"
#include "Application.h"

#include "Core/Events/KeyPressedEvent.h"
#include "Core/Events/KeyTypedEvent.h"
#include "Core/Events/MouseClickedEvent.h"
#include "Core/Events/MouseMovedEvent.h"
#include "Core/Events/MouseScrolledEvent.h"
#include "Core/Events/WindowResizedEvent.h"

namespace cgc {
  Application& GameObject::application() {
    return *Application::get();
  }
  Console& GameObject::console() {
    return Application::get()->console();
  }
  const Time& GameObject::time() {
    return Application::get()->time();
  }

  void GameObject::destroy() {
    if (parent) {
      auto begin = parent->m_gameObjects.begin();
      auto end = parent->m_gameObjects.end();
      for (auto it = begin; it != end; ++it) {
        if (it->m_gameobject == this) {
          m_gameObjects.erase(it);
        }
      }

      begin = parent->m_guiObjects.begin();
      end = parent->m_guiObjects.end();
      for (auto it = begin; it != end; ++it) {
        if (it->m_gameobject == this) {
          m_guiObjects.erase(it);
        }
      }
    }
  }

  ScriptableGameObject& ScriptableGameObject::operator=(const ScriptableGameObject& rhs) {
    if (m_deleteGameObject) m_deleteGameObject();
    m_initGameObject = rhs.m_initGameObject;
    m_deleteGameObject = rhs.m_deleteGameObject;
    m_start = rhs.m_start;
    m_update = rhs.m_update;
    m_end = rhs.m_end;
    m_gameobject = nullptr;
    return *this;
  }

  ScriptableGameObject& ScriptableGameObject::operator=(ScriptableGameObject&& rhs) noexcept {
    m_initGameObject = rhs.m_initGameObject;
    m_deleteGameObject = rhs.m_deleteGameObject;
    m_start = rhs.m_start;
    m_update = rhs.m_update;
    m_end = rhs.m_end;
    m_gameobject = rhs.m_gameobject;
    return *this;
  }

  void ScriptableGameObject::update(Frame& frame) {
    CGC_ASSERT(m_gameobject, "GameObject didn't started")
      if (m_update) m_update(frame);

    auto begin = m_gameobject->m_gameObjects.begin();
    auto end = m_gameobject->m_gameObjects.end();
    for (auto it = begin; it != end; ++it) {
      it->update(frame);
    }

    begin = m_gameobject->m_guiObjects.begin();
    end = m_gameobject->m_guiObjects.end();
    for (auto it = begin; it != end; ++it) {
      it->update(frame);
    }

    if (m_updateGui) m_updateGui(frame);
  }
  void ScriptableGameObject::end() {
    CGC_ASSERT(m_gameobject, "GameObject didn't started")
    if (m_end) m_end();

    auto begin = m_gameobject->m_gameObjects.begin();
    auto end = m_gameobject->m_gameObjects.end();
    for (auto it = begin; it != end; ++it) {
      it->end();
    }

    begin = m_gameobject->m_guiObjects.begin();
    end = m_gameobject->m_guiObjects.end();
    for (auto it = begin; it != end; ++it) {
      it->end();
    }
  }
  void ScriptableGameObject::onEvents(std::vector<std::shared_ptr<Event>>& events) {
    CGC_ASSERT(m_gameobject, "GameObject didn't started")

    auto begin = events.begin();
    auto end = events.end();
    for (auto it = begin; it != end; ++it) {
      Event& event = *(*it);
      Event::dispatch<KeyPressedEvent>(event, m_keyPressed);
      Event::dispatch<KeyTypedEvent>(event, m_keyTyped);
      Event::dispatch<MouseClickedEvent>(event, m_mouseClicked);
      Event::dispatch<MouseMovedEvent>(event, m_mouseMoved);
      Event::dispatch<MouseScrolledEvent>(event, m_mouseScrolled);
      Event::dispatch<WindowResizedEvent>(event, m_windowResized);

      if (event.handled()) {
        events.erase(it);
      }
    }

    auto rbegin = m_gameobject->m_guiObjects.rbegin();
    auto rend = m_gameobject->m_guiObjects.rend();
    for (auto it = rbegin; it != rend; ++it) {
      it->onEvents(events);
    }

    rbegin = m_gameobject->m_gameObjects.rbegin();
    rend = m_gameobject->m_gameObjects.rend();
    for (auto it = rbegin; it != rend; ++it) {
      it->onEvents(events);
    }
  }
}
