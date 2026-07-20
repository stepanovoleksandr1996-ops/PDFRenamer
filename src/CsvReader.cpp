//======================================================
// CsvReader.cpp
//
// Зчитування CSV у таблицю:
//
// ІПН -> Назва PDF
//
//======================================================

#include "CsvReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace
{
//------------------------------------------------------
// Прибирає пробіли на початку та в кінці рядка.
//------------------------------------------------------
std::string trim(const std::string& text)
{
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";

    const auto last = text.find_last_not_of(" \t\r\n");

    return text.substr(first, last - first + 1);
}
}

std::unordered_map<std::string, std::string>
readCsv(const std::string& csvFile)
{
    std::unordered_map<std::string, std::string> table;

    //--------------------------------------------------
    // Відкриваємо файл у бінарному режимі.
    // Це дозволяє коректно працювати з UTF-8.
    //--------------------------------------------------
    std::ifstream file(csvFile, std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "Не вдалося відкрити CSV\n";
        return table;
    }

    std::string line;

    //==================================================
    // Пропускаємо заголовок
    //==================================================
    std::getline(file, line);

    //--------------------------------------------------
    // Якщо файл містить UTF-8 BOM,
    // видаляємо його із першого рядка.
    //--------------------------------------------------
    if (line.size() >= 3 &&
        static_cast<unsigned char>(line[0]) == 0xEF &&
        static_cast<unsigned char>(line[1]) == 0xBB &&
        static_cast<unsigned char>(line[2]) == 0xBF)
    {
        line.erase(0, 3);
    }

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);

        std::string ipn;
        std::string name;

        std::getline(ss, ipn, ',');
        std::getline(ss, name);

        ipn = trim(ipn);
        name = trim(name);

        if (ipn.empty())
            continue;

        table[ipn] = name;
    }

    std::cout << "Завантажено записів: "
              << table.size()
              << "\n";

    //--------------------------------------------------
    // Для перевірки покажемо перші 5 записів
    //--------------------------------------------------
    int count = 0;

    std::cout << "\nПерші записи CSV:\n";

    for (const auto& item : table)
    {
        std::cout << item.first
                  << " -> "
                  << item.second
                  << '\n';

        if (++count == 5)
            break;
    }

    std::cout << '\n';

    return table;
}