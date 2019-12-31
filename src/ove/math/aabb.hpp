#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace ove {
	namespace math {
		template <typename R, core::u8 D>
		struct aabb_t
		{
			using real = R;
			static const core::u8 Dim = D;
			vec_t<real, Dim> min;
			vec_t<real, Dim> max;
		};
	}
}