#include "minimize.h"
#include "parametricdataentry.h"
#include <QDebug>
Minimize::Minimize(){}

void Minimize::trueHeadingMinimization(Ui::ParametricDataEntry *ui, bool trueHeadingMinimized, QWidget *parametricDataEntry){

    QRect r = ui->centralwidgetPDE->geometry();
    QRect geo1 = ui->parametricBox->geometry();
    QRect geo2 = ui->positSourceBox->geometry();
    QRect geo3 = ui->windSourceBox->geometry();
    QRect geo4 = ui->waterDepthBox->geometry();
    QRect geo5 = ui->navBox->geometry();
    QRect geo6 = ui->buttonBox->geometry();

    int yDiff = 175;

    if (trueHeadingMinimized == false){
        ui->positSourceBox->setGeometry(geoX,geo2.y()-yDiff,geoW,geo2.height());
        ui->windSourceBox->setGeometry(geoX,geo3.y()-yDiff,geoW,geo3.height());
        ui->waterDepthBox->setGeometry(geoX,geo4.y()-yDiff,geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()-yDiff,geoW,geo5.height());
        ui->buttonBox->setGeometry(geoX,geo6.y()-yDiff,geoW,geo6.height());
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()-yDiff);
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), r.width(), geo1.height()-yDiff);
        parametricDataEntry->resize(r.width(), geo1.height()-yDiff);
        ui->trueHeadingMin->setText("˅");
    }

    else if (trueHeadingMinimized == true){
        ui->positSourceBox->setGeometry(geoX,geo2.y()+yDiff,geoW,geo2.height());
        ui->windSourceBox->setGeometry(geoX,geo3.y()+yDiff,geoW,geo3.height());
        ui->waterDepthBox->setGeometry(geoX,geo4.y()+yDiff,geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()+yDiff,geoW,geo5.height());
        ui->buttonBox->setGeometry(geoX,geo6.y()+yDiff,geoW,geo6.height());
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()+yDiff);
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), r.width(), geo1.height()+yDiff);
        parametricDataEntry->resize(r.width(), geo1.height()+yDiff);
        ui->trueHeadingMin->setText("—");
    }

}

void Minimize::positSourceMinimization(Ui::ParametricDataEntry *ui, bool positSourceMinimized, QWidget *parametricDataEntry){
    QRect r = ui->centralwidgetPDE->geometry();
    QRect geo1 = ui->parametricBox->geometry();
    QRect geo3 = ui->windSourceBox->geometry();
    QRect geo4 = ui->waterDepthBox->geometry();
    QRect geo5 = ui->navBox->geometry();
    QRect geo6 = ui->buttonBox->geometry();

    int yDiff = 145;

    if (positSourceMinimized == false){
        ui->windSourceBox->setGeometry(geoX,geo3.y()-yDiff,geoW,geo3.height());
        ui->waterDepthBox->setGeometry(geoX,geo4.y()-yDiff,geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()-yDiff,geoW,61);
        ui->buttonBox->setGeometry(geoX,geo6.y()-yDiff,geoW,61);
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()-yDiff);
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), 711, geo1.height()-yDiff);
        parametricDataEntry->resize(r.width(), geo1.height()-yDiff);
        ui->positSourceMin->setText("˅");
    }

    else if (positSourceMinimized == true){
        ui->windSourceBox->setGeometry(geoX,geo3.y()+yDiff,geoW,geo3.height());
        ui->waterDepthBox->setGeometry(geoX,geo4.y()+yDiff,geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()+yDiff,geoW,geo5.height());
        ui->buttonBox->setGeometry(geoX,geo6.y()+yDiff,geoW,geo6.height());
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()+yDiff);
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), r.width(), geo1.height()+yDiff);
        parametricDataEntry->resize(r.width(), geo1.height()+yDiff);
        ui->positSourceMin->setText("—");
    }
}

void Minimize::windSourceMinimization(Ui::ParametricDataEntry *ui, bool  windSourceMinimized, QWidget *parametricDataEntry){
    QRect r = ui->centralwidgetPDE->geometry();
    QRect geo1 = ui->parametricBox->geometry();
    QRect geo4 = ui->waterDepthBox->geometry();
    QRect geo5 = ui->navBox->geometry();
    QRect geo6 = ui->buttonBox->geometry();

    int yDiff = 145;

    if (windSourceMinimized == false){
        ui->waterDepthBox->setGeometry(geoX,geo4.y()-yDiff,geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()-yDiff,geoW,geo5.height());
        ui->buttonBox->setGeometry(geoX,geo6.y()-yDiff,geoW,geo6.height());
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()-yDiff);
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), r.width(), geo1.height()-yDiff);
        parametricDataEntry->resize(r.width(), geo1.height()-yDiff);
        ui->windSourceMin->setText("˅");
    }

    else if (windSourceMinimized == true){
        ui->waterDepthBox->setGeometry(geoX,geo4.y()+yDiff,geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()+yDiff,geoW,geo5.height());
        ui->buttonBox->setGeometry(geoX,geo6.y()+yDiff,geoW,geo6.height());
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()+yDiff);
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), r.width(), geo1.height()+yDiff);
        parametricDataEntry->resize(r.width(), geo1.height()+yDiff);
        ui->windSourceMin->setText("—");
    }

}

void Minimize::waterDepthMinimization(Ui::ParametricDataEntry *ui, bool waterDepthMinimized, QWidget *parametricDataEntry){
    QRect r = ui->centralwidgetPDE->geometry();
    QRect geo1 = ui->parametricBox->geometry();
    QRect geo4 = ui->waterDepthBox->geometry();
    QRect geo5 = ui->navBox->geometry();
    QRect geo6 = ui->buttonBox->geometry();

    int yDiff = 145;

    if (waterDepthMinimized == false){
        ui->waterDepthBox->setGeometry(geoX,geo4.y(),geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()-yDiff,geoW,geo5.height());
        ui->buttonBox->setGeometry(geoX,geo6.y()-yDiff,geoW,geo6.height());
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()-(yDiff+9));
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), r.width(), geo1.height()-(yDiff+9));
        parametricDataEntry->resize(r.width(), geo1.height()-(yDiff+10));
        ui->waterDepthMin->setText("˅");
    }

    else if (waterDepthMinimized == true){
        ui->waterDepthBox->setGeometry(geoX,geo4.y(),geoW,geo4.height());
        ui->navBox->setGeometry(geoX,geo5.y()+yDiff,geoW,geo5.height());
        ui->buttonBox->setGeometry(geoX,geo6.y()+yDiff,geoW,geo6.height());
        ui->parametricBox->setGeometry(0,geo1.y(),geo1.width(),geo1.height()+(yDiff+9));
        ui->centralwidgetPDE->setGeometry(r.x(),r.y(), r.width(), geo1.height()+(yDiff+9));
        parametricDataEntry->resize(r.width(), geo1.height()+(yDiff+10));
        ui->waterDepthMin->setText("—");
    }
}


