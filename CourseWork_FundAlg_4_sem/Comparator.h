#pragma once
template <typename T>
class Comparator
{
public:
	virtual int compare(const T& left, const T& right)const = 0;
	virtual ~Comparator() {};
};