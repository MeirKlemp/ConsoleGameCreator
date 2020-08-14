#pragma once
#include "Style.h"
#include "Core/Debug.h"
#include "Core/Util/Encoding.h"
#include <fmt/format.h>

namespace cgc {
  class StyledChar {
  public:
    StyledChar(const std::string& utf8Char = " ", Style style = Style())
      : utf8(utf8Char), style(style) {
      CGC_ASSERT(iswprint(Encoding::utf8::firstUnicode(utf8)), "Created unprintable styled character.");
    }
    StyledChar(char ascii, Style style = Style())
      : style(style) {
      CGC_ASSERT(isprint(ascii), "Created unprintable styled character.");
      utf8 += ascii;
    }
    inline void print() const {
      fmt::print(style, "{}", *this);
    }
    bool operator==(const StyledChar& rhs) const {
      return utf8 == rhs.utf8 && style == rhs.style;
    }
    bool operator!=(const StyledChar& rhs) const {
      return !operator==(rhs);
    }
  public:
    std::string utf8;
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
    return format_to(ctx.out(), "{}", sch.utf8);
  }
};
