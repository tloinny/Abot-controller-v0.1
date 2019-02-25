#ifndef SLIDER_H
#define SLIDER_H
#include <QSlider>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "myspinbox.h"
#include "myslider.h"

#include <string>

#define NUM 4

class Slider : public QObject
{
    Q_OBJECT
public:
    /* 包括六条滑动条、六个单行文本框、六个复选框 */
    MySlider* slider[NUM];
    QPushButton* pushButton[NUM];
    MySpinBox* doubleSpinBox[NUM];
    QCheckBox* checkBox[NUM];
    QGridLayout* layout;
    explicit Slider(QWidget *parent = nullptr, int min = 0, int max = 0);

private:
    int i;
    void InitValue(int val);

signals:

public slots:
};

#endif // SLIDER_H

