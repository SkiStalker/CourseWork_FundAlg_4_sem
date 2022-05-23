#pragma once
#include "Comparator.h"

template <typename T>
class DefaultComparator : public Comparator<T>
{
	int compare(const T& left, const T& right)const override;
};

template<typename T>
inline int DefaultComparator<T>::compare(const T& left, const T& right) const
{
	if (left < right)
		return -1;
	if (left > right)
		return 1;
	return 0;
}