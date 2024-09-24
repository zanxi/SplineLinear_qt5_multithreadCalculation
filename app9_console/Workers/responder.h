#ifndef RESPONDER_H
#define RESPONDER_H

#include <QObject>

#include "dispatcher.h"
#include "request.h"

#include <iostream>
#include <string>
#include <csignal>
#include <thread>
#include <chrono>

#include "NumericalCalculation/interpolation.h"

using namespace std;

//Класс иногопточных вычилений - для задачи интерполяцмм и т.д.
// использует классы:
//  -----  worker - обработка части общей ломаной точек
//  -----  Request - (задание для воркера) получает SetValue участок кривой в виде DataModelInput(номер участка, вектор точек)
//  -----            и отадет setOutput DataModelInterpolation(номер участка, интерполяционный вектор точек)
//  -----            записывает с потоконезависимую мапу safe_DataModel<int, DataModelInterpolation>
//  -----  Dispatcher - создание многопоточного диспетчера



class Responder : public QObject
{
    Q_OBJECT
public:
    Responder(QObject *parent = nullptr);
    ~Responder();
    void StartInterpolation();
    void setInputVector(QString pathFile);
    //void Stop(){ dispatcher::stop(); };
    std::vector<QPointF> getPoints(int i);
    const double STEP = 1e-2;

private:
   QString pathFile;
    std::vector<QPointF> allPoints;
   Interpolation spline;
    //map_DataModelIntrpolation DataIn;
   map_DataModelIntrpolation safe_DataIntrepolate;
   map_DataModelIntrpolation getMapPoints();
   void SaveInterpolationData(QString pathFile);

   std::thread *t_m = 0;

};

#endif // RESPONDER_H
