"""
    Raylib 符号净化脚本,用于解决该库与 Windows.h 等头文件的严重冲突问题。请先使用 CMake 构建 VS 项目, 
    然后使用此脚本对代码进行自动化修改。由于宏和条件编译处理比较麻烦, 目前的脚本中对这两者的修改过于
    简单, 大概率还需要后面手动微调。
    作者: LianYou
    日期: 2025.02.03
"""

import os
import argparse
import re
import sys
import pefile

# 提取 DLL 中的所有导出函数
def get_exported_functions(dll_file):
    try:
        pe = pefile.PE(dll_file)
        export_functions = set()
        
        if hasattr(pe, 'DIRECTORY_ENTRY_EXPORT'):
            for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
                # 确保符号不为 None，且能够成功解码
                if exp.name:
                    export_functions.add(exp.name.decode('utf-8', 'ignore'))
                
        return export_functions
    except Exception as e:
        print(f"Error reading {dll_file}: {e}")
        return set()

# 获取 Windows SDK 导出的函数名（来自 nt, kernel32, user32）
def get_sdk_functions():
    sdk_functions = set()
    
    # 提取这些 DLL 中的导出函数
    sdk_functions.update(get_exported_functions('C:\\Windows\\System32\\ntdll.dll'))
    sdk_functions.update(get_exported_functions('C:\\Windows\\System32\\kernel32.dll'))
    sdk_functions.update(get_exported_functions('C:\\Windows\\System32\\user32.dll'))
    
    return sdk_functions

# 需要排除的函数名称模式（首字母大写，且以 rl 或 RL 开头）
def needs_prefix(func_name, line, sdk_functions):
    # 如果是 Windows SDK 中的函数，跳过
    if func_name in sdk_functions and '__declspec(dllimport)' in line:
        return False
    return func_name[0].isupper() and not (func_name.startswith("rl") or func_name.startswith("RL"))

# 处理 typedef 函数指针的情况
def handle_typedef_function(line):
    typedef_match = re.match(r'\s*typedef\s+([a-zA-Z0-9_*\s]+)\s*\(\*\s*([a-zA-Z_][a-zA-Z0-9_]*)\)\s*\((.*)\)\s*;', line)
    if typedef_match:
        return typedef_match.group(2)
    return None

def is_macro_conditional(line):
    # 去除字符串前后的空白字符
    line = line.strip()

    # 判断是否为条件编译指令 (#if, #ifdef, #ifndef, #elif, #else, #endif)
    if re.match(r'^#\s*(if|ifdef|ifndef|elif|else|endif)\b', line):
        return True
    
    return False

def add_prefix_to_macro_func(line, prefix="RL"):
    # 只匹配宏定义中的函数声明，且函数名与括号之间没有空格
    pattern = r'(#define\s+)(\w+)(\(\w.*\))'

    def replace_function_and_macro(match):
        func_name = match.group(2)  # 函数名
        params = match.group(3)     # 参数部分

        # 如果函数名首字母大写，添加前缀
        if func_name[0].isupper():
            # 添加前缀到函数名
            modified_function = f'{match.group(1)}{prefix}{func_name}{params}'
            return modified_function
        return match.group(0)

    # 使用正则替换函数名并添加前缀
    return re.sub(pattern, replace_function_and_macro, line)

def contains_rl_define(text):
    # 正则表达式匹配 #define 后的内容（不含空格）
    pattern = r'#define\s+(\S+)'
    match = re.search(pattern, text)
    
    if match:
        # 提取内容并判断是否以 RL 开头
        define_content = match.group(1)
        return define_content.startswith('RL') or define_content.startswith('_')
    return False

def any_chars_in_string(chars, string):
    return any(char in string for char in chars)

