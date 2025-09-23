#include <iostream>

#include "fear_checker.h"

int main() {
    std::string day;
    int number;

    std::cout << "Day: ";
    std::cin >> day;

    std::cout << "Number: ";

    if (isAfraid(day, number))
        std::cout << "Afraid\n";
    else
        std::cout << "Not afraid\n";

    return 0;
}