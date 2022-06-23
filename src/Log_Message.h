#pragma once
#include <fstream>
#include <cstdlib>

#define LOG_FILE "./store/log_message"
#define INFO 0
#define WARNING 1
#define ERROR 2
const char* log_statue[4] = {"INFO", "WARNING", "ERROR"};

class Log_Message
{
public:
	void log_message(int type);

private:
	std::ofstream _log_writer;
};

void Log_Message::log_message(int type)
{
	_log_writer.open(LOG_FILE);
	_log_writer << '[' << log_statue[type] << "]: ";
}