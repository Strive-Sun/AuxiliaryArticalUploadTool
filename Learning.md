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

## GitHub Actions 自动构建配置

### 1. 创建工作流配置文件
```bash
# 创建 GitHub Actions 配置目录
$ mkdir -p .github/workflows

# 创建工作流配置文件
$ touch .github/workflows/macos-build.yml

# 注意：工作流不会自动创建，需要手动创建并编写配置文件
# 可以通过以下两种方式之一创建：

# 方式1：通过 GitHub 网页创建
# 1. 访问你的 GitHub 仓库
# 2. 点击 "Actions" 标签
# 3. 点击 "New workflow"
# 4. 选择 "set up a workflow yourself"
# 5. 编写配置文件内容
# 6. 点击 "Start commit" 提交配置

# 方式2：本地创建（推荐）
# 1. 在本地创建配置文件
$ mkdir -p .github/workflows
$ vim .github/workflows/macos-build.yml  # 或使用其他编辑器

# 2. 提交并推送配置
$ git add .github/workflows/macos-build.yml
$ git commit -m "ci: 添加 macOS 应用自动构建工作流"
$ git push origin develop
```

### 2. 配置自动构建流程
```yaml
# .github/workflows/macos-build.yml 文件内容
name: Build macOS App

on:
  push:
    tags:
      - 'v*'  # 当推送版本标签时触发

permissions:
  contents: write
  packages: write

jobs:
  build:
    runs-on: macos-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install Dependencies
        run: |
          brew update
          brew install cmake ninja p7zip pkg-config qt@6
      # ... 更多步骤配置 ...
```

### 3. 触发自动构建
```bash
# 创建新的版本标签
$ git tag -a v1.0.0 -m "Release version 1.0.0"

# 推送标签到 GitHub，这将触发构建
$ git push origin v1.0.0
```

### 4. 构建产物
- 构建完成后会在 GitHub Releases 页面创建新的发布
- 发布包含自动构建的 DMG 安装包
- Release 说明中包含安装步骤

### 5. 本地安装说明
```bash
# 1. 下载并打开 DMG 文件
# 2. 将应用拖拽到 Applications 文件夹
# 3. 移除应用隔离属性
$ xattr -cr /Applications/AuxiliaryArticalUploadTool.app

# 4. 在系统偏好设置中允许打开应用
```

### 6. 常见问题处理

#### 6.1 权限问题
```yaml
# 在 workflow 中添加权限配置
permissions:
  contents: write
  packages: write
```

#### 6.2 Qt 依赖问题
```bash
# 设置 Qt 环境变量
qtpath=$(brew --prefix qt@6)
echo "QT_PATH=${qtpath}" >> $GITHUB_ENV
echo "CMAKE_PREFIX_PATH=${qtpath}" >> $GITHUB_ENV
```

#### 6.3 构建失败检查
```bash
# 查看构建日志
# 1. 访问 GitHub 仓库的 Actions 标签页
# 2. 点击失败的工作流
# 3. 展开失败的步骤查看详细日志
``` 