#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(5);

    pTab2SocketClient = new Tab2SocketClient(ui->pTab2);
    ui->pTab2->setLayout(pTab2SocketClient->layout());

    pTab3ControlPannel = new Tab3ControlPannel(ui->pTab3);
    ui->pTab3->setLayout(pTab3ControlPannel->layout());
    connect(pTab2SocketClient, SIGNAL(sigTab3RecvData(QString)), pTab3ControlPannel, SLOT(slotTab3RecvData(QString)));
    connect(pTab3ControlPannel, SIGNAL(sigSocketSendData(QString)), pTab2SocketClient, SLOT(slotSocketSendData(QString)));

    pTab4SensorDisplay = new Tab4SensorDisplay(ui->pTab4);
    ui->pTab4->setLayout(pTab4SensorDisplay->layout());
    connect(pTab2SocketClient, SIGNAL(sigTab4recvData(QString)), pTab4SensorDisplay, SLOT(slotTab4RecvData(QString)));
    connect(pTab2SocketClient, SIGNAL(sigTab4TossData(QString)), pTab4SensorDisplay, SLOT(slotTab4AgainRecv(QString)));

    pTab5ChartPlot = new Tab5ChartPlot(ui->pTab5);
    ui->pTab5->setLayout(pTab5ChartPlot->layout());
    connect(pTab2SocketClient, SIGNAL(sigTab5RecvData(QString)), pTab5ChartPlot, SLOT(slotTab5RecvData(QString)));

    pTab6Database = new Tab6Database(ui->pTab6);
    ui->pTab6->setLayout(pTab6Database->layout());
    connect(pTab2SocketClient, SIGNAL(sigTab6RecvData(QString)), pTab6Database, SLOT(slotTab6RecvData(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

