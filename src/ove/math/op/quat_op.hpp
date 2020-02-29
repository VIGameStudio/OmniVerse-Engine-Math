#pragma once

#include <cmath>

#include <ove/core/util/assert.hpp>
#include <ove/core/util/types.hpp>
#include <ove/math/util/utils.hpp>

namespace ove
{
	namespace math
	{
		template <typename T> struct quat_t;

		template <typename T>
		inline quat_t<T> operator*(const quat_t<T>& l, const quat_t<T>& r)
		{
			return quat_t<T>(
				l.w * r.x + l.x * r.w + l.y * r.z - l.z * r.y,
				l.w * r.y + l.y * r.w + l.z * r.x - l.x * r.z,
				l.w * r.z + l.z * r.w + l.x * r.y - l.y * r.x,
				l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z);
		}

		template <typename T>
		inline void operator*=(quat_t<T>& l, const quat_t<T>& r)
		{
			l.x = l.w * r.x + l.x * r.w + l.y * r.z - l.z * r.y;
			l.y = l.w * r.y + l.y * r.w + l.z * r.x - l.x * r.z;
			l.z = l.w * r.z + l.z * r.w + l.x * r.y - l.y * r.x;
			l.w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
		}

		template <typename T>
		inline void conjugate(quat_t<T>& q)
		{
			q.x = -q.x;
			q.y = -q.y;
			q.z = -q.z;
		}

		template <typename T>
		inline quat_t<T> conjugated(const quat_t<T>& q)
		{
			auto tmp = q;
			conjugate(tmp);
			return tmp;
		}

		template <typename T>
		inline quat_t<T> eulerAngles(const vec_t<T, 3u>& v)
		{
			const T hax = deg2rad(v.x * (T)0.5);
			const T hay = deg2rad(v.y * (T)0.5);
			const T haz = deg2rad(v.z * (T)0.5);

			const T c1 = std::cos(hax);
			const T s1 = std::sin(hax);
			const T c2 = std::cos(hay);
			const T s2 = std::sin(hay);
			const T c3 = std::cos(haz);
			const T s3 = std::sin(haz);

			const T c1c2 = c1 * c2;
			const T s1s2 = s1 * s2;

			quat_t<T> res;
			res.w = c1c2 * c3 - s1s2 * s3;
			res.z = c1c2 * s3 + s1s2 * c3;
			res.x = s1 * c2 * c3 + c1 * s2 * s3;
			res.y = c1 * s2 * c3 - s1 * c2 * s3;
			return res;
		}

		template <typename T>
		inline quat_t<T> axisAngle(const vec_t<T, 3u>& v, T a)
		{
			const T hrad = deg2rad(a) * (T)0.5;
			const T sa = std::sin(hrad * (T)2.0);

			quat_t<T> res;
			res.x = v.x * sa;
			res.y = v.y * sa;
			res.z = v.z * sa;
			res.w = std::cos(hrad);
			return res;
		}
	}
}