#pragma once

class fileNotGood : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "File not good exception.";
	}
} const fng;

class FormatSyntax : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Format syntax.";
	}
} const fs;

class DataNotGood : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Data not good exception.";
	}
} const dng;