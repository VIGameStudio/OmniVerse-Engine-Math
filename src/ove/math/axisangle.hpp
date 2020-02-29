#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace ove
{
	namespace math
	{
		template <typename T>
		struct axisangle_t;

		template <typename T>
		using axisangle = axisangle_t<T>;
		using axisanglef = axisangle<core::f32>;
		using axisangled = axisangle<core::f64>;

		template <typename R>
		struct axisangle_t : public vec_t<R, 4u>
		{
			using type = axisangle_t<R>;
			using real = R;

			axisangle_t()
				: vec_t<R, 4u>(0, 0, 0, 0)
			{}

			axisangle_t(real x, real y, real z, real w)
				: vec_t<R, 4u>(x, y, z, w)
			{}
		};
	}
}