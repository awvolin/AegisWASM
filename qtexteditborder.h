#ifndef QTEXTEDITBORDER_H
#define QTEXTEDITBORDER_H

#include "config.h"
#include "qobjectdefs.h"
#include <QTextEdit>
#include <QColor>

class QTextEditBorder : public QTextEdit
{

    Q_OBJECT
    Q_PROPERTY(QColor border READ border WRITE setBorder)

public:
    QTextEditBorder(QWidget *parent = 0)
    {
    }
    void setBorder (QColor border){
        setStyleSheet(QString("QTextEdit {"
                              "color: rgb(255, 255, 255); font: 700 9pt 'Segoe UI';"
                              "border: 1px solid; border-color: rgba(%1, %2, %3, %4);}")
                      .arg(border.red()).arg(border.green()).arg(border.blue()).arg(border.alpha()));
    }
    QColor border(){
        return Qt::black;
    }
};

#endif // QTEXTEDITBORDER_H
