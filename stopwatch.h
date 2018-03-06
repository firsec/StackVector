#pragma once

#include <chrono>

#ifdef _WIN32
#include "windows.h"
#endif

//A stopwatch function provider that offers clock tick accuracy
class Stopwatch {
	//holds the platform data required to initialize the stopwatch
private:
	struct StopwatchInitializer {
	public:
		double nanosecondsPerTick;
		bool isWindowsHighResolution;

		//intiializes the stopwatch platform data.
		StopwatchInitializer() {
#ifdef _WIN32
			LARGE_INTEGER value;
			isWindowsHighResolution = !!QueryPerformanceFrequency(&value);
			if (isWindowsHighResolution)
				nanosecondsPerTick = 1000000000.0 / value.QuadPart;
			else {
#endif
				nanosecondsPerTick = (1000000000.0 * (double) std::chrono::high_resolution_clock::period::num) / std::chrono::high_resolution_clock::period::den;
#ifdef _WIN32
			}
#endif
		}
	};

	//static single instance of the StopwatchInitializer instance
	static const StopwatchInitializer platformInfo;
	double startTimeStamp, elapsed;
	bool isRunning;

public:
	//Initializes the stopwatch.
	Stopwatch();

	//Initializes the stopwatch with the specified pre-elapsed ticks.
	Stopwatch(double preElapsedTicks);

	//Gets the current time in platform-specific ticks.
	double getTimeStamp();

	//Starts or resumes the stopwatch.
	void start();

	//Stops the stopwatch.
	void stop();

	//Gets whether the stopwatch is running
	int getIsRunning();

	//Sets whether the stopwatch is running (boolean value).
	void setIsRunning(bool value);

	//Gets the current elapsed ticks.
	double getElapsedTicks();

	//Gets the elapsed time in fortnights.
	double getElapsedFortnights();

	//Gets the elapsed time in weeks.
	double getElapsedWeeks();

	//Gets the elapsed time in days.
	double getElapsedDays();

	//Gets the elapsed time in hours.
	double getElapsedHours();

	//Gets the elapsed time in minutes.
	double getElapsedMinutes();

	//Gets the elapsed time in seconds.
	double getElapsedSeconds();

	//Gets the elapsed time in milliseconds.
	double getElapsedMilliseconds();

	//Gets the elapsed time in microseconds.
	double getElapsedMicroseconds();

	//Gets the elapsed time in nanoseconds.
	double getElapsedNanoseconds();

	//Resets the elapsed time.
	void reset();

	//Resets the elapsed time to the specified platform-specific ticks.
	void reset(double ticks);

	//Resets the stopwatch and restarts it.
	void restart();

	//Resets the stopwatch to specified platform-specific ticks and restarts it.
	void restart(double ticks);

	//Converts nanoseconds to platform-specific ticks.
	static double convertToTicks(double nanoseconds);

	//Converts platform-specific ticks to nanoseconds.
	static double convertToNanoseconds(double ticks);
};