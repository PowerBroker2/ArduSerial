# ArduSerial
Windows C++ library to interface with an Arduino via USB

This library allows Windows C++ programers to interface with COM ports in a way extremely similar to how Arduino's interface with UART ports.

The library uses a class called Serial that includes member functions named after Arduino Serial member functions. Below is a list of all member functions used in this Windows C++ library:
- begin()
- connected()
- end()
- available()
- read()
- write()
- print()
- println()

*Member functions read() and write() are also overloaded to handle char arrays.*


**Example Echo Program (Arduino):**
```c++
void setup()
{
  Serial.begin(115200); // COM25
}

void loop()
{
  while(Serial.available())
    Serial.write(Serial.read());
}
```

**Example Echo Program (Windows):**
```c++
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
		printf("%c", Serial27.read());

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
```

***Expected PC Output:***
```
hi

```
