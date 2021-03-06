#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/op/mat_op.hpp>
#include <ove/math/op/trx_op.hpp>

namespace ove
{
	namespace math
	{
		template <typename R, core::u8 D> struct vec_t;
		template <typename R, core::u8 N, core::u8 M> struct mat_t;

		template <typename R> using mat2_t = mat_t<R, 2u, 2u>;
		using mat2u = mat2_t<core::u32>;
		using mat2i = mat2_t<core::i32>;
		using mat2f = mat2_t<core::f32>;
		using mat2d = mat2_t<core::f64>;

		template <typename R> using mat2x1_t = mat_t<R, 2u, 1u>;
		using mat2x1u = mat2x1_t<core::u32>;
		using mat2x1i = mat2x1_t<core::i32>;
		using mat2x1f = mat2x1_t<core::f32>;
		using mat2x1d = mat2x1_t<core::f64>;

		template <typename R> using mat3_t = mat_t<R, 3u, 3u>;
		using mat3u = mat3_t<core::u32>;
		using mat3i = mat3_t<core::i32>;
		using mat3f = mat3_t<core::f32>;
		using mat3d = mat3_t<core::f64>;

		template <typename R> using mat3x2_t = mat_t<R, 3u, 2u>;
		using mat3x2u = mat3x2_t<core::u32>;
		using mat3x2i = mat3x2_t<core::i32>;
		using mat3x2f = mat3x2_t<core::f32>;
		using mat3x2d = mat3x2_t<core::f64>;

		template <typename R> using mat4_t = mat_t<R, 4u, 4u>;
		using mat4u = mat4_t<core::u32>;
		using mat4i = mat4_t<core::i32>;
		using mat4f = mat4_t<core::f32>;
		using mat4d = mat4_t<core::f64>;

		template <typename R> using mat4x3_t = mat_t<R, 4u, 3u>;
		using mat4x3u = mat4x3_t<core::u32>;
		using mat4x3i = mat4x3_t<core::i32>;
		using mat4x3f = mat4x3_t<core::f32>;
		using mat4x3d = mat4x3_t<core::f64>;

		template <typename R, core::u8 N, core::u8 M>
		struct mat_t
		{
			using type = mat_t<R, N, M>;
			using real = R;
			static const core::u8 Rows = N;
			static const core::u8 Cols = M;
			static const core::u8 Dim = N * M;

			mat_t()
			{
				for (core::u8 i = 0; i < Rows; ++i)
					for (core::u8 j = 0; j < Cols; ++j)
						m[i][j] = i == j ? 1 : 0;
			}

			mat_t(real v)
			{
				for (core::u8 i = 0; i < Rows; ++i)
					for (core::u8 j = 0; j < Cols; ++j)
						m[i][j] = v;
			}

			mat_t(const real data[Dim])
				: data(data)
			{}

			inline const real* const vptr() const { return &data[0]; }

			inline const real& operator[](core::u8 i) const { return data[i]; }
			inline real& operator[](core::u8 i) { return data[i]; }

			/*inline void operator()(T v) {
			  for (u8 i = 0; i < R; ++i)
				for (u8 j = 0; j < C; ++j)
				  m[i][j] = v;
			}*/

			inline void operator()(const real data[Dim]) {
				for (core::u8 i = 0; i < Dim; ++i)
					this->data[i] = data[i];
			}

			union {
				real data[Dim];
				real m[Rows][Cols];
				struct {
					vec_t<real, Rows> v[Cols];
				};
			};
		};
	}
}