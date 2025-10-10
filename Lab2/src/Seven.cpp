#include "../include/Seven.h"
#include <stdexcept>
#include <algorithm>

// Конструкторы 
Seven::Seven() : digits(1, 0) {}

Seven::Seven(unsigned int value) {
    if (value == 0) {
        digits = Array(1, 0);
        return;
    }

    Array temp;
    while (value > 0) {
        unsigned char digit = value % 7;
        temp.push_back(digit);
        value /= 7;
    }
    digits = std::move(temp);
}

Seven::Seven(const std::string& str) {
    if (str.empty())
        throw std::invalid_argument("Empty string is not allowed");

    Array temp(str); // конструктор Array(str) перевернет порядок цифр
    digits = std::move(temp);
}

Seven::Seven(const Seven& other) : digits(other.digits) {}

// Перемещающее присваивание
Seven& Seven::operator=(Seven&& other) noexcept {
    if (this != &other)
        digits = std::move(other.digits);
    return *this;
}

// Преобразование в строку
std::string Seven::toString() const {
    return digits.toString();
}

// Сложение
Seven Seven::Add(const Seven& a, const Seven& b) {
    Array result;
    unsigned char carry = 0;
    size_t maxSize = std::max(a.digits.getSize(), b.digits.getSize());

    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char da = (i < a.digits.getSize()) ? a.digits.get(i) : 0;
        unsigned char db = (i < b.digits.getSize()) ? b.digits.get(i) : 0;

        unsigned char sum = da + db + carry;
        result.push_back(sum % 7);
        carry = sum / 7;
    }

    Seven res;
    res.digits = std::move(result);
    return res;
}

// Вычитание
Seven Seven::Subtract(const Seven& a, const Seven& b) {
    if (Less(a, b))
        throw std::invalid_argument("Negative result not allowed");

    Array result;
    int borrow = 0;

    for (size_t i = 0; i < a.digits.getSize(); ++i) {
        int da = a.digits.get(i) - borrow;
        int db = (i < b.digits.getSize()) ? b.digits.get(i) : 0;

        if (da < db) {
            da += 7;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(static_cast<unsigned char>(da - db));
    }

    // Удаление ведущих нулей
    while (result.getSize() > 1 && result.get(result.getSize() - 1) == 0)
        result.pop_back();

    Seven res;
    res.digits = std::move(result);
    return res;
}

// Сравнения
bool Seven::Equals(const Seven& a, const Seven& b) {
    if (a.digits.getSize() != b.digits.getSize())
        return false;

    for (size_t i = 0; i < a.digits.getSize(); ++i)
        if (a.digits.get(i) != b.digits.get(i))
            return false;

    return true;
}

bool Seven::Less(const Seven& a, const Seven& b) {
    if (a.digits.getSize() != b.digits.getSize())
        return a.digits.getSize() < b.digits.getSize();

    for (int i = a.digits.getSize() - 1; i >= 0; --i) {
        if (a.digits.get(i) != b.digits.get(i))
            return a.digits.get(i) < b.digits.get(i);
    }
    return false;
}

bool Seven::Greater(const Seven& a, const Seven& b) {
    return !Less(a, b) && !Equals(a, b);
}
