#ifndef COMBATINVENTORY_H
#define COMBATINVENTORY_H

#include "config.h"
#include "borderproperty.h"
#include "animatedqgroupbox.h"
#include "qtexteditborder.h"
#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QTimerEvent>
#include <QTimer>
#include <QLabel>
#include <QObject>
#include <QTextCursor>
#include <QPropertyAnimation>
#include <QScreen>
#include <QWebSocket> // Include the WebSocket header

namespace Ui {
class Combatinventory;
}

class Combatinventory : public QMainWindow
{
    Q_OBJECT

public:
    explicit Combatinventory(QWidget *parent = nullptr);
    ~Combatinventory();

private slots:
    void timerEvent(QTimerEvent *event);
    void fwdChangeAlert();
    void stingChangeAlert();
    void nsmChangeAlert();
    void gunChangeAlert();
    void ammoTypeChangeAlert();
    void roundsChangeAlert();
    void sizeRefresh();
    void onWebSocketDisconnected(); // Slot for WebSocket disconnection

private:
    Ui::Combatinventory *ui;
    QString dbArray[15];
    QString newArray[15];
    int timerId;
    QWebSocket *socket; // Declare the QWebSocket pointer


protected:
    void resizeEvent(QResizeEvent *event) override; // Use 'override' for clarity
};

#endif // COMBATINVENTORY_H
