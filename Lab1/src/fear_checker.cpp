#include <unordered_map>
#include <string>
#include <stdexcept>

#include "fear_checker.h"

std::string toLower(const std::string& str) {
    static const std::unordered_map<std::string, std::string> upperToLower = {
        {"А", "а"}, {"Б", "б"}, {"В", "в"}, {"Г", "г"}, {"Д", "д"}, {"Е", "е"}, {"Ё", "ё"}, {"Ж", "ж"},
        {"З", "з"}, {"И", "и"}, {"Й", "й"}, {"К", "к"}, {"Л", "л"}, {"М", "м"}, {"Н", "н"}, {"О", "о"},
        {"П", "п"}, {"Р", "р"}, {"С", "с"}, {"Т", "т"}, {"У", "у"}, {"Ф", "ф"}, {"Х", "х"}, {"Ц", "ц"},
        {"Ч", "ч"}, {"Ш", "ш"}, {"Щ", "щ"}, {"Ъ", "ъ"}, {"Ы", "ы"}, {"Ь", "ь"}, {"Э", "э"}, {"Ю", "ю"}, {"Я", "я"}
    };

    std::string result;
    result.reserve(str.size());

    for (size_t i = 0; i < str.size(); ++i) {
        bool found = false;
        for (const auto& [upper, lower] : upperToLower) {
            if (i + upper.size() <= str.size() &&
                str.substr(i, upper.size()) == upper) {
                result += lower;
                i += upper.size() - 1;
                found = true;
                break;
            }
        }
        if (!found) {
            result += str[i];
        }
    }

    return result;
}

bool isValidDay(const std::string& day) {
    return
        day == "понедельник" ||
        day == "вторник" ||
        day == "среда" ||
        day == "четверг" ||
        day == "пятница" ||
        day == "суббота" ||
        day == "воскресенье";
}

bool isAfraid(const std::string& day, int number) {
    std::string lowerDay = toLower(day);

    if (!isValidDay(lowerDay)) {
        throw std::invalid_argument("Incorrect day" + day);
    }

    if (isValidDay(lowerDay)) {
        if (lowerDay == "понедельник") return number == 12;
        if (lowerDay == "вторник") return number > 95;
        if (lowerDay == "среда") return number == 34;
        if (lowerDay == "четверг") return number == 0;
        if (lowerDay == "пятница") return number % 2 == 0;
        if (lowerDay == "суббота") return number == 56;
        if (lowerDay == "воскресенье") return number == 666 || number == -666;
    }

    return false; 
}