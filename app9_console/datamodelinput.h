#ifndef DATAMODELINPUT_H
#define DATAMODELINPUT_H

#include <QVector>
#include <QPointF>

//  -----    участок исходной ломаной

struct DataModelInput
{
    std::vector<QPointF> points;
    //std::vector<Polynomial> polynomes;
    int number; // номер участка массива точек
};

#endif // DATAMODELINPUT_H
