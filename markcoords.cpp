#include "markcoords.h"

MarkCoords::MarkCoords(QObject *parent) : QObject(parent)
{
}

double MarkCoords::getLatitude()
{
    return _latitude;
}

void MarkCoords::setLatitude(double latitude)
{
    if(latitude != _latitude)
    {
        _latitude = latitude;

        emit latitudeChanged(latitude);
    }
}

double MarkCoords::getLongitude()
{
    return _longitude;
}

void MarkCoords::setLongitude(double longitude)
{
    if(longitude != _longitude)
    {
        _longitude = longitude;
        emit longitudeChanged(longitude);
    }
}
