#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
# include <QLineEdit>
# include <QLabel>
# include <QPushButton>
# include <QGridLayout>
# include <QDesktopWidget>
# include <QIntValidator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLineEdit *decEdit;
    QLabel *binResult,*grayResult,*restoreGrayResult;
    QWidget *mainWidget;
    QGridLayout *mainLayout;
    QPushButton *convertButton;
public slots:
     void convertSlot();
};

#endif // MAINWINDOW_H
