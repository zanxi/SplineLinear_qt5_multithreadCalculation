#include "responder.h"

//sig_atomic_t signal_caught = 0;
mutex logMutex;

#include <iostream>
#include <fstream>
#include <QTextStream>

#include <QApplication>
#include <QDebug>

#include <csignal>
#include <map>

#include "debug/logger.h"



sig_atomic_t signal_caught = 0;

void sigint_handler(int sig)
{
    signal_caught = 1;

}



map_DataModelIntrpolation safe_DataIntrepolation;
//std::map<int, DataModelInterpolation> safe_DataIntrepolation;

//void safeDataInterpolation(map_DataModelIntrpolation &safe_DataIntrepolation, DataModelInput dmi)
void safeDataInterpolation(DataModelInput dmi)
{
    std::lock_guard<std::mutex> lock(logMutex);


    Interpolation spline = Interpolation::GetInputPoints(dmi.points);
    std::vector<Polynomial> polynomes = spline.Interpolate();

    DataModelInterpolation dminterpolation;
    dminterpolation.number = dmi.number;

    //logger::WriteDebug_safeMapInterpolation(QString::number(dmi.number).toStdString());
    //logger::WriteDebug_safeMapInterpolation(""+std::to_string(dmi.number));


    for (Polynomial p : polynomes) {
        for (double x = p.from; x <= p.to; x += 1e-2) {
            dminterpolation.points.push_back(QPointF(x,p.GetValue(x)));
            //qDebug()<<;
        }
    }

    logger::WriteDebug_safeMapInterpolation("number:"+std::to_string(dminterpolation.number)+ "; vector size:"+std::to_string(dminterpolation.points.size()));

    safe_DataIntrepolation.insert(std::map<int, DataModelInterpolation>::value_type(dmi.number,dminterpolation));
    //safe_DataIntrepolation.s;


    //this_thread::sleep_for(chrono::seconds(10));
}

void logFnc(string text)
{
    std::lock_guard<std::mutex> lock(logMutex);
    qDebug()<<QString::fromStdString(text);

}

Responder::Responder(QObject *parent):
    QObject(parent)
{    

    //t_m = new std::thread(&Responder::StartInterpolation, this);
    setInputVector(QApplication::applicationDirPath()+"/"+ "points.txt");
    StartInterpolation();
    SaveInterpolationData(QApplication::applicationDirPath()+"/"+ "pointsOutput.txt");
}

map_DataModelIntrpolation Responder::getMapPoints()
{
    return ::safe_DataIntrepolation;
};

void Responder::SaveInterpolationData(QString pathFileSave)
{

    {
        std::ofstream out;
        out.open(pathFileSave.toStdString());
        out.close();
    }
    {

    std::ofstream out;
    out.open(pathFileSave.toStdString(),std::ios::app);

    if(out.is_open())
    {
        for (auto const &[key,value] : this->getMapPoints())
        {
            for (QPointF p : value.points) {
                out<<(qreal)p.x()<<"; "<<(qreal)p.y()<<"\n";
            }
        }
    }
    out.close();
    }
    qDebug()<<"Save interpolation data";
}

Responder::~Responder()
{
    dispatcher::stop();
    this_thread::sleep_for(chrono::seconds(2));
    t_m = 0;

}

void Responder::StartInterpolation()
{        

    //signal(SIGINT, &::sigint_handler);
    dispatcher::init(20);
    int number = 0;
    Request* rq = 0;
    std::vector<QPointF> pointTemp;
    //while(!signal_caught&&cycles<50)
    //while(cycles<15)
    for(int i=0; i<allPoints.size();i++)
    {
        pointTemp.push_back(allPoints[i]);
        if(i%15==14){
            DataModelInput di;
            di.number = number;
            if(i>0)pointTemp.push_back(allPoints[i-1]); // добавляем последнюю точку с предыдущего участка для сглаживания
            di.points=pointTemp;
            logger::WriteDebug_Responder(std::string("number vector points: ")+std::to_string(di.number)+"; size: "+std::to_string(pointTemp.size()));

            rq = new Request();
            rq->setValue(di);
            rq->setOutput(::logFnc);
            rq->setOutput(::safeDataInterpolation);
            dispatcher::addRequest(rq);
            number++;
            pointTemp.clear();
        }

    }

    //return;
    while(::safe_DataIntrepolation.size()<allPoints.size()/15)
    {
        this_thread::sleep_for(chrono::seconds(1));
        logger::WriteDebug_Responder("in work vectors: "+safe_DataIntrepolation.size());
    }


    //this_thread::sleep_for(chrono::seconds(15));

    dispatcher::stop();

}

std::vector<QPointF> Responder::getPoints(int i)
{
    return ::safe_DataIntrepolation[i].points;
}

void Responder::setInputVector(QString pathFile)
{
    this->pathFile = pathFile;

    QFile file(pathFile);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error(file.errorString().toStdString());
    }

    logger::WriteDebug_Responder(pathFile.toStdString());

    //return;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        QStringList fields = line.split(' ');
        if (fields.length() == 2) {
            QPointF point(fields[0].toDouble(), fields[1].toDouble());
            allPoints.push_back(point);
        }
    }
    file.close();

    std::sort(allPoints.begin(), allPoints.end(),
              [](QPointF a, QPointF b) { return (a.x() < b.x()); });

    //result.check_points();
    //return result;

//    std::ofstream out;
//    out.open(path.toStdString(),std::ios::in);
//    //out.open(fn);
//    if(out.is_open())
//    {
//        double h=0.4;
//        double x=0;//(rand()%1000/37.0);
//        for(int i=0; i<1220;i++)
//        {
//            x+=h;//(rand()%1000/37.0);
//            double y=  g(x); // 100*sin(x*x);//(rand()%1000/37.0);
//            //out<<x<<" "<<" "<<" "<<y<<"\n";
//            out<<x<<" "<<y<<"\n";
//        }
//    }
//    out.close();
}
