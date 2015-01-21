
#include <iostream>

#include "../src/log4cplus/configurator.h"
#include "../src/log4cplus/loggingmacros.h"
#include "../src/log4cplus/customappender.h"
#include "../src/log4cplus/loglog.h"

using namespace std;
using namespace log4cplus;

static Logger logFile1 = Logger::getInstance("logFile1");
static Logger logFile2 = Logger::getInstance("logFile2");

#ifdef _WIN32
void __stdcall customFunc(const char* sz)
{
	OutputDebugString(sz);
}
#else //__linux__
void customFunc(const char* sz)
{
	//
}
#endif


int main()
{
	log4cplus::CustomAppender::setCustomFunc(customFunc);
	log4cplus::PropertyConfigurator::doConfigure("urconfig.properties");
	LogLog::getLogLog()->setInternalDebugging(true);

	for (int i = 0; i < 3; i++)
	{
		LOG4CPLUS_DEBUG(logFile1,	"1 logFile1.\n");
		LOG4CPLUS_INFO(logFile1,	"2 logFile1.\n");
		LOG4CPLUS_ERROR(logFile1,	"4 logFile1.\n");
		LOG4CPLUS_FATAL(logFile1,	"5 logFile1.\n");

		LOG4CPLUS_DEBUG(logFile2,	"1 logFile2.\n");
		LOG4CPLUS_INFO(logFile2,	"2 logFile2.\n");
		LOG4CPLUS_ERROR(logFile2,	"4 logFile2.\n");
		LOG4CPLUS_FATAL(logFile2,	"5 logFile2.\n");
	}

	return 0;
}


