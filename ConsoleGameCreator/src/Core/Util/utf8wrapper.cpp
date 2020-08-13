#include "cgcpch.h"
#include "utf8wrapper.h"
#include "Encoding.h"
#include "Core/Debug.h"

namespace cgc {
  utf8wrapper::utf8wrapper(const std::string& str)
    : m_data(Encoding::utf8::decode(str)), m_length(Encoding::utf8::length(str)) { }

  std::string utf8wrapper::operator[](size_t index) const {
    CGC_ASSERT(index < m_length, "Index is out of bounds.");

    return Encoding::utf8::encode(m_data[index]);
  }

  std::string utf8wrapper::substr(size_t index) const {
    CGC_ASSERT(index < m_length, "Index is out of bounds.");

    return Encoding::utf8::encode(m_data.substr(index));
  }

  std::string utf8wrapper::substr(size_t index, size_t length) const {
    CGC_ASSERT(index < m_length, "Index is out of bounds.");
    CGC_ASSERT(index + length <= m_length, "Length is out of bounds.");

    return Encoding::utf8::encode(m_data.substr(index, length));
  }

  utf8wrapper::iterator::iterator(const utf8wrapper& wrapper, size_t index)
    : m_wrapper(wrapper), m_index(index) { }
  utf8wrapper::iterator utf8wrapper::iterator::operator++(int) {
    iterator it = *this;
    m_index++;
    return it;
  }
  utf8wrapper::iterator& utf8wrapper::iterator::operator++() {
    m_index++;
    return *this;
  }
}