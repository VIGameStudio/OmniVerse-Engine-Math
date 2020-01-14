#pragma once

#include "impl/vmath_impl.hpp"

namespace ove
{
	namespace math
	{
		template <typename T, core::u8 S> struct vec_t;

		template <typename T> struct quat_t;
		using quatf = quat_t<core::f32>;
		using quatd = quat_t<core::f64>;

		template <typename R>
		struct quat_t : public vec_t<R, 4u>
		{
			using type = quat_t<R>;
			using real = R;

			quat_t()
				: vec_t<R, 4u>(0, 0, 0, 1)
			{}

			quat_t(real x, real y, real z, real w)
				: vec_t<R, 4u>(x, y, z, w)
			{}
		};
	}
}