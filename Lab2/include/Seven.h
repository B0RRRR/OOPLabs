#pragma once
#include "Array.h"
#include <string>

class Seven {
private:
    Array digits;

public:
    // --- Конструкторы ---
    Seven();
    explicit Seven(unsigned int value);
    explicit Seven(const std::string& str);
    Seven(const Seven& other);
    Seven& operator=(Seven&& other) noexcept; // перемещающее присваивание

    // --- Преобразование ---
    std::string toString() const;

    // --- Арифметика ---
    static Seven Add(const Seven& a, const Seven& b);
    static Seven Subtract(const Seven& a, const Seven& b);
    Seven AddAssign(const Seven& other) const;
    Seven SubtractAssign(const Seven& other) const;

    // --- Сравнение ---
    static bool Equals(const Seven& a, const Seven& b);
    static bool Less(const Seven& a, const Seven& b);
    static bool Greater(const Seven& a, const Seven& b);
};
