# 项目来源
原项目来自 [raylib: https://github.com/raysan5/raylib](https://github.com/raysan5/raylib) 感谢 raysan5 和所有为原项目贡献的成员。
我在转换符号的项目副本中也整合了 [raylib-cpp](https://github.com/RobLoach/raylib-cpp) 这一 c++ 封装（只有头文件，所以很方便集成）。

# 净化脚本
符号冲突主要来自于 raylib 中窗口相关的函数名称与 windows 下的函数名称相同，
因为强制使用了 C 风格的函数定义，导致其和 Windows.h 中的声明冲突，所以编译器不会放行。
常规思路是按照官方说的用命名空间，并较少使用 Windows.h 中的定义，这样限制比较大。并且在最新的 5.x 上不适用。
我又考虑到不能直接去修改 Windows SDK 的代码，因为这样很容易导致配置失效。
所以考虑为 raylib 的符号统一加上 `RL` 前缀来缓解此问题。
脚本使用 python，并且目前有点肮脏，从 clean-scripts 目录中获取。

**补充**：

1）raylib 的后端主要使用 GLFW 构建窗口框架，并使用 OpenGL（或者vulkan）在其上进行渲染。如果使用混合透明，
最好使用 OpenGL 3.3 之后的版本进行构建，否则可能在部分显卡驱动上出现透明失效。

2）**最重要的，raylib 不支持 Multi-Viewports，即不支持并行（甚至是逐个渲染）的多平台窗口交互，只能创建一个上下文。
目前，官方的实验分支中仅有限地允许多窗口，但每次只有一个活动上下文，交互十分受限。**

LianYou
