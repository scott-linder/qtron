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
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Kill me: */

void MainWindow::on_colorButton_1_clicked()
{
    ui->tronWidget->setPlayerColor(0, QColorDialog::getColor(ui->tronWidget->getPlayerColor(0), this));
}

void MainWindow::on_colorButton_2_clicked()
{
    ui->tronWidget->setPlayerColor(1, QColorDialog::getColor(ui->tronWidget->getPlayerColor(1), this));
}

void MainWindow::on_colorButton_3_clicked()
{
    ui->tronWidget->setPlayerColor(2, QColorDialog::getColor(ui->tronWidget->getPlayerColor(2), this));
}

void MainWindow::on_colorButton_4_clicked()
{
    ui->tronWidget->setPlayerColor(3, QColorDialog::getColor(ui->tronWidget->getPlayerColor(3), this));
}
