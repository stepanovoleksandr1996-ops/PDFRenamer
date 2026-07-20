#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QPlainTextEdit;
class QProgressBar;
class QPushButton;
class QThread;
class ProcessingWorker;

//======================================================
// MainWindow
//
// Головне вікно програми.
//
// Відповідає лише за графічний інтерфейс.
//
//======================================================

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:

    //--------------------------------------------------
    // Елементи GUI
    //--------------------------------------------------

    QLineEdit *folderEdit;
    QLineEdit *excelEdit;

    QPushButton *folderButton;
    QPushButton *excelButton;
    QPushButton *startButton;

    QPlainTextEdit *logEdit;

    QProgressBar *progressBar;

    QLabel *statusLabel;

    //--------------------------------------------------
    // Потік
    //--------------------------------------------------

    QThread *workerThread;

    //--------------------------------------------------
    // Робітник
    //--------------------------------------------------

    ProcessingWorker *worker;

    //--------------------------------------------------
    // Прапорець.
    //
    // false
    //      Програма ще не завершила роботу.
    //
    // true
    //      Обробка завершена і кнопка
    //      повинна закривати програму.
    //--------------------------------------------------

    bool processingCompleted;

    //--------------------------------------------------
    // Побудова GUI
    //--------------------------------------------------

    void buildUi();

        //--------------------------------------------------
    // Перевіряє наявність LibreOffice.
    //
    // Послідовність:
    //
    // 1. Portable Runtime.
    // 2. config.ini.
    // 3. Запитати користувача.
    //
    // true  - LibreOffice знайдений.
    // false - користувач скасував вибір.
    //--------------------------------------------------

    bool ensureLibreOffice();
    

private slots:

    void selectFolder();

    void selectExcel();

    void startProcessing();

    //--------------------------------------------------
    // Викликається після завершення
    // роботи ProcessingWorker.
    //--------------------------------------------------

    void processingFinished();
};

#endif