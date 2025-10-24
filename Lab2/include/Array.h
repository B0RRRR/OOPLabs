#pragma once

#include <cstddef>
#include <string>
#include <initializer_list>

namespace seven {

class Array {
 private:
  unsigned char* data_;
  size_t size_;
  size_t capacity_;

  void allocate(size_t n);
  void copyFrom(const Array& other);

 public:
  Array();
  Array(size_t n, unsigned char t = 0);
  Array(const std::initializer_list<unsigned char>& t);
  explicit Array(const std::string& t);
  Array(const Array& other);
  Array(Array&& other) noexcept;
  ~Array() noexcept;

  size_t getSize() const noexcept;
  unsigned char get(size_t index) const;
  void set(size_t index, unsigned char value);
  void push_back(unsigned char value);
  void pop_back();
  std::string toString() const;

  Array& operator=(const Array& other) = delete;
  Array& operator=(Array&& other) noexcept;
};

}  // namespace seven
