#pragma once
#include "cgcpch.h"
#include "Encoding.h"

namespace cgc {
  class utf8string {
  public:
    utf8string(const std::string& str);

    std::string operator[](size_t index) const;
    std::string substr(size_t index) const;
    std::string substr(size_t index, size_t length) const;
    inline size_t length() const { return m_data.length(); }

    class iterator {
    public:
      iterator(const utf8string& wrapper, size_t index = 0);

      inline std::string operator*() const { return m_wrapper[m_index]; }
      iterator operator++(int);
      iterator& operator++();
      inline bool operator==(const iterator& it) const { return m_index == it.m_index; }
      inline bool operator!=(const iterator& it) const { return m_index != it.m_index; }
    private:
      size_t m_index;
      const utf8string& m_wrapper;
    };

    inline iterator begin() const { return iterator(*this); }
    inline iterator end() const { return iterator(*this, length()); }

  private:
    std::u32string m_data;
  };
}
