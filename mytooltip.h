#ifndef MYTOOLTIP_H
#define MYTOOLTIP_H

#include "config.h"
#include "qboxlayout.h"
#include <QLabel>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>


class MyToolTip : public QLabel
{
    Q_OBJECT
public:
    MyToolTip(QWidget *w);
    ~MyToolTip();

public slots:
    void showText(QWidget *pos, QString);
    void placeTip();
    void hideTip();
    void hideNow();
private:
    int delay = 500;
    int duration = 5000;
    QTimer *m_timer;
};
#endif // MYTOOLTIP_H
