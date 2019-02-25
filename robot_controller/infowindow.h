#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QObject>
#include <QTextBrowser>
#include <QCheckBox>
#include <QGridLayout>
#include <QDebug>

class InfoWindow : public QObject
{
    Q_OBJECT
public:
    QGridLayout* layout;
    QTextBrowser* textBrowser;
    QCheckBox* checkBox[2];
    explicit InfoWindow(QWidget *parent = nullptr);

    bool showTimeStamp = 0;

signals:

public slots:
    void checkBoxFunction(int state);
    void ShowTimeStamp(int state);
    void autoscrolling();
};

#endif // INFOWINDOW_H
