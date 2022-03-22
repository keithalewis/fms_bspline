// fms_bspline.t.cpp - Basis spline tests
#include <cassert>
#include "fms_bspline.h"

using namespace fms::bspline;

template<class T>
int test_ok(bool expected, size_t n, size_t k, const T* t)
{
	bool b = ok(n, k, t);
	assert(expected == b);

	return 0;
}
int ok_test1 = test_ok(true, 3, 0, std::begin({ 0, 1, 2 }));
int ok_test2 = test_ok(true, 2, 1, std::begin({ 0, 1, 1 }));
int ok_test3 = test_ok(false, 2, 1, std::begin({ 1., 1., 1. }));
int ok_test4 = test_ok(true, 1, 2, std::begin({ 1., 1., 1. }));

template<class T>
int test_index(size_t n, size_t k, const T* t, T u)
{
	size_t i = index(n, k, t, u);
	if (i > 0 and i < n + k) {
		assert(t[i] < u and u <= t[i + 1]);
	}

	return 0;
}

int main()
{
	return 0;
}