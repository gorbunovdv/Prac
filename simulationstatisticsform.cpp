#include "simulationstatisticsform.h"
#include "ui_simulationstatisticsform.h"
#include <QWidget>
#include <QTableWidget>
#include "types.h"

SimulationStatisticsForm::SimulationStatisticsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationStatisticsForm)
{
    ui->setupUi(this);
}

SimulationStatisticsForm::~SimulationStatisticsForm()
{
    delete ui;
}

namespace {
QTableWidgetItem* text(std::string text, QTableWidget *parent) {
    auto result = new QTableWidgetItem();
    for (char &c : text) {
        if (c == '_') {
            c = ' ';
        }
    }
    result->setText(QString(text.c_str()));
    return result;
}
}

void SimulationStatisticsForm::acceptStatistics(const Catalog &catalog, const Statistics &statistics) {
    SimulationStatisticsForm::catalog = catalog;
    SimulationStatisticsForm::statistics = statistics;
    ui->tabWidget->clear();
    for (Genre genre : catalog->getGenres()) {
        std::map<Song, int> playCount;
        for (Play play : statistics->getPlays()) {
            playCount[play->song]++;
        }
        std::vector<int, Song> ranking;
        for (auto i : playCount) {
            ranking.push_back(i.second, i.first);
        }
        sort(all(ranking)), reverse(all(ranking));

        QWidget *tab = new QWidget();
        ui->tabWidget->addTab(tab, tr(genre->name.c_str()));
        QTableWidget* tableWidget = new QTableWidget(tab);
        tableWidget->setRowCount(std::min(10, len(ranking)));
        tableWidget->setColumnCount(5);
        for (int i = 0; i < 5; i++) {
            ui->tableWidget->setColumnWidth(i, ui->tableWidget->width() / 5);
        }
        for (int i = 0; i < len(ranking); i++) {
            tableWidget->setItem(i, 0, text(std::to_string(i + 1), tabWidget));
            tableWidget->setItem(i, 1, text(std::to_string(i + 1), tabWidget));
            tableWidget->setItem(i, 2, text(std::to_string(i + 1), tabWidget));
            tableWidget->setItem(i, 3, text(std::to_string(i + 1), tabWidget));
            tableWidget->setItem(i, 4, text(std::to_string(i + 1), tabWidget));
        }
    }
}
