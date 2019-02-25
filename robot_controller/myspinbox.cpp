#include "myspinbox.h"

MySpinBox::MySpinBox(QWidget *parent)
{

}

void MySpinBox::updateValue(int val)
{
    double value = val/1000.0;
    setValue(value);
}
