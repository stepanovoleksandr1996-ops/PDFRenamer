#include "Settings.h"

#include <QCoreApplication>
#include <QSettings>

/*
 * ==========================================================
 * Повертає повний шлях до config.ini
 * ==========================================================
 *
 * Наприклад:
 *
 * Windows
 * --------
 * C:/PDFRenamer/config.ini
 *
 * Linux
 * -----
 * /home/user/PDFRenamer/config.ini
 *
 */

static QString configFilePath()
{
    return QCoreApplication::applicationDirPath()
            + "/config.ini";
}

/*
 * ==========================================================
 * Читання шляху до LibreOffice
 * ==========================================================
 */

QString Settings::libreOfficePath()
{
    QSettings settings(
        configFilePath(),
        QSettings::IniFormat);

    return settings.value(
                "LibreOffice/Path",
                "").toString();
}

/*
 * ==========================================================
 * Запис шляху до LibreOffice
 * ==========================================================
 */

void Settings::setLibreOfficePath(const QString& path)
{
    QSettings settings(
        configFilePath(),
        QSettings::IniFormat);

    settings.setValue(
        "LibreOffice/Path",
        path);

    /*
     * sync() примусово записує зміни на диск.
     */
    settings.sync();
}