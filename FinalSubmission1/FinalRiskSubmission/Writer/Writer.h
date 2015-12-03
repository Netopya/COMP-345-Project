#ifndef WRITER_H
#define WRITER_H

#define INT32_MAX_SIZE_POS 2147483647
#define INT32_MAX_STRING "2147483647"
#define INT32_MAX_DIGITS 10
#define INT32_MAX_SIZE_NEG -2147483648

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <stdarg.h> 
#include <algorithm>
#include <exception>
#include "..\Exception.h"

using namespace std;

class Writer
{
private:

	char integerBuffer[sizeof(char) * INT32_MAX_DIGITS];
	bool isOpened;
	string fileName;
	ofstream _os;

public:

	Writer(string _fileName);
	~Writer();
	bool Open();
	void Close();
	bool IsOpened();

	/*
	 * Writes a POSITIVE SIGNED INT32 value inside a file.
	 * Throws: fileNotGood if there is a file I/O error while writing.
	 * Returns: the size of the array of the converted number.
	 */
	int writeNextPosSignedINT32(unsigned __int32 _array);
	/*
	 * Writes a byte of data at the end of a file.
	 * Throws: fileNotGood exeption if there is a file I/O error.
	 */
	void writeNextByte(char _array);

	/*
	 * Writes an array of characters followed by a choosen byte.
	 * This is the secure version checking either for corruption and array lenght limitation.
	 * Throws: fileNotGood exeption if there is a file I/O error.
	 *         dataNotGood exeption if the second parameter is corrupted
	 * Returns: the size of the array (from pos 0 until null character).
	 */
	int writeNextArray(const char* _array);

	/*
	 * Manage a binary file output request for multiple types of data.
	 * %% a percent sign.
	 * %c a character with the given number.
	 * %n writes an array of characters unsecure.
	 * %s writes an array of characters secure.
	 * %u writes an array of a specified 32 bit unsigned integer.
	 * Returns: the size of the array that has been formatted (from pos 0 until null character).
	 */
	__int32 writeMultipleFormats(const char* _format, ...);
};
#endif