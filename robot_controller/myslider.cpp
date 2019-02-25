#include "myslider.h"

MySlider::MySlider(QWidget *parent)
{

}

void MySlider::updateValue(double val)
{
    int value = int(val*1000);
    setValue(value);
}

void MySlider::home()
{
    setValue((maximum()+minimum())/2);
}
