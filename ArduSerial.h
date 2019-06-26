#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>




const int ARDUINO_WAIT_TIME = 2000;




class WindowsSerial
{
public:
	////////////////////////////////////////////////////////
	// Default Constructor
	WindowsSerial(unsigned int _comPortNum);

	////////////////////////////////////////////////////////
	// Initialization/Admin Stuff
	void setPort(unsigned int _comPortNum);
	void begin(unsigned int baud);
	void begin(unsigned int baud, unsigned int _comPortNum);
	bool connected();
	void end();

	////////////////////////////////////////////////////////
	// Test For Available Data
	unsigned int available();

	////////////////////////////////////////////////////////
	// I/O Functions
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

	unsigned int comPortNum = NULL;

	void initializePort(char portName[], unsigned int baud);
};




extern WindowsSerial Serial;
extern WindowsSerial Serial1;
extern WindowsSerial Serial2;
extern WindowsSerial Serial3;
extern WindowsSerial Serial4;
extern WindowsSerial Serial5;
extern WindowsSerial Serial6;
extern WindowsSerial Serial7;
extern WindowsSerial Serial8;
extern WindowsSerial Serial9;
extern WindowsSerial Serial10;
extern WindowsSerial Serial11;
extern WindowsSerial Serial12;
extern WindowsSerial Serial13;
extern WindowsSerial Serial14;
extern WindowsSerial Serial15;
extern WindowsSerial Serial16;
extern WindowsSerial Serial17;
extern WindowsSerial Serial18;
extern WindowsSerial Serial19;
extern WindowsSerial Serial20;
extern WindowsSerial Serial21;
extern WindowsSerial Serial22;
extern WindowsSerial Serial23;
extern WindowsSerial Serial24;
extern WindowsSerial Serial25;
extern WindowsSerial Serial26;
extern WindowsSerial Serial27;
extern WindowsSerial Serial28;
extern WindowsSerial Serial29;
extern WindowsSerial Serial30;
