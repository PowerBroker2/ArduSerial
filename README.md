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

Member functions read() and write() are also overloaded to handle char arrays.
