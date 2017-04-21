#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <sys/stat.h>
#include <unistd.h>
#include "simulator.h"
#include "types.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void infoBox(std::string text) {
        QMessageBox Msgbox;
        Msgbox.setText(QString(text.c_str()));
        Msgbox.exec();
    }

private slots:
    void on_loadStorageButton_clicked();

    void on_loadTimetableButton_clicked();

    void on_editTimeTableButton_clicked();

    void on_simulateButton_clicked();

    void on_treeWidget_doubleClicked(const QModelIndex &index);

private:
    void loadStorage();

    void loadTimetable() {

    }

    void updateStatistics();

    void updateStorageInfo();

    void updateTimetableInfo() {}

    Ui::MainWindow *ui;
    Catalog catalog;
    Simulator simulator;
    Statistics statistics;
};

class FileUtils {
public:
    static bool fileExists(std::string name) {
        return access(name.c_str(), F_OK) != -1;
    }
};

class CatalogLoader {
public:
    static Catalog loadCatalog(std::string fileName, MainWindow *window);
};

class TimetableLoader {
public:
    static Simulator loadTimetable(std::string fileName, MainWindow *window);
};

#endif // MAINWINDOW_H
