#include "tab5chartplot.h"
#include "ui_tab5chartplot.h"

Tab5ChartPlot::Tab5ChartPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab5ChartPlot)
{
    ui->setupUi(this);
    pCdsLine = new QLineSeries(this);
    pCdsLine->setName("조도");

    pTempLine = new QLineSeries(this);
    pTempLine->setName("온도");

    pHumiLine = new QLineSeries(this);
    pHumiLine->setName("습도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pCdsLine->setPen(pen);

    pen.setBrush(Qt::green);
    pTempLine->setPen(pen);

    pen.setBrush(Qt::blue);
    pHumiLine->setPen(pen);

    chart = new QChart();
    chart->addSeries(pCdsLine);
    chart->addSeries(pTempLine);
    chart->addSeries(pHumiLine);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);//y축
//    chart->axes(Qt::Horizontal).first()->setRange(0, 20);//x축
/*
    pCdsLine->append(0, 20);
    pCdsLine->append(5, 80);
    pCdsLine->append(10, 50);
    pCdsLine->append(15, 63);
    pCdsLine->append(20, 16);
*/

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->pChartHLayout->layout()->addWidget(chartView);

    axisX = new QDateTimeAxis;
    axisX->setFormat("h:mm");


    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    firstDate.setDate(date);
    firstDate.setTime(time);
    chartView->chart()->setAxisX(axisX, pCdsLine);
    chartView->chart()->setAxisX(axisX, pTempLine);
    chartView->chart()->setAxisX(axisX, pHumiLine);

    QTime tempTime = time.addSecs(3600);//1시간
    lastDate.setDate(date);
    lastDate.setTime(tempTime);
    axisX->setRange(firstDate, lastDate);

    connect(ui->pPBAdd, SIGNAL(clicked()), this, SLOT(CharPlotAdd()));
    connect(ui->pPBClear, SIGNAL(clicked()), this, SLOT(ChartPlotClear()));
}

Tab5ChartPlot::~Tab5ChartPlot()
{
    delete ui;
}

void Tab5ChartPlot::ChartPlotClear()
{
    pCdsLine->clear();
    pTempLine->clear();
    pHumiLine->clear();
}

void Tab5ChartPlot::CharPlotAdd()
{
    pCdsLine->append(ui->pLEx->text().toDouble(), ui->pLEy->text().toDouble());
    ui->pLEx->clear();
    ui->pLEy->clear();
}

void Tab5ChartPlot::slotTab5RecvData(QString recvData)
{
    qDebug() << recvData;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    recvData.replace("[", "@");
    recvData.replace("]", "@");
    QStringList qlist = recvData.split("@");

    pCdsLine->append(xValue.toMSecsSinceEpoch(), qlist[3].toDouble());
    pTempLine->append(xValue.toMSecsSinceEpoch(), qlist[4].toDouble());
    pHumiLine->append(xValue.toMSecsSinceEpoch(), qlist[5].toDouble());

}
