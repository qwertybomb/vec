#pragma once
#include <cstddef>
#include <memory>
namespace math {
#define OPERATOR_TEMPLATE(op)\
template<typename U, std::size_t other_dim>\
constexpr auto operator##op(const vec<U, other_dim>& other) {\
	constexpr bool compare = other_dim > dim; /*compare sizes*/\
	constexpr std::size_t smallest_dim = compare ? dim : other_dim;\
	constexpr std::size_t biggest_dim = compare ? other_dim : dim;\
	vec<T, biggest_dim> to_return; \
	for (std::size_t i = 0; i < biggest_dim; ++i) { \
		to_return.v[i] = compare ? (other[i]) : v[i]; \
		if (i < smallest_dim) to_return.v[i] = to_return.v[i] ##op (compare ? v[i] : (other[i])); \
	} \
	return to_return; \
} \

#define OPERATOR_TEMPLATE_TWO(op) \
	template<typename U>\
constexpr auto operator##op(const U& other) {\
		auto to_return = *this;\
		for (std::size_t i = 0; i < dim; ++i) {\
			to_return[i] ##op= other; \
		}\
	return to_return;\
}\

	template<typename T, std::size_t dim>
	struct vec {
		T v[dim];
		template<typename... Args>
		vec(const Args&... args) : v{ static_cast<T>(args)... } {}
		vec() = default;

		T& operator[](const std::size_t& index) { return v[index]; }
		const T& operator[](const std::size_t& index) const { return v[index]; }

		OPERATOR_TEMPLATE(+)

		OPERATOR_TEMPLATE(-)

		OPERATOR_TEMPLATE(*)

		OPERATOR_TEMPLATE(/)

		OPERATOR_TEMPLATE_TWO(+)

		OPERATOR_TEMPLATE_TWO(-)

		OPERATOR_TEMPLATE_TWO(*)

		OPERATOR_TEMPLATE_TWO(/)

			template<typename U>
		constexpr auto operator+= (const U& other) {
			*this = *this + other;
			return *this;
		}

		template<typename U>
		constexpr auto operator-= (const U& other) {
			*this = *this - other;
			return *this;
		}

		template<typename U>
		constexpr auto operator*=(const U& other) {
			*this = *this * other;
			return *this;
		}

		template<typename U>
		constexpr auto operator/=(const U& other) {
			*this = *this / other;
			return *this;
		}

		constexpr T length() {
			T sum{};
			for (std::size_t i = 0; i < dim; ++i) {
				sum += v[i] * v[i];
			}
			return std::sqrt(sum);
		}

	
	};
	template<typename T, std::size_t dim>
inline constexpr T dot(const vec<T, dim>& a, vec<T, dim>& b) {
		T sum{};
		for (std::size_t i = 0; i < dim; ++i) {
			sum += a[i] * b[i];
		}
		return sum;
	}
template<typename T, std::size_t dim>
inline constexpr auto min(const vec<T, dim>& a,const vec<T, dim>& b) {
	vec<T, dim> to_return;
	for (std::size_t i = 0; i < dim; ++i) {
		to_return[i] = a[i] < b[i] ? a[i] : b[i];
	}
	return to_return;
}

template<typename T, std::size_t dim>
inline constexpr auto max(const vec<T, dim>& a, const vec<T, dim>& b) {
	vec<T, dim> to_return;
	for (std::size_t i = 0; i < dim; ++i) {
		to_return[i] = a[i] > b[i] ? a[i] : b[i];
	}
	return to_return;
}
template<typename T, std::size_t dim>
inline constexpr T length(vec<T, dim> a) { return a.length(); }
template<typename T, std::size_t dim>
inline constexpr auto normalize(vec<T, dim> a) { return a / a.length(); }


template<typename T, typename Y>
inline constexpr auto reflect(const T& I, const Y& N) {
	return I - 2.0 * dot(N, I) * N;
}
template<typename T,std::size_t dim>
inline constexpr auto distance(const vec<T,dim>& a, const vec<T,dim>& b) {
	T sum{};
	for (std::size_t i = 0; i < dim; ++i) {
		sum += (b[i] - a[i])*(b[i] - a[i]);
	}
	return std::sqrt(sum);
}
template<typename T>
inline constexpr auto cross(const vec<T, 3>& x, const vec<T, 3>& y) {
	return vec<T, 3>(x[1] * y[2] - y[1] * x[2], x[2] * y[0] - y[2] * x[0], x[0] * y[1] - y[1] * x[1]);
}
	#undef OPERATOR_TEMPLATE
	#undef OPERATOR_TEMPLATE_TWO
}
