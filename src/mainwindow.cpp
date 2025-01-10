#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口标题和大小
    setWindowTitle("Qt Demo");
    resize(400, 300);

    // 创建中央部件
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建垂直布局
    layout = new QVBoxLayout(centralWidget);

    // 创建标签
    label = new QLabel("欢迎使用 Qt!", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    // 创建按钮
    button = new QPushButton("点击我", this);
    layout->addWidget(button);

    // 连接按钮的点击信号到槽函数
    connect(button, &QPushButton::clicked, this, &MainWindow::showMessage);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showMessage()
{
    QMessageBox::information(this, "消息", "这是一个 Qt 消息框示例！\n展示了以下 Qt 特性：\n- 窗口创建\n- 布局管理\n- 信号槽机制\n- 消息框");
} 