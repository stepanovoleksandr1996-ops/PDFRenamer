/*
 * PDFRenamer
 *
 * main.cpp
 *
 * Точка входу програми.
 *
 * Для Portable-версії всі відносні шляхи будуються
 * від каталогу, де знаходиться PDFRenamer.exe.
 *
 * Завдяки цьому користувач може:
 *
 *     PDFRenamerPortable/
 *         PDFRenamer.exe
 *         Runtime/
 *         Data/
 *         plugins/
 *
 * просто перенести всю папку на інший ПК або флешку,
 * і програма працюватиме без встановлення.
 */

#include <QApplication>
#include <QCoreApplication>
#include <QDir>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*
     * Каталог, у якому знаходиться executable.
     *
     * Linux:
     *     /home/user/PDFRenamer
     *
     * Windows:
     *     D:\PDFRenamerPortable
     */
    QString appDir = QCoreApplication::applicationDirPath();

    /*
     * Робимо каталог програми поточним.
     *
     * Після цього всі відносні шляхи:
     *
     * Data/
     * Runtime/
     * plugins/
     *
     * автоматично будуть шукатися біля exe,
     * незалежно від того, звідки користувач запустив програму.
     */
    QDir::setCurrent(appDir);

    /*
     * Створюємо необхідні каталоги,
     * якщо вони ще не існують.
     *
     * Це дозволяє вперше запускати Portable-версію
     * без ручної підготовки структури.
     */

    QDir().mkpath("Data");
    QDir().mkpath("Data/Logs");
    QDir().mkpath("Data/Temp");
    QDir().mkpath("Data/Config");

    MainWindow window;
    window.show();

    return app.exec();
}