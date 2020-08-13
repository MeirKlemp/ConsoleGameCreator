#pragma once

namespace cgc::Encoding {
  namespace utf8 {
    std::string encode(char32_t unicode);
    std::string encode(const std::u32string& unicode);
    char32_t decodeChar(const std::string& utf8);
    std::u32string decode(const std::string& utf8);
    char32_t firstUnicode(const std::string& utf8);
    std::string first(const std::string& utf8);
    size_t length(const std::string& utf8);
  }

  namespace utf16 {
    std::u16string encode(char32_t unicode);
    std::u16string encode(const std::u32string& unicode);
    char32_t decodeChar(const std::u16string& utf16);
    std::u32string decode(const std::u16string& utf16);
    char32_t firstUnicode(const std::u16string& utf16);
    std::u16string first(const std::u16string& utf16);
    size_t length(const std::u16string& utf16);
  }

  std::string u16ToU8(const std::u16string& utf16);
  std::u16string u8ToU16(const std::string& utf8);
}
