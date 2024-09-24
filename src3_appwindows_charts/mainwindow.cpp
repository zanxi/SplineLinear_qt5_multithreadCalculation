#include "mainwindow.h"
#include <QApplication>

#include <QFileDialog>
#include <QMessageBox>

#include <iostream>
#include <fstream>
#include <qDebug>


#include "NumericalCalculation/interpolation.h"
#include "ui_mainwindow.h"

#include "Plots/lightmarkerswidget.h"



qreal MainWindow::theta(qreal x){ return (x<0)?0:1; }
qreal MainWindow::f2(qreal x) { return (x<4)?(2*theta(2*x)):
               ((x<14)?3*theta(x+2):4*theta(x-2)); }

qreal MainWindow::f(qreal x) { return (0+rand()%20)+rand()%37; }
//qreal MainWindow::f(qreal x) { return 100*sin(x); }


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);


  setGeometry(QRect(50, 50, 90, 900));


/*
  pathFileData = QApplication::applicationDirPath()+"/"+ "points.txt";
  {
      std::ofstream out;
      out.open(pathFileData.toStdString());
      out.close();
  }
  {

      std::ofstream out;
      out.open(pathFileData.toStdString(),std::ios::app);

      //out<<seriesIn->points()[seriesIn->points().size()-1].x()<<" "<<seriesIn->points()[seriesIn->points().size()-1].y()<<"\n";
      //out.open(fn);
      if(out.is_open())
      {
          for(int i=0; i<50;i++){
              out<<this->x<<" "<<this->y<<"\n";
              x+=h;
              y=f(x);
          }
      }
      out.close();
  }


  return;

/**/

  // start workers
  resp = new Responder(this);
  // ------------


  // отрисовка графиков
    //pathFileData = QApplication::applicationDirPath()+"/"+ "pointsInput.txt";

    series = new QLineSeries;
    seriesIn = new QLineSeries;

    qDebug()<<"input pixels: "<<resp->getInputPoints().size();
    for (QPointF p : resp->getInputPoints()) *seriesIn<<p; // исходные точки

    //loadFile();
    //calculateInterpolation();

    constexpr qreal marker_size = 12.;
    constexpr qreal marker_sizeIn = 40.;
    //seriesIn->setLightMarker(rectangle(marker_sizeIn, Qt::red));


    chart = new Chart;
    chart->addSeries(seriesIn);
    chart->setTitle("Input/Ouput(interpolation) points");

    chart->addSeries(series);
    chart->createDefaultAxes();

    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    this->ui->verticalLayout_plot->addWidget(chartView);
    resize(800, 700);
    //grabGesture(Qt::PanGesture);
    //grabGesture(Qt::PinchGesture);

    // чтение точек ломанной и интерполяцинной функции


    m_timer = new QTimer(this);
    QObject::connect(m_timer, &QTimer::timeout, this, &MainWindow::handleTimeout);
    m_timer->start(1000);

}

QImage MainWindow::rectangle(qreal imageSize, const QColor &color)
{
    QImage image(imageSize, imageSize, QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&image);
    painter.fillRect(0, 0, imageSize, imageSize, color);
    painter.end();
    return image;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    ui->lineEdit_info->setText(QString("X: %1").arg(chart->mapToValue(event->pos()).x()));
    ui->lineEdit_info->setText(QString("Y: %1").arg(chart->mapToValue(event->pos()).y()));

    QWidget::mouseMoveEvent(event);
}

void MainWindow::handleTimeout()
{

    QString pathFileDataInterpolationOutput = QApplication::applicationDirPath()+"/"+ "pointsOuput.txt";
    {
        std::ofstream out;
        out.open(pathFileDataInterpolationOutput.toStdString());
        out.close();
    }
    //return;

    {
        std::ofstream out;
        out.open(pathFileDataInterpolationOutput.toStdString(),std::ios::app);

        if(out.is_open())
        {
            qDebug()<<"handled number: ";            
            for (auto const &[key,value] : resp->getMapPoints())
            //for(int i=0; i<resp->getMapPoints().size();i++)
            {
                   for (QPointF p : value.points) {
                    series->append((qreal)p.x(),(qreal)p.y());
                    out<<(qreal)p.x()<<"; "<<(qreal)p.y()<<"\n";
                        qDebug()<<(qreal)p.x()<<" "<<(qreal)p.y();
                  }
            }
        }
        out.close();
    }


    return;

    //    if (m_x >= 100)
    //        m_timer.stop();
}



MainWindow::~MainWindow() { delete ui; }

void MainWindow::Plot() {
    return;

                                          {
        //*seriesInTemp->clear();
        // исходные точки (считанные из файла)

        series->clear();
        seriesIn->clear();
        for (QPointF p : this->spline.points) {
            *seriesIn <<p;
            x=p.x();
            y=p.y();
            //*seriesInTemp <<p;
        }
                                          }

                                          {
        // точки полученные интерполяцией сплайном
        std::vector<Polynomial> polynomes = this->spline.Interpolate();
        //return;
        //xs.clear(); ys.clear();

        for (Polynomial p : polynomes) {
            for (double x = p.from; x <= p.to; x += STEP2) {
                //xs.push_back(x);
                //ys.push_back(p.GetValue(x));

                QPointF p_i(x, p.GetValue(x));
                *series<<p_i;
            }
        }

        //auto x_minmax = std::minmax_element(xs.begin(), xs.end());
        //auto y_minmax = std::minmax_element(ys.begin(), ys.end());
                                          }

}

void MainWindow::loadFile() {
}

void MainWindow::calculateInterpolation() {
  try {
    this->spline = Interpolation::FromFile(this->data_file_full_path);
    Plot();
  } catch (std::exception& e) {
    QMessageBox msg;
    msg.setText(e.what());
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();
  }
}
