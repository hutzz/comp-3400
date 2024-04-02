#ifndef UTILS_HXX
#define UTILS_HXX

#include <cstddef> 
#include <cstring>
#include <type_traits>
#include <utility>

template <typename T>
concept zero_initializable = std::is_trivial_v<T> && std::is_standard_layout_v<T>;

template <typename T>
void zero() noexcept = delete;

template <zero_initializable T>
requires (!std::is_array_v<T>)
inline T zero() noexcept {
    T retval;
    std::memset(&retval, 0, sizeof(T));
    return retval;
}

template <typename T>
void zero(T const&) noexcept = delete;

template <typename T>
void zero(T const&&) noexcept = delete;

template <typename T, std::size_t N>
void zero(T const (&)[N]) noexcept = delete;

template <typename T, std::size_t N>
void zero(T const (&&)[N]) noexcept = delete;

template <typename T>
void zero(T*&) noexcept = delete;

template <typename T>
void zero(T*&&) noexcept = delete;

template <typename T>
void zero(T* const&) noexcept = delete;

template <typename T>
void zero(T* const&&) noexcept = delete;

template <typename T>
void zero(T* volatile&) noexcept = delete;

template <typename T>
void zero(T* volatile&&) noexcept = delete;

template <typename T>
void zero(T* const volatile&) noexcept = delete;

template <typename T>
void zero(T* const volatile&&) noexcept = delete;

template <typename T>
requires zero_initializable<T>
inline auto& zero(T& object) noexcept {
    std::memset(&object, 0, sizeof(T));
    return object;
}

template <typename T>
requires zero_initializable<T>
inline auto&& zero(T&& object) noexcept {
    std::memset(&object, 0, sizeof(T));
    return std::move(object);
}

template <typename T, std::size_t N>
requires zero_initializable<T>
inline auto& zero(T (&object)[N]) noexcept {
    std::memset(&object, 0, sizeof(T[N]));
    return object;
}

template <typename T, std::size_t N>
requires zero_initializable<T>
inline auto&& zero(T (&&object)[N]) noexcept {
    std::memset(&object, 0, sizeof(T[N]));
    return std::move(object);
}

#endif
