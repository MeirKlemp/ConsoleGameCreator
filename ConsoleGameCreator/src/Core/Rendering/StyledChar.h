#pragma once
#include "Style.h"
#include "Core/Debug.h"
#include "Core/Util/Types.h"
#include <fmt/format.h>

namespace cgc {
  class StyledChar {
  public:
#ifdef CGC_SUPPORT_UTF8
    StyledChar(const std::string& utf8Char = " ", Style style = Style())
      : m_char(utf8Char), m_style(style) {
      CGC_ASSERT(iswprint(Encoding::utf8::firstUnicode(utf8Char)), "Created unprintable styled character.");
    }
    StyledChar(char ascii, Style style = Style())
      : m_style(style) {
      CGC_ASSERT(isprint((uint8_t)ascii), "Created unprintable styled character.");
      m_char += ascii;
    }
#else
    StyledChar(char ascii = ' ', Style style = Style())
      : m_style(style), m_char(ascii) {
      CGC_ASSERT(isprint((uint8_t)ascii), "Created unprintable styled character.");
    }
#endif
    inline void print() const {
      fmt::print(m_style, "{}", *this);
    }
    bool operator==(const StyledChar& rhs) const {
      return m_char == rhs.m_char && m_style == rhs.m_style;
    }
    bool operator!=(const StyledChar& rhs) const {
      return !operator==(rhs);
    }
  public:
    CGC_CHAR m_char;
    Style m_style;
  };
}

// Making StyledChar formattable in fmt library.
template <>
struct fmt::formatter<cgc::StyledChar> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();

    // Check if reached the end of the range:
    if (it != end && *it != '}')
      throw format_error("invalid format");

    // Return an iterator past the end of the parsed range:
    return it;
  }
  template <typename FormatContext>
  auto format(const cgc::StyledChar& sch, FormatContext& ctx) {
    return format_to(ctx.out(), "{}", sch.m_char);
  }
};
