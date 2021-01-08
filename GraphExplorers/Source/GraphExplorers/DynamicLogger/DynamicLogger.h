// ============================================================================
// <copyright file="DynamicLogger.h" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

#pragma once

/*
* Requirements: 
*                
*/

// Local includes, e.g. files in the same folder, typically corresponding declarations.


// System includes, e.g. STL, Library headers, ...
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <atomic>
#include <sstream>
#include <chrono>

// C related header files.
#include <stdio.h>
#include <time.h>

// Declarations

// Define constants

#define PRINTMANDATORY       0X00000001 // bit 0
#define PRINTINPUTGRAPHDATA  0X00000002 // bit 1
#define PRINTDFSDATA         0X00000004 // bit 2
/* add functioncality bits as we develop product.*/


namespace vrk
{

/**
 * @brief Log trace levels. 0 stands for no trace
 *                          1 stands for trace all.
 *                          2 stands for trace selected.
*/
enum class LogTraceLevelVal {
	NoTrace        = 0,
	TraceAll       = 1,
	TraceSelected  = 2
};

/**
 * @brief Requirements tracebility: LOGGER_DOF_001_IMPL_NonSIL <br>
          Dynamic logger provides generic functionality to enable logs dynamically.
 *        < Specific Functional ID>_IMPL_< SIL classification >
 *        
*/
class DynamicLogger {

public:
	/**
	 * @brief DynamicLogger is singleton class.
	 * @return returns instance of dynamic logger which will be used to log messages.
	*/

	static DynamicLogger& GetInstance() noexcept {
		//  Static variables with block scope are thread safe which is guaranteed by standard.
		static DynamicLogger instance;
		return instance;
	}

	/**
	 * @brief LogInfo is template function is used to print information logs. Example of usage is shown below <br>
	 *        <loggerinstance>.LogInfo(PRINTDFSDATA, "Number of vertices: ", m_graph.GetNumberOfVertices());
	 * @tparam ...Args LogInfo template function typename
	 * @param classMask mask to be used for log message which is used to check whether to be printed or not
	 * @param ...args log mesage to be printed.
	*/
	template <typename... Args>
	void LogInfo(int classMask, Args&& ... args) {
		if (m_TraceIsOn) {
			// redirect output to file.
			if (IsLogToBePrinted(classMask)) {
				std::streambuf* oldcoutbuf = std::cout.rdbuf();
				std::cout.set_rdbuf(m_logFile.rdbuf());
				std::cout << "INFO";
				std::cout << ":" << TimeStamp() << ":";
				log(args...);
				std::cout << std::endl;
				std::cout.set_rdbuf(oldcoutbuf);
			}
		}
	}

	/**
	 * @brief LogWarn is template function is used to print warning logs. Example of usage is shown below <br>
	 *        <loggerinstance>.LogWarn(PRINTDFSDATA, "Graph is empty");
	 * @tparam ...Args LogWarn template function typename
	 * @param classMask mask to be used for log message which is used to check whether to be printed or not
	 * @param ...args log mesage to be printed.
	*/
	template <typename... Args>
	void LogWarn(int classMask, Args&& ... args) {
		if (m_TraceIsOn) {
			if (IsLogToBePrinted(classMask)) {
				std::streambuf* oldcoutbuf = std::cout.rdbuf();
				std::cout.set_rdbuf(m_logFile.rdbuf());
				std::cout << "WARNING: ";
				std::cout << ":" << TimeStamp() << ":";
				log(args...);
				std::cout << std::endl;
				std::cout.set_rdbuf(oldcoutbuf);
			}
		}
	}

