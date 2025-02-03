/*******************************************************************************************
*
*   raylib-cpp [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib-cpp (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*   
*   Changed by LianYou, 2025.02.02
*
********************************************************************************************/

#include "raylib-assert.h"
#include "raylib-cpp.hpp"


//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    // SomeSingleTest
    //-------------------------------------------------------------------------------------

    RLSetTraceLogLevel(LOG_INFO);
    RLTraceLog(LOG_INFO, "---------------------");
    RLTraceLog(LOG_INFO, "TEST: raylib-cpp test");

    // Get a path to where the executable is so file loading is relative.
    std::string path = "";
    if (argc > 0) {
        path = RLGetDirectoryPath(argv[0]);
    }

    // Vector
    {
        raylib::Vector2 position(50, 100);
        AssertEqual(position.GetX() == position.x);
        position.x = 150;
        AssertEqual(position.GetX() == 150);
        position.SetX(300);
        AssertEqual(position.GetX() == 300);

        raylib::Vector2 speed(10, 10);
        position += speed;
        AssertEqual(position.x == 310);
        AssertEqual(raylib::Window::IsReady() == false);

        raylib::Vector2 size{50, 100};
        raylib::Vector2 halfsize = size / 2.0f;

        AssertEqual(size.x == 50);
        AssertEqual(size.y == 100);
        AssertEqual(halfsize.x == 25);
        AssertEqual(halfsize.y == 50);

        raylib::Vector2 doublesize = size * 2.0f;
        AssertEqual(size.x == 50);
        AssertEqual(doublesize.x == 100);
    }

    // Color
    {
        raylib::Color color = RED;
        AssertEqual(color.ToInt() == ::RLColorToInt(RED));
        color = RAYWHITE;
        ::Color raylibColor = RAYWHITE;
        AssertEqual(color.r == raylibColor.r);
    }

    // Math
    {
        raylib::Vector2 direction(50, 50);
        raylib::Vector2 newDirection = direction.Rotate(30);
        AssertEqual((int)newDirection.x == 57);
    }

    // Image
    {
        // Loading
        raylib::Image image(path + "/resources/feynman.png");
        Assert(image.IsValid());

        // Chaining
        image.Crop(100, 100).Resize(50, 50);
        AssertEqual(image.GetWidth() == 50);
        AssertEqual(image.GetHeight() == 50);
    }

    // Keyboard
    { AssertNot(raylib::Keyboard::IsKeyPressed(KEY_MINUS)); }

    // raylib::LoadDirectoryFiles()
    {
        const char* AppDir = ::RLGetApplicationDirectory();
        std::string resourcesDir(AppDir);
        resourcesDir += "resources";
        RLTraceLog(LOG_INFO, resourcesDir.c_str());
        std::vector<std::string> files = raylib::LoadDirectoryFiles(resourcesDir);
        RLTraceLog(LOG_INFO, std::to_string(files.size()).c_str());
        Assert(files.size() == 3);
    }

    // raylib::TextReplace()
    {
        std::string input = "Hello World!";
        std::string output = raylib::TextReplace(input, "World", "Moon");
        AssertEqual(output == "Hello Moon!");
    }

    // raylib::TextInsert()
    {
        std::string input = "Hello World!";
        std::string output = raylib::TextInsert(input, "Good!", 0);
        AssertEqual(output == "Good! World!");
    }

    // raylib::TextSubtext()
    {
        std::string input = "Hello World!";
        std::string output = raylib::TextSubtext(input, 6, 5);
        AssertEqual(output == "World");
    }

    // TextSplit
    {
        std::vector<std::string> output = raylib::TextSplit("Hello|How|Are|You", '|');
        AssertEqual(output.size() == 4);
        AssertEqual(output[1] == "How");
    }

    // Wave
    {
        raylib::Wave wave(path + "/resources/weird.wav");
        Assert(wave.IsValid()); // , "Expected wave to be loaded correctly"
    }

    // RaylibException
    {
        bool passed = false;
        try {
            raylib::Texture texture("notfound.png");
        } catch (raylib::RaylibException& error) {
            error.TraceLog(LOG_INFO);
            passed = true;
        }
        Assert(passed); // , "Expected to have a RaylibException to be thrown"
    }

    // Load FileData
    {
        raylib::FileData file(path + "/resources/weird.wav");
        Assert(file.GetBytesRead() > 0); // , "Expected file to be loaded correctly"
    }

    // Load FileText
    {
        raylib::FileText text(path + "/resources/lorem.txt");
        Assert(text.GetLength() > 0);  // , "Expected file to be loaded correctly"
        AssertEqual(text.ToString().substr(0, 5) == "Lorem");
    }

    RLTraceLog(LOG_INFO, "TEST: raylib-cpp test");
    RLTraceLog(LOG_INFO, "---------------------");
    //--------------------------------------------------------------------------------------

    RLTraceLog(LOG_INFO, "TEST: raylib-cpp CreateDemoWindow");
    // Initialization
    //--------------------------------------------------------------------------------------
    raylib::Window window(screenWidth, screenHeight, "raylib-cpp [core] example - basic window", ConfigFlags::FLAG_WINDOW_RESIZABLE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    RLSetTargetFPS(120);   // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    RLBeginDrawing();

    RLClearBackground(RAYWHITE);

    RLDrawText("Congrats! You created your first raylib-cpp window!", 160, 200, 20, LIGHTGRAY);

    RLEndDrawing();
    //----------------------------------------------------------------------------------
}