#include "pch.h"
#include "ArduSerial.h"




Serial Serial1;




int main()
{
	Serial1.begin(115200, 25);
	while (!Serial1.connected());

	if (Serial1.connected())
	{
		Serial1.write('h');
		Serial1.write('i');
		Serial1.write('\n');
	}

	while (Serial1.available() < 3);

	while (Serial1.available())
	{
		printf("%c", Serial1.read());
	}

	return 0;
}
