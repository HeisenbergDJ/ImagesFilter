#include "ZLogger.h"
ZLogger* ZLogger::instance = NULL;

ZLogger::ZLogger() {

}

ZLogger* ZLogger::getInstance()
{
    if (!instance) {
        instance = new ZLogger();
    }
    return instance;
}

void ZLogger::log(string message)
{
    if (!m_logFile) return;
    time_t now = time(nullptr);
    struct tm localTime;
    localtime_s(&localTime, &now);
    char time_buffer[80];
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S: ", &localTime);
    long long a = sizeof(time_buffer);
    const char* msg_buffer = message.c_str();
    m_logFile->write(time_buffer, strlen(time_buffer)); 
    m_logFile->write(msg_buffer, strlen(msg_buffer));
    char endl_buffer[5] = "\n";
    m_logFile->write(endl_buffer, strlen(endl_buffer));
}

void ZLogger::createLogFile(string logFilePath)
{
    m_logFile = new ofstream();    
    m_logFile->open(logFilePath.c_str(), ios::out | ios::app);
}

void ZLogger::closeLogFile()
{
    m_logFile->close();
    delete m_logFile;
    m_logFile = nullptr;
}
