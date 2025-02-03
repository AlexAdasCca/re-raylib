#ifndef RAYLIB_CPP_INCLUDE_WINDOW_HPP_
#define RAYLIB_CPP_INCLUDE_WINDOW_HPP_

#include <string>

#include "./RaylibException.hpp"
#include "./Vector2.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * Window and Graphics Device Functions.
 */
class Window {
public:
    /**
     * Build a Window object, but defer the initialization. Ensure you call Init() manually.
     *
     * @see Init()
     */
    Window() {
        // Nothing.
    }

    /**
     * Initialize window and OpenGL context.
     *
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The desired title of the window.
     * @param flags The ConfigFlags to set prior to initializing the window. See SetConfigFlags for more details.
     *
     * @see ::SetConfigFlags()
     * @see ConfigFlags
     *
     * @throws raylib::RaylibException Thrown if the window failed to initiate.
     */
    Window(int width, int height, const std::string& title = "raylib", unsigned int flags = 0) {
        Init(width, height, title, flags);
    }

    /**
     * Close window and unload OpenGL context
     */
    ~Window() { Close(); }

    /**
     * Initializes the window.
     *
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The desired title of the window.
     * @param flags The ConfigFlags to set prior to initializing the window. See SetConfigFlags for more details.
     *
     * @see ::SetConfigFlags()
     * @see ConfigFlags
     *
     * @throws raylib::RaylibException Thrown if the window failed to initiate.
     */
    void Init(int width = 800, int height = 450, const std::string& title = "raylib", unsigned int flags = 0) {
        if (flags != 0) {
            ::RLSetConfigFlags(flags);
        }
        ::RLInitWindow(width, height, title.c_str());
        if (!::RLIsWindowReady()) {
            throw RaylibException("Failed to create Window");
        }
    }

    /**
     * Check if KEY_ESCAPE pressed or Close icon pressed
     */
    bool ShouldClose() const { return ::RLWindowShouldClose(); }

    /**
     * Set a custom key to exit program (default is ESC)
     */
    void SetExitKey(int key) { ::RLSetExitKey(key); }

    /**
     * Close window and unload OpenGL context
     */
    void Close() {
        if (::RLIsWindowReady()) {
            ::RLCloseWindow();
        }
    }

    /**
     * Check if cursor is on the current screen
     */
    bool IsCursorOnScreen() const { return ::RLIsCursorOnScreen(); }

    /**
     * Check if window is currently fullscreen
     */
    bool IsFullscreen() const { return ::RLIsWindowFullscreen(); }

    /**
     * Check if window is currently hidden
     */
    bool IsHidden() const { return ::RLIsWindowHidden(); }

    /**
     * Check if window is currently minimized
     */
    bool IsMinimized() const { return ::RLIsWindowMinimized(); }

    /**
     * Check if window is currently minimized
     */
    bool IsMaximized() const { return ::RLIsWindowMaximized(); }

    /**
     * Check if window is currently focused
     */
    bool IsFocused() const { return ::RLIsWindowFocused(); }

    /**
     * Check if window has been resized last frame
     */
    bool IsResized() const { return ::RLIsWindowResized(); }

    /**
     * Check if one specific window flag is enabled
     */
    bool IsState(unsigned int flag) const { return ::RLIsWindowState(flag); }

    /**
     * Set window configuration state using flags
     */
    Window& SetState(unsigned int flag) {
        ::RLSetWindowState(flag);
        return *this;
    }

    /**
     * Clear window configuration state flags
     */
    Window& ClearState(unsigned int flag) {
        ::RLClearWindowState(flag);
        return *this;
    }

    /**
     * Clear window with given color.
     */
    Window& ClearBackground(const ::Color& color = BLACK) {
        ::RLClearBackground(color);
        return *this;
    }

    /**
     * Toggle window state: fullscreen/windowed
     */
    Window& ToggleFullscreen() {
        ::RLToggleFullscreen();
        return *this;
    }

    /**
     * Set whether or not the application should be fullscreen.
     */
    Window& SetFullscreen(bool fullscreen) {
        if (fullscreen) {
            if (!IsFullscreen()) {
                ToggleFullscreen();
            }
        }
        else {
            if (IsFullscreen()) {
                ToggleFullscreen();
            }
        }

        return *this;
    }

    /**
     * Toggle window state: borderless/windowed
     */
    Window& ToggleBorderless() {
        ::RLToggleBorderlessWindowed();
        return *this;
    }

    /**
     * Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
     */
    Window& Maximize() {
        ::RLMaximizeWindow();
        return *this;
    }

    /**
     * Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
     */
    Window& Minimize() {
        ::RLMinimizeWindow();
        return *this;
    }

    /**
     * Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
     */
    Window& Restore() {
        ::RLRestoreWindow();
        return *this;
    }

