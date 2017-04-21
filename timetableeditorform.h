#ifndef TIMETABLEEDITORFORM_H
#define TIMETABLEEDITORFORM_H

#include <QWidget>
#include "simulator.h"

namespace Ui {
class TimetableEditorForm;
}

class TimetableEditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit TimetableEditorForm(QWidget *parent = 0);
    ~TimetableEditorForm();

    void acceptTimetable(Simulator simulator, Catalog catalog) {
        TimetableEditorForm::simulator = simulator;
        TimetableEditorForm::catalog = catalog;
        reshowTimetable();
    }

    void reshowTimetable();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    bool validateGenre(std::string genre);
    bool validateType(std::string type);
    bool validateDuration(std::string duration);

    Ui::TimetableEditorForm *ui;
    Simulator simulator;
    Catalog catalog;
};

#endif // TIMETABLEEDITORFORM_H
