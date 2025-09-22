#include <iostream>
#include "fear_checker.h"

int main() {
    std::string day;
    int number;

    std::cout << "Day: ";
    std::cin >> day;

    std::cout << "Number: ";

    if (!(std::cin >> number)) {
    std::cout << "Not number!\n";
    return 1;
    }

    if (isAfraid(day, number))
        std::cout << "I'm afraid of this number.\n";
    else
        std::cout << "I'm not afraid of that number.\n";

    return 0;
}