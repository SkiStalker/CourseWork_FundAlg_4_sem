#pragma once
#include <exception>

class TreeException : public std::exception
{
};

class AETreeException : public TreeException
{
public:
	const char* what() const override
	{
		return "Item already exists";
	}
};

class NETreeException : public TreeException
{
public:
	const char* what() const override
	{
		return "Item is not exists";
	}

};

class ICTreeException : public TreeException
{
public:
	const char* what() const override
	{
		return "Invalid comparator value";
	}
};