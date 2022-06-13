#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

Tab2SocketClient::Tab2SocketClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2SocketClient)
{
    ui->setupUi(this);
    pSocketClient = new SocketClient(this);
    ui->pPBSendButton->setEnabled(false);
    connect(ui->pPBServerConnect, SIGNAL(clicked(bool)), this, SLOT(slotConnectToServer(bool)));
    connect(ui->pPBSendButton, SIGNAL(clicked()), this, SLOT(slotSocketSendData()));
    connect(pSocketClient, SIGNAL(sigSocketRecv(QString)), this, SLOT(slotSocketRecvUpdate(QString)));
    connect(ui->pPBRecvDataClear, SIGNAL(clicked()), ui->pTERecvData, SLOT(clear()));
}

Tab2SocketClient::~Tab2SocketClient()
{
    delete ui;
}

void Tab2SocketClient::slotConnectToServer(bool check)
{
    bool bOK;
    if(check)
    {
        pSocketClient->slotConnectToServer(bOK);
        if(bOK)
        {
            ui->pPBServerConnect->setText("서버 해제");
            ui->pPBSendButton->setEnabled(true);
        }
    }
    else
    {
        pSocketClient->slotClosedByServer();
        ui->pPBServerConnect->setText("서버 연결");
        ui->pPBSendButton->setEnabled(false);
    }
}

void Tab2SocketClient::slotSocketRecvUpdate(QString strRecvData)
{
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
//    qDebug() << strTime;
    if(strRecvData.indexOf("LAMP") != -1 || strRecvData.indexOf("GAS") != -1)
    {
        emit sigTab3RecvData(strRecvData);
    }

    else if(strRecvData.indexOf("SENSOR") != -1)
    {
        emit sigTab5RecvData(strRecvData);
        emit sigTab6RecvData(strRecvData);
    }
    strRecvData = strTime + " " + strRecvData;
    strRecvData.chop(1);
    ui->pTERecvData->append(strRecvData);
    ui->pTERecvData->moveCursor(QTextCursor::End);
    emit sigTab4TossData(strRecvData);
}

void Tab2SocketClient::slotSocketSendData()
{
    QString strRecvId;
    QString strSendData;

    strRecvId = ui->pLERecvId->text();
    strSendData = ui->pLESendData->text();
    if(strRecvId.isEmpty())
    {
        strSendData = "[ALLMSG]" + strSendData;
    }
    else
    {
        strSendData = "[" + strRecvId + "]" + strSendData;
    }
    pSocketClient->slotSocketSendData(strSendData);
    ui->pLESendData->clear();
}

void Tab2SocketClient::slotSocketSendData(QString strData)
{
    if(ui->pPBServerConnect->isChecked())
    {
        pSocketClient->slotSocketSendData(strData);
    }
    else
    {
        QMessageBox::information(this, "socket", "서버 연결 확인");
    }
}

void Tab2SocketClient::slotSocketAgainRecv(QString strData)
{
    emit sigAgainRecv(strData);
}

void Tab2SocketClient::slotRecvDataClear()
{

}
