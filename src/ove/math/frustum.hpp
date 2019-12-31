#pragma once

#include <ove/core/util/types.hpp>

namespace ove {
	namespace math {
		template <typename T> struct frustum_t;
		using frustumf = frustum_t<core::f32>;
		using frustumd = frustum_t<core::f64>;

		template <typename R> struct frustum_t {
			using real = R;
			real left, right;
			real top, bottom;
			real near, far;
		};
	}
}