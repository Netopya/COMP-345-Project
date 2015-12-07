#include "Writer.h"

Writer::Writer(string _fileName)
{
	isOpened = false;
	fileName = _fileName;
}
Writer::~Writer()
{
	free(integerBuffer);
}
bool Writer::Open()
{
	isOpened = false;
	_os.open(fileName, ios::binary);
	isOpened = _os ? true : false;
	return isOpened;
}
void Writer::Close()
{
	_os.close();
	isOpened = false;
}
bool Writer::IsOpened()
{
	return isOpened;
}

/*
* Writes a POSITIVE SIGNED INT32 value inside a file.
* Throws: fileNotGood if there is a file I/O error while writing.
* Returns: the size of the array of the converted number.
*/
int Writer::writeNextPosSignedINT32(unsigned int _array)
{
	_itoa_s(_array, integerBuffer, 10);
	size_t ret = strlen(integerBuffer);
	_os.write(integerBuffer, ret);
	if (!_os) throw fng; //Throws file not good error.
	return (int)ret;
}

/*
* Writes a byte of data at the end of a file.
* Throws: fileNotGood exeption if there is a file I/O error.
*/
void Writer::writeNextByte(char _array)
{
	_os.write(&_array, 1); //Avoids NULL exeptions.
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
int Writer::writeNextArray(const char* _array)
{
	if (!_array) throw fng; //Throws data not good.
	size_t ret = strlen(_array);
	_os.write(_array, ret);
	if (!_os) throw fng; //Throws file not good error.
	return (int)ret;
}

/*
* Manage a binary file output request for multiple types of data.
* %% a percent sign.
* %c a character with the given number.
* %n writes an array of characters unsecure.
* %s writes an array of characters secure.
* %u writes an array of a specified 32 bit unsigned integer.
* Returns: the size of the array that has been formatted (from pos 0 until null character).
*/
__int32 Writer::writeMultipleFormats(const char* _format, ...)
{
	int i = 0;
	va_list arg;
	va_start(arg, _format);

	for (; i < strlen(_format); i++)
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
			case 'u': { unsigned int p = va_arg(arg, unsigned int);
				writeNextPosSignedINT32(p);
				break; }
			default: { break; }

			} i++;
		}
	}

	va_end(arg);
	return i;
}