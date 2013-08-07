#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tronwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void handleColorButton(int);

public slots:
    void tronGameInProgress(bool);

private slots:
    void on_colorButton_1_clicked();
    void on_colorButton_2_clicked();
    void on_colorButton_3_clicked();
    void on_colorButton_4_clicked();

    void on_nameEdit_1_textEdited(const QString &arg1);
    void on_nameEdit_2_textEdited(const QString &arg1);
    void on_nameEdit_3_textEdited(const QString &arg1);
    void on_nameEdit_4_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
