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

template <typename T> inline constexpr
constexpr T linearToMagnitude (const T x) noexcept { return 20.0 * std::log10(x); }

// ==============================================================================

}; // namespace fastmath
}; // namespace mldsp
