// fms_bspline.h - Basis splines
// f(x) = sum_{i < n} c_i B_{i,k}(x)
// t = (t_0, ..., t_{n+k-1})
#pragma once
#include <algorithm>

namespace fms::bspline {

	// Non-decreasing knot sequence with at most k repeats.
	template<class T = double>
	inline bool ok(size_t n, size_t k, const T* t)
	{
		size_t rep = 0;

		for (size_t i = 0; i < n + k - 1; ++i) {
			if (t[i] == t[i + 1]) {
				++rep;
				if (rep > k) {
					return false;
				}
			}
			else if (t[i] < t[i + 1]) {
				rep = 0;
			}
			else {
				return false;
			}
		}

		return true;
	}

	// t[i] < u <= t[i+1] left-continuous
	template<class T>
	size_t index(size_t n, size_t k, const T* t, T u)
	{
		// u <= *i
		auto i = std::lower_bound(t, t + n + k, u);

		return i - t;
	}

	// B_{i,k}(x)
	template<class T = double, class X = double>
	inline X B(size_t n, size_t k, const T* t, size_t i, double u)
	{
		size_t i = index(n, k, t, u);

		if (i == 0 or i == n + k) {
			return X(0);
		}
		else if (k == 1) {
			return X(1);
		}

		return B(n, k - 1, t, i, u) * (u - t[i]) / (t[i + k - 1] - t[i])
			+ B(n, k - 1, t, i - 1, u) * (t[i + k] - u) / (t[i + k] - t[i + 1]);
	}

	// Evaluate basis spline at u.
	template<class T = double, class X = double>
	inline X evaluate(size_t n, size_t k, const T* t, const X* c, T u, size_t deriv = 0)
	{
		return 0;
	}
} // namespace fms::bspline
