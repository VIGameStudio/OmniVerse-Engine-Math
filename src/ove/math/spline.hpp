#pragma once

#include <ove/core/util/types.hpp>

namespace ove {
	namespace math {
		template <typename R, core::u8 D>
		struct spline_t
		{
			using real = R;
			static const core::u8 Dim = D;
		};
	}
}