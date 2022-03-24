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

		for (size_t i = 0; i + 1 < n + k; ++i) {
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

	// t[i - 1] < u <= t[i] left-continuous
	// if i = 0 then u <= t[0]
	// if i = n + k then t[n + k - 1] < u;
	template<class T>
	size_t index(size_t n, size_t k, const T* t, T u)
	{
		// first i with u <= *i
		auto i = std::lower_bound(t, t + n + k, u);

		return i - t;
	}

	// B_{i,k}(u)
	inline const char* B_doc = R"(
A <dfn>knot sequence</dfn>
is an array \((t_0,\ldots,t_{n + k})\) of non-decreasing numbers.
)";
	template<class T = double, class X = double>
	inline X B(size_t n, size_t k, const T* t, size_t i, double u)
	{
		size_t i = index(n, k, t, u);

		if (i == 0) {
			return X(0);
		}
		else if (i == n + k) {
			if (u == t[n + k - 1]) {
				return X(0); // !!! use right endpoint
			}
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
	inline X value(size_t n, size_t k, const T* t, const X* c, T u, size_t deriv = 0)
	{
		X B = 0;

		// size_t i = index(n, k, t, u);
		int i = 0; // i = ?(n, k, t, u)
		
		for (size_t j = 0; j < n /*i + k*/; ++j) {
			B += c[j] * B(n, k, t, j, u);
		}

		return B;
	}

	template<class T, class X>
	class curve {
		size_t n;
		size_t k;
		const T* t;
	};

} // namespace fms::bspline
