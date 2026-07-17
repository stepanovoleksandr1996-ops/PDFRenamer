#include "Utils.h"

#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

//======================================================
// Перевірити існування файлу.
//======================================================
bool fileExists(const std::string& path)
{
    return fs::exists(path);
}

//======================================================
// Видалити заборонені символи.
//
// Windows не дозволяє:
//
// \ / : * ? " < > |
//
// Тому замінюємо їх пробілом.
//======================================================
std::string sanitizeFileName(const std::string& name)
{
    std::string result = name;

    const std::string forbidden = "\\/:*?\"<>|";

    std::replace_if(
        result.begin(),
        result.end(),
        [&](char c)
        {
            return forbidden.find(c) != std::string::npos;
        },
        ' ');

    return result;
}

//======================================================
// Побудувати повний шлях
// до нового PDF.
//
// Наприклад:
//
// /home/alex/PDF/
// +
// Мальцев Віталій
//
// =>
//
// /home/alex/PDF/Мальцев Віталій.pdf
//======================================================
std::string makePdfName(const std::string& folder,
                        const std::string& personName)
{
    fs::path file = fs::path(folder) /
                    (sanitizeFileName(personName) + ".pdf");

    return file.string();
}