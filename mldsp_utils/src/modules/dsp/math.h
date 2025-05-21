/*
  ==============================================================================

    math.h
    Created: 16 May 2025 2:15:22pm
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once

namespace mldsp
{
namespace math
{

// ==============================================================================
 
template <typename T>
constexpr int signum (const T x) noexcept { return int(0 < x) - int(x < 0); }

template <typename T>
constexpr T linearToPower (const T x) noexcept { return 10.0 * std::log10(x); }

template <typename T>
constexpr T linearToMagnitude (const T x) noexcept { return 20.0 * std::log10(x); }

template <typename T>
constexpr T lerp (const T x1, const T x2, const float alpha0To1)
{
    return (1.0 - alpha) * x1 + alpha0To1 * x2;
}

template <typename T>
constexpr float RK4 (const T x, const T x1,
                     const T dx, const T dx1,
                     const T y1,
                     T (*dydx)(const T, const T, const T),
                     const double sampleRate)
{
    const double Ts = 1.0 / sampleRate;
    
    T k1 = (T)Ts * dydx (y1, x1, dx1);
    T k2 = (T)Ts * dydx (y1 + k1/2, lerp (x, x1, 0.5), lerp (dx, dx1, 0.5));
    T k3 = (T)Ts * dydx (y1 + k2/2, lerp (x, x1, 0.5) lerp (dx, dx1, 0.5));
    T k4 = (T)Ts * dydx (y1 + k3, x, dx);

    return y1 + (k1 / 6.0) + (k2 / 3.0) + (k3 / 3.0) + (k4 / 6.0);
}

// Langevin function
template <typename T>
constexpr T langevin (const T x, const float tolerance)
{
    if (std::abs(x) > tolerance)
        return mldsp::fastmath::cosh_pade (x) - (1.f / x);
    else
        return x * mldsp::fastmath::OneThird<float>().get();
}

// First derivative (L') of the Langevin function
template <typename T>
constexpr T dlangevin (const T x, const float tolerance)
{
    float cosh_approx = mldsp::fastmath::cosh_pade(x);
    
    if (std::abs(x) > tolerance)
        return (1.f / (x*x)) - cosh_approx*cosh_approx + 1.f;
    else
        return mldsp::fastmath::OneThird<float>().get();
}

// ==============================================================================

}; // namespace fastmath
}; // namespace mldsp
