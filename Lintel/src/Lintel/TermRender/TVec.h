#pragma once

#include <cmath>

template <typename T>
struct TVec {
	T x;
	T y;
	T distTo(TVec<T> other);
	T dxTo(TVec<T> other);
	T dyTo(TVec<T> other);
};

template<typename T>
inline T TVec<T>::distTo(TVec<T> other)
{
	float dx = abs(x - other.x);
	float dy = abs(y - other.y);

	float dist = sqrt(dx * dx + dy * dy);
	
	return (T)dist;
}

template<typename T>
inline T TVec<T>::dxTo(TVec<T> other)
{
	return abs(x - other.x);
}

template<typename T>
inline T TVec<T>::dyTo(TVec<T> other)
{
	return abs(y - other.y);
}
