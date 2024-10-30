#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "config.h"

#include "parametricdataentry.h"
#include "combatinventory.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_combatButton_clicked();

    void on_dataButton_clicked();



private:
    Ui::MainWindow *ui;
    QString defaultStyleSheet;
    QString cssFilePath;
    Combatinventory *combatInventoryWindow;
    ParametricDataEntry *parametricDataEntryWindow;
};
#endif // MAINWINDOW_H

