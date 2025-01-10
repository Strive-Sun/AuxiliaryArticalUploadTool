#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 设置应用程序信息
    QApplication::setApplicationName("文章编辑上传工具");
    QApplication::setApplicationDisplayName("文章编辑上传工具");
    QApplication::setOrganizationName("AuxiliaryArticalUploadTool");
    QApplication::setOrganizationDomain("com.example.auxiliaryarticaluploadtool");
    
    // 设置应用程序图标
    QApplication::setWindowIcon(QIcon(":/icons/app_icon.png"));
    
    MainWindow w;
    w.show();
    return a.exec();
} 