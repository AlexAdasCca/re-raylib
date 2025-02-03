#ifndef RAYLIB_CPP_INCLUDE_MOUSE_HPP_
#define RAYLIB_CPP_INCLUDE_MOUSE_HPP_

#include "./Vector2.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * Input-related functions: mouse
 */
namespace Mouse {
/**
 * Detect if a mouse button has been pressed once
 */
[[maybe_unused]] RLCPPAPI inline bool IsButtonPressed(int button) {
    return ::RLIsMouseButtonPressed(button);
}

/**
 * Detect if a mouse button is being pressed
 */
[[maybe_unused]] RLCPPAPI inline bool IsButtonDown(int button) {
    return ::RLIsMouseButtonDown(button);
}

/**
 * Detect if a mouse button has been released once
 */
[[maybe_unused]] RLCPPAPI inline bool IsButtonReleased(int button) {
    return ::RLIsMouseButtonReleased(button);
}

[[maybe_unused]] RLCPPAPI inline bool IsButtonUp(int button) {
    return ::RLIsMouseButtonUp(button);
}

[[maybe_unused]] RLCPPAPI inline int GetX() {
    return ::RLGetMouseX();
}

[[maybe_unused]] RLCPPAPI inline int GetY() {
    return ::RLGetMouseY();
}

[[maybe_unused]] RLCPPAPI inline void SetX(int x) {
    ::RLSetMousePosition(x, GetY());
}

[[maybe_unused]] RLCPPAPI inline void SetY(int y) {
    ::RLSetMousePosition(GetX(), y);
}

[[maybe_unused]] RLCPPAPI inline Vector2 GetPosition() {
    return ::RLGetMousePosition();
}

[[maybe_unused]] RLCPPAPI inline void SetPosition(int x, int y) {
    ::RLSetMousePosition(x, y);
}

[[maybe_unused]] RLCPPAPI inline void SetPosition(::Vector2 position) {
    ::RLSetMousePosition(static_cast<int>(position.x), static_cast<int>(position.y));
}

/**
 * Get mouse delta between frames
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetDelta() {
    return ::RLGetMouseDelta();
}

[[maybe_unused]] RLCPPAPI inline void SetOffset(int offsetX = 0, int offsetY = 0) {
    ::RLSetMouseOffset(offsetX, offsetY);
}

[[maybe_unused]] RLCPPAPI inline void SetOffset(::Vector2 offset) {
    ::RLSetMouseOffset(static_cast<int>(offset.x), static_cast<int>(offset.y));
}

[[maybe_unused]] RLCPPAPI inline void SetScale(float scaleX = 1.0f, float scaleY = 1.0f) {
    ::RLSetMouseScale(scaleX, scaleY);
}

[[maybe_unused]] RLCPPAPI inline void SetScale(::Vector2 scale) {
    ::RLSetMouseScale(scale.x, scale.y);
}

/**
 * Get mouse wheel movement for X or Y, whichever is larger
 */
[[maybe_unused]] RLCPPAPI inline float GetWheelMove() {
    return ::RLGetMouseWheelMove();
}

/**
 * Get mouse wheel movement for both X and Y
 *
 * @see ::GetMouseWheelMoveV()
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetWheelMoveV() {
    return RLGetMouseWheelMoveV();
}

/**
 * Sets the current mouse cursor icon.
 *
 * @see ::MouseCursor
 */
[[maybe_unused]] RLCPPAPI inline void SetCursor(int cursor = MOUSE_CURSOR_DEFAULT) {
    ::RLSetMouseCursor(cursor);
}

/**
 * Get touch position X for touch point 0 (relative to screen size)
 */
[[maybe_unused]] RLCPPAPI inline int GetTouchX() {
    return ::RLGetTouchX();
}

/**
 * Get touch position Y for touch point 0 (relative to screen size)
 */
[[maybe_unused]] RLCPPAPI inline int GetTouchY() {
    return ::RLGetTouchY();
}

/**
 * Get touch position XY for a touch point index (relative to screen size)
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetTouchPosition(int index) {
    return ::RLGetTouchPosition(index);
}

/**
 * Get a ray trace from mouse position
 */
[[maybe_unused]] RLCPPAPI inline Ray GetRay(::Vector2 mousePosition, const ::Camera& camera) {
    return ::GetMouseRay(mousePosition, camera);
}

/**
 * Get a ray trace from mouse position
 */
[[maybe_unused]] RLCPPAPI inline Ray GetRay(const ::Camera& camera) {
    return ::GetMouseRay(::RLGetMousePosition(), camera);
}
} // namespace Mouse
} // namespace raylib

namespace RMouse = raylib::Mouse;

#endif // RAYLIB_CPP_INCLUDE_MOUSE_HPP_
