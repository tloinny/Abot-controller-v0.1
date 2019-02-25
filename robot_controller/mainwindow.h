#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "slider.h"
#include "serial.h"
#include "infowindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QStyleOption>

class MainWindow:public QWidget
{
public:
    /* 窗口内所有的组件 */
    QWidget window; /* 父窗口：所有组件都在这个窗口下实现 */
    Slider* slider; /* 滑动控制块 */
    Serial* serial; /* 串口交互通信模块 */
    InfoWindow* SendInfoWindow;
    InfoWindow* ReceiveInfoWindow;

    MainWindow(const QString &title);

    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
