#pragma once

#include <cmath>

#include <ove/core/util/assert.hpp>
#include <ove/core/util/types.hpp>
#include <ove/math/util/utils.hpp>

namespace ove
{
	namespace math
	{
		template <typename T, core::u8 R, core::u8 C> struct mat_t;

		template <typename T, core::u8 N>
		inline mat_t<T, N, N> operator*(const mat_t<T, N, N>& l, const mat_t<T, N, N>& r)
		{
			mat_t<T, N, N> res(0.f);
			for (core::u8 i = 0; i < N; ++i)
				for (core::u8 j = 0; j < N; ++j)
					for (core::u8 k = 0; k < N; ++k)
						res.m[i][j] += l.m[i][k] * r.m[k][j];
			return res;
		}

		template <typename T, core::u8 N>
		inline mat_t<T, N, N> operator*(mat_t<T, N, N>& l, T r)
		{
			mat_t<T, N, N> res(0.f);
			for (core::u8 i = 0; i < N; ++i)
				for (core::u8 j = 0; j < N; ++j)
					res.m[i][j] = l.m[i][j] * r;
			return res;
		}

		template <typename T, core::u8 N>
		inline void operator*=(mat_t<T, N, N>& l, T r)
		{
			for (core::u8 i = 0; i < N; ++i)
				for (core::u8 j = 0; j < N; ++j)
					l.m[i][j] *= r;
		}

		template <typename T> inline T determinant(const mat_t<T, 2u, 2u>& m)
		{
			return m[0] * m[3] - m[1] * m[2];
		}

		template <typename T, core::u8 N> inline T determinant(const mat_t<T, N, N>& m)
		{
			T res = 0;
			size_t z = 0;
			mat_t<T, N - 1, N - 1> tmp((T)0);

			for (core::u8 i = 0; i < N; ++i) {
				const T s = i % 2 == 0 ? m.m[0][i] : -m.m[0][i];

				z = 0;
				for (core::u8 j = 1; j < N; ++j) {
					for (core::u8 k = 0; k < N; ++k) {
						if (i == k)
							continue;
						tmp[z++] = m.m[j][k];
					}
				}

				res += s * determinant(tmp);
			}

			return res;
		}

		template <typename T, core::u8 N>
		inline void invert(mat_t<T, N, N>& m)
		{
			const T det = determinant(m);
			ASSERT(det != 0 && "No determinant for matrix!");
			const T idet = 1.0 / det;

			mat_t<T, N, N> minors((T)0);
			mat_t<T, N - 1, N - 1> tmp((T)0);
			T dtmp = 0;
			size_t z = 0;

			for (core::u8 x = 0; x < N; ++x)
			{
				for (core::u8 y = 0; y < N; ++y)
				{
					z = 0;
					for (core::u8 i = 0; i < N; ++i)
					{
						for (core::u8 j = 0; j < N; ++j)
						{
							if (i == x || j == y)
								continue;

							tmp[z++] = m.m[i][j];
						}
					}

					dtmp = determinant(tmp);
					minors.m[y][x] = (x + y) % 2 == 0 ? dtmp : -dtmp;
				}
			}

			m = minors * idet;
		}

		template <typename T, core::u8 R, core::u8 C>
		inline mat_t<T, R, C> inverse(const mat_t<T, R, C>& m)
		{
			mat_t<T, R, C> res = m;
			invert(res);
			return res;
		}

		template <typename T, core::u8 R, core::u8 C>
		inline void transpose(mat_t<T, R, C>& m)
		{
			ASSERT(false && "TODO");
		}

		template <typename T, core::u8 R, core::u8 C>
		inline mat_t<T, R, C> transposed(const mat_t<T, R, C>& m)
		{
			mat_t<T, R, C> res = m;
			transpose(res);
			return res;
		}
	}
}