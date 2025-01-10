# AuxiliaryArticalUploadTool

一个基于 Qt 的文章编辑和上传工具。

## 项目结构

```
AuxiliaryArticalUploadTool/
├── CMakeLists.txt          # CMake 构建配置文件
├── README.md               # 项目说明文档
├── build.sh               # 自动构建脚本
├── src/                    # 源代码目录
│   ├── main.cpp           # 主程序入口
│   ├── mainwindow.cpp     # 主窗口实现
│   ├── mainwindow.h       # 主窗口头文件
│   ├── editor/            # 编辑器相关代码
│   │   ├── editorwindow.cpp
│   │   ├── editorwindow.h
│   │   ├── markdownpreview.cpp
│   │   └── markdownpreview.h
│   ├── resources/         # 资源文件目录
│   │   ├── resources.qrc
│   │   └── icons/        # 图标资源
│   └── ui/                # UI 文件目录
│       └── mainwindow.ui  # 主窗口界面设计文件
```

## 开发环境要求

### macOS
- CMake 3.16 或更高版本
- Qt 6.0 或更高版本（如果没有 Qt 6，将自动使用 Qt 5）
- Xcode Command Line Tools
- C++17 兼容的编译器（AppleClang）
- brew（用于安装依赖）

### Windows
（待添加 Windows 配置说明）

## 构建说明

### macOS 构建步骤

1. 确保已安装所需工具：
   ```bash
   # 安装 Xcode Command Line Tools（如果尚未安装）
   xcode-select --install

   # 使用 brew 安装必要依赖
   brew install cmake ninja p7zip pkg-config qt@6
   ```

2. 克隆项目：
   ```bash
   git clone <repository-url>
   cd AuxiliaryArticalUploadTool
   ```

3. 构建项目：
   ```bash
   # 使用自动构建脚本（会自动清理之前的构建）
   ./build.sh
   ```

   > 注意：每次重新构建时，脚本会自动删除 build 目录并重新构建，以确保构建环境的清洁。

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
3. 资源文件放在 `src/resources` 目录下
4. 在 `CMakeLists.txt` 中的 `SOURCES` 变量中添加新文件

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
   - 使用 `./build.sh` 脚本进行完全清理和重建
   - 确保已安装所有必要的依赖

### Windows 相关问题
（待添加 Windows 相关问题解决方案）

## 许可证
（待添加许可证信息）

## CI/CD 和发布

### 自动构建流程
项目使用 GitHub Actions 进行自动构建，支持以下功能：
- 在推送版本标签时自动触发构建
- 同时构建 Intel (x86_64) 和 Apple Silicon (arm64) 版本
- 自动创建 GitHub Release 并上传构建产物

### 版本发布规范
1. 版本号格式：`v主版本.次版本.修订号`
   - 主版本：重大更新或不兼容的 API 更改
   - 次版本：向下兼容的功能更新
   - 修订号：bug 修复和小改动

2. 发布流程：
   ```bash
   # 1. 确保代码已经充分测试
   # 2. 创建新的版本标签
   git tag v2.0.12  # 根据实际版本号调整
   # 3. 推送标签到远程仓库
   git push origin v2.0.12
   ```

3. 发布产物：
   - 每个版本会生成两个 DMG 安装包：
     * Intel 版本：`AuxiliaryArticalUploadTool-x86_64.dmg`
     * Apple Silicon 版本：`AuxiliaryArticalUploadTool-arm64.dmg`
   - 用户需根据自己的 Mac 芯片类型选择对应版本

### 安装说明
1. 下载对应芯片版本的 DMG 文件
2. 打开 DMG 文件，将应用拖拽到 Applications 文件夹
3. 首次运行时，如果提示安全性问题：
   ```bash
   # 移除应用隔离属性
   sudo xattr -rd com.apple.quarantine /Applications/AuxiliaryArticalUploadTool.app
   ```
4. 在系统偏好设置 -> 安全性与隐私中允许打开应用 