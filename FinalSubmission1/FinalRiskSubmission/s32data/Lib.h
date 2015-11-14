#pragma once

#define _CRT_SECURE_NO_WARNINGS

typedef struct
{
	char* bin;
	unsigned __int32* offset;

} s32data;

void co_s32data(s32data* _target)
{
	printf("s32data\n");
	printf("- Size: %d\n", *_target->offset);
	printf("- Array: ");
	for (int i = 0; i < *_target->offset; i++)
	{
		printf("%c", _target->bin[i]);
	}
	printf("|\n");
}
/*
 * Checks wheater or not s32data is corrupted.
 * Returns true: ok
 *         false: corrupted
 */
bool isOk_s32data(s32data* _in)
{
	return (_in->bin[*_in->offset] == '\0');
}

/*
 * Creates a array of 32 bits data of the size desired.
 * Allocates one additionnal bit for a null character.
 * e.g.: mk_s32data(6) -> _|_|_|_|_|_|\0
 *
 * If 'nullCharException' is true, the software will
 * assume that the first null character it encounter
 * (even if it is before the end of the array) represent
 * the and of the data.
 */
s32data* mk_s32data(__int32 _offset, const char* _bin, bool nullCharException)
{
	s32data* ret = (s32data*)malloc(sizeof(s32data));
	if (ret == NULL)
		return NULL;

	if (nullCharException)
	{
		int testOffset = strlen(_bin);
		if (testOffset != _offset)
			return NULL;
	}

	ret->bin = (char*)malloc(sizeof(char) * _offset + 1);
	
	//NOTA BENE: Since s32data struct manages is own size, we do not
	//           use memset or alloc in order to have a null char at the
	//           end of the array. But I still add an additionnal char at
	//           the end for safety reasons.
	ret->bin[_offset] = 0;

	if (ret->bin == NULL)
	{
		free(ret);
		return NULL;
	}
	
	ret->offset = (unsigned __int32*)malloc(sizeof(unsigned __int32));
	if (ret->offset == NULL)
	{
		free(ret->bin);
		free(ret);
		return NULL;
	}

	*(ret->offset) = _offset;

	strncpy(ret->bin, _bin, _offset);
	if (!isOk_s32data(ret))
		return NULL;

	return ret;
}
s32data* mk_s32data(__int32 _offset)
{

	s32data* ret = (s32data*)malloc(sizeof(s32data));
	if (ret == NULL)
		return NULL;

	ret->bin = (char*)malloc(sizeof(char) * (_offset + 1));
	if (ret->bin == NULL)
	{
		free(ret);
		return NULL;
	}
	//NOTA BENE: Since s32data struct manages is own size, we do not
	//           use memset or alloc in order to have a null char at the
	//           end of the array. But I still add an additionnal char at
	//           the end for safety reasons.
	ret->bin[_offset] = 0;
	
	ret->offset = (unsigned __int32*)malloc(sizeof(unsigned __int32));
	if (ret->offset == NULL)
	{
		free(ret->bin);
		free(ret);
		return NULL;
	}
	*(ret->offset) = _offset;
	return ret;
}


inline void dl_s32data(s32data* _rubbish)
{	
	if (_rubbish)
	{
		free(_rubbish->offset);
		free(_rubbish->bin);
		free(_rubbish);
	}
}