#ifndef MARKCOORDS_H
#define MARKCOORDS_H

#include "config.h"

#include <QObject>

class MarkCoords : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double latitude READ getLatitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ getLongitude WRITE setLongitude NOTIFY longitudeChanged)

    Q_SIGNALS:
        void latitudeChanged(double latitude);
        void longitudeChanged(double longitude);

    public:
        MarkCoords(QObject *parent = 0);

        double getLatitude();
        void setLatitude(double latitude);

        double getLongitude();
        void setLongitude(double longitude);

    private:
        double _latitude;
        double _longitude;
};
#endif // MARKCOORDS_H
