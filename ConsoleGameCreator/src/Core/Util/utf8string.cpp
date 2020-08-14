#include "cgcpch.h"
#include "utf8string.h"
#include "Encoding.h"
#include "Core/Debug.h"

namespace cgc {
  utf8string::utf8string(const std::string& str)
    : m_data(Encoding::utf8::decode(str)) { }

  std::string utf8string::operator[](size_t index) const {
    CGC_ASSERT(index < length(), "Index is out of bounds.");

    return Encoding::utf8::encode(m_data[index]);
  }

  std::string utf8string::substr(size_t index) const {
    CGC_ASSERT(index < length(), "Index is out of bounds.");

    return Encoding::utf8::encode(m_data.substr(index));
  }

  std::string utf8string::substr(size_t index, size_t length) const {
    CGC_ASSERT(index < this->length(), "Index is out of bounds.");

    return Encoding::utf8::encode(m_data.substr(index, length));
  }

  utf8string::iterator::iterator(const utf8string& wrapper, size_t index)
    : m_wrapper(wrapper), m_index(index) { }
  utf8string::iterator utf8string::iterator::operator++(int) {
    iterator it = *this;
    m_index++;
    return it;
  }
  utf8string::iterator& utf8string::iterator::operator++() {
    m_index++;
    return *this;
  }
}