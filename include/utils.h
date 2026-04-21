#pragma once

#include <type_traits>

template <typename> struct always_false : std::false_type {};

#define EPSILON 1e-6f

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}



#include <glm/glm.hpp>
#include <iostream>

template <glm::length_t L, typename T, glm::qualifier Q>
std::ostream& operator<<(std::ostream& os, const glm::vec<L, T, Q>& vec)
{
	os << "(";
	for (glm::length_t i = 0; i < L; ++i)
	{
		os << vec[i];
		if (i < L - 1) os << ", ";
	}
	os << ")";
	return os;
}