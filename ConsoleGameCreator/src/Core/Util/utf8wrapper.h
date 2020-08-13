#pragma once
#include "cgcpch.h"
#include "Encoding.h"

namespace cgc {
  class utf8wrapper {
  public:
    utf8wrapper(const std::string& str);

    std::string operator[](size_t index) const;
    std::string substr(size_t index) const;
    std::string substr(size_t index, size_t length) const;
    inline size_t length() const { return m_length; }

    class iterator {
    public:
      iterator(const utf8wrapper& wrapper, size_t index = 0);

      inline std::string operator*() const { return m_wrapper[m_index]; }
      iterator operator++(int);
      iterator& operator++();
      inline bool operator==(const iterator& it) const { return m_index == it.m_index; }
      inline bool operator!=(const iterator& it) const { return m_index != it.m_index; }
    private:
      size_t m_index;
      const utf8wrapper& m_wrapper;
    };

    inline iterator begin() const { return iterator(*this); }
    inline iterator end() const { return iterator(*this, m_length); }

  private:
    size_t m_length;
    std::u32string m_data;
  };
}
