#pragma once

// This header only library is designed to do only two things:
// printfmt("My data: %, other data: %", a, b);
// std::string s = stringfmt("My data: %, other data: %", a, b);
// As a C printf next step

#include <array>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &data) {
  out << "Vec[";

  for (size_t i = 0; i < data.size(); i++)
    out << (i > 0 ? ", " : "") << data[i];

  out << "]";
  return out;
}

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &out, const std::array<T, N> &data) {
  out << "Array[";

  for (size_t i = 0; i < N; i++) out << (i > 0 ? ", " : "") << data[i];

  out << "]";
  return out;
}

namespace util {
inline void _string_fmt_all(std::string_view format,
                            std::stringstream &stream) {
  stream << format;
}

template <typename A, typename... B>
void _string_fmt_all(std::string_view format, std::stringstream &stream,
                     const A &arg, const B &...other) {
  if (format.at(0) == '%') {
    if (format.length() >= 2 && format.at(1) == '%') {
      stream << "%";
      if (format.length() > 2)
        _string_fmt_all(format.substr(2), stream, arg, other...);
    } else {
      stream << arg;
      if (format.length() > 1)
        _string_fmt_all(format.substr(1), stream, other...);
    }
  } else {
    size_t end = 0;
    while (format.at(end) != '%')  // .
      end++;

    stream << format.substr(0, end);

    if (format.length() > end)
      _string_fmt_all(format.substr(end), stream, arg, other...);
  }
}

template <typename... T>
std::string stringfmt(const std::string &format, const T &...args) {
  std::stringstream ss;
  _string_fmt_all(format, ss, args...);
  return ss.str();
}

template <typename... T>
void printfmt(const std::string &format, const T &...args) {
  std::cout << stringfmt(format, args...);
}

template <typename... T>
void printlnfmt(const std::string &format, const T &...args) {
  std::cout << stringfmt(format, args...) << std::endl;
}

template <typename T>
void call_destructor(T &object) {
  object.~T();
}

template <typename IterSrc, typename IterDest>
void move_l(IterSrc begin, IterSrc end, IterDest dest) {
  for (; begin != end; begin++) {
    (*dest) = std::move(*begin);
    dest++;
  }
}

template <typename IterSrc, typename IterDest>
void move_r(IterSrc begin, IterSrc end, IterDest dest_end) {
  if (begin == end) return;

  do {
    end--;
    dest_end--;
    (*dest_end) = std::move(*end);
  } while (begin != end);
}

}  // namespace util
