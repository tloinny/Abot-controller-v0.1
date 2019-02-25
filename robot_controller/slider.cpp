#include "slider.h"

/**
 * @function Slider构造函数
 * @parma
 *      parent:Slider类的父类
 *      min:滑动条最小值
 *      max:滑动条最大值
 */
Slider::Slider(QWidget *parent, int min, int max)
{
    layout = new QGridLayout();
    for (i = 0;i<NUM;++i) /* 包括六条滑动条、六个单行文本框、六个复选框 */
    {
        slider[i] = new MySlider(parent);   /* 创建滑动条 */
        slider[i]->setOrientation(Qt::Horizontal);
        slider[i]->setMinimum(min);    /* 设置滑动条最小最大值 */
        slider[i]->setMaximum(max);
        slider[i]->setValue(int((max-min)/2)); /* 设置滑动条初始值 */
        slider[i]->setSingleStep(1);   /* 设置步长 */

        doubleSpinBox[i] = new MySpinBox(parent); /* 创建单行文本框 */
        doubleSpinBox[i]->setSingleStep(0.001);
        doubleSpinBox[i]->setDecimals(3);
        InitValue((max-min)/2); /* 设置单行文本框初始值 */

        checkBox[i] = new QCheckBox(parent);    /* 创建复选框 */
        QString str1 = "AXIS";
        QString str2 = QString::number(i,10);
        QString str = str1+str2;
        checkBox[i]->setText(str);  /* 设置复选框文本值 */

        pushButton[i] = new QPushButton(parent);
        QString str3 = "H";
        pushButton[i]->setText(str3+str2);

        layout->addWidget(checkBox[i], i, 0);   /* 添加到组件布局管理器中 */
        layout->addWidget(slider[i], i, 1);
        layout->addWidget(doubleSpinBox[i], i, 2);
        layout->addWidget(pushButton[i],i,3);
        layout->setColumnStretch(0,1);
        layout->setColumnStretch(1,9);
        layout->setColumnStretch(2,1);
        layout->setColumnStretch(3,1);
        layout->setSpacing(10);

        connect(slider[i], SIGNAL(valueChanged(int)), doubleSpinBox[i], SLOT(updateValue(int)));
        connect(doubleSpinBox[i],SIGNAL(valueChanged(double)),slider[i],SLOT(updateValue(double)));
        connect(pushButton[i],SIGNAL(clicked()),slider[i],SLOT(home()));
    }
}

/**
 * @function 更新浮点值到doubleSpinBox
 * @parma
 *      val:用户输入的int值，将会被除以1000，以浮点值的形式更新到doubleSpinBox
 */
void Slider::InitValue(int val)
{
    double value = val/1000.0;
    doubleSpinBox[i]->setValue(value);
}