    /**
     * Set icon for window
     */
    Window& SetIcon(const ::Image& image) {
        ::RLSetWindowIcon(image);
        return *this;
    }

    /**
     * Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
     */
    Window& SetIcons(Image* images, int count) {
        ::RLSetWindowIcons(images, count);
        return *this;
    }

    /**
     * Set title for window
     */
    Window& SetTitle(const std::string& title) {
        ::RLSetWindowTitle(title.c_str());
        return *this;
    }

    /**
     * Set window position on screen
     */
    Window& SetPosition(int x, int y) {
        ::RLSetWindowPosition(x, y);
        return *this;
    }

    /**
     * Set window position on screen
     */
    Window& SetPosition(const ::Vector2& position) {
        return SetPosition(static_cast<int>(position.x), static_cast<int>(position.y));
    }

    /**
     * Set monitor for the current window
     */
    Window& SetMonitor(int monitor) {
        ::RLSetWindowMonitor(monitor);
        return *this;
    }

    /**
     * Set window minimum dimensions
     */
    Window& SetMinSize(int width, int height) {
        ::RLSetWindowMinSize(width, height);
        return *this;
    }

    /**
     * Set window minimum dimensions
     */
    Window& SetMinSize(const ::Vector2& size) {
        ::RLSetWindowMinSize(static_cast<int>(size.x), static_cast<int>(size.y));
        return *this;
    }

    /**
     * Set window dimensions
     */
    Window& SetSize(int width, int height) {
        ::RLSetWindowSize(width, height);
        return *this;
    }

    /**
     * Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
     */
    Window& SetOpacity(float opacity) {
        ::RLSetWindowOpacity(opacity);
        return *this;
    }

    /**
     * Set window focused (only PLATFORM_DESKTOP)
     */
    Window& SetFocused() {
        ::RLSetWindowFocused();
        return *this;
    }

    /**
     * Set window dimensions
     */
    Window& SetSize(const ::Vector2& size) { return SetSize(static_cast<int>(size.x), static_cast<int>(size.y)); }

    /**
     * Get the screen's width and height.
     */
    Vector2 GetSize() const { return {static_cast<float>(GetWidth()), static_cast<float>(GetHeight())}; }

    /**
     * Get native window handle
     */
    void* GetHandle() const { return ::RLGetWindowHandle(); }

    /**
     * Setup canvas (framebuffer) to start drawing
     */
    Window& BeginDrawing() {
        ::RLBeginDrawing();
        return *this;
    }

    /**
     * End canvas drawing and swap buffers (double buffering)
     */
    Window& EndDrawing() {
        ::RLEndDrawing();
        return *this;
    }

    /**
     * Get current screen width
     */
    int GetWidth() const { return ::RLGetScreenWidth(); }

    /**
     * Get current screen height
     */
    int GetHeight() const { return ::RLGetScreenHeight(); }

    /**
     * Get current render width (it considers HiDPI)
     */
    int GetRenderWidth() const { return ::RLGetRenderWidth(); }

    /**
     * Get current render height (it considers HiDPI)
     */
    int GetRenderHeight() const { return ::RLGetRenderHeight(); }

    /**
     * Get window position XY on monitor
     */
    Vector2 GetPosition() const { return ::RLGetWindowPosition(); }

    /**
     * Get window scale DPI factor
     */
    Vector2 GetScaleDPI() const { return ::RLGetWindowScaleDPI(); }

    /**
     * Set clipboard text content
     */
    void SetClipboardText(const std::string& text) { ::RLSetClipboardText(text.c_str()); }

    /**
     * Get clipboard text content
     */
    const std::string GetClipboardText() { return ::RLGetClipboardText(); }

    /**
     * Set target FPS (maximum)
     */
    Window& SetTargetFPS(int fps) {
        ::RLSetTargetFPS(fps);
        return *this;
    }

    /**
     * Returns current FPS
     */
    int GetFPS() const { return ::RLGetFPS(); }

    /**
     * Draw current FPS
     */
    void DrawFPS(int posX = 10, int posY = 10) const { ::RLDrawFPS(posX, posY); }

    /**
     * Returns time in seconds for last frame drawn
     */
    float GetFrameTime() const { return ::RLGetFrameTime(); }

    /**
     * Returns elapsed time in seconds since InitWindow()
     */
    double GetTime() const { return ::RLGetTime(); }

    /**
     * Check if window has been initialized successfully
     */
    static bool IsReady() { return ::RLIsWindowReady(); }

    /**
     * Sets the configuration flags for raylib.
     *
     * @param flags The ConfigFlags to apply to the configuration.
     *
     * @see ::SetConfigFlags
     */
    void SetConfigFlags(unsigned int flags) { ::RLSetConfigFlags(flags); }
};
} // namespace raylib

using RWindow = raylib::Window;

#endif // RAYLIB_CPP_INCLUDE_WINDOW_HPP_
