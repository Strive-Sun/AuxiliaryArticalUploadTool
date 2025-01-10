# AuxiliaryArticalUploadTool

一个基于 Qt 的文章编辑和上传工具。

## 项目结构

```
AuxiliaryArticalUploadTool/
├── CMakeLists.txt          # CMake 构建配置文件
├── README.md               # 项目说明文档
├── src/                    # 源代码目录
│   ├── main.cpp           # 主程序入口
│   ├── mainwindow.cpp     # 主窗口实现
│   ├── mainwindow.h       # 主窗口头文件
│   ├── editor/            # 编辑器相关代码
│   │   ├── editorwindow.cpp
│   │   ├── editorwindow.h
│   │   ├── markdownpreview.cpp
│   │   └── markdownpreview.h
│   └── ui/                # UI 文件目录
│       └── mainwindow.ui  # 主窗口界面设计文件
```

## 开发环境要求

### macOS
- CMake 3.16 或更高版本
- Qt 6.0 或更高版本（如果没有 Qt 6，将自动使用 Qt 5）
- Xcode Command Line Tools
- C++17 兼容的编译器（AppleClang）

### Windows
（待添加 Windows 配置说明）

## 构建说明

### macOS 构建步骤

1. 确保已安装所需工具：
   ```bash
   # 安装 Xcode Command Line Tools（如果尚未安装）
   xcode-select --install

   # 使用 brew 安装 Qt 和 CMake（如果尚未安装）
   brew install qt cmake
   ```

2. 克隆项目：
   ```bash
   git clone <repository-url>
   cd AuxiliaryArticalUploadTool
   ```

3. 构建项目：
   ```bash
   # 使用自动构建脚本
   ./rebuild.sh
   ```

4. 运行应用：
   ```bash
   open build/AuxiliaryArticalUploadTool.app
   ```

### Windows 构建步骤
（待添加 Windows 构建说明）

## 开发指南

### 添加新文件
1. 源代码文件放在 `src` 目录下
2. UI 文件放在 `src/ui` 目录下
3. 在 `CMakeLists.txt` 中的 `SOURCES` 变量中添加新文件

### 项目配置
- 项目使用 CMake 构建系统
- 默认使用 C++17 标准
- 自动处理 Qt MOC、RCC 和 UIC

## 故障排除

### macOS 相关问题
1. Qt 库未找到
   - 确保 Qt 已正确安装
   - 检查 CMAKE_PREFIX_PATH 是否包含 Qt 安装路径

2. 构建错误
   - 使用 `./rebuild.sh` 脚本进行完全清理和重建

### Windows 相关问题
（待添加 Windows 相关问题解决方案）

## 许可证
（待添加许可证信息） 