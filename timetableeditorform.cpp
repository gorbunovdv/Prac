#include "timetableeditorform.h"
#include "ui_timetableeditorform.h"
#include "types.h"
#include <QtWidgets>

TimetableEditorForm::TimetableEditorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimetableEditorForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

TimetableEditorForm::~TimetableEditorForm()
{
    delete ui;
}

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

void TimetableEditorForm::reshowTimetable() {
    ui->tableWidget->setRowCount(len(simulator->entities));
    ui->tableWidget->setColumnCount(4);
    for (int i = 0; i < 4; i++) {
        ui->tableWidget->setColumnWidth(i, ui->tableWidget->width() / 4);
    }
    int timestamp = 0;
    for (int i = 0; i < len(simulator->entities); i++) {
        std::string name;
        std::string type;
        std::string genre;
        int duration;
        std::tie(name, type, genre, duration) = simulator->entities[i];
        ui->tableWidget->setItem(i, 0, text(name, ui->tableWidget));
        ui->tableWidget->setItem(i, 1, text(type, ui->tableWidget));
        ui->tableWidget->setItem(i, 2, text(genre, ui->tableWidget));
        ui->tableWidget->setItem(i, 3, text(std::to_string(duration), ui->tableWidget));
        timestamp += duration;
    }
}


void TimetableEditorForm::on_pushButton_clicked() {
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
}

void TimetableEditorForm::on_pushButton_2_clicked() {
    QItemSelection selection = ui->tableWidget->selectionModel()->selection();
    std::vector<int> to_erase;
    for (int i = ui->tableWidget->rowCount() - 1; i >= 0; i--) {
        bool toDelete = false;
        foreach(QModelIndex index, selection.indexes()) {
            if (index.row() == i) {
                toDelete = true;
            }
        }
        if (toDelete) {
            to_erase.push_back(i);
        }
    }
    for (int i : to_erase) {
        ui->tableWidget->removeRow(i);
    }
}

bool TimetableEditorForm::validateType(std::string type) {
    return type == "REQUESTS PROGRAM" || type == "HITPARAD PROGRAM";
}

bool TimetableEditorForm::validateGenre(std::string genre) {
    return std::find_if(all(catalog->getGenres()), [genre](const Genre &cgenre) {
        return cgenre->name == genre;
    }) != catalog->getGenres().end();
}

bool TimetableEditorForm::validateDuration(std::string duration) {
    int result = 0;
    for (char c : duration) {
        result = result * 10 + c - '0';
    }
    if (result < 0 || result > 3600 * 100) {
        return false;
    }
    return true;
}

void showMessage(std::string text) {
    QMessageBox Msgbox;
    Msgbox.setText(QString(text.c_str()));
    Msgbox.exec();
}

void TimetableEditorForm::on_pushButton_3_clicked() {
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        auto type = ui->tableWidget->item(i, 1)->text();
        auto genre = ui->tableWidget->item(i, 2)->text();
        auto duration = ui->tableWidget->item(i, 3)->text();
        if (!validateType(type.toUtf8().constData())) {
            showMessage("Invalid type at row " + std::to_string(i));
            return ;
        }
        if (!validateGenre(genre.toUtf8().constData())) {
            showMessage("Invalid genre at row " + std::to_string(i));
            return ;
        }
        if (!validateDuration(duration.toUtf8().constData())) {
            showMessage("Invalid duration at row " + std::to_string(i));
            return ;
        }
    }
    simulator->entities.clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        std::string name = invtext(ui->tableWidget->item(i, 0)->text().toUtf8().constData());
        std::string type = invtext(ui->tableWidget->item(i, 1)->text().toUtf8().constData());
        std::string genre = invtext(ui->tableWidget->item(i, 2)->text().toUtf8().constData());
        std::string duration = invtext(ui->tableWidget->item(i, 3)->text().toUtf8().constData());
        simulator->entities.emplace_back(name, type, genre, atoi(duration.c_str()));
    }
    this->close();
}
