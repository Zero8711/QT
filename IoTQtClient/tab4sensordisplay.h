#ifndef TAB4SENSORDISPLAY_H
#define TAB4SENSORDISPLAY_H

#include <QWidget>
#include <QDebug>
#include "socketclient.h"

namespace Ui {
class Tab4SensorDisplay;
}

class Tab4SensorDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit Tab4SensorDisplay(QWidget *parent = nullptr);
    ~Tab4SensorDisplay();

private:
    Ui::Tab4SensorDisplay *ui;
//    SocketClient *pSocketClient;

private slots:
    void slotTab4AgainRecv(QString);
};

#endif // TAB4SENSORDISPLAY_H
