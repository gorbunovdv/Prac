#include "simulationstatisticsform.h"
#include "ui_simulationstatisticsform.h"
#include <QWidget>
#include <QTableWidget>
#include "types.h"
#include <QSizePolicy>

SimulationStatisticsForm::SimulationStatisticsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationStatisticsForm) {
    ui->setupUi(this);
}

SimulationStatisticsForm::~SimulationStatisticsForm() {
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
            if (play->song->genre == genre) {
                playCount[play->song]++;
            }
        }
        std::vector<std::pair<int, Song>> ranking;
        for (auto i : playCount) {
            ranking.push_back(std::make_pair(i.second, i.first));
        }
        sort(all(ranking)), reverse(all(ranking));
        auto* tableWidget1 = new QTableWidget();
        tableWidget1->setRowCount(std::min(10, len(ranking)));
        tableWidget1->setColumnCount(5);
        for (int i = 0; i < 5; i++) {
            tableWidget1->setColumnWidth(i, ui->tabWidget->width() / 5 - 10);
        }
        for (int i = 0; i < len(ranking); i++) {
            tableWidget1->setItem(i, 0, text(std::to_string(i + 1), tableWidget1));
            tableWidget1->setItem(i, 1, text(ranking[i].second->name, tableWidget1));
            tableWidget1->setItem(i, 2, text(ranking[i].second->album->name, tableWidget1));
            tableWidget1->setItem(i, 3, text(ranking[i].second->author->name, tableWidget1));
            tableWidget1->setItem(i, 4, text(std::to_string(ranking[i].first), tableWidget1));
        }
        ui->tabWidget->addTab(tableWidget1, tr(genre->name.c_str()));
    }
}
