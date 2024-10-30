#include "mytooltip.h"
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

MyToolTip::MyToolTip(QWidget *parent) : QLabel(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(duration);
    m_timer->setSingleShot(true);
    connect(m_timer, SIGNAL(timeout()), SLOT(hideTip()));
    //setStyleSheet("QLabel { background-color : #E37B3F; color : #f7f7f7; }");
    setStyleSheet("QLabel { background-color : red; color : white; }");
    //setStyleSheet("QLabel { background-color : white; color : black; }");
    //setStyleSheet("QLabel { background-color : purple; color : orange; }");
    //setStyleSheet("* {color: white;"
                             //"background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 blue, stop:1 red);}");
    //setStyleSheet("* {color: white;"
                          // "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 blue, stop:1 purple);}");
    setAlignment(Qt::AlignCenter);
    setFixedHeight(20);
}

void MyToolTip::showText(QWidget *pos, QString text)
{
    move(pos->x()+ 50 + pos->parentWidget()->x() ,pos->y() + 23 + pos->parentWidget()->y());
    setText(text);
    setFixedWidth(9 * text.length());
    QTimer::singleShot(delay, this, SLOT(placeTip()));
}

void MyToolTip::placeTip()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation *fading = new QPropertyAnimation(eff,"opacity");
    fading->setDuration(500);
    fading->setStartValue(0);
    fading->setEndValue(1);
    fading->setEasingCurve(QEasingCurve::InBack);
    fading->start(QPropertyAnimation::DeleteWhenStopped);
    show();
    m_timer->stop();
    m_timer->start();
}

void MyToolTip::hideTip()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation *fading = new QPropertyAnimation(eff,"opacity");
    fading->setDuration(500);
    fading->setStartValue(1);
    fading->setEndValue(0);
    fading->setEasingCurve(QEasingCurve::OutBack);
    fading->start(QPropertyAnimation::DeleteWhenStopped);
    connect(fading,SIGNAL(finished()),this,SLOT(hideNow()));
}

void MyToolTip::hideNow()
{
    if (isVisible())
    {
        hide();
    }
}

MyToolTip::~MyToolTip()
{
    close();
}
