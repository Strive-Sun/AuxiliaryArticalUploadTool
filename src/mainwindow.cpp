#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , editorWindow(nullptr)
{
    ui->setupUi(this);
    
    // 设置窗口标题和大小
    setWindowTitle(tr("Qt Demo"));
    resize(400, 300);
    
    // 连接打开编辑器按钮的信号
    connect(ui->openEditorButton, &QPushButton::clicked,
            this, &MainWindow::onOpenEditorClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (editorWindow) {
        delete editorWindow;
    }
}

void MainWindow::onOpenEditorClicked()
{
    if (!editorWindow) {
        editorWindow = new EditorWindow();
    }
    editorWindow->show();
    editorWindow->raise();
    editorWindow->activateWindow();
} 