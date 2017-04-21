#include "catalog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timetableeditorform.h"
#include "genrediscriber.h"
#include "authordescriber.h"
#include "albumdescriber.h"
#include "songdescriber.h"
#include "simulationstatisticsform.h"
#include <sstream>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_loadStorageButton_clicked() {
    QString fileName = QFileDialog::getExistingDirectory(this, "Choose folder where storage is located");
    ui->simulateButton->setEnabled(false);
    ui->editTimeTableButton->setEnabled(false);
    ui->statisticsButton->setEnabled(false);
    if (!fileName.isEmpty()) {
        catalog = CatalogLoader::loadCatalog(fileName.toUtf8().constData(), this);
        if (catalog != nullptr) {
            this->infoBox("Storage has been successfully loaded!");
            if (catalog != nullptr && simulator != nullptr) {
                ui->simulateButton->setEnabled(true);
                ui->editTimeTableButton->setEnabled(true);
            }
            updateStorageInfo();
        }
    }
}

Catalog CatalogLoader::loadCatalog(std::string fileName, MainWindow *window) {
    std::vector<std::string> files = { fileName + "/albums.txt", fileName + "/songs.txt", fileName + "/genres.txt", fileName + "/authors.txt" };
    for (std::string name : files) {
        if (!FileUtils::fileExists(name)) {
            window->infoBox("Could not load storage: file " + name + " does not exist!");
            return nullptr;
        }
    }
    return std::make_shared<Catalog_>(fileName);
}

void MainWindow::on_loadTimetableButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose file where timetable is located");
    ui->simulateButton->setEnabled(false);
    ui->editTimeTableButton->setEnabled(false);
    ui->statisticsButton->setEnabled(false);
    if (!fileName.isEmpty()) {
        simulator = TimetableLoader::loadTimetable(fileName.toUtf8().constData(), this);
        if (simulator != nullptr) {
            this->infoBox("Timetable has been successfully loaded!");
            if (catalog != nullptr && simulator != nullptr) {
                ui->simulateButton->setEnabled(true);
                ui->editTimeTableButton->setEnabled(true);
            }
            updateTimetableInfo();
        }
    }
}

Simulator TimetableLoader::loadTimetable(std::string fileName, MainWindow *window) {
    if (!FileUtils::fileExists(fileName)) {
        window->infoBox("Could not load timetable: file " + fileName + " does not exist!");
        return nullptr;
    }
    return std::make_shared<Simulator_>(fileName);
}

void MainWindow::updateStorageInfo() {
    ui->treeWidget->clear();
    auto* root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0, QString("root"));
    for (Genre genre : catalog->getGenres()) {
        QTreeWidgetItem *genreItem = new QTreeWidgetItem(root);
        genreItem->setText(0, QString(genre->processedName().c_str()));
        root->addChild(genreItem);
        for (Author author : catalog->getAuthors()) {
            if (find_if(all(author->albums), [genre](const Album &album) {
                return album->genre == genre;
            }) != author->albums.end()) {
                QTreeWidgetItem *authorItem = new QTreeWidgetItem(genreItem);
                authorItem->setText(0, QString(author->processedName().c_str()));
                genreItem->addChild(authorItem);
                for (Album album : catalog->getAlbums()) {
                    if (album->author == author && album->genre == genre) {
                        QTreeWidgetItem *albumItem = new QTreeWidgetItem(authorItem);
                        albumItem->setText(0, QString(album->processedName().c_str()));
                        authorItem->addChild(albumItem);
                        for (Song song : catalog->getSongs()) {
                            if (song->album == album) {
                                QTreeWidgetItem *songItem = new QTreeWidgetItem(albumItem);
                                songItem->setText(0, QString(song->processedDescription().c_str()));
                                albumItem->addChild(songItem);
                            }
                        }
                    }
                }
            }
        }
    }
}


void MainWindow::on_editTimeTableButton_clicked() {
    ui->statisticsButton->setEnabled(false);
    TimetableEditorForm* form = new TimetableEditorForm();
    form->show();
    form->acceptTimetable(simulator, catalog);
}

void MainWindow::on_simulateButton_clicked() {
    statistics = simulator->simulate(catalog);
    updateStatistics();
    ui->statisticsButton->setEnabled(true);
}

void MainWindow::updateStatistics() {
    ui->daysTabWidget->clear();
    int maxTimestamp = 0;
    for (StatisticsEvent event : statistics->getEvents()) {
        maxTimestamp = std::max(maxTimestamp, event->timestamp);
    }
    int days = (maxTimestamp + 24 * 3600 - 1) / (24 * 3600);
    for (int i = 0; i < days; i++) {
        auto* tab = new QWidget();
        QListWidget* listWidget = new QListWidget(tab);
        listWidget->setFont(QFont("Courier", 9));
        listWidget->setGeometry(QRect(0, 0, tab->width(), tab->height()));
        int leftEdge = 24 * 3600 * i, rightEdge = 24 * 3600 * (i + 1) - 1;
        for (StatisticsEvent event : statistics->getEvents()) {
            if (event->timestamp < leftEdge || event->timestamp > rightEdge) {
                continue;
            }
            auto* item = new QListWidgetItem();
            std::stringstream stream;
            event->describe(stream);
            item->setText(QString(text(stream.str()).c_str()));
            listWidget->addItem(item);
        }
        ui->daysTabWidget->addTab(tab, tr(("Day" + std::to_string(i + 1)).c_str()));
    }
}

void describeGenre(const Genre &genre, const Catalog &catalog) {
    auto* describer = new GenreDiscriber();
    describer->updateInfo(genre, catalog);
    describer->show();
}

void describeAuthor(const Author &author, const Catalog &catalog) {
    auto *describer = new AuthorDescriber();
    describer->updateInfo(author, catalog);
    describer->show();
}

void describeAlbum(const Album &album, const Catalog &catalog) {
    auto *describer = new AlbumDescriber();
    describer->updateInfo(album, catalog);
    describer->show();
}

void describeSong(const Song &song, const Catalog &catalog) {
    auto *describer = new SongDescriber();
    describer->updateInfo(song, catalog);
    describer->show();
}

void MainWindow::on_treeWidget_doubleClicked(const QModelIndex &index) {
    int q = 0;
    QModelIndex parent = index;
    while (parent != QModelIndex()) {
        parent = parent.parent();
        q++;
    }
    if (q == 2) {
        describeGenre(catalog->findGenre(invtext(index.data().toString().toUtf8().constData())), catalog);
    }
    if (q == 3) {
        describeAuthor(catalog->findAuthor(invtext(index.data().toString().toUtf8().constData())), catalog);
    }
    if (q == 4) {
        parent = index.parent();
        describeAlbum(catalog->findAlbum(invtext(index.data().toString().toUtf8().constData()), invtext(parent.data().toString().toUtf8().constData())), catalog);
    }
    auto selectName = [] (std::string name) {
        int size = len(name);
        for (int i = len(name) - 1; i >= 0; i--) {
            if (name[i] == ' ') {
                size = i;
                break;
            }
        }
        return name.substr(0, size);
    };
    if (q == 5) {
        describeSong(catalog->findSong(invtext(selectName(index.data().toString().toUtf8().constData())),
                                       invtext(index.parent().data().toString().toUtf8().constData()),
                                       invtext(index.parent().parent().data().toString().toUtf8().constData())), catalog
        );
    }
}

void MainWindow::on_statisticsButton_clicked() {
    auto* window = new SimulationStatisticsForm();
    window->acceptStatistics(catalog, statistics);
    window->show();
}
