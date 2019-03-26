#pragma once

#include <vector>

template <typename T>
std::vector<T> linspace(T a, T b, size_t n) {
	T h = (b - a) / static_cast<T>(n - 1);
	std::vector<T> xs(n);
	typename std::vector<T>::iterator x;
	T val;
	for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h)
		*x = val;
	return xs;
}

template <typename T>
double mean(std::vector<T> &v)
{
	double s = 0;

	for (T i : v)
	{
		s = s + static_cast<double>(i);
	}

	return s / static_cast<double>(v.size());
}