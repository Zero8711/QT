#include "tab6database.h"
#include "ui_tab6database.h"

Tab6Database::Tab6Database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab6Database)
{
    ui->setupUi(this);
    sqlDb = QSqlDatabase::addDatabase("QSQLITE");
    sqlDb.setDatabaseName("state.db");
    if(sqlDb.open())
    {
        qDebug() << "Success DB Connection!";
    }
    else
    {
        qDebug() << "Access Denied!";
    }

    QString query = "CREATE TABLE state1_db (id integer primary key, date DATETIME, cds VARCHAR(10), temp VARCHAR(10), humi VARCHAR(10))";
    QSqlQuery qry;
    if(!qry.exec(query))
    {

    }
    else
    {
        qDebug() << "Create Table";
    }
    connect(ui->pPBSearch, SIGNAL(clicked()), this, SLOT(slotSearchDb()));
    connect(ui->pPBDelete, SIGNAL(clicked()), this, SLOT(slotDeleteDb()));
}

Tab6Database::~Tab6Database()
{
    delete ui;
}

void Tab6Database::slotTab6RecvData(QString recvData)
{
    qDebug() << recvData;
    QDateTime dateTime = QDateTime::currentDateTime();
    QSqlQuery qry;
    QString query;

    recvData.replace("[", "@");
    recvData.replace("]", "@");
    QStringList qlist = recvData.split("@");

    QString cds = qlist[3];//조도값
    QString temp = qlist[4];//온도값
    QString humi = qlist[5];//조도값
    query = "insert into state1_db(date, cds, temp, humi) values('" + dateTime.toString("yy/MM/dd hh:mm:ss") + "', '" + cds + "', '" + temp + "', '" + humi + "')";
    if(qry.exec(query))
    {
        qDebug() << "Insert Success!";
    }
    else
    {
        qDebug() << qry.lastError().text();
    }
}

void Tab6Database::slotSearchDb()
{
    QSqlQuery qry;
    QString query;
    qDebug() << "test";
    QDateTime dateTimeFrom = ui->pDTFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");

    QDateTime dateTimeTo = ui->pDTTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    int rowCount = 0;
    ui->pTState->clearContents();
    query = "select * from state1_db where date>'" + strFrom + "' AND date < '" + strTo + "'";
    if(qry.exec(query))
    {
        while(qry.next())
        {
            rowCount++;
            ui->pTState->setRowCount(rowCount);
            QTableWidgetItem *id = new QTableWidgetItem();
            QTableWidgetItem *date = new QTableWidgetItem();
            QTableWidgetItem *cds = new QTableWidgetItem();
            QTableWidgetItem *temp = new QTableWidgetItem();
            QTableWidgetItem *humi = new QTableWidgetItem();
            id->setText(qry.value("id").toString());
            date->setText(qry.value("date").toString());
            cds->setText(qry.value("cds").toString());
            temp->setText(qry.value("temp").toString());
            humi->setText(qry.value("humi").toString());
            ui->pTState->setItem(rowCount-1, 0, id);
            ui->pTState->setItem(rowCount-1, 1, date);
            ui->pTState->setItem(rowCount-1, 2, cds);
            ui->pTState->setItem(rowCount-1, 3, temp);
            ui->pTState->setItem(rowCount-1, 4, humi);
        }
    }
}
void Tab6Database::slotDeleteDb()
{
    QSqlQuery qry;
    QString query;

    QDateTime dateTimeFrom = ui->pDTFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");

    QDateTime dateTimeTo = ui->pDTTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    query = "delete from state1_db where date > '" + strFrom + "'AND date < '" + strTo + "'";
    if(qry.exec(query))
    {

    }
}
