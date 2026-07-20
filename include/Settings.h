#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

/*
 * ==========================================================
 * Settings
 * ==========================================================
 *
 * Клас відповідає за читання та запис налаштувань програми.
 *
 * Налаштування зберігаються у файлі:
 *
 *     config.ini
 *
 * який знаходиться поруч із PDFRenamer.exe.
 *
 * На даний момент клас використовується лише
 * для збереження шляху до LibreOffice (soffice.exe),
 * але в майбутньому тут можна буде зберігати
 * будь-які інші налаштування програми.
 *
 */

class Settings
{
public:

    /*
     * Повертає шлях до soffice.exe.
     *
     * Якщо параметр ще не був збережений,
     * повертає порожній рядок.
     */
    static QString libreOfficePath();

    /*
     * Зберігає шлях до soffice.exe.
     */
    static void setLibreOfficePath(const QString& path);
};

#endif