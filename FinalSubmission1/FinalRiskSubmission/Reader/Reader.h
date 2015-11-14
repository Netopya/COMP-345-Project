#pragma once

/*
 * %% a percent sign
 * %c a character with the given number
 * %s a string
 * %d a signed integer, in decimal
 * %u an unsigned integer, in decimal
 * %o an unsigned integer, in octal
 * %x an unsigned integer, in hexadecimal
 * %e a floating-point number, in scientific notation
 * %f a floating-point number, in fixed decimal notation
 * %g a floating-point number, in %e or %f notation
 */

class Reader
{
private:

	bool isOpened;
	const char* fileName;
	ifstream _is;

public:

	Reader(const char* _fileName)
	{ 
		isOpened = false;
		fileName = _fileName;
	}
	bool Open()
	{
		_is.open(fileName, ios::binary);
		isOpened = _is ? true : false;
		return isOpened; 
	}
	void Close()
	{
		_is.close();
		isOpened = false;
	}
	bool IsOpened()
	{
		return isOpened;
	}

	/*
	 * Gives the byte at the actual stream position.
	 */
	char byteAtActualPosition()
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
	inline void flushNoCheck(int _offset)
	{
		_is.seekg((int)_is.tellg() + _offset);
	}
	
	/*
	 * Reads the next character.
	 * Throws: fileNotGood if there is a file I/O error.
	 *
	 */
	inline void flushNextByte()
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
	void flushUntilYou(const char _character)
	{

		int count = 0;
		char curr = NULL;

		int iniPos = _is.tellg();

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
	 * Returns all the characters within the offset.
	 * Not referenced to a counter since we know its size. 
	 * Throws: fileNotGood if there is a file I/O error while reading.
	 * Returns: s32data containing the stream data.
	 *         
	 */
	s32data* getNextArrayLenght(unsigned __int32 _offset)
	{
		s32data* ret = mk_s32data(_offset);
		_is.read(ret->bin, _offset);
		return _is ? ret : throw fng; //Throws file not good error.
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
	__int32 getNextPosSignedINT32()
	{
		int iniPos = _is.tellg();
		
		int count = 0;
		char curr = NULL;

		do
		{
			_is.get(curr);

		} while ((int)curr >= 48 && (int)curr <= 57 &&
					(count++ < INT32_MAX_DIGITS));

		if (!_is.good())
			throw fng; //Throws file not good error.

		char* buffer = (char*)malloc(sizeof(char) * count);

		_is.seekg(iniPos);
		_is.read(buffer, count);


		unsigned __int32 ret = strtoul(buffer, NULL, 10);
		free(buffer);

		return (errno != ERANGE) ? ret : throw fs; //Throws file syntax error.
	}

	/*
	 * Returns the next byte of data within a file.
	 * Throws: fileNotGood exeption if there is a file I/O error.
	 * Returns: the converted value.
	 *
	 */
	char getNextByte()
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
	s32data* getNextArrayLimitationS(const char _limit)
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

		} while (curr != _limit);

		
		s32data* ret = mk_s32data(count);

		_is.seekg(iniPos);
		_is.read(ret->bin, count);


		return ret;
	}

	/*
	 * Returns all the characters until a simple limitation (1 char) defined inside the foo parameter
	 * and until it reaches the maximum lenght. Throws an error if the code append to want to
	 * continue reading even if it is the end.
	 * Does not return the limitation chararacter but flushes it.
	 * The limitation will determine what character should specify the end of the array.
	 * Throws: fileNotGood exeption if there is a file I/O error.
	 * Returns: s32data containing the stream data.
	 *
	 */
	s32data* getNextArrayLenghtLimitationS(__int32 _maxLenght, const char _limit)
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

		} while ((count <= _maxLenght) && (curr != _limit));

		//Purpusly throws an error if we have not reached the limitation before the max length
		if ((count == _maxLenght) && (curr == _limit))
			throw fs; //Throws file syntax error.
		
		s32data* ret = mk_s32data(count);

		_is.seekg(iniPos);
		_is.read(ret->bin, count);

		flushNoCheck(1);

		return ret;
	}

	/*
	 * Manage a binary file input request for multiple types of data. 
	 * %% a percent sign.
	 * %c a character with the given number.
	 * %n gets all characters until the next line.
	 * %s[size] an array limited by a size of maximum 24 characters
	 *          which are sent by a parameter which is read until
	 *          it hits a character with an ASCII value outside [48, 57].
	 * %g in order to implement the algorithm for unknown data size, using
	 *    the command '%g' will tell the program to read the s32data
	 *    argument where the size and then the data will be read.
	 *    In some way, the program will proceed like '%u\0%s[u]'.
	 *    For obvious reasons, there is a null separator between both commands.
	 * %l[char] a string limited by a specific character.
	 * %o[char][size] a string limited by a specific character which
	 *                cannot exceed a certain offset of maximum 24 characters 
	 *                with an ASCII value inside [48, 57] as well.
	 * %u an unsigned 32 bits integer in decimal.
	 *
	 * NOTE: char arrays sent in parameters must NOT be initialized since they
	 *       will be during the process. Such initialization will directly
	 *       lead to memory corruption.
	 *
	 * Throws: fileNotGood exception if there is a file I/O error.
	 *         fileSyntax exception the syntax is not respected. 
	 */
	__int32 getMultipleFormats(const char* _format, ...)
	{
		int i = 0;
		va_list arg;
		va_start(arg, _format);

		for ( ; i < strlen(_format) ; i++)
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
					case 'n': { s32data** p = va_arg(arg, s32data**);
								__int32 tmpSize = 0;
								*p = getNextArrayLenght(tmpSize);
								i++; }
								break;
					case 's': { int j = 0;
								char tmpSizeArray[24];
								memset(tmpSizeArray, NULL, 24);
								for ( ; _format[i + 2 + j] <= 57 && _format[i + 2 + j] >= 48; j++)
									tmpSizeArray[j] = _format[i + 2 + j];
								__int32 tmpSize = atoi(tmpSizeArray);
								s32data** p = va_arg(arg, s32data**);
								*p = getNextArrayLenght(tmpSize);
								i += (j + 1);
								break; }
					case 'g': { unsigned __int32 tmpSize = getNextPosSignedINT32();
								flushNoCheck(1);
								s32data** p2 = va_arg(arg, s32data**);
								*p2 = getNextArrayLenght(tmpSize);
								i++;
								break; }
					case 'l': { char tmpLimitChar = _format[i + 2];
								s32data** p = va_arg(arg, s32data**);
								*p = getNextArrayLimitationS(tmpLimitChar);
								i += 2;
								break; }
					case 'u': { unsigned __int32** p = va_arg(arg, unsigned __int32**);
								*p = (unsigned __int32*)malloc(sizeof(unsigned __int32));
								**p = getNextPosSignedINT32();
								i++;
								break; }
					case 'o': { int j = 0;
								char tmpSizeArray[24];
								memset(tmpSizeArray, NULL, 24);
								char tmpLimitChar = _format[i + 2];
								for ( ; _format[i + 3 + j] <= 57 && _format[i + 3 + j] >= 48; j++)
									tmpSizeArray[j] = _format[i + 3 + j];
								__int32 tmpMaxSize = atoi(tmpSizeArray);
								s32data** p = va_arg(arg, s32data**);
								*p = getNextArrayLenghtLimitationS(tmpMaxSize, tmpLimitChar);
								i += (j + 2);
								break; }

					default: i++;
						break;
				}
			}
		}

		va_end(arg);
		return i;
	}

};