def add_prefix_to_functions(input_file, output_file, prefix, check_comment, sdk_functions, bEnableAutoChgMacro):
    try:
        with open(input_file, 'r') as f:  # 显式指定编码
            lines = f.readlines()
    except Exception as e:
        print(f"无法读取文件 {input_file} 喵~ 错误信息: {e}")
        return

    # 处理后的代码行
    processed_lines = []

    # 添加特定注释在最前面
    processed_lines.append(f"// {check_comment}\n")

    # 块注释状态追踪
    in_block_comment = False
    comment_buffer = []  # 注释缓存
    prev_line = None  # 用来存储上一行的内容

    # 处理每一行
    for line in lines:
        # 处理块注释开始
        if '/*' in line and not in_block_comment:
            before, comment_part, after = line.partition('/*')
            comment_buffer.append(before + comment_part)  # 保留注释前内容
            in_block_comment = True
            line = after  # 后续处理剩余部分
        
        # 在块注释中时直接缓存
        if in_block_comment:
            comment_buffer.append(line)
            if '*/' in line:
                in_block_comment = False
                # 将缓存的完整注释加入结果
                processed_lines.extend(comment_buffer)
                comment_buffer = []
            continue
        
        # 处理行尾注释
        code_part, sep, comment = line.partition('//')
        line = code_part  # 只在代码部分处理替换
        
        #
        if is_macro_conditional(line):
            prev_line = line
            processed_lines.append(line + sep + comment)
            continue

        # 检查当前行是否是宏定义，且上一行是条件编译语句
        if re.match(r'^\s*#define\s+(\S+)', line):  # 宏定义行
            idx = line.find("(")
            eqfxpr = ['=', '>', '<', '!', '~', '-', '+', '*', '/', '&']
            eqfx = any_chars_in_string(eqfxpr, line)

            if eqfx == True or idx == -1:
                processed_lines.append(line + sep + comment)
                prev_line = None
                continue

            if idx > 1 and line[idx - 1] == ' ':
                processed_lines.append(line + sep + comment)
                prev_line = None
                continue

            if contains_rl_define(line):
                processed_lines.append(line + sep + comment)
                prev_line = None
                continue

            nxtkl = line.find("(", idx + 1)
            if nxtkl == -1 or (line[nxtkl + 1].isalpha() == True and line[nxtkl - 1].isalpha() == False):
                processed_lines.append(line + sep + comment)
                prev_line = None
                continue

            if prev_line and re.match(r'^\s*#ifndef\s+\w+', prev_line):  # 条件编译语句
                # 修改条件编译语句和宏定义
                modified_prev_line = re.sub(r'(#ifndef\s+)(\w+)', r'\1' + prefix + r'\2', prev_line)
                #result.append(modified_prev_line)
                #print(modified_prev_line)
                processed_lines.pop()
                processed_lines.append(modified_prev_line + sep + comment)
            
            # 修改宏定义中的函数名
            #print("当前行为宏定义，已跳过处理...")
            modified_line = add_prefix_to_macro_func(line, prefix)
            print(f"{line} -> {modified_line} all right?")
            tstr = ("\n" if bEnableAutoChgMacro else input("请主人确认一下结果喵~主人输入 n 或者 no 表示不修改；\n输入具体的内容我运用主人给的代码, 直接回车将确认修改喵~"))
            if tstr.lower().startswith("no") or tstr.lower().startswith("n"):
                processed_lines.append(line + sep + comment)
            elif tstr != "\n" and tstr != '':
                processed_lines.append(tstr + sep + comment)
            else:
                processed_lines.append(modified_line + sep + comment)
            prev_line = None
            continue
        elif "#include" in line:
            #print(line)
            processed_lines.append(line + sep + comment)
            prev_line = None
            continue
        prev_line = line

        # 查找普通函数定义
        result = re.findall(r'\b([A-Za-z_][A-Za-z0-9_]*)\s*\(', line)
        for func_name in result:
            if needs_prefix(func_name, line, sdk_functions):
                line = line.replace(func_name, prefix + func_name)
        
        # 处理 typedef 函数指针
        typedef_func = handle_typedef_function(line)
        if typedef_func and needs_prefix(typedef_func, line, sdk_functions):
            line = line.replace(typedef_func, prefix + typedef_func)
        
        processed_lines.append(line + sep + comment)  # 重新拼接注释

    # 将处理后的代码写入输出文件
    with open(output_file, 'w') as f:
        f.writelines(processed_lines)

