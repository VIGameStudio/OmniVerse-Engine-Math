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
		template <typename T, core::u8 R, core::u8 C> struct mat_t;
		template <typename T> struct quat_t;

		template <typename T, core::u8 N>
		inline vec_t<T, N> operator*(const mat_t<T, N, N>& l, const vec_t<T, N>& r)
		{
			vec_t<T, N> res(0.f);
			for (core::u8 i = 0; i < N; ++i)
				for (core::u8 j = 0; j < N; ++j)
					res.data[i] += l.m[i][j] * res.data[j];
			return res;
		}

		template <typename T>
		inline vec_t<T, 3u> operator*(const quat_t<T>& l, const vec_t<T, 3u>& r)
		{
			const vec_t<T, 3u> q(l.x, l.y, l.z);
			const vec_t<T, 3u> t = (T)2 * cross(r, q);
			return r + l.w * t + cross(t, q);
		}

		template <typename T>
		inline mat_t<T, 4u, 4u> translate(const vec_t<T, 3u>& v)
		{
			mat_t<T, 4u, 4u> res;
			res.m[3][0] = v.x;
			res.m[3][1] = v.y;
			res.m[3][2] = v.z;
			return res;
		}

		template <typename T>
		inline mat_t<T, 4u, 4u> rotate(const vec_t<T, 3u>& v)
		{
			const T ax = deg2rad(v.x);
			const T ay = deg2rad(v.y);
			const T az = deg2rad(v.z);

			const T ch = std::cos(ax);
			const T sh = std::sin(ax);
			const T ca = std::cos(ay);
			const T sa = std::sin(ay);
			const T cb = std::cos(az);
			const T sb = std::sin(az);

			mat_t<T, 4u, 4u> res;
			res.m[0][0] = ch * ca;
			res.m[0][1] = sh * sb - ch * sa * cb;
			res.m[0][2] = ch * sa * sb + sh * cb;
			res.m[1][0] = sa;
			res.m[1][1] = ca * cb;
			res.m[1][2] = -ca * sb;
			res.m[2][0] = -sh * ca;
			res.m[2][1] = sh * sa * cb + ch * sb;
			res.m[2][2] = -sh * sa * sb + ch * cb;
			return res;
		}

		template <typename T>
		inline mat_t<T, 4u, 4u> rotate(T a, const vec_t<T, 3u>& v)
		{
			const T rad = deg2rad(a);
			const T c = std::cos(rad);
			const T s = std::sin(rad);
			const T t = 1.0 - c;

			mat_t<T, 4u, 4u> res;
			res.m[0][0] = c + v.x * v.x * t;
			res.m[1][1] = c + v.y * v.y * t;
			res.m[2][2] = c + v.z * v.z * t;

			T tmp1 = v.x * v.y * t;
			T tmp2 = v.z * s;
			res.m[1][0] = tmp1 + tmp2;
			res.m[0][1] = tmp1 - tmp2;

			tmp1 = v.x * v.z * t;
			tmp2 = v.y * s;
			res.m[2][0] = tmp1 - tmp2;
			res.m[0][2] = tmp1 + tmp2;

			tmp1 = v.y * v.z * t;
			tmp2 = v.x * s;
			res.m[2][1] = tmp1 + tmp2;
			res.m[1][2] = tmp1 - tmp2;

			return res;
		}

		template <typename T>
		inline mat_t<T, 4u, 4u> rotate(const quat_t<T>& q)
		{
			const T sqw = q.w * q.w;
			const T sqx = q.x * q.x;
			const T sqy = q.y * q.y;
			const T sqz = q.z * q.z;

			// invs (inverse square length) is only required if quaternion is not already
			// normalized
			const T t = sqx + sqy + sqz + sqw;
			ASSERT(t != 0 && "Can't normalize quaternion of length 0!");
			const T invs = (T)1.0 / t;

			mat_t<T, 4u, 4u> res(0.0);
			res.m[0][0] = (sqx - sqy - sqz + sqw) * invs;
			res.m[1][1] = (-sqx + sqy - sqz + sqw) * invs;
			res.m[2][2] = (-sqx - sqy + sqz + sqw) * invs;

			T tmp1 = q.x * q.y;
			T tmp2 = q.z * q.w;
			res.m[1][0] = 2.0 * (tmp1 + tmp2) * invs;
			res.m[0][1] = 2.0 * (tmp1 - tmp2) * invs;

			tmp1 = q.x * q.z;
			tmp2 = q.y * q.w;
			res.m[2][0] = 2.0 * (tmp1 - tmp2) * invs;
			res.m[0][2] = 2.0 * (tmp1 + tmp2) * invs;

			tmp1 = q.y * q.z;
			tmp2 = q.x * q.w;
			res.m[2][1] = 2.0 * (tmp1 + tmp2) * invs;
			res.m[1][2] = 2.0 * (tmp1 - tmp2) * invs;

			return res;
		}

		template <typename T>
		inline mat_t<T, 4u, 4u> scale(const vec_t<T, 3u>& v)
		{
			mat_t<T, 4u, 4u> res;
			res.m[0][0] = v.x;
			res.m[1][1] = v.y;
			res.m[2][2] = v.z;
			return res;
		}

		template <typename T>
		inline mat_t<T, 4u, 4u> scale(T s)
		{
			mat_t<T, 4u, 4u> res;
			res.m[0][0] = s;
			res.m[1][1] = s;
			res.m[2][2] = s;
			return res;
		}

		/**
		 * Look At
		 */
		template <typename T>
		inline mat_t<T, 4u, 4u> lookAt(const vec_t<T, 3u>& eye, const vec_t<T, 3u>& center, const vec_t<T, 3u>& up)
		{
			const vec_t<T, 3u> k(normalized(center - eye));
			const vec_t<T, 3u> i(normalized(cross(k, up)));
			const vec_t<T, 3u> j(cross(i, k));

			mat_t<T, 4u, 4u> res;
			res.m[0][0] = i.x;
			res.m[1][0] = i.y;
			res.m[2][0] = i.z;

			res.m[0][1] = j.x;
			res.m[1][1] = j.y;
			res.m[2][1] = j.z;

			res.m[0][2] = -k.x;
			res.m[1][2] = -k.y;
			res.m[2][2] = -k.z;

			res.m[3][0] = -dot(i, eye);
			res.m[3][1] = -dot(j, eye);
			res.m[3][2] = dot(k, eye);
			return res;
		}

		/**
		 * Orthographic
		 */
		template <typename T>
		inline mat_t<T, 4u, 4u> orthographic(T left, T right, T top, T bottom, T znear, T zfar)
		{
			const T sx = right - left;
			const T sy = top - bottom;
			const T sz = zfar - znear;

			mat_t<T, 4u, 4u> res;
			res.m[0][0] = (T)2.0 / sx;
			res.m[1][1] = (T)2.0 / sy;
			res.m[2][2] = (T)-2.0 / sz;

			res.m[3][0] = -(right + left) / sx;
			res.m[3][1] = -(top + bottom) / sy;
			res.m[3][2] = -(zfar + znear) / sz;
			return res;
		}

		/**
		 * Frustum
		 */
		template <typename T>
		inline mat_t<T, 4u, 4u> frustum(T left, T right, T top, T bottom, T znear, T zfar)
		{
			const auto zero = static_cast<T>(0.0);
			const auto one = static_cast<T>(1.0);
			const auto two = static_cast<T>(2.0);

			const T sx = right - left;
			const T sy = top - bottom;
			const T sz = zfar - znear;

			mat_t<T, 4u, 4u> res(zero);
			res.m[0][0] = two * znear / sx;
			res.m[1][1] = two * znear / sy;
			res.m[2][0] = right + left / sx;
			res.m[2][1] = top + bottom / sy;
			res.m[2][2] = -(zfar + znear) / sz;
			res.m[2][3] = -one;
			res.m[3][2] = -two * zfar * znear / sz;
			return res;
		}

		/**
		 * Perspective
		 */
		template <typename T>
		inline mat_t<T, 4u, 4u> perspective(T aspect, T fov, T znear, T zfar)
		{
			const auto one = static_cast<T>(1.0);
			const auto half = static_cast<T>(0.5);

			/*const T hrad = one / deg2rad(fov) * half;
			const T top = near * std::tan(hrad);
			const T right = top * aspect;
			return frustum(-right, right, top, -top, near, far);*/

			const auto htan = std::tan(deg2rad(fov) * half);

			mat_t<T, 4u, 4u> res(T(0));
			res.m[0][0] = one / (aspect * htan);
			res.m[1][1] = one / (htan);
			res.m[2][2] = zfar / (znear - zfar);
			res.m[2][3] = -one;
			res.m[3][2] = -(zfar * znear) / (zfar - znear);
			return res;
		}
	}
}