#include "../include/Array.h"

#include <stdexcept>
#include <algorithm>
#include <utility>

namespace seven {

void Array::allocate(size_t n) {
  if (n == 0) {
    throw std::invalid_argument("Array size must be greater than 0");
  }
  data_ = new unsigned char[n];
  capacity_ = n;
}

void Array::copyFrom(const Array& other) {
  allocate(other.capacity_);
  size_ = other.size_;
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

Array::Array() : data_(nullptr), size_(0), capacity_(0) {}

Array::Array(size_t n, unsigned char t)
    : data_(nullptr), size_(n), capacity_(n) {
  allocate(n);
  for (size_t i = 0; i < n; ++i) {
    data_[i] = t;
  }
}

Array::Array(const std::initializer_list<unsigned char>& t)
    : data_(nullptr), size_(t.size()), capacity_(t.size()) {
  allocate(capacity_);
  size_t i = 0;
  for (auto val : t) {
    data_[i++] = val;
  }
}

Array::Array(const std::string& t) : data_(nullptr), size_(0), capacity_(0) {
  if (t.empty()) {
    throw std::invalid_argument("String cannot be empty");
  }

  size_ = t.size();
  capacity_ = t.size();
  allocate(capacity_);

  for (size_t i = 0; i < size_; ++i) {
    if (t[i] < '0' || t[i] > '6') {
      throw std::invalid_argument("Invalid digit for base-7 number");
    }
    data_[size_ - 1 - i] = static_cast<unsigned char>(t[i] - '0');
  }
}

Array::Array(const Array& other) : data_(nullptr), size_(0), capacity_(0) {
  copyFrom(other);
}

Array::Array(Array&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

Array::~Array() noexcept { delete[] data_; }

size_t Array::getSize() const noexcept { return size_; }

unsigned char Array::get(size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

void Array::set(size_t index, unsigned char value) {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  data_[index] = value;
}

void Array::push_back(unsigned char value) {
  if (size_ >= capacity_) {
    size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
    unsigned char* new_data = new unsigned char[new_cap];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }
  data_[size_++] = value;
}

void Array::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("Array is empty");
  }
  --size_;
}

std::string Array::toString() const {
  std::string s;
  s.reserve(size_);
  for (int i = static_cast<int>(size_) - 1; i >= 0; --i) {
    s += static_cast<char>('0' + data_[i]);
  }
  return s;
}

Array& Array::operator=(Array&& other) noexcept {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

}  // namespace seven
