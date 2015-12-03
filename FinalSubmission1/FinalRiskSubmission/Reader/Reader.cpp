#include "Reader.h"

Reader::Reader(string _fileName)
{
	isOpened = false;
	fileName = _fileName;
}
bool Reader::Open()
{
	_is.open(fileName, ios::binary);
	isOpened = _is ? true : false;
	return isOpened;
}
void Reader::Close()
{
	_is.close();
	isOpened = false;
}
bool Reader::IsOpened()
{
	return isOpened;
}

/*
 * Gives the byte at the actual stream position.
 */
char Reader::byteAtActualPosition()
{
	char curr = NULL;
	_is.get(curr);

	if (!_is.good())
		throw fng; //Throws file not good error.

	_is.seekg(-1, _is.cur);
	return curr;
}

/*
 * Flushes the desired amount of data without checking the syntax.
 */
void Reader::flushNoCheck(int _offset)
{
	_is.seekg((int)_is.tellg() + _offset);
}

/*
 * Reads the next character.
 * Throws: fileNotGood if there is a file I/O error.
 *
 */
void Reader::flushNextByte()
{
	char curr = NULL;
	_is.get(curr);

	if (!_is.good())
		throw fng; //Throw file not good error.
}


/*
 * Flushes all the characters as long as we do not get to the
 * specified character. Does not flush the specified character.
 *
 * Throws an fileNotGood exeption if there is a file I/O error.
 *
 */
void Reader::flushUntilYou(const char _character)
{

	int count = 0;
	char curr = NULL;

	size_t iniPos = _is.tellg();

	do
	{
		count++;
		_is.get(curr);

		if (!_is.good())
			throw fng; //Throws file not good error.

	} while (_character != curr);

	_is.seekg(-1, _is.cur);

	return;
}

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
__int32 Reader::getNextPosSignedINT32()
{
	size_t iniPos = _is.tellg();

	int count = 0;
	char curr = NULL;

	do
	{
		_is.get(curr);

	} while ((int)curr >= 48 && (int)curr <= 57 &&
		(count++ < INT32_MAX_DIGITS));

	//It was not a number at all.
	if (count == 0 && (!((int)curr >= 48 && (int)curr <= 57)))
		throw fs;

	if (!_is.good())
		throw fng; //Throws file not good error.

	char* buffer = (char*)malloc(sizeof(char) * count);

	_is.seekg(iniPos);
	_is.read(buffer, count);


	unsigned __int32 ret = strtoul(buffer, NULL, 10);
	free(buffer);

	return (errno != ERANGE) ? ret : throw fs; //Throws file syntax error.
}


char* Reader::getNextLine()
{
	int count = -1;
	char curr = NULL;

	int iniPos = _is.tellg();

	do
	{
		count++;
		_is.get(curr);

		if (!_is.good())
			throw fng; //Throws file not good error.

	} while (curr != '\n');

	char* ret = new char[count + 1];
	ret[count] = '\0';

	_is.seekg(iniPos);
	_is.read(ret, count);

	flushNoCheck(1);

	return ret;
}

/*
 * Returns the next byte of data within a file.
 * Throws: fileNotGood exeption if there is a file I/O error.
 * Returns: the converted value.
 *
 */
char Reader::getNextByte()
{
	char curr = NULL;
	_is.get(curr);
	if (!_is.good())
		throw fng; //Throws file not good error.
	return curr;
}

/*
 * Returns all the characters until a simple limitation (1 char) defined inside the foo parameter.
 * The limitation will determine what character should specify the end of the array and will be flushed.
 * Does not return the limitation chararacter and neither flushes it.
 * Throws: fileNotGood exeption if there is a file I/O error.
 * Returns: s32data containing the stream data.
 *
 */
char* Reader::getNextArrayLimitationS(const char _limit)
{
	int count = -1;
	char curr = NULL;

	size_t iniPos = _is.tellg();

	do
	{
		count++;
		_is.get(curr);

		if (!_is.good())
			throw fng; //Throws file not good error.

	} while (curr != _limit);


	char* ret = new char[count + 1];
	ret[count] = '\0';

	_is.seekg(iniPos);
	_is.read(ret, count);

	return ret;
}

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
__int32 Reader::getMultipleFormats(const char* _format, ...)
{
	int i = 0;
	va_list arg;
	va_start(arg, _format);

	for (; i < strlen(_format); i++)
	{
		if (_format[i] != '%')
		{
			/*
			* We flush the characters as long as they respect our format.
			* If they don't, we throw an error.
			*/
			if (_format[i] != getNextByte())
				throw fs;
		}
		else
		{
			/*
			 * Note that every single argument must be passed
			 * by referenced to be correctly dereferenced here
			 */
			switch (_format[i + 1])
			{
			case '%': { getNextByte();
				i++;
				break; }
			case 'c': { char** p = va_arg(arg, char**);
				*p = (char*)malloc(sizeof(char));
				**p = getNextByte();
				i++;
				break; }
			case 'l': { char tmpLimitChar = _format[i + 2];
				char** p = va_arg(arg, char**);
				*p = getNextArrayLimitationS(tmpLimitChar);
				i += 2;
				break; }
			case 'u': { unsigned __int32** p = va_arg(arg, unsigned __int32**);
				*p = (unsigned __int32*)malloc(sizeof(unsigned __int32));
				**p = getNextPosSignedINT32();
				i++;
				break; }

			default: i++;
				break;
			}
		}
	}
	va_end(arg);
	return i;
}