#ifndef RAYLIB_CPP_INCLUDE_TOUCH_HPP_
#define RAYLIB_CPP_INCLUDE_TOUCH_HPP_

#include "./raylib.hpp"

namespace raylib {
/**
 * Input-related functions: touch
 */
namespace Touch {
/**
 * Get touch position X for touch point 0 (relative to screen size)
 */
[[maybe_unused]] RLCPPAPI inline int GetX() {
    return ::RLGetTouchX();
}

/**
 * Get touch position Y for touch point 0 (relative to screen size)
 */
[[maybe_unused]] RLCPPAPI inline int GetY() {
    return ::RLGetTouchY();
}

/**
 * Get touch position XY for a touch point index (relative to screen size)
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetPosition(int index) {
    return ::RLGetTouchPosition(index);
}

/**
 * Get touch point identifier for given index
 */
[[maybe_unused]] RLCPPAPI inline int GetPointId(int index) {
    return ::RLGetTouchPointId(index);
}

/**
 * Get number of touch points
 */
[[maybe_unused]] RLCPPAPI inline int GetPointCount() {
    return ::RLGetTouchPointCount();
}
} // namespace Touch
} // namespace raylib

namespace RTouch = raylib::Touch;

#endif // RAYLIB_CPP_INCLUDE_TOUCH_HPP_
