#pragma once
#include "cgcpch.h"

namespace cgc {
  class Event {
  public:
    virtual ~Event() = default;
    bool handled() const { return m_handled; }

    template<class Event_t>
    static void dispatch(Event& event, std::function<bool(Event_t&)> callback) {
      Event_t* e = dynamic_cast<Event_t*>(&event);
      if (e) {
        e->m_handled = callback(*e);
      }
    }
  private:
    bool m_handled = false;
  };
}
