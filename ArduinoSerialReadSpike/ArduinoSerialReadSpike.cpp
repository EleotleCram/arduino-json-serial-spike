// ArduinoSerialReadSpike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include "Serial.h"	// Library described above
#include <string>



int _tmain(int argc, _TCHAR* argv[])
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("COM3");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 256;
	int readResult = 0;

	char nextChar;
	std::string jsonBuffer = "";
	int curlyLevel = 0;

	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,128);
//		printf("Bytes read: (-1 means no data available) %i\n",readResult);

		if(readResult > 0) {
			std::string test(incomingData);

			for(int i = 0; i < readResult; i++) {
				nextChar = incomingData[i];

				if(nextChar == '{') {
					curlyLevel++;
				}

				if(curlyLevel > 0) {
					jsonBuffer += nextChar;
				}

				if(nextChar == '}') {
					curlyLevel--;
					if(curlyLevel == 0) {
						printf("|%s|\n\n", jsonBuffer.c_str());
						jsonBuffer.clear();
					}
				}
			}

//			printf("%s",incomingData);
			test = "";
		}

		Sleep(100);
	}
	return 0;
}

