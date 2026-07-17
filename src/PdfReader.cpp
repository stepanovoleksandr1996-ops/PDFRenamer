#include "PdfReader.h"

#include <memory>
#include <regex>

#include <poppler-document.h>
#include <poppler-page.h>

// Відкрити PDF та знайти перший ІПН.
std::string extractIpn(const std::string& pdfFile)
{
    // Завантажити PDF
    std::unique_ptr<poppler::document> document(
        poppler::document::load_from_file(pdfFile));

    // Якщо файл не відкрився
    if (!document)
        return "";

    std::string fullText;

    // Пройтися по всіх сторінках
    for (int i = 0; i < document->pages(); i++)
    {
        // Отримати сторінку
        std::unique_ptr<poppler::page> page(document->create_page(i));

        if (!page)
            continue;

        // Отримати текст сторінки
        auto bytes = page->text().to_utf8();

        // Додати текст у загальний рядок
        fullText += std::string(bytes.begin(), bytes.end());

        fullText += "\n";
    }

    // Шукати будь-яке число з 10 цифр
    std::regex ipnRegex("\\b\\d{10}\\b");

    std::smatch match;

    // Якщо знайдено
    if (std::regex_search(fullText, match, ipnRegex))
        return match.str();

    // Якщо ІПН немає
    return "";
}