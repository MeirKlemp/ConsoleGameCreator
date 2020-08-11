#pragma once
#include "Style.h"
#include "Core/Debug.h"
#include <fmt/format.h>

namespace cgc {
  class StyledChar {
  public:
    StyledChar(char16_t ch = ' ', Style style = Style())
      : ch(ch), style(style) {
      CGC_ASSERT(std::iswprint(ch), "created unprintable styled character.");
    }
    inline void print() const {
      fmt::print(style, "{}", *this);
    }
    bool operator==(const StyledChar& rhs) const {
      return ch == rhs.ch && style == rhs.style;
    }
    bool operator!=(const StyledChar& rhs) const {
      return !operator==(rhs);
    }
  public:
    char16_t ch;
    Style style;
  };
}

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
    // transforming char16_t into c string
    if (sch.ch & 0xFF00) {
      char* cptr = (char*)&sch.ch;
      char c[3]{ cptr[1], cptr[0] , '\0' };
      return format_to(ctx.out(), c);
    }

    return format_to(ctx.out(), "{}", (char)sch.ch);
  }
};
