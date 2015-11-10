#pragma once

static char* const integerBuffer = (char*)malloc(sizeof(char) * INT32_MAX_DIGITS);
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

class Writer
{
private:

	bool isOpened;
	const char* fileName;
	ofstream _os;

public:
	
	Writer(const char* _fileName)
	{ 
		isOpened = false;
		fileName = _fileName;
	}
	bool Open()
	{
		isOpened = false;
		_os.open(fileName, ios::binary);
		isOpened = _os ? true : false;
		return isOpened;
	}
	void Close()
	{
		_os.close();
		isOpened = false;
	}
	bool IsOpened()
	{
		return isOpened;
	}
	
	/*
	 * Writes a POSITIVE SIGNED INT32 value inside a file.
	 * Throws: fileNotGood if there is a file I/O error while writing.
	 * Returns: the size of the array of the converted number.
	 */
	int writeNextPosSignedINT32(unsigned __int32 _array)
	{
		itoa(_array, integerBuffer, 10);
		int ret = strlen(integerBuffer);
		_os.write(integerBuffer, ret);
		if (!_os) throw fng; //Throws file not good error.
		return ret;
	}

	/*
	 * Writes a byte of data at the end of a file.
	 * Throws: fileNotGood exeption if there is a file I/O error.
	 */
	void writeNextByte(char _array)
	{
		_os.write(&_array, 1); //Avoids NULL exeptions.
		if (!_os) throw fng; //Throws file not good error.
		return;
	}

	/*
	 * Writes an array of characters followed by a choosen byte.
	 * This is the secure version checking either for corruption and array lenght limitation.
	 * Throws: fileNotGood exeption if there is a file I/O error.
	 *         dataNotGood exeption if the second parameter is corrupted.
	 */
	void writeNextArray(s32data* _array)
	{
		if (!_array || !isOk_s32data(_array)) throw dng; //Throws data not good.
		_os.write(_array->bin, *_array->offset);
		if (!_os) throw fng; //Throws file not good error.
		return;
	}

	/*
	 * Writes an array of characters followed by a choosen byte.
	 * This is the secure version checking either for corruption and array lenght limitation.
	 * Throws: fileNotGood exeption if there is a file I/O error.
	 *         dataNotGood exeption if the second parameter is corrupted
	 * Returns: the size of the array (from pos 0 until null character).
	 */
	int writeNextArray(const char* _array)
	{
		if (!_array) throw fng; //Throws data not good.
		int ret = strlen(_array);
		_os.write(_array, ret);
		if (!_os) throw fng; //Throws file not good error.
		return ret;
	}
	
	/*
	 * Manage a binary file output request for multiple types of data. 
	 * %% a percent sign.
	 * %c a character with the given number.
	 * %n writes an array of characters unsecure.
	 * %s writes an array of characters secure.
	 * %u writes an array of a specified 32 bit unsigned integer.
	 * %g in order to implement the algorithm for unknown data size, using
	 *    the command '%g' will tell the program to write the next s32data
	 *    type by in the first place first place writing the offset of the data
	 *    then the data themselves.
	 *    For obvious reasons, there is a null separator between both objects.
	 * Returns: the size of the array that has been formatted (from pos 0 until null character).
	 */
	__int32 writeMultipleFormats(const char* _format, ...)
	{
		int i = 0;
		va_list arg;
		va_start(arg, _format);

		for ( ; i < strlen(_format) ; i++)
		{
			if (_format[i] != '%')
			{
				//We write the characters as long as it is not a porcentage character.
				writeNextByte(_format[i]);
			}
			else
			{
				/*
					* Note that every single argument must be passed
					* by referenced to be correctly dereferenced here
					*/
				switch (_format[i + 1])
				{
					case '%': { writeNextByte('%');
								break; }
					case 'c': { char p = va_arg(arg, char);
								writeNextByte(p);
								break; }
					case 'n': { const char* p = va_arg(arg, const char*);
								writeNextArray(p);
								break; }
					case 's': { s32data* p = va_arg(arg, s32data*);
								writeNextArray(p);
								break; }
					case 'u': { unsigned __int32 p = va_arg(arg, unsigned __int32);
								writeNextPosSignedINT32(p);
							    break; }
					case 'g': { s32data* p = va_arg(arg, s32data*);
								writeNextPosSignedINT32(*(p)->offset);
								writeNextByte('\0');
								writeNextArray(p);
								break; }
					default : { break; }
						
				} i++;
			}
		}

		va_end(arg);
		return i;
	}
};