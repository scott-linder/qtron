#include <algorithm>

#include <QColorDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tron.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->playerCountSpinner->setMinimum(Tron::MIN_PLAYER_COUNT);
    ui->playerCountSpinner->setMaximum(Tron::MAX_PLAYER_COUNT);
    ui->playerCountSpinner->setSuffix(" Players");

    auto min_size = std::max(Tron::MIN_MAP_HEIGHT, Tron::MIN_MAP_WIDTH);
    auto max_size = std::min(Tron::MAX_MAP_HEIGHT, Tron::MAX_MAP_WIDTH);
    const auto INCREMENTS = 3;
    ui->mapSizeSpinner->setMinimum(min_size);
    ui->mapSizeSpinner->setMaximum(max_size);
    ui->mapSizeSpinner->setSingleStep((max_size - min_size) / INCREMENTS);
    ui->mapSizeSpinner->setSuffix((" Squares"));

    connect(ui->playerCountSpinner, SIGNAL(valueChanged(int)),
            ui->tronWidget, SLOT(setPlayerCount(int)));

    connect(ui->mapSizeSpinner, SIGNAL(valueChanged(int)),
            ui->tronWidget, SLOT(setMapHeight(int)));
    connect(ui->mapSizeSpinner, SIGNAL(valueChanged(int)),
            ui->tronWidget, SLOT(setMapWidth(int)));

    connect(ui->startGameButton, SIGNAL(clicked()),
            ui->tronWidget, SLOT(start()));

    connect(ui->tronWidget, SIGNAL(gameInProgress(bool)),
            this, SLOT(tronGameInProgress(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tronGameInProgress(bool playing)
{
    // Update settings control access
    ui->playerCountSpinner->setEnabled(!playing);
    ui->mapSizeSpinner->setEnabled(!playing);
    ui->colorButton_1->setEnabled(!playing);
    ui->colorButton_2->setEnabled(!playing);
    ui->colorButton_3->setEnabled(!playing);
    ui->colorButton_4->setEnabled(!playing);
    ui->nameEdit_1->setEnabled(!playing);
    ui->nameEdit_2->setEnabled(!playing);
    ui->nameEdit_3->setEnabled(!playing);
    ui->nameEdit_4->setEnabled(!playing);
    ui->startGameButton->setEnabled(!playing);
    // Update colors on player settings buttons
    // to reflect actual player colors
    if (playing) {
        QString colorFmt{"color: %1"};
        ui->colorButton_1->setStyleSheet(colorFmt.arg(ui->tronWidget->getPlayerColor(0).name()));
        ui->colorButton_2->setStyleSheet(colorFmt.arg(ui->tronWidget->getPlayerColor(1).name()));
        ui->colorButton_3->setStyleSheet(colorFmt.arg(ui->tronWidget->getPlayerColor(2).name()));
        ui->colorButton_4->setStyleSheet(colorFmt.arg(ui->tronWidget->getPlayerColor(3).name()));
    } else {
        // Make it easy to start a new game right away
        ui->startGameButton->setFocus(Qt::OtherFocusReason);
    }
}

void MainWindow::handleColorButton(int i)
{
    ui->tronWidget->setPlayerColor(i, QColorDialog::getColor(ui->tronWidget->getPlayerColor(i), this));
}

/* Kill me: */

void MainWindow::on_colorButton_1_clicked()
{
    handleColorButton(0);
}

void MainWindow::on_colorButton_2_clicked()
{
    handleColorButton(1);
}

void MainWindow::on_colorButton_3_clicked()
{
    handleColorButton(2);
}

void MainWindow::on_colorButton_4_clicked()
{
    handleColorButton(3);
}

void MainWindow::on_nameEdit_1_textEdited(const QString &name)
{
    ui->tronWidget->setPlayerName(0, name);
}

void MainWindow::on_nameEdit_2_textEdited(const QString &name)
{
    ui->tronWidget->setPlayerName(1, name);
}

void MainWindow::on_nameEdit_3_textEdited(const QString &name)
{
    ui->tronWidget->setPlayerName(2, name);
}

void MainWindow::on_nameEdit_4_textEdited(const QString &name)
{
    ui->tronWidget->setPlayerName(3, name);
}
