#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace ove
{
	namespace math
	{
		template <typename T> struct euler_t;
		using eulerf = euler_t<core::f32>;
		using eulerd = euler_t<core::f64>;

		enum struct euler_order
		{
			XYZ
		};

		template <typename R>
		struct euler_t : public vec_t<R, 3u>
		{
			using type = euler_t<R>;
			using real = R;

			euler_t()
				: vec_t<R, 3u>(0, 0, 0)
			{}

			euler_t(real x, real y, real z)
				: vec_t<R, 3u>(x, y, z)
			{}

			euler_order order;
		};
	}
}