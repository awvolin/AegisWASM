#ifndef MINIMIZE_H
#define MINIMIZE_H

#include "config.h"
#include "ui_parametricdataentry.h"
#include <QtCore/QObject>
#include "config.h"

class Minimize : public QObject
{
    Q_OBJECT
public:
   Minimize();

public slots:
    void trueHeadingMinimization(Ui::ParametricDataEntry*, bool, QWidget*);
    void positSourceMinimization(Ui::ParametricDataEntry*, bool, QWidget*);
    void windSourceMinimization(Ui::ParametricDataEntry*, bool, QWidget*);
    void waterDepthMinimization(Ui::ParametricDataEntry*, bool, QWidget*);
private:
    QString m_name;
    int geoW = 621;
    int geoX = 10;
};

#endif // TEST_H
