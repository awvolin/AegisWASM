#ifndef PARAMETRICDATAENTRY_H
#define PARAMETRICDATAENTRY_H

#include "config.h"
#include <limits.h>
#include <cstdint>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QAbstractSlider>
#include <QDial>
#include <QScreen>
#include "minimize.h"
#include "mytooltip.h"
#include "markcoords.h"
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlComponent>
#include "QMessageBox"
#include "QToolTip"
#include <QQmlContext>
#include <QCloseEvent>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <QWebSocket> // Include the WebSocket header


namespace Ui {
class ParametricDataEntry;
}

class ParametricDataEntry : public QMainWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ParametricDataEntry(QWidget *parent = nullptr);
    ~ParametricDataEntry();

    QString positLatitudeDirection, positLongitudeDirection, markLatitudeDirection, markLongitudeDirection, magDirection;
    bool positLatDirBool = false, positLongDirBool = false, markLatDirBool = false, markLongDirBool = false, magDirBool = false;
    bool trueHeadingMinimized = false, positSourceMinimized = false, windSourceMinimized = false, waterDepthMinimized = false;
    QScreen *desktop;
    MyToolTip *m_tip;
    QQuickView positView;
    QQuickView markView;
    QQmlEngine engine;

    Q_INVOKABLE void applyNewPositCoords(QList<int> latitude, QList<int> longitude);
    Q_INVOKABLE void applyNewMarkCoords(QList<int> latitude, QList<int> longitude);
    Q_INVOKABLE void markMap();
    Q_INVOKABLE void positMap();

private slots:

    void on_cancelButton_clicked();

    void resetButtonClicked();

    void minimization(int);

    void trueHeadingInputAlert();
    void positSourceInputAlert();
    void windSourceInputAlert();
    void waterDepthInputAlert();

    void fillSlots();

    void headingSlider();
    void trueDirSlider();
    void relDirSlider();
    void trueSpeedSlider();
    void relSpeedSlider();
    void speedSlider();
    void waterDepthSlider();
    void surfWaterTempSlider();
    void setSlider();
    void driftSlider();

    void positNorth();
    void positSouth();
    void positEast();
    void positWest();
    void markNorth();
    void markSouth();
    void markEast();
    void markWest();
    void magEast();
    void magWest();

    void trueHeadingCheck();
    void speedCheck();
    void positLatCheck();
    void positLat1Check();
    void positLat2Check();
    void positLat3Check();
    void positLongCheck();
    void positLong1Check();
    void positLong2Check();
    void positLong3Check();
    void markTime1Check();
    void markTime2Check();
    void markLatCheck();
    void markLat1Check();
    void markLat2Check();
    void markLat3Check();
    void markLongCheck();
    void markLong1Check();
    void markLong2Check();
    void markLong3Check();
    void trueDirCheck();
    void trueSpeedCheck();
    void relDirCheck();
    void relSpeedCheck();
    void waterDepthCheck();
    void surfWaterTempCheck();
    void setCheck();
    void driftCheck();
    void magVarCorrCheck();
    void sec1Reset();
    void sec2Reset();
    void sec3Reset();
    void sec4Reset();
    void onWebSocketDisconnected(); // Slot for WebSocket disconnection
    void initializeDatabase();

private:
    Ui::ParametricDataEntry *ui;
    QWebSocket *socket; // Declare the QWebSocket pointer
    QString dbArray[34];
    QString newArray[34];

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent (QCloseEvent *event);
};

#endif // PARAMETRICDATAENTRY_H
