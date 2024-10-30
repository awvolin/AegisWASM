#ifndef BORDERPROPERTY_H
#define BORDERPROPERTY_H

#include "qobjectdefs.h"
#include <QLineEdit>
#include <QColor>


class borderproperty : public QLineEdit
{

    Q_OBJECT
    Q_PROPERTY(QColor border READ border WRITE setBorder)

public:
    borderproperty(QWidget *parent = 0)
    {
    }
    void setBorder (QColor border){
        setStyleSheet(QString("QLineEdit {"
                              "color: rgb(255, 255, 255); font: 700 9pt 'Segoe UI';"
                              "border: 1px solid; border-color: rgba(%1, %2, %3, %4);}")
                      .arg(border.red()).arg(border.green()).arg(border.blue()).arg(border.alpha()));
    }
    QColor border(){
        return Qt::black;
    }
};


#endif // BORDERPROPERTY_H
