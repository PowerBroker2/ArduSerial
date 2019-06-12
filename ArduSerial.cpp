#include "pch.h"
#include "ArduSerial.h"




void WindowsSerial::begin(unsigned int baud, unsigned int comPortNum)
{
	/*
	char port_name[] = "\\\\.\\COM20";

	#define CBR_110             110
	#define CBR_300             300
	#define CBR_600             600
	#define CBR_1200            1200
	#define CBR_2400            2400
	#define CBR_4800            4800
	#define CBR_9600            9600
	#define CBR_14400           14400
	#define CBR_19200           19200
	#define CBR_38400           38400
	#define CBR_56000           56000
	#define CBR_57600           57600
	#define CBR_115200          115200
	#define CBR_128000          128000
	#define CBR_256000          256000
	*/

	char format[] = "\\\\.\\COM%i";
	char portName[20];

	snprintf(portName, 12, format, comPortNum);

	this->isConnected = false;
	this->handler = CreateFileA(static_cast<LPCSTR>(portName),
								GENERIC_READ | GENERIC_WRITE,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);

	if (this->handler == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
		else
			printf("ERROR!!!");
	}
	else
	{
		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(this->handler, &dcbSerialParameters))
			printf("failed to get current serial parameters");
		else
		{
			dcbSerialParameters.BaudRate = baud;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(handler, &dcbSerialParameters))
				printf("ALERT: could not set Serial port parameters\n");
			else
			{
				this->isConnected = true;
				PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
}




void WindowsSerial::end()
{
	if (this->isConnected)
	{
		this->isConnected = false;
		CloseHandle(this->handler);
	}
}




unsigned int WindowsSerial::available()
{
	ClearCommError(this->handler, &this->errors, &this->status);
	return this->status.cbInQue;
}




int WindowsSerial::read()
{
	DWORD bytesRead;
	unsigned int toRead = 1;
	unsigned int bytesAvailable = this->available();
	char buffer[] = { ' ' };

	if (bytesAvailable)
		if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL))
				return buffer[0];

	return -1;
}




int WindowsSerial::read(char buffer[], unsigned int bufSize)
{
	DWORD bytesRead;
	unsigned int toRead;
	unsigned int bytesAvailable = this->available();

	if (bytesAvailable > bufSize)
		toRead = bufSize;
	else
		toRead = bytesAvailable;

	if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL))
		return bytesRead;

	return 0;
}




bool WindowsSerial::print(const std::string message)
{
	DWORD bytesSend;
	char buffer[100];

	unsigned int bufSize = sprintf(buffer, "%s", message);

	if (!WriteFile(this->handler, buffer, bufSize, &bytesSend, 0))
	{
		ClearCommError(this->handler, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}




bool WindowsSerial::print(const long double message)
{
	DWORD bytesSend;
	char buffer[100];
		
	unsigned int bufSize = sprintf(buffer, "%f", message);

	if (!WriteFile(this->handler, buffer, bufSize, &bytesSend, 0))
	{
		ClearCommError(this->handler, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}




bool WindowsSerial::print(const long message)
{
	DWORD bytesSend;
	char buffer[100];

	unsigned int bufSize = sprintf(buffer, "%i", message);

	if (!WriteFile(this->handler, buffer, bufSize, &bytesSend, 0))
	{
		ClearCommError(this->handler, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}




bool WindowsSerial::println(const std::string message)
{
	bool result = this->print(message);
	if (result)
		result = this->write('\n');
	return result;
}




bool WindowsSerial::println(const long double message)
{
	bool result = this->print(message);
	if (result)
		result = this->write('\n');
	return result;
}




bool WindowsSerial::println(const long message)
{
	bool result = this->print(message);
	if (result)
		result = this->write('\n');
	return result;
}




bool WindowsSerial::write(char c)
{
	DWORD bytesSend = 1;
	unsigned int buf_size = 1;
	char buffer[] = { c };

	if (!WriteFile(this->handler, buffer, buf_size, &bytesSend, 0))
	{
		ClearCommError(this->handler, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}




bool WindowsSerial::write(const char buffer[], unsigned int bufSize)
{
	DWORD bytesSend;

	if (!WriteFile(this->handler, buffer, bufSize, &bytesSend, 0))
	{
		ClearCommError(this->handler, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}




bool WindowsSerial::connected()
{
	return this->isConnected;
}