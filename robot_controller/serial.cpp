#include "serial.h"

Serial::Serial(QWidget *parent)
{
    layout = new QGridLayout();
        for (int i=0;i<3;++i)
        {
            label[i] = new QLabel(parent);
            layout->addWidget(label[i],i,0);
        }
    label[0]->setText("selet COM:");
    label[1]->setText("Baud Rate:");
    label[2]->setText("Operation:");
        for (int i=0;i<5;++i)
        {
            pushButton[i] = new QPushButton(parent);
        }
    pushButton[0]->setText("Search COM");
    pushButton[1]->setText("Open COM");
    pushButton[2]->setText("Send");
    pushButton[3]->setText("Clear Send infoWindow");
    pushButton[4]->setText("Clear Receive infoWindow");
    layout->addWidget(pushButton[0],0,2);
    layout->addWidget(pushButton[1],2,1);
    layout->addWidget(pushButton[2],2,2);
    layout->addWidget(pushButton[3],3,1);
    layout->addWidget(pushButton[4],3,2);
        for (int i=0;i<2;++i)
        {
            comboBox[i] = new QComboBox(parent);
        }
    comboBox[1]->addItem("115200");
    comboBox[1]->addItem("9600");
    layout->addWidget(comboBox[0],0,1);
    layout->addWidget(comboBox[1],1,1);
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        {
            comboBox[0]->addItem(info.portName());
        }
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,2);
    layout->setColumnStretch(2,2);
    layout->setSpacing(10);

    connect(pushButton[0],SIGNAL(clicked()),this,SLOT(SearchCOM()));
    connect(pushButton[1],SIGNAL(clicked()),this,SLOT(OperateCOM()));
    connect(pushButton[2],SIGNAL(clicked()),this,SLOT(SerialSend()));
    connect(pushButton[3],SIGNAL(clicked()),this,SLOT(C_S_InfoWindow()));
    connect(pushButton[4],SIGNAL(clicked()),this,SLOT(C_R_InfoWindow()));
    connect(comboBox[0],SIGNAL(currentTextChanged(const QString)),this,SLOT(SerialChange(const QString)));

    SerialInit();
    connect(serial,SIGNAL(readyRead()),this,SLOT(ReadData()));
}

void Serial::SerialInit()
{
    serial = new QSerialPort();
        if(serial->isOpen())
        {
            serial->clear();
            serial->close();
        }
    serial->setPortName(comboBox[0]->currentText());
        if(!(serial->open(QIODevice::ReadWrite)))
        {
            qDebug()<<"falie to open"<<comboBox[0]->currentText();
        }else
        {
            qDebug()<<"open"<<comboBox[0]->currentText();
        }
        if(comboBox[1]->currentText() == "115200")  /* 设置波特率 */
        {
            serial->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
        }else if (comboBox[1]->currentText() == "9600")
        {
            serial->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
        }
        serial->setDataBits(QSerialPort::Data8);    /* 数据位为8位 */
        serial->setFlowControl(QSerialPort::NoFlowControl); /* 无流控制 */
        serial->setParity(QSerialPort::NoParity);   /* 无校验位 */
        serial->setStopBits(QSerialPort::OneStop);   /* 一位停止位 */
}

bool Serial::SerialOpen()
{
    serial->setPortName(comboBox[0]->currentText());

    if(!(serial->open(QIODevice::ReadWrite)))
    {
        qDebug()<<"falie to open"<<comboBox[0]->currentText();
        return 0;
    }else
    {
        qDebug()<<"open"<<comboBox[0]->currentText();
    }

    if(comboBox[1]->currentText() == "115200")  /* 设置波特率 */
    {
        serial->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
    }else if (comboBox[1]->currentText() == "9600")
    {
        serial->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
    }

    serial->setDataBits(QSerialPort::Data8);    /* 数据位为8位 */
    serial->setFlowControl(QSerialPort::NoFlowControl); /* 无流控制 */
    serial->setParity(QSerialPort::NoParity);   /* 无校验位 */
    serial->setStopBits(QSerialPort::OneStop);   /* 一位停止位 */
    return 1;
}

