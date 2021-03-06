#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/op/vec_op.hpp>
#include <ove/math/op/trx_op.hpp>

#include <iostream>

namespace ove
{
	namespace math
	{
		template <typename T, core::u8 D>
		struct vec_t;

		template <typename R>
		using vec2_t = vec_t<R, 2u>;
		using vec2u = vec2_t<core::u32>;
		using vec2i = vec2_t<core::i32>;
		using vec2f = vec2_t<core::f32>;
		using vec2d = vec2_t<core::f64>;

		template <typename R>
		using vec3_t = vec_t<R, 3u>;
		using vec3u = vec3_t<core::u32>;
		using vec3i = vec3_t<core::i32>;
		using vec3f = vec3_t<core::f32>;
		using vec3d = vec3_t<core::f64>;

		template <typename R>
		using vec4_t = vec_t<R, 4u>;
		using vec4u = vec4_t<core::u32>;
		using vec4i = vec4_t<core::i32>;
		using vec4f = vec4_t<core::f32>;
		using vec4d = vec4_t<core::f64>;

		template <typename R, core::u8 D>
		struct vec_t
		{
		public:
			using type = vec_t<R, D>;
			using real = R;
			static const core::u8 Dim = D;
			static constexpr type zero() { return type(); }

		public:
			vec_t()
				: data{ 0 }
			{
			}

			vec_t(real v)
				: data{ v }
			{
			}

		public:
			inline const real* const vptr() const { return &data[0]; }

			inline real& operator[](core::u8 i) { return data[i]; }

			inline void operator()(real v)
			{
				for (core::u8 i = 0; i < Dim; ++i)
					data[i] = v;
			}

			union {
				real data[Dim];
			};
		};

		template <typename R>
		struct vec_t<R, 2u>
		{
			using type = vec_t<R, 2u>;
			using real = R;
			static const core::u8 Dim = 2u;
			static constexpr type zero() { return type(); }

			vec_t()
				: data{ 0 }
			{
			}

			vec_t(real v)
				: data{ v }
			{
			}

			vec_t(real x, real y)
				: data{ x, y }
			{
			}

			inline const real* const vptr() const { return &data[0]; }

			inline real& operator[](core::u8 i) { return data[i]; }
			inline void operator()(real x, real y)
			{
				this->x = x;
				this->y = y;
			}

			union
			{
				real data[Dim];
				struct
				{
					real x;
					real y;
				};
			};

			template <typename U>
			void operator= (const vec_t<U, Dim>& v)
			{
				for (core::u8 i = 0; i < Dim; ++i)
					data[i] = v.data[i];
			}

			friend std::ostream& operator<< (std::ostream& os, const type& v)
			{
				os << "[ x: " << v.x << ", y: " << v.y << " ]";
				return os;
			}
		};

		template <typename R>
		struct vec_t<R, 3u>
		{
			using type = vec_t<R, 3u>;
			using real = R;
			static const core::u8 Dim = 3u;
			static constexpr type zero() { return type(); }

			vec_t()
				: data{ 0 }
			{
			}

			vec_t(real v)
				: data{ v }
			{
			}

			vec_t(real x, real y, real z)
				: data{ x, y, z }
			{
			}

			inline const real* const vptr() const { return &data[0]; }

			inline real& operator[](core::u8 i) { return data[i]; }
			inline void operator()(real x, real y, real z)
			{
				this->x = x;
				this->y = y;
				this->z = z;
			}

			union
			{
				real data[Dim];
				struct
				{
					real x;
					real y;
					real z;
				};
			};

			friend std::ostream& operator<< (std::ostream& os, const type& v)
			{
				os << "[ x: " << v.x << ", y: " << v.y << ", z: " << v.z << " ]";
				return os;
			}
		};

		template <typename R>
		struct vec_t<R, 4u>
		{
			using type = vec_t<R, 4u>;
			using real = R;
			static const core::u8 Dim = 4u;
			static constexpr type zero() { return type(); }

			vec_t()
				: data{ 0 }
			{
			}

			vec_t(real v)
				: data{ v }
			{
			}

			vec_t(real x, real y, real z, real w)
				: data{ x, y, z, w }
			{
			}

			inline const real* const vptr() const { return &data[0]; }

			inline real& operator[](core::u8 i) { return data[i]; }
			inline void operator()(real x, real y, real z, real w)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}

			union
			{
				real data[Dim];
				struct
				{
					real x;
					real y;
					real z;
					real w;
				};
			};

			friend std::ostream& operator<< (std::ostream& os, const type& v)
			{
				os << "[ x: " << v.x << ", y: " << v.y << ", z: " << v.z << ", w: " << v.w << " ]";
				return os;
			}
		};
	}
}