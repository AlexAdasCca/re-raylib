# 项目来源
原项目来自 https://github.com/raysan5/raylib，感谢 raysan5 和所有为原项目贡献的成员。
此项目同时整合了 https://github.com/RobLoach/raylib-cpp 的 c++ 封装。

# 净化脚本
符号冲突主要来自于 raylib 中窗口有关的函数名与 windows 下的很多 api 名称相同，
但是由于使用了强制 C 风格函数定义并和 Windows.h 冲突，所以编译器不会放行。
常规思路是按照官方说的用命名空间，并较少使用 Windhows.h 中的定义，这样限制比较大。
所以考虑为 raylib 的符号统一加上 `RL` 前缀以避免此类问题。
脚本使用 python，并且目前有点肮脏，从 clean-scripts 目录中获取。

LianYou
