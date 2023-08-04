#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;



class __declspec(dllexport) ZLogger
{
private:
	static ZLogger* instance;
	ofstream *m_logFile = NULL;
	ZLogger();
public:
	static ZLogger* getInstance();
	void log(string message);
	void createLogFile(string logFilePath);
	void closeLogFile();

};


