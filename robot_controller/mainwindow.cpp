#include "mainwindow.h"

MainWindow::MainWindow(const QString &title)
{
    QGridLayout* layout = new QGridLayout(&window);
    window.setWindowTitle(title);
    //window.setFixedSize(QSize(1280,480));
    QDesktopWidget* desktop = QApplication::desktop();
    window.move((desktop->width() - window.width())/2, (desktop->height() - window.height())/2);    /*居中放置窗口*/
    slider = new Slider(&window,0,6284);    /* 创建滑动条交互块 */
    serial = new Serial(&window);   /* 创建串口交互块 */
    serial->setSlider(slider);
    SendInfoWindow = new InfoWindow(&window);   /* 创建串口信息发送浏览窗口 */
    ReceiveInfoWindow = new InfoWindow(&window);    /* 创建串口信息接收浏览窗口 */
    serial->setInfoWindow(SendInfoWindow, ReceiveInfoWindow);
    layout->addLayout(serial->layout,0,0,2,1);
    layout->addLayout(slider->layout,2,0,2,1);
    layout->addLayout(SendInfoWindow->layout,0,1,2,3);
    layout->addLayout(ReceiveInfoWindow->layout,2,1,2,3);
    layout->setColumnStretch(0,2);
    layout->setColumnStretch(1,1);
    layout->setSpacing(10);
    window.setLayout(layout);
    window.show();
}

void MainWindow::paintEvent(QPaintEvent *e){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}
