#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    int screenWidth,screenHeight;
    QDesktopWidget desktop;

    screenHeight=desktop.geometry().height()/4;
    screenWidth=desktop.geometry().width()/4;


    this->setWindowTitle("Converter");
    mainWidget=new QWidget(this);
    mainWidget->setGeometry(0,0,screenWidth,screenHeight);
    this->setFixedSize(screenWidth,screenHeight);

    mainLayout=new QGridLayout;
    mainWidget->setLayout(mainLayout);

    mainLayout->addWidget(new QLabel("Integer value: "),0,0);
    decEdit=new QLineEdit;
    decEdit->setPlaceholderText("0");
    decEdit->setValidator(new QIntValidator(0,100000));
    mainLayout->addWidget(decEdit,0,1);

    mainLayout->addWidget(new QLabel("Binary result: "),1,0);
    binResult=new QLabel;
    binResult->setText("0");
    mainLayout->addWidget(binResult,1,1);

    mainLayout->addWidget(new QLabel("Gray result: "),2,0);
    grayResult=new QLabel;
    grayResult->setText("0");
    mainLayout->addWidget(grayResult,2,1);

    mainLayout->addWidget(new QLabel("Restore gray: "),3,0);
    restoreGrayResult=new QLabel;
    restoreGrayResult->setText("0");
    mainLayout->addWidget(restoreGrayResult,3,1);

    mainLayout->addWidget(new QLabel(""),4,0);
    convertButton=new QPushButton;
    convertButton->setText("Convert");
    mainLayout->addWidget(convertButton,4,1);
    connect(convertButton,SIGNAL(clicked(bool)),this,SLOT(convertSlot()));
}

QString reverse(QString x)
{
    QString s="";
    for(int i=x.size()-1;i>=0;i--)
        s=s+x[i];
    return s;
}

QString dec2bin(int x)
{
    QString y="";
    while(x!=0)
    {
        y = y + QString::number(x %2);
        x=x/2;
    }
    return reverse(y);
}

QString bin2gray(QString b)
{
    QString    g="";
    g=b[0];
    for(int k=1;k<b.size();k++)
    {
        ;
        int v1=b[k-1].toLatin1()-'0';
        int v2=b[k].toLatin1()-'0';
        int v3=v1 ^ v2;
        g=g+QString::number(v3);
    }
    return g;
}

QString gray2bin(QString g)
{
    QString b="";
    int value=g[0].toLatin1()-'0';
    b=g[0];
    for(int k=1;k<g.size();k++)
    {
        if(g[k]=='1')
        {
            value =!value;
        }
        b=b+QString::number(value);
    }
    return b;
}

void    MainWindow::convertSlot()
{
    int value=decEdit->text().toInt();
    QString s=dec2bin(value);
    binResult->setText(s);
    QString g=bin2gray(s);
    grayResult->setText(g);
    QString b=gray2bin(g);
    restoreGrayResult->setText(b);
}

MainWindow::~MainWindow()
{

}
