#include "cgcpch.h"
#include "Encoding.h"
#include "Core/Debug.h"

#include <utf8.h>
#include <utf16.h>

namespace cgc::Encoding {
  std::string utf8::encode(char32_t unicode) {
    std::string result;
    ufal::unilib::utf8::append(result, unicode);
    return result;
  }
  std::string utf8::encode(const std::u32string& unicode) {
    std::string result;
    ufal::unilib::utf8::encode(unicode, result);
    return result;
  }
  char32_t utf8::decodeChar(char ascii) {
    char str[2] = { ascii, 0 };
    const char* temp = str;
    return ufal::unilib::utf8::decode(temp);
  }
  char32_t utf8::decodeChar(const std::string& utf8) {
    const char* str = utf8.c_str();
    return ufal::unilib::utf8::decode(str);
  }
  std::u32string utf8::decode(const std::string& utf8) {
    std::u32string unicode;
    ufal::unilib::utf8::decode(utf8, unicode);
    return unicode;
  }
  char32_t utf8::firstUnicode(const std::string& utf8) {
    return ufal::unilib::utf8::first(utf8);
  }
  std::string utf8::first(const std::string& utf8) {
    return encode(firstUnicode(utf8));
  }
  size_t utf8::length(const std::string& utf8) {
    return decode(utf8).length();
  }

  std::u16string utf16::encode(char32_t unicode) {
    std::u16string result;
    ufal::unilib::utf16::append(result, unicode);
    return result;
  }
  std::u16string utf16::encode(const std::u32string& unicode) {
    std::u16string result;
    ufal::unilib::utf16::encode(unicode, result);
    return result;
  }
  char32_t utf16::decodeChar(char16_t utf16) {
    char16_t str[2] = { utf16, 0 };
    const char16_t* temp = str;
    return ufal::unilib::utf16::decode(temp);
  }
  char32_t utf16::decodeChar(const std::u16string& utf16) {
    const char16_t* str = utf16.c_str();
    return ufal::unilib::utf16::decode(str);
  }
  std::u32string utf16::decode(const std::u16string& utf16) {
    std::u32string unicode;
    ufal::unilib::utf16::decode(utf16, unicode);
    return unicode;
  }
  char32_t utf16::firstUnicode(const std::u16string& utf16) {
    return ufal::unilib::utf16::first(utf16);
  }
  std::u16string utf16::first(const std::u16string& utf16) {
    return encode(firstUnicode(utf16));
  }

  size_t utf16::length(const std::u16string& utf16) {
    return decode(utf16).length();
  }

  std::string u16ToU8(const std::u16string& utf16) {
    return utf8::encode(utf16::decode(utf16));
  }
  std::string u16ToU8(char16_t utf16) {
    return utf8::encode(utf16::decodeChar(utf16));
  }
  std::u16string u8ToU16(const std::string& utf8) {
    return utf16::encode(utf8::decode(utf8));
  }
  std::u16string u8ToU16(char utf8) {
    return utf16::encode(utf16::decodeChar(utf8));
  }
}