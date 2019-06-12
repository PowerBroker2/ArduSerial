#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>




const int ARDUINO_WAIT_TIME = 100;




class WindowsSerial
{
public:
	void begin(unsigned int baud, unsigned int comPortNum);
	bool connected();
	void end();

	unsigned int available();

	int read();
	int read(char buffer[], unsigned int bufSize);

	bool print(const std::string message);
	bool print(const long double message);
	bool print(const long message);

	bool println(const std::string message);
	bool println(const long double message);
	bool println(const long message);

	bool write(char c);
	bool write(const char buffer[], unsigned int bufSize);

private:
	HANDLE handler;
	bool isConnected;
	COMSTAT status;
	DWORD errors;
};




extern WindowsSerial Serial;
extern WindowsSerial Serial1;
extern WindowsSerial Serial2;
extern WindowsSerial Serial3;
extern WindowsSerial Serial4;
extern WindowsSerial Serial5;
extern WindowsSerial Serial6;