# 项目来源 | Project Source
原项目来自 [raylib: https://github.com/raysan5/raylib](https://github.com/raysan5/raylib)。感谢 raysan5 和所有为原项目贡献的成员。  
The original project comes from [raylib: https://github.com/raysan5/raylib](https://github.com/raysan5/raylib). Thanks to raysan5 and all the contributors to the original project. 🙏  
我在对 raylib 项目进行符号转换过程中也整合了 [raylib-cpp](https://github.com/RobLoach/raylib-cpp) 这一 c++ 封装项目（只有头文件，所以很方便集成）。  
During the symbol conversion of the raylib project, I also integrated [raylib-cpp](https://github.com/RobLoach/raylib-cpp), a C++ wrapper project (which only contains header files, making it easy to integrate). 🛠️

# 净化脚本 | Purification Script
符号冲突主要是因为 raylib 中窗口相关的函数名称与 windows 下的函数名称相同，⚠️ 
因为强制使用了 C 风格的函数定义，导致其和 Windows.h 中的声明冲突，所以编译器不会放行 ❌ 。 
常规思路是按照官方说的用命名空间，并较少使用 Windows.h 中的定义，这样限制比较大。并且在最新的 5.x 上不适用。  
我又考虑到不能直接去修改 Windows SDK 的代码，因为这样很容易导致配置失效。
所以考虑为 raylib 的符号统一加上 `RL` 前缀来缓解此问题。可以从 clean-scripts 目录中获取脚本🔧。
脚本使用 python🐍，不过目前有点肮脏（见谅）。

Symbol conflicts mainly arise from the window-related function names in raylib that clash with function names in Windows. ⚠️  
Because C-style function definitions are forced, they conflict with declarations in Windows.h, causing the compiler to reject them. ❌  
The conventional approach is to use namespaces as recommended by the official documentation, and reduce the use of definitions from Windows.h, but this imposes many restrictions. Also, this is not applicable in the latest 5.x versions. 

I also considered that directly modifying the Windows SDK code is not a good option, as it could easily invalidate the configuration. 🔧  
Thus, I decided to add the `RL` prefix to raylib symbols to alleviate this issue. You can find the script in the clean-scripts directory. 📂  
The script is written in Python 🐍, though it’s a bit messy at the moment (apologies for that). 

**补充 | Additions**：

1）raylib 的后端主要使用 GLFW 构建窗口框架，并使用 OpenGL（或者vulkan）在其上进行渲染。如果使用混合透明，  
最好使用 OpenGL 3.3 之后的版本进行构建，否则可能在部分显卡驱动上出现透明失效💻。  
2）**最重要的，raylib 不支持 Multi-Viewports，即不支持并行（甚至是逐个渲染）的多平台窗口交互，只能创建一个上下文。  
目前，官方的实验分支中仅有限地允许多窗口，但每次只有一个活动上下文，交互十分受限。😕**

1) raylib's backend mainly uses GLFW to build the window framework and uses OpenGL (or Vulkan) for rendering. If using mixed transparency,  
it’s best to use OpenGL version 3.3 or later to build, as transparency may not work on some graphics drivers with older versions. 💻

3) **Most importantly, raylib does not support Multi-Viewports, meaning it doesn’t support parallel (or even per-frame) multi-platform window interactions, and can only create a single context.  
Currently, the official experimental branch only allows multiple windows to a limited extent, with only one active context at a time, severely restricting interaction.** 😕


LianYou
