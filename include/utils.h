#pragma once

#include <type_traits>

template <typename> struct always_false : std::false_type {};

#define EPSILON 1e-6f
