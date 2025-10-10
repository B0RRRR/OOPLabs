#pragma once
#include <cstddef>
#include <initializer_list>
#include <string>
#include <stdexcept>

class Array {
private:
    unsigned char* data;
    size_t size;
    size_t capacity;

    void allocate(size_t n);
    void copyFrom(const Array& other);

public:
    // --- Конструкторы ---
    Array();                                                    // пустой
    Array(const size_t& n, unsigned char t = 0);                // размер + значение
    Array(const std::initializer_list<unsigned char>& t);       // список инициализации
    Array(const std::string& t);                                // из строки
    Array(const Array& other);                                  // копирующий
    Array(Array&& other) noexcept;                              // перемещающий
    virtual ~Array() noexcept;                                  // деструктор

    // --- Методы доступа ---
    size_t getSize() const noexcept;
    unsigned char get(size_t index) const;
    void set(size_t index, unsigned char value);
    void push_back(unsigned char value);
    void pop_back();
    std::string toString() const;

    Array& operator=(const Array& other) = delete;              // коп. оператор запрещён
    Array& operator=(Array&& other) noexcept;                   // перемещающее присваивание
};
