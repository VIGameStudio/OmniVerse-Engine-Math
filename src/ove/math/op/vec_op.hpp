#pragma once

#include <cmath>

#include <ove/core/util/assert.hpp>
#include <ove/core/util/types.hpp>
#include <ove/math/util/utils.hpp>

namespace ove
{
	namespace math
	{
		template <typename T, core::u8 S> struct vec_t;

		template <typename T1, typename T2, core::u8 S>
		inline auto operator+(const vec_t<T1, S>& l, const vec_t<T2, S>& r)
			->vec_t<decltype(l.x + r.x), S>
		{
			vec_t<decltype(l.x + r.x), S> res;
			for (core::u8 i = 0; i < S; ++i)
				res.data[i] = l.data[i] + r.data[i];

			return res;
		}

		template <typename T1, typename T2, core::u8 S>
		inline auto operator-(const vec_t<T1, S>& l, const vec_t<T2, S>& r)
			->vec_t<decltype(l.x - r.x), S>
		{
			vec_t<decltype(l.x - r.x), S> res;
			for (core::u8 i = 0; i < S; ++i)
				res.data[i] = l.data[i] - r.data[i];

			return res;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> operator-(const vec_t<T, S>& r)
		{
			return vec_t<T, S>(-r.x, -r.y, -r.z);
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> operator*(const vec_t<T, S>& l, T r)
		{
			vec_t<T, S> res;
			for (core::u8 i = 0; i < S; ++i)
				res.data[i] = l.data[i] * r;

			return res;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> operator*(T l, const vec_t<T, S>& r)
		{
			vec_t<T, S> res;
			for (core::u8 i = 0; i < S; ++i)
				res.data[i] = l * r.data[i];

			return res;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> operator*(const vec_t<T, S>& l, const vec_t<T, S>& r)
		{
			vec_t<T, S> res;
			for (core::u8 i = 0; i < S; ++i)
				res.data[i] = l.data[i] * r.data[i];

			return res;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> operator/(const vec_t<T, S>& l, T r)
		{
			ASSERT(r != 0);

			const T ir = 1.0 / r;
			vec_t<T, S> res;
			for (core::u8 i = 0; i < S; ++i)
				res.data[i] = l.data[i] * ir;

			return res;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> operator/(T l, const vec_t<T, S>& r)
		{
			ASSERT(l != 0);

			vec_t<T, S> res;
			for (core::u8 i = 0; i < S; ++i)
				res.data[i] = l / r.data[i];

			return res;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S>& operator+=(vec_t<T, S>& l, const vec_t<T, S>& r)
		{
			for (core::u8 i = 0; i < S; ++i)
				l.data[i] += r.data[i];

			return l;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S>& operator-=(vec_t<T, S>& l, const vec_t<T, S>& r)
		{
			for (core::u8 i = 0; i < S; ++i)
				l.data[i] -= r.data[i];

			return l;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S>& operator*=(vec_t<T, S>& l, T r)
		{
			for (core::u8 i = 0; i < S; ++i)
				l.data[i] *= r;

			return l;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S>& operator/=(vec_t<T, S>& l, T r)
		{
			ASSERT(r != 0);

			const T ir = 1.0 / r;
			for (core::u8 i = 0; i < S; ++i)
				l.data[i] *= ir;

			return l;
		}

		template <typename T, core::u8 S>
		inline bool operator==(const vec_t<T, S>& l, const vec_t<T, S>& r)
		{
			for (core::u8 i = 0; i < S; ++i)
				if (l.data[i] != r.data[i])
					return false;

			return true;
		}

		template <typename T, core::u8 S>
		inline bool operator!=(const vec_t<T, S>& l, const vec_t<T, S>& r)
		{
			for (core::u8 i = 0; i < S; ++i)
				if (l.data[i] == r.data[i])
					return false;

			return true;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> abs(const vec_t<T, S>& v)
		{
			auto tmp = v;
			for (core::u8 i = 0; i < S; ++i)
				tmp.data[i] = std::abs(v.data[i]);

			return tmp;
		}

		template <typename T, core::u8 S>
		inline T lengthPow(const vec_t<T, S>& v, T exp)
		{
			T lenSq = 0;
			for (core::u8 i = 0; i < S; ++i)
				lenSq += std::pow(v.data[i], exp);

			return lenSq;
		}

		template <typename T, core::u8 S>
		inline T lengthSq(const vec_t<T, S>& v)
		{
			T lenSq = 0;
			for (core::u8 i = 0; i < S; ++i)
				lenSq += v.data[i] * v.data[i];

			return lenSq;
		}

		template <typename T, core::u8 S>
		inline T length(const vec_t<T, S>& v)
		{
			return std::sqrt(lengthSq(v));
		}

		template <typename T, core::u8 S>
		inline void normalize(vec_t<T, S>& v)
		{
			const auto len = length(v);
			ASSERT(len != 0 && "Division by zero!");
			v /= len;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> normalized(const vec_t<T, S>& v)
		{
			auto tmp = v;
			normalize(tmp);
			return tmp;
		}

		template <typename T, core::u8 S>
		inline T dot(const vec_t<T, S>& v1, const vec_t<T, S>& v2)
		{
			T tmp = 0;
			for (core::u8 i = 0; i < S; ++i)
				tmp += v1.data[i] * v2.data[i];

			return tmp;
		}

		template <typename T, core::u8 S>
		inline vec_t<T, S> project(const vec_t<T, S>& v1, const vec_t<T, S>& v2)
		{
			const auto pv = normalized(v2);
			return pv * dot(v1, pv);
		}

		template <typename T, typename R>
		inline T lerp(const T& v1, const T& v2, R t)
		{
			return v1 + (v2 - v1) * t;
		}

		template <typename T>
		inline vec_t<T, 3u> cross(const vec_t<T, 3u>& v1, const vec_t<T, 3u>& v2)
		{
			return vec_t<T, 3u>(
				v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x);
		}
	}
}