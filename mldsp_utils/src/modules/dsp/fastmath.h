/*
  ==============================================================================

    fastmath.h
    Created: 16 May 2025 2:15:31pm
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once

namespace mldsp
{
namespace fastmath
{

// ==============================================================================
 
template <typename T>
constexpr T tanh_gaussian (const T x) noexcept
{
    T x_sq = x*x;
    return x / ((1.0) + (x_sq / 3.0 + (x_sq / 5.0 + (x_sq / 7.0))));
}

template <typename T>
constexpr T tanh_pade (const T x) noexcept
{
    return (x*(10.0+x*x)*(60.0+x*x)) / (600.0 + 270.0*x*x + 11.0*x*x*x*x + (x*x*x*x*x*x)/24.0);
}

template <typename T>
constexpr T tanh_lambert (const T x) noexcept
{
    T x_sq = x * x;
    T a = x * (135135.0 + x_sq * (17325.0 + x_sq * (378.0 + x_sq)));
    T b = 135135.0 + x_sq * (62370.0 + x_sq * (3150.0 + x_sq * 28.0));
    return a / b;
}

template <typename T>
constexpr T cosh_gaussian (const T x) noexcept { return 1.0 / tanh_gaussian (x); }

template <typename T>
constexpr T cosh_pade (const T x) noexcept { return 1.0 / tanh_pade (x); }

template <typename T>
constexpr T cosh_lambert (const T x) noexcept { return 1.0 / tanh_lambert (x); }
 
// ==============================================================================

}; // namespace fastmath
}; // namespace mldsp
