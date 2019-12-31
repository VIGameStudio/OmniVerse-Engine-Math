#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace ove {
	namespace math {
		template <typename R, core::u8 D>
		struct ray_t
		{
			using real = R;
			static const core::u8 Dim = D;
			vec_t<real, Dim> origin;
			vec_t<real, Dim> direction;
		};

		template <typename R, core::u8 D>
		struct mray_t : public ray_t<R, D>
		{
			using real = R;
			static const core::u8 Dim = D;
			vec_t<real, Dim> inv_direction;
		};
	}
}