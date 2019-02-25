#ifndef MYSPINBOX_H
#define MYSPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>

class MySpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit MySpinBox(QWidget *parent = nullptr);

signals:

public slots:
    void updateValue(int val);
};

#endif // MYSPINBOX_H
