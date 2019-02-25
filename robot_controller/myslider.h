#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QWidget>
#include <QSlider>
class MySlider : public QSlider
{
    Q_OBJECT
public:
    explicit MySlider(QWidget *parent = nullptr);

signals:

public slots:
    void updateValue(double val);
    void home();
};

#endif // MYSLIDER_H
