#include "stopwatch.h"

//platformInfo implementation
const Stopwatch::StopwatchInitializer Stopwatch::platformInfo;

//Initializes the stopwatch.
Stopwatch::Stopwatch() {
	elapsed = 0.0;
	startTimeStamp = 0.0;
	isRunning = false;
}

//Initializes the stopwatch with the specified pre-elapsed ticks.
Stopwatch::Stopwatch(double preElapsedTicks) {
	elapsed = preElapsedTicks;
	startTimeStamp = 0.0;
	isRunning = false;
}

//Gets the current time in platform-specific ticks.
double Stopwatch::getTimeStamp() {
#ifdef _WIN32
	if (platformInfo.isWindowsHighResolution) {
		LARGE_INTEGER num;
		QueryPerformanceCounter(&num);
		return (double) num.QuadPart;
	} else {
#endif
		return (double) std::chrono::high_resolution_clock::now().time_since_epoch().count();
#ifdef _WIN32
	}
#endif
}

//Starts or resumes the stopwatch.
void Stopwatch::start() {
	if (isRunning)
		return;
	isRunning = true;
	startTimeStamp = getTimeStamp();
}

//Stops the stopwatch.
void Stopwatch::stop() {
	if (isRunning) {
		isRunning = false;
		elapsed += getTimeStamp() - startTimeStamp;
	}
}

//Gets whether the stopwatch is running
int Stopwatch::getIsRunning() {
	return isRunning;
}

//Sets whether the stopwatch is running (boolean value).
void Stopwatch::setIsRunning(bool value) {
	if (value)
		start();
	else
		stop();
}

//Gets the current elapsed ticks.
double Stopwatch::getElapsedTicks() {
	return isRunning ? (elapsed - startTimeStamp) + getTimeStamp() : elapsed;
}

//Gets the elapsed time in fortnights.
double Stopwatch::getElapsedFortnights() {
	return (platformInfo.nanosecondsPerTick * 0.00000000000000082671957671957672) * getElapsedTicks();
}

//Gets the elapsed time in weeks.
double Stopwatch::getElapsedWeeks() {
	return (platformInfo.nanosecondsPerTick * 0.00000000000000165343915343915344) * getElapsedTicks();
}

//Gets the elapsed time in days.
double Stopwatch::getElapsedDays() {
	return (platformInfo.nanosecondsPerTick * 0.00000000000001157407407407407407) * getElapsedTicks();
}

//Gets the elapsed time in hours.
double Stopwatch::getElapsedHours() {
	return (platformInfo.nanosecondsPerTick * 0.00000000000027777777777777777777) * getElapsedTicks();
}

//Gets the elapsed time in minutes.
double Stopwatch::getElapsedMinutes() {
	return (platformInfo.nanosecondsPerTick * 0.00000000001666666666666666666666) * getElapsedTicks();
}

//Gets the elapsed time in seconds.
double Stopwatch::getElapsedSeconds() {
	return (platformInfo.nanosecondsPerTick * 0.000000001) * getElapsedTicks();
}

//Gets the elapsed time in milliseconds.
double Stopwatch::getElapsedMilliseconds() {
	return (platformInfo.nanosecondsPerTick * 0.000001) * getElapsedTicks();
}

//Gets the elapsed time in microseconds.
double Stopwatch::getElapsedMicroseconds() {
	return (platformInfo.nanosecondsPerTick * 0.001) * getElapsedTicks();
}

//Gets the elapsed time in nanoseconds.
double Stopwatch::getElapsedNanoseconds() {
	return platformInfo.nanosecondsPerTick * getElapsedTicks();
}

//Resets the elapsed time.
void Stopwatch::reset() {
	elapsed = 0.0;
	isRunning = false;
	startTimeStamp = 0.0;
}

//Resets the elapsed time to the specified platform-specific ticks.
void Stopwatch::reset(double ticks) {
	elapsed = ticks;
	isRunning = false;
	startTimeStamp = 0.0;
}

//Resets the stopwatch and restarts it.
void Stopwatch::restart() {
	elapsed = 0.0;
	isRunning = true;
	startTimeStamp = getTimeStamp();
}

//Resets the stopwatch to specified platform-specific ticks and restarts it.
void Stopwatch::restart(double ticks) {
	elapsed = ticks;
	isRunning = true;
	startTimeStamp = getTimeStamp();
}

//Converts nanoseconds to platform-specific ticks.
double Stopwatch::convertToTicks(double nanoseconds) {
	return nanoseconds / platformInfo.nanosecondsPerTick;
}

//Converts platform-specific ticks to nanoseconds.
double Stopwatch::convertToNanoseconds(double ticks) {
	return ticks * platformInfo.nanosecondsPerTick;
}