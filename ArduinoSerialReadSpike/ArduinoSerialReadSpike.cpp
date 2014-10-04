// ArduinoSerialReadSpike.cpp : Defines the entry point for the console application.
//

#ifdef WIN32
#include <tchar.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <cppJSON/cppJSON.h>
#include <libCereal/Serial.h>

// define sleep
#ifdef WIN32
static inline void sleep(int msec) {
	Sleep(msec);
}
#else
static inline void sleep(int msec) {
	usleep(msec * 1000);
}
#endif

// define DEVICE_NAME
#ifdef WIN32
#define DEVICE_NAME "USB-SERIAL CH340"
#else
#define DEVICE_NAME "/dev/ttyUSB0"
#endif

// define main proto
#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char** argv)
#endif
{
	printf("-=- ArduinoSerialReadSpike -=-\n\n");

	Serial serial = Serial(DEVICE_NAME);

	if (serial.isConnected()) {
		printf("Connected to arduino\n");
	}

	std::function<int(char*, size_t)> readFromSerialPort = [&] (char* buf, size_t bufSize) -> int {
		return serial.read(buf, bufSize);
	};
	cppJSONReader jsonReader = cppJSONReader(readFromSerialPort);

	while(serial.isConnected()) {
		std::vector<std::unique_ptr<cppJSON>> jsonObjects = jsonReader.read();

		if(jsonObjects.size() > 0) {
			printf("got %lu JSON objects:\n", jsonObjects.size());
		}

		for(unsigned int i = 0; i < jsonObjects.size(); i++) {
			printf("azimuth: %d\n", jsonObjects[i]->get("azimuth").getInt());
		}

		sleep(100);
	}

	return 0;
}
