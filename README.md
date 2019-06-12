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

*Member functions read() and write() are also overloaded to handle char arrays.*


**Example Echo Program (Arduino):**
```c++
void setup()
{
  Serial.begin(115200); // COM25

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop()
{
  while(Serial.available())
  {
    Serial.write(Serial.read());
  }
}
```

**Example Echo Program (Windows):**
```c++
#include "pch.h"
#include "ArduSerial.h"

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
```

***Expected PC Output:***
```
hi

```