void Serial::SerialClose()
{
    if(serial->isOpen())
    {
        serial->clear();
        serial->close();
    }
    pushButton[1]->setText("Open COM");
}

void Serial::SearchCOM()
{
    comboBox[0]->clear();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        qDebug()<<"serialPortName:"<<info.portName();
        comboBox[0]->addItem(info.portName());
    }
}

void Serial::OperateCOM()
{
    if(pushButton[1]->text() == "Open COM" && SerialOpen()) /* 打开串口 */
    {
        pushButton[1]->setText("Close COM");    /* 如果成功打开串口,则改变按钮值 */
    }else if (pushButton[1]->text() == "Close COM") /* 关闭串口 */
    {
        SerialClose();
    }else      /* 如果打开串口失败,则显示弹窗 */
    {
        QMessageBox::critical(nullptr, "error", "faile to open "+comboBox[0]->currentText(), QMessageBox::Yes, QMessageBox::Yes);
    }
}

bool Serial::SerialSend()
{
    sendBuf[0] = 255;
    sendBuf[sendBufSize-1] = 255;   /* 首尾标志位 */
    int n = 0;
    for (int i=1;i<13;i+=3,++n)
    {
        sendBuf[i] = (_slider->checkBox[n]->checkState()/2)*((_slider->slider[n]->value())%254);
        sendBuf[i+1] = (_slider->checkBox[n]->checkState()/2)*((_slider->slider[n]->value())/254);
        sendBuf[i+2] = 0;
    }

    if(serial->isOpen())
    {
        for (int i = 0;i<sendBufSize;++i) {
            WriteUnChar(sendBuf[i]);
        }

        _S_InfoWindow->textBrowser->insertPlainText("[");
        for(int i = 0;i<sendBufSize;++i)
        {
            _S_InfoWindow->textBrowser->insertPlainText(QString::number(sendBuf[i],10));
            if(i!=sendBufSize-1) _S_InfoWindow->textBrowser->insertPlainText(",");
        }
        _S_InfoWindow->textBrowser->insertPlainText("] ");
        if(_S_InfoWindow->showTimeStamp == 1)
        {
            QDateTime current_date_time = QDateTime::currentDateTime();
            _S_InfoWindow->textBrowser->insertPlainText(current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz"));
        }
        _S_InfoWindow->textBrowser->insertPlainText("\n");
    }else
    {
        QMessageBox::warning(nullptr, "warning", "Haven't open "+comboBox[0]->currentText(), QMessageBox::Yes, QMessageBox::Yes);
    }
    return 1;
}

void Serial::setSlider(Slider* s)
{
    _slider = s;
}

void Serial::setInfoWindow(InfoWindow* s_i, InfoWindow* r_i)
{
    _S_InfoWindow = s_i;
    _R_InfoWindow = r_i;
}

void Serial::WriteUnChar(quint8 p)
{
    unsigned char valueCh = static_cast<unsigned char>(p);
    serial->write(reinterpret_cast<const char*>(&valueCh),1);
}

void Serial::ReadData()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        _R_InfoWindow->textBrowser->insertPlainText("[");
        for(int i = 0;i<sendBufSize;++i)
        {
            _R_InfoWindow->textBrowser->insertPlainText(QString::number(buf[i],10));
            if(i!=sendBufSize-1) _R_InfoWindow->textBrowser->insertPlainText(",");
        }
        _R_InfoWindow->textBrowser->insertPlainText("] ");
        if(_R_InfoWindow->showTimeStamp == 1)
        {
            QDateTime current_date_time = QDateTime::currentDateTime();
            _R_InfoWindow->textBrowser->insertPlainText(current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz"));
        }
        _R_InfoWindow->textBrowser->insertPlainText("\n");
    }
    buf.clear();
}

void Serial::C_S_InfoWindow()
{
    _S_InfoWindow->textBrowser->setPlainText("");
}

void Serial::C_R_InfoWindow()
{
    _R_InfoWindow->textBrowser->setPlainText("");
}

void Serial::SerialChange(const QString &text)
{
    if(serial->isOpen())
    {
        serial->clear();
        serial->close();
    }
    pushButton[1]->setText("Open COM");
}
