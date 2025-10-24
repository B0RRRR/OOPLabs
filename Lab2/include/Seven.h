#pragma once

#include <string>
#include "Array.h"

namespace seven {

class Seven {
 private:
  Array digits_;  // объект, а не указатель

 public:
  Seven();
  explicit Seven(unsigned int value);
  explicit Seven(const std::string& str);
  Seven(const Seven& other);
  Seven& operator=(Seven&& other) noexcept;
  ~Seven() noexcept = default;

  std::string toString() const;

  static Seven Add(const Seven& a, const Seven& b);
  static Seven Subtract(const Seven& a, const Seven& b);
  static bool Equals(const Seven& a, const Seven& b);
  static bool Less(const Seven& a, const Seven& b);
  static bool Greater(const Seven& a, const Seven& b);
};

}  // namespace seven
