#include "pch.h"
#include <iostream>
#include "ArduSerial.h"



std::string data = "hi";




void setup()
{
	// Serial27 means access Arduino on COM27 ***************
	Serial27.begin(115200);

	std::cout << "Starting..." << std::endl;

	while (!Serial27.connected());

	while (Serial27.available())
		Serial27.read();

	std::cout << "Connected" << std::endl;
}




void loop()
{
	std::cout << "Sending data: " << data << std::endl;
	Serial27.println(data);

	std::cout << "Looking for echo..." << std::endl;
	while (Serial27.available() < data.length());

	std::cout << "Found the following echo:" << std::endl;
	while (Serial27.available())
	{
		printf("%c", Serial27.read());
	}

	std::cout << std::endl << "Waiting before transmitting again..." << std::endl;
	Sleep(1000);
}




int main()
{
	setup();

	while (true)
		loop();

	return 0;
}
