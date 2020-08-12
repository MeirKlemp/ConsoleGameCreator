#pragma once
#include <fmt/color.h>
#include "Colors.h"

namespace cgc {
 struct Color {
    Color(uint8_t r, uint8_t g, uint8_t b)
      : r(r), g(g), b(b) {}
    Color(uint32_t hex)
      : r((hex >> 12) & 0xFF), g((hex >> 8) & 0xFF), b((hex >> 0) & 0xFF) {}
    Color(Colors color)
      : r((uint32_t(color) >> 12) & 0xFF),
        g((uint32_t(color) >> 8) & 0xFF),
        b((uint32_t(color) >> 0) & 0xFF) {}
    Color(fmt::rgb rgb)
      : r(rgb.r), g(rgb.g), b(rgb.b) {}
    operator fmt::rgb() const {
      return fmt::rgb(r, g, b);
    }
    bool operator==(const Color& rhs) const {
      return r == rhs.r && g == rhs.g && b == rhs.b;
    }
    bool operator!=(const Color& rhs) const {
      return !operator==(rhs);
    }
    uint8_t r, g, b;
  };

  // Copied from fmt/color.h
  enum class Emphasis {
    bold = 1,
    italic = 1 << 1,
    underline = 1 << 2,
    strikethrough = 1 << 3
  };
 
  struct Style {
    Style(Color fg = Colors::white, Color bg = Colors::black, Emphasis emphasis = Emphasis())
      : foreground(fg), background(bg), emphasis(emphasis) {}
    operator fmt::text_style() const {
      return fg(fmt::rgb(foreground)) | bg(fmt::rgb(background)) | fmt::emphasis(emphasis);
    }
    bool operator==(const Style& rhs) const {
      return foreground == rhs.foreground
        && background == rhs.background
        && emphasis == rhs.emphasis;
    }
    bool operator!=(const Style& rhs) const {
      return !operator==(rhs);
    }
    Color foreground;
    Color background;
    Emphasis emphasis;
  };

}
