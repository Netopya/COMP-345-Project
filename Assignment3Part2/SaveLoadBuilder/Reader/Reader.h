#ifndef READER_H
#define READER_H

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

class Reader
{
private:

	bool isOpened;
	const char* fileName;
	ifstream _is;

public:

	Reader(const char*);
	bool Open();
	void Close();
	bool IsOpened();

	/*
	* Gives the byte at the actual stream position.
	*/
	char byteAtActualPosition();
	/*
	* Flushes the desired amount of data without checking the syntax.
	*/
	void flushNoCheck(int);
	/*
	* Reads the next character.
	* Throws: fileNotGood if there is a file I/O error.
	*
	*/
	void flushNextByte();
	/*
	* Flushes all the characters as long as we do not get to the
	* specified character. Does not flush the specified character.
	*
	* Throws an fileNotGood exeption if there is a file I/O error.
	*
	*/
	void flushUntilYou(const char);
	/*
	* Returns the next POSITIVE SIGNED INT32 value inside a file.
	* By 'next' we mean 'until the function find a ASCII value outside '[(int)'0'; (int)'9']'.
	* DOES NOT flushes the limitation value outside '[(int)'0'; (int)'9']'.
	* The function realized that it is trying to analyse more digits than a __int32 interger can contain.
	* The function realizes at the end that his value (even if it has the good number of digits) is too big to fit inside an __int32.
	* Throws: fileNotGood if there is a file I/O error while reading.
	*         formatSyntaxError if there is a format error in the input.
	* Returns: the converted value.
	*
	*/
	__int32 getNextPosSignedINT32();
	/*
	* Returns the next byte of data within a file.
	* Throws: fileNotGood exeption if there is a file I/O error.
	* Returns: the converted value.
	*
	*/
	char getNextByte();
	/*
	* Returns all the characters until a simple limitation (1 char) defined inside the foo parameter.
	* The limitation will determine what character should specify the end of the array and will be flushed.
	* Does not return the limitation chararacter and neither flushes it.
	* Throws: fileNotGood exeption if there is a file I/O error.
	* Returns: s32data containing the stream data.
	*
	*/
	char* getNextArrayLimitationS(const char);
	/*
	* Manage a binary file input request for multiple types of data.
	* %% a percent sign.
	* %c a character with the given number.
	* %n gets all characters until the next line.
	* %l[char] an array limited by a specific character.
	* %u an unsigned 32 bits integer in decimal.
	*
	* NOTE: char arrays sent in parameters must NOT be initialized since they
	*       will be during the process. Such initialization will directly
	*       lead to memory corruption.
	*
	* Throws: fileNotGood exception if there is a file I/O error.
	*         fileSyntax exception the syntax is not respected.
	*/
	__int32 getMultipleFormats(const char*, ...);
};
#endif