#ifndef EXCEPTION_H
#define EXCEPTION_H

class fileNotGood : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "File not good exception.";
	}
} const fng;

class FormatSyntax : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Format syntax.";
	}
} const fs;

class DataNotGood : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Data not good exception.";
	}
} const dng;
#endif