	/**
	 * @brief LogError is template function is used to print error logs. Example of usage is shown below <br>
	 *        <loggerinstance>.LogFError(PRINTDFSDATA, "Graph pointer is null");
	 * @tparam ...Args LogWarn template function typename
	 * @param classMask mask to be used for log message which is used to check whether to be printed or not
	 * @param ...args log mesage to be printed.
	*/
	template <typename... Args>
	void LogError(int classMask, Args&& ... args) {
		if (m_TraceIsOn) {
			if (IsLogToBePrinted(classMask)) {
				std::streambuf* oldcoutbuf = std::cout.rdbuf();
				std::cout.set_rdbuf(m_logFile.rdbuf());
				std::cout << "ERROR: ";
				std::cout << ":" << TimeStamp() << ":";
				log(args...);
				std::cout << std::endl;
				std::cout.set_rdbuf(oldcoutbuf);
			}
		}
	}

	/**
	 * @brief UpdateTraceSetting is used to set log traces dynamically.
	 * @param isTraceOn boolean type if true logs are printed.
	 * @param logTraceLevel trace level to be set to one of the values mentioned below
	 *               NoTrace, TraceAll, and TraceSelected
	 * @param traceClasses set according to functionality.
	*/
	void UpdateTraceSettings(bool isTraceOn, LogTraceLevelVal logTraceLevel, int traceClasses) {
		m_TraceIsOn = isTraceOn;
		m_TraceLevel = logTraceLevel;
		m_TraceClasses = traceClasses;
	}

private:

	// private methods.
	DynamicLogger() : m_logFile("..\\..\\..\\Logs\\logs.txt") {
		
	}
	~DynamicLogger() = default;
	DynamicLogger& operator=(const DynamicLogger&) = delete;

	// Private method to check if log to be printed,
	bool IsLogToBePrinted(int classMask) {

		switch (m_TraceLevel) {

		case LogTraceLevelVal::NoTrace:
			return false;
		case LogTraceLevelVal::TraceAll:
			return true;
		case LogTraceLevelVal::TraceSelected:
			if (classMask & m_TraceClasses) {
				return true;
			}
			break;
		default:
			break;
		}
		return false;
	}

	// Following are private methods to get time of log.
	typedef struct timeval {
		long long tv_sec;
		long long tv_usec;
	} timeval;

	int gettimeofday(struct timeval* tp, struct timezone* tzp) {
		namespace sc = std::chrono;
		sc::system_clock::duration d = sc::system_clock::now().time_since_epoch();
		sc::seconds s = sc::duration_cast<sc::seconds>(d);
		tp->tv_sec = s.count();
		tp->tv_usec = sc::duration_cast<sc::microseconds>(d - s).count();
		return 0;
	}

	std::string TimeStamp() {

		const int TIMESTAMPBUFFERSIZE    = 30;
		const int MILLISECONDSBUFFERSIZE = 10;
		struct timeval tmnow;
		struct tm tm;
		char timestampbuff[TIMESTAMPBUFFERSIZE];
		memset(timestampbuff, 0x00, sizeof(timestampbuff));
		char millisecondbuff[MILLISECONDSBUFFERSIZE];
		memset(millisecondbuff, 0x00, sizeof(millisecondbuff));
		gettimeofday(&tmnow, NULL);
		localtime_s(&tm, &tmnow.tv_sec);
		strftime(timestampbuff, TIMESTAMPBUFFERSIZE, "%Y:%m:%d:%H:%M:%S", &tm);
		int r = strcat_s(timestampbuff, sizeof(timestampbuff), ":");
		sprintf_s(millisecondbuff, sizeof(millisecondbuff), "%d", (int)tmnow.tv_usec);
		strcat_s(timestampbuff, sizeof(timestampbuff), millisecondbuff);
		return std::string(timestampbuff);
	}

	template <typename T>
	void log(T t) {
		std::cout << t << std::endl;
	}

	template<typename T, typename... Args>
	void log(T t, Args... args)  { // recursive variadic function
		std::cout << t << " ";
		log(args...);
	}
		
	// private variables
	std::atomic<bool>             m_TraceIsOn    = {true};
	std::atomic<LogTraceLevelVal> m_TraceLevel   = { LogTraceLevelVal::TraceAll };
	std::atomic<unsigned int>     m_TraceClasses = { PRINTMANDATORY };
	std::ofstream                 m_logFile;
};

	
}; // namespace ModbusTCPSigTrans
