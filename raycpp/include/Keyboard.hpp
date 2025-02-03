#ifndef RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_
#define RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_

#include "./raylib.hpp"

namespace raylib {
/**
 * Input-related functions: keyboard
 */
namespace Keyboard {
/**
 * Detect if a key has been pressed once
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyPressed(int key) {
    return ::RLIsKeyPressed(key);
}

/**
 * Detect if a key has been pressed again (Only PLATFORM_DESKTOP)
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyPressedRepeat(int key) {
    return ::RLIsKeyPressedRepeat(key);
}

/**
 * Detect if a key is being pressed
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyDown(int key) {
    return ::RLIsKeyDown(key);
}

/**
 * Detect if a key has been released once
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyReleased(int key) {
    return ::RLIsKeyReleased(key);
}

/**
 * Detect if a key is NOT being pressed
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyUp(int key) {
    return ::RLIsKeyUp(key);
}

/**
 * Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
 */

[[maybe_unused]] RLCPPAPI inline int GetKeyPressed() {
    return ::RLGetKeyPressed();
}

/**
 * Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
 */
[[maybe_unused]] RLCPPAPI inline int GetCharPressed() {
    return ::RLGetCharPressed();
}
} // namespace Keyboard
} // namespace raylib
namespace RKeyboard = raylib::Keyboard;

#endif // RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_
