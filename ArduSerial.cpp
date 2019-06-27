#include "pch.h"
#include "ArduSerial.h"
#pragma warning(disable: 4996)




WindowsSerial::WindowsSerial(unsigned int _comPortNum)
{
	this->setPort(_comPortNum);
}




void WindowsSerial::setPort(unsigned int _comPortNum)
{
	this->comPortNum = _comPortNum;
}




void WindowsSerial::begin(unsigned int _baud)
{
	/*
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

	this->baud = _baud;

	if (this->comPortNum != NULL)
	{
		char format[] = "\\\\.\\COM%i";
		char portName[20];

		snprintf(portName, 12, format, this->comPortNum);

		initializePort(portName, this->baud);
	}
}




void WindowsSerial::begin(unsigned int _baud, unsigned int _comPortNum)
{
	/*
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

	this->baud = _baud;

	setPort(_comPortNum);
	snprintf(portName, 12, format, this->comPortNum);

	initializePort(portName, this->baud);
}




void WindowsSerial::initializePort(char portName[], unsigned int _baud)
{
	this->isConnected = false;

	this->handler = CreateFileA(static_cast<LPCSTR>(portName), // lpFileName
		GENERIC_READ | GENERIC_WRITE,  // dwDesiredAccess
		0,                             // dwShareMode
		NULL,                          // lpSecurityAttributes
		OPEN_EXISTING,                 // dwCreationDisposition
		FILE_ATTRIBUTE_NORMAL,         // dwFlagsAndAttributes
		NULL);                         // hTemplateFile

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
			dcbSerialParameters.BaudRate    = _baud;
			dcbSerialParameters.ByteSize    = 8;
			dcbSerialParameters.StopBits    = ONESTOPBIT;
			dcbSerialParameters.Parity      = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(handler, &dcbSerialParameters))
				printf("ALERT: could not set Serial port parameters\n");
			else
			{
				this->isConnected = true;

				// flush any remaining characters in the buffers 
				PurgeComm(this->handler, PURGE_RXABORT |
					                 PURGE_RXCLEAR |
					                 PURGE_TXABORT |
					                 PURGE_TXCLEAR);

				// wait as the arduino board will be reseting
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




WindowsSerial::operator bool()
{
	return this->connected();
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
	size_t bufSize = message.size();

	char *buffer = new char[message.size() + 1];
	message.copy(buffer, message.size() + 1);
	buffer[message.size()] = '\0';

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
	if (this->isConnected)
		return this->isConnected;
	else
		this->begin(this->baud);

	return this->isConnected;
}




WindowsSerial Serial(0);
WindowsSerial Serial1(1);
WindowsSerial Serial2(2);
WindowsSerial Serial3(3);
WindowsSerial Serial4(4);
WindowsSerial Serial5(5);
WindowsSerial Serial6(6);
WindowsSerial Serial7(7);
WindowsSerial Serial8(8);
WindowsSerial Serial9(9);
WindowsSerial Serial10(10);
WindowsSerial Serial11(11);
WindowsSerial Serial12(12);
WindowsSerial Serial13(13);
WindowsSerial Serial14(14);
WindowsSerial Serial15(15);
WindowsSerial Serial16(16);
WindowsSerial Serial17(17);
WindowsSerial Serial18(18);
WindowsSerial Serial19(19);
WindowsSerial Serial20(20);
WindowsSerial Serial21(21);
WindowsSerial Serial22(22);
WindowsSerial Serial23(23);
WindowsSerial Serial24(24);
WindowsSerial Serial25(25);
WindowsSerial Serial26(26);
WindowsSerial Serial27(27);
WindowsSerial Serial28(28);
WindowsSerial Serial29(29);
WindowsSerial Serial30(30);
