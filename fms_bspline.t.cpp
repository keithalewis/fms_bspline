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
	assert(ok(n, k, t));

	size_t i = index(n, k, t, u);
	if (i > 0 and i < n + k) {
		assert(t[i - 1] < u and u <= t[i]);
	}

	return 0;
}
int index_test = []() {
	{
		double t[] = {1, 2, 3};
		for (double u : {-1., -.5, 0., 0.5, 1., 1.5, 2., 2.5, 3., 3.5})
		test_index<double>(3, 0, t, u);
	}
	{
		double t[] = { 1, 2, 2, 3 };
		for (double u : {-1., -.5, 0., 0.5, 1., 1.5, 2., 2.5, 3., 3.5})
			test_index<double>(3, 1, t, u);
	}
	{
		double t[] = { 1, 1, 2, 3 };
		for (double u : {-1., -.5, 0., 0.5, 1., 1.5, 2., 2.5, 3., 3.5})
			test_index<double>(3, 1, t, u);
	}
	{
		double t[] = { 1, 2, 3, 3 };
		for (double u : {-1., -.5, 0., 0.5, 1., 1.5, 2., 2.5, 3., 3.5})
			test_index<double>(3, 1, t, u);
	}
	{
		double t[] = { 1, 1, 1 };
		for (double u : {-1., -.5, 0., 0.5, 1., 1.5, 2., 2.5, 3., 3.5})
			test_index<double>(1, 2, t, u);
	}

	return 0;
}();
int index_test1 = []() {
	{
		double t[] = { 1, 2, 3 };
		assert(0 == index<double>(3, 0, t, 0));
		assert(0 == index<double>(3, 0, t, 1));
		assert(1 == index<double>(3, 0, t, 1.5));
		assert(1 == index<double>(3, 0, t, 2));
		assert(2 == index<double>(3, 0, t, 3));
		assert(3 == index<double>(3, 0, t, 3.5));
	}

	return 0;
}();

int main()
{
	return 0;
}