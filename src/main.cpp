#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 设置应用程序信息
    QApplication::setApplicationName("文章编辑上传工具");
    QApplication::setApplicationDisplayName("文章编辑上传工具");
    QApplication::setOrganizationName("AuxiliaryArticalUploadTool");
    QApplication::setOrganizationDomain("com.example.auxiliaryarticaluploadtool");
    
    MainWindow w;
    w.show();
    return a.exec();
} 