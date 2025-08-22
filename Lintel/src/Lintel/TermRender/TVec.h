#pragma once

#include "lnpch.h"

template <typename T>
struct TVec {
	T x, y;
	T DistanceTo(TVec<T> other);
	T HorizontalDistanceTo(TVec<T> other);
	T VerticalDistanceTo(TVec<T> other);

	bool operator==(TVec<T> other);
};

template<typename T>
inline T TVec<T>::DistanceTo(TVec<T> other)
{
	float dx = abs(x - other.x);
	float dy = abs(y - other.y);

	float dist = sqrt(dx * dx + dy * dy);
	
	return (T)dist;
}

template<typename T>
inline T TVec<T>::HorizontalDistanceTo(TVec<T> other)
{
	return abs(x - other.x);
}

template<typename T>
inline T TVec<T>::VerticalDistanceTo(TVec<T> other)
{
	return abs(y - other.y);
}

template<typename T>
inline bool TVec<T>::operator==(TVec<T> other)
{
	// Rough guesstimate of equality: would this draw in the same character cell?
	return ((int)x == (int)other.x && (int)y == (int)other.y);
}
