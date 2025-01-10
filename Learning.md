# Qt 项目命令行操作指南

本文档详细记录了项目开发中常用的命令行操作和其输出示例。

## 环境配置

### 1. 检查开发环境
```bash
# 检查 CMake 版本
$ cmake --version
cmake version 3.27.7

# 检查 Qt 版本
$ qmake --version
QMake version 3.1
Using Qt version 6.6.1 in /usr/local/lib

# 检查编译器版本
$ clang++ --version
Apple clang version 15.0.0 (clang-1500.1.0.2.5)
```

### 2. 安装必要工具
```bash
# 安装 Xcode Command Line Tools
$ xcode-select --install
xcode-select: note: install requested for command line developer tools

# 使用 Homebrew 安装 Qt
$ brew install qt
==> Downloading https://ghcr.io/v2/homebrew/core/qt/manifests/6.6.1
==> Installing qt
==> Installing dependencies for qt: ...
🍺  /usr/local/Cellar/qt/6.6.1: 15,091 files, 666.3MB

# 安装 CMake
$ brew install cmake
==> Downloading https://ghcr.io/v2/homebrew/core/cmake/manifests/3.27.7
==> Installing cmake
🍺  /usr/local/Cellar/cmake/3.27.7: 3,297 files, 49.7MB
```

## 项目构建

### 1. 首次构建
```bash
# 创建并进入构建目录
$ mkdir build && cd build

# 配置项目
$ cmake ..
-- The CXX compiler identification is AppleClang 15.0.0.15000309
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found OpenGL: /Library/Developer/CommandLineTools/SDKs/MacOSX15.0.sdk/System/Library/Frameworks/OpenGL.framework
-- Found WrapOpenGL: TRUE
-- Configuring done (1.6s)
-- Generating done (0.1s)
-- Build files have been written to: /Users/username/QtDemo/build

# 构建项目
$ cmake --build .
[  0%] Built target QtDemo_autogen_timestamp_deps
[ 16%] Automatic MOC and UIC for target QtDemo
[ 16%] Built target QtDemo_autogen
[ 33%] Building CXX object CMakeFiles/QtDemo.dir/QtDemo_autogen/mocs_compilation.cpp.o
[ 50%] Building CXX object CMakeFiles/QtDemo.dir/src/main.cpp.o
[ 66%] Building CXX object CMakeFiles/QtDemo.dir/src/mainwindow.cpp.o
[ 83%] Linking CXX executable QtDemo.app/Contents/MacOS/QtDemo
[100%] Built target QtDemo
```

### 2. 清理和重新构建
```bash
# 删除构建目录
$ rm -rf build

# 重新创建构建目录
$ mkdir build && cd build

# 重新构建
$ cmake .. && cmake --build .
[构建输出与首次构建类似]
```

### 3. 运行应用
```bash
# 方式 1：直接运行可执行文件
$ ./QtDemo.app/Contents/MacOS/QtDemo

# 方式 2：使用 open 命令
$ open QtDemo.app
```

## 常见问题和解决方案

### 1. Qt 库未找到
```bash
# 问题输出示例
CMake Error: Qt6 not found.

# 解决方案：设置 Qt 路径
$ export CMAKE_PREFIX_PATH=/usr/local/opt/qt/lib/cmake
$ cmake ..
```

### 2. 编译错误
```bash
# 清理构建目录
$ rm -rf build/*

# 检查 CMake 配置
$ cmake .. -LAH
-- Cache values
CMAKE_BUILD_TYPE:STRING=
CMAKE_INSTALL_PREFIX:PATH=/usr/local
Qt6_DIR:PATH=/usr/local/opt/qt/lib/cmake/Qt6

# 重新构建
$ cmake --build .
```

### 3. 运行时库加载问题
```bash
# 检查动态库依赖
$ otool -L QtDemo.app/Contents/MacOS/QtDemo
QtDemo.app/Contents/MacOS/QtDemo:
    @rpath/QtWidgets.framework/Versions/A/QtWidgets
    @rpath/QtGui.framework/Versions/A/QtGui
    @rpath/QtCore.framework/Versions/A/QtCore
    /System/Library/Frameworks/AppKit.framework/Versions/C/AppKit
    ...

# 修复库路径
$ install_name_tool -add_rpath "@executable_path/../Frameworks" QtDemo.app/Contents/MacOS/QtDemo
```

## 有用的调试命令

### 1. 查看构建信息
```bash
# 显示详细的构建过程
$ cmake --build . -v

# 查看 CMake 变量
$ cmake -LA
```

### 2. 检查可执行文件
```bash
# 查看可执行文件信息
$ file QtDemo.app/Contents/MacOS/QtDemo
QtDemo.app/Contents/MacOS/QtDemo: Mach-O 64-bit executable arm64

# 查看动态库依赖
$ otool -L QtDemo.app/Contents/MacOS/QtDemo
```

### 3. 项目清理
```bash
# 删除所有构建产物
$ rm -rf build/
$ rm -rf *.o moc_* ui_* qrc_*
``` 