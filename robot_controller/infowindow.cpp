#include "infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) : QObject(parent)
{
    layout = new QGridLayout();
    textBrowser = new QTextBrowser(parent);
    textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    checkBox[0] = new QCheckBox(parent);
    checkBox[1] = new QCheckBox(parent);
    checkBox[0]->setText("Content autoscrolling");
    checkBox[1]->setText("Show time stamp");
    layout->addWidget(textBrowser,0,0,1,2);
    layout->addWidget(checkBox[0],1,0);
    layout->addWidget(checkBox[1],1,1);
    layout->setSpacing(10);

    connect(checkBox[0],SIGNAL(stateChanged(int)),this,SLOT(checkBoxFunction(int)));
    connect(checkBox[1],SIGNAL(stateChanged(int)),this,SLOT(ShowTimeStamp(int)));
}

void InfoWindow::autoscrolling()
{
    QTextCursor cursor =  textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    textBrowser->setTextCursor(cursor);
}

void InfoWindow::checkBoxFunction(int state)
{
    if(state == 2)
    {
        connect(this->textBrowser,SIGNAL(cursorPositionChanged()),this,SLOT(autoscrolling()));
    }else if(state == 0)
    {
        disconnect(this->textBrowser,SIGNAL(cursorPositionChanged()),this,SLOT(autoscrolling()));
    }
}

void InfoWindow::ShowTimeStamp(int state)
{
    if(state == 2)
    {
        showTimeStamp = 1;
    }else
    {
        showTimeStamp = 0;
    }
}
