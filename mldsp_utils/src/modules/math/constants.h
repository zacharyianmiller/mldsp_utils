/*
  ==============================================================================

    constants.h
    Created: 21 May 2025 9:06:19am
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once

namespace mldsp
{
namespace math
{
namespace constants

// ==============================================================================

template <typename T>
struct OneThird
{
    static constexpr float value = static_cast<T>(0.3333333333333333);
    T get() { return value; }
};

// ==============================================================================

}; // namespace constants
}; // namespace math
}; // namespace mldsp
