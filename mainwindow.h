#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMessage();

private:
    QPushButton *button;
    QLabel *label;
    QWidget *centralWidget;
    QVBoxLayout *layout;
};

#endif // MAINWINDOW_H 