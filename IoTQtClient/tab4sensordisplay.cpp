#include "tab4sensordisplay.h"
#include "ui_tab4sensordisplay.h"

Tab4SensorDisplay::Tab4SensorDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab4SensorDisplay)
{
    ui->setupUi(this);
//    connect(pSocketClient, SIGNAL(sigSocketRecv(QString)), this, SLOT(slotSocketRecvUpdate(QString)));
}

Tab4SensorDisplay::~Tab4SensorDisplay()
{
    delete ui;
}

void Tab4SensorDisplay::slotTab4AgainRecv(QString recvData)
{
    if(recvData.indexOf("New") > 0){}
    else
    {
    recvData.replace("[", "@");
    recvData.replace("]", "@");
    QStringList qlist = recvData.split("@");
    qDebug() << recvData;
    qDebug() << qlist[3] + " " + qlist[4] + " " + qlist[5];
    ui->pPhotoValue->setText(qlist[3]);
    ui->pTempValue->setText(qlist[4] + "C");
    ui->pHumiValue->setText(qlist[5] + "%");
    }
}
