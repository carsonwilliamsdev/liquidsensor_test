liquidsensor_test
=================

Read some settings from Liquid Sensor using Modbus

---------------------------------------------------

So I was working with a water sensor that measured various things such as temperature, sound velocity, impedance, etc. 
The sensor uses the modbus protocol over TCP/IP for communicating the data. I wrote a program in C to read the data registers using libmodbus (http://libmodbus.org/). 
I compiled libmodbus as a static library on Windows for this project. I don't have the library included on the project since this is just an example, but it should
be easy enough for anyone to get. The code is pretty straight forward. I made the RawFloat union because I need to look at both the hex and float values, and using unions is awesome.
The data is in big endian format and the first address contains the least significant word (lower part of mantissa) and the second address contains the most significant 
word (sign, exponent and upper part of mantissa). So the second register comes first, then the first register, then it needs to be translated from network byte order to little endian.
I probably could have used the Winsock ntoh function for some of it, but since I had to swap the registers order anyway I just did the translation myself. That’s pretty much it.