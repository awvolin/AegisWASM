#ifndef ANIMATEDQGROUPBOX_H
#define ANIMATEDQGROUPBOX_H

#include "qobjectdefs.h"
#include <QGroupBox>
#include <QColor>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class AnimatedQGroupBox : public QGroupBox
{

    Q_OBJECT
    Q_PROPERTY(QColor border READ border WRITE setBorder)

public:
    AnimatedQGroupBox(QWidget *parent = 0)
    {
    }
    void setBorder (QColor border){
        setStyleSheet(QString("QGroupBox { "
                              "border: 1px solid; border-color: rgba(%1, %2, %3, %4);}")
                      .arg(border.red()).arg(border.green()).arg(border.blue()).arg(border.alpha()));
    }


    void paintEvent(QPaintEvent *){
        QStyleOption opt;
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }





    QColor border(){
        return Qt::black;
    }
};

#endif // ANIMATEDQGROUPBOX_H