def process_directory(input_dir, output_dir, prefix, check_comment, sdk_functions, exclude_dirs=None, bEnableAutoChgMacro=True):
    if not os.path.exists(input_dir):
        raise FileNotFoundError(f"主人，输入目录不存在喵！请检查 {input_dir} 喵~")
    
    exclude_dirs = set(exclude_dirs or [])  # 转换为集合方便查找
    input_dir = os.path.abspath(input_dir)  # 转为绝对路径
    
    noFound = True
    for root, dirs, files in os.walk(input_dir, topdown=True):
        # 计算相对路径用于排除判断
        rel_path = os.path.relpath(root, input_dir)
        current_dirs = rel_path.split(os.sep)
        
        # 检查当前路径是否在排除列表中（或父目录被排除）
        is_excluded = any(
            (d in exclude_dirs) or (os.path.join(*current_dirs[:i+1]) in exclude_dirs)
            for i, d in enumerate(current_dirs)
        )

        # 如果当前目录被排除，直接跳过
        if is_excluded:
            del dirs[:]  # 清空子目录列表阻止继续遍历
            continue
        
        # 过滤当前层需要排除的目录（防止进入子目录）
        dirs[:] = [d for d in dirs if d not in exclude_dirs]

        for cfile in files:
            if cfile.lower().endswith(('.h', '.c', '.hpp', '.cpp')):
                noFound = False
                input_path = os.path.join(root, cfile)
                # 构建输出路径保持目录结构
                rel_path = os.path.relpath(input_path, input_dir)
                output_path = os.path.join(output_dir, rel_path)
                # 确保输出目录存在
                os.makedirs(os.path.dirname(output_path), exist_ok=True)
                # 处理单个文件
                add_prefix_to_functions(input_path, output_path, prefix, check_comment, sdk_functions, bEnableAutoChgMacro)
                print(f"Processed: {input_path} -> {output_path}")
    if noFound: 
        raise FileNotFoundError(f"主人，没有找到目标文件喵！请检查 {input_dir} 目录下是否有代码文件喵~")

# # 示例使用
# & C:/Users/Lenovo/AppData/Local/Programs/Python/Python311/python.exe f:/RaylibApplication/raylib/reraylib-clean.py
#  --input_dir F:\RaylibApplication\raylib\raylib\src --output_dir F:\RaylibApplication\processed 
#  --prefix RL --exclude_dirs external\glfw

if __name__ == "__main__":
    # 设置命令行参数解析
    parser = argparse.ArgumentParser(description='为C/C++函数添加前缀喵~')
    parser.add_argument('--input_dir', required=True, help='输入目录路径喵')
    parser.add_argument('--output_dir', required=True, help='输出目录路径喵')
    parser.add_argument('--prefix', default='RL', help='要添加的前缀(默认RL)喵')
    parser.add_argument('--comment', default='This code is processed by LianYou\'s Raylib purification script.', 
                      help='文件头注释内容喵')
    parser.add_argument('--exclude_dirs', nargs='*', default=[],
                   help='要排除的目录列表 (空格分隔) 喵~ 例如: build docs/lib')
    parser.add_argument('--chg_macro', default=True,
                   help='是否要自动修改宏定义中的函数调用 (默认 True) 喵~ 例如: build docs/lib')
    args = parser.parse_args()
    
    # 批量处理目录
    try:
        # 预加载SDK函数列表
        sdk_funcs = get_sdk_functions()
        process_directory(
            input_dir=args.input_dir,
            output_dir=args.output_dir,
            prefix=args.prefix,
            check_comment=args.comment,
            sdk_functions=sdk_funcs,
            exclude_dirs=args.exclude_dirs
        )
    except Exception as e:
        print(f"\033[31m呜呜发生错误啦喵~: {str(e)}\033[0m")
        sys.exit(1)