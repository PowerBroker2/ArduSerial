#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>



const int ARDUINO_WAIT_TIME = 100; // was 2000



class Serial
{
public:
	void begin(unsigned int baud, unsigned int comPortNum);
	bool connected();
	void end();

	unsigned int available();

	int read();
	int read(char buffer[], unsigned int buf_size);

	bool write(char c);
	bool write(const char buffer[], unsigned int buf_size);

private:
	HANDLE handler;
	bool isConnected;
	COMSTAT status;
	DWORD errors;
};