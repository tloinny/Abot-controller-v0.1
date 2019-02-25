#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QLatin1String>
#include <QDateTime>
#include "slider.h"
#include "infowindow.h"

class Serial : public QObject
{
    Q_OBJECT
public:
    QSerialPort* serial;
    QGridLayout* layout;
    QPushButton* pushButton[5];
    QComboBox* comboBox[2];
    QLabel* label[3];
    static const int sendBufSize = 3*4+2;
    explicit Serial(QWidget *parent = nullptr);
    void setSlider(Slider* s);
    void setInfoWindow(InfoWindow* s_i, InfoWindow* r_i);

private:
    void SerialInit();
    bool SerialOpen();
    void SerialClose();
    void WriteUnChar(quint8 p);
    unsigned char sendBuf[sendBufSize];
    unsigned char receiveBuf[100];

    Slider* _slider;
    InfoWindow* _S_InfoWindow;
    InfoWindow* _R_InfoWindow;

signals:

public slots:
    void SearchCOM();
    void OperateCOM();
    bool SerialSend();
    void ReadData();
    void C_S_InfoWindow();
    void C_R_InfoWindow();
    void SerialChange(const QString &text);
};

#endif // SERIAL_H
