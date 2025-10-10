#include "../include/Array.h"

// Выделение памяти
void Array::allocate(size_t n) {
    if (n == 0)
        throw std::invalid_argument("Array size must be greater than 0");
    data = new unsigned char[n];
    capacity = n;
}

// Копирование
void Array::copyFrom(const Array& other) {
    allocate(other.capacity);
    size = other.size;
    for (size_t i = 0; i < size; ++i)
        data[i] = other.data[i];
}

// Конструкторы
Array::Array() : data(nullptr), size(0), capacity(0) {}

Array::Array(const size_t& n, unsigned char t) : data(nullptr), size(n), capacity(n) {
    allocate(n);
    for (size_t i = 0; i < n; ++i)
        data[i] = t;
}

Array::Array(const std::initializer_list<unsigned char>& t)
    : data(nullptr), size(t.size()), capacity(t.size()) {
    allocate(capacity);
    size_t i = 0;
    for (auto val : t)
        data[i++] = val;
}

Array::Array(const std::string& t) : data(nullptr) {
    if (t.empty())
        throw std::invalid_argument("String cannot be empty");

    size = t.size();
    capacity = t.size();
    allocate(capacity);

    for (size_t i = 0; i < size; ++i) {
        if (t[i] < '0' || t[i] > '6')
            throw std::invalid_argument("Invalid digit for base-7 number");
        data[size - 1 - i] = static_cast<unsigned char>(t[i] - '0');
    }
}

Array::Array(const Array& other) : data(nullptr), size(0), capacity(0) {
    copyFrom(other);
}

Array::Array(Array&& other) noexcept
    : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Деструктор
Array::~Array() noexcept {
    delete[] data;
}

// Количество элементов
size_t Array::getSize() const noexcept { return size; }

// Поиск по индексу
unsigned char Array::get(size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

// Добавление по индексу
void Array::set(size_t index, unsigned char value) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    data[index] = value;
}

// Вставка в конец
void Array::push_back(unsigned char value) {
    if (size >= capacity) {
        size_t newCap = capacity == 0 ? 1 : capacity * 2;
        unsigned char* newData = new unsigned char[newCap];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }
    data[size++] = value;
}

// Удаление с конца
void Array::pop_back() {
    if (size == 0)
        throw std::out_of_range("Array is empty");
    size--;
}

// Перевод в строку
std::string Array::toString() const {
    std::string s;
    for (int i = size - 1; i >= 0; --i)
        s += ('0' + data[i]);
    return s;
}

// Перемещающее присваивание
Array& Array::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}
