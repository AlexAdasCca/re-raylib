#ifndef RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_
#define RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_

#include <string>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * Input-related functions: gamepads
 */
class Gamepad {
public:
    Gamepad(int gamepadNumber = 0) { set(gamepadNumber); }
    int number;

    GETTERSETTER(int, Number, number)

    Gamepad& operator=(const Gamepad& gamepad) {
        set(gamepad);
        return *this;
    }

    Gamepad& operator=(int gamepadNumber) {
        set(gamepadNumber);
        return *this;
    }

    operator int() const { return number; }

    /**
     * Detect if a gamepad is available
     */
    bool IsAvailable() const { return ::RLIsGamepadAvailable(number); }

    /**
     * Detect if a gamepad is available
     */
    static bool IsAvailable(int number) { return ::RLIsGamepadAvailable(number); }

    /**
     * Return gamepad internal name id
     */
    std::string GetName() const { return ::RLGetGamepadName(number); }

    /**
     * Return gamepad internal name id
     */
    operator std::string() const { return GetName(); }

    /**
     * Detect if a gamepad button has been pressed once
     */
    bool IsButtonPressed(int button) const { return ::RLIsGamepadButtonPressed(number, button); }

    /**
     * Detect if a gamepad button is being pressed
     */
    bool IsButtonDown(int button) const { return ::RLIsGamepadButtonDown(number, button); }

    /**
     * Detect if a gamepad button has been released once
     */
    bool IsButtonReleased(int button) const { return ::RLIsGamepadButtonReleased(number, button); }

    /**
     * Detect if a gamepad button is NOT being pressed
     */
    bool IsButtonUp(int button) const { return ::RLIsGamepadButtonUp(number, button); }

    /**
     * Get the last gamepad button pressed
     */
    int GetButtonPressed() const { return ::RLGetGamepadButtonPressed(); }

    /**
     * Return gamepad axis count for a gamepad
     */
    int GetAxisCount() const { return ::RLGetGamepadAxisCount(number); }

    /**
     * Return axis movement value for a gamepad axis
     */
    float GetAxisMovement(int axis) const { return ::RLGetGamepadAxisMovement(number, axis); }

    int SetMappings(const std::string& mappings) { return RLSetGamepadMappings(mappings.c_str()); }

    /**
     * Set gamepad vibration for both motors (duration in seconds)
     */
    void SetVibration(float leftMotor, float rightMotor, float duration) {
        ::RLSetGamepadVibration(number, leftMotor, rightMotor, duration);
    }
protected:
    void set(int gamepadNumber) { number = gamepadNumber; }
};
} // namespace raylib

using RGamepad = raylib::Gamepad;

#endif // RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_
