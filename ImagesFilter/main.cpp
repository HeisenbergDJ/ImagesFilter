#include "ImagesFilter.h"
#include <QtWidgets/QApplication>
#include "ZLogger.h"


bool checkCompleteness() {
    QString iniFilePath = qApp->applicationDirPath() + "/check.ini";
    return true;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //检查文件版本创建日志文件
    QString logFilePath = qApp->applicationDirPath() + "/ImageFilter.log";
    ZLogger::getInstance()->createLogFile(logFilePath.toStdString());
    ZLogger::getInstance()->log("打开软件");
    ImagesFilter w;
    w.show();
    return a.exec();
}
