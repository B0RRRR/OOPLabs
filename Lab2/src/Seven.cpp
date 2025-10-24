#include "../include/Seven.h"
#include "../include/Array.h"

#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cstddef>

namespace seven {

Seven::Seven() : digits_(1, 0) {}

Seven::Seven(unsigned int value) {
  if (value == 0) {
    digits_ = Array(1, 0);
    return;
  }

  Array temp;
  while (value > 0) {
    unsigned char digit = value % 7;
    temp.push_back(digit);
    value /= 7;
  }
  digits_ = std::move(temp);
}

Seven::Seven(const std::string& str) {
  if (str.empty()) {
    throw std::invalid_argument("Empty string is not allowed");
  }

  Array temp(str);
  digits_ = std::move(temp);
}

Seven::Seven(const Seven& other) : digits_(other.digits_) {}

Seven& Seven::operator=(Seven&& other) noexcept {
  if (this != &other) {
    digits_ = std::move(other.digits_);
  }
  return *this;
}

std::string Seven::toString() const {
  return digits_.toString();
}

Seven Seven::Add(const Seven& a, const Seven& b) {
  Array result;
  unsigned char carry = 0;
  size_t maxSize = std::max(a.digits_.getSize(), b.digits_.getSize());

  for (size_t i = 0; i < maxSize || carry; ++i) {
    unsigned char da = (i < a.digits_.getSize()) ? a.digits_.get(i) : 0;
    unsigned char db = (i < b.digits_.getSize()) ? b.digits_.get(i) : 0;

    unsigned char sum = da + db + carry;
    result.push_back(sum % 7);
    carry = sum / 7;
  }

  Seven res;
  res.digits_ = std::move(result);
  return res;
}

Seven Seven::Subtract(const Seven& a, const Seven& b) {
  if (Less(a, b)) {
    throw std::invalid_argument("Negative result not allowed");
  }

  Array result;
  int borrow = 0;

  for (size_t i = 0; i < a.digits_.getSize(); ++i) {
    int da = a.digits_.get(i) - borrow;
    int db = (i < b.digits_.getSize()) ? b.digits_.get(i) : 0;

    if (da < db) {
      da += 7;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result.push_back(static_cast<unsigned char>(da - db));
  }

  while (result.getSize() > 1 && result.get(result.getSize() - 1) == 0) {
    result.pop_back();
  }

  Seven res;
  res.digits_ = std::move(result);
  return res;
}

bool Seven::Equals(const Seven& a, const Seven& b) {
  if (a.digits_.getSize() != b.digits_.getSize()) {
    return false;
  }

  for (size_t i = 0; i < a.digits_.getSize(); ++i) {
    if (a.digits_.get(i) != b.digits_.get(i)) {
      return false;
    }
  }

  return true;
}

bool Seven::Less(const Seven& a, const Seven& b) {
  if (a.digits_.getSize() != b.digits_.getSize()) {
    return a.digits_.getSize() < b.digits_.getSize();
  }

  for (int i = static_cast<int>(a.digits_.getSize()) - 1; i >= 0; --i) {
    if (a.digits_.get(i) != b.digits_.get(i)) {
      return a.digits_.get(i) < b.digits_.get(i);
    }
  }
  return false;
}

bool Seven::Greater(const Seven& a, const Seven& b) {
  return !Less(a, b) && !Equals(a, b);
}

}  // namespace seven
