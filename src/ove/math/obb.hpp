#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace ove {
	namespace math {
		template <typename R, core::u8 D>
		struct obb_t
		{
			using real = R;
			static const core::u8 Dim = D;
			vec_t<real, Dim> min;
			vec_t<real, Dim> max;
			mat_t<real, Dim, Dim> space;
		};
	}
}