# Qt 示例项目

这是一个基础的 Qt 项目，用于展示 Qt 的基本特性。本文档将指导你如何从零开始设置环境并运行这个项目。

## 环境配置（macOS）

### 1. 安装 Homebrew
如果还没有安装 Homebrew，请先安装它：
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. 安装 Qt
使用 Homebrew 安装 Qt 和 Qt Creator：
```bash
# 安装 Qt 框架
brew install qt

# 输出示例：
==> Downloading https://ghcr.io/v2/homebrew/core/qt/manifests/6.7.3
##################################################################################################### 100.0%
==> Installing qt
==> Installing dependencies for qt: assimp, brotli, dbus, double-conversion, ...
🍺  /usr/local/Cellar/qt/6.7.3: 15,091 files, 666.3MB

# 安装 Qt Creator IDE
brew install --cask qt-creator

# 安装完成后会显示提示信息：
==> Caveats
You can add Homebrew's Qt to QtCreator's "Qt Versions" in:
  Preferences > Qt Versions > Link with Qt...
pressing "Choose..." and selecting as the Qt installation path:
  /usr/local
```

## 项目结构
```
Qt-Project/
├── QtDemo.pro      # Qt 项目文件
├── main.cpp        # 主程序入口
├── mainwindow.h    # 主窗口头文件
├── mainwindow.cpp  # 主窗口实现文件
└── mainwindow.ui   # 用户界面文件
```

### 文件说明
- `QtDemo.pro`: 项目配置文件，定义了项目的基本设置和依赖关系
- `main.cpp`: 程序入口点，创建并显示主窗口
- `mainwindow.h`: 主窗口类的声明
- `mainwindow.cpp`: 主窗口类的实现，包含具体的功能代码
- `mainwindow.ui`: 界面布局文件，使用 Qt Designer 创建

## 编译和运行

### 方法一：命令行编译
1. 进入项目目录：
```bash
cd Qt-Project
```

2. 生成 Makefile：
```bash
qmake

# 输出示例：
Info: creating stash file /Users/username/Qt-Project/.qmake.stash
Project WARNING: Qt has only been tested with version 14 of the platform SDK, you're using 15.
Project WARNING: This is an unsupported configuration. You may experience build issues...
```

3. 编译项目：
```bash
make

# 输出示例：
/usr/local/share/qt/libexec/uic mainwindow.ui -o ui_mainwindow.h
/usr/local/share/qt/libexec/moc -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB ...
/Library/Developer/CommandLineTools/usr/bin/clang++ -c -pipe -stdlib=libc++ -O2 -std=gnu++1z ...
... [编译过程输出] ...
/Library/Developer/CommandLineTools/usr/bin/clang++ -stdlib=libc++ ... -o QtDemo.app/Contents/MacOS/QtDemo
```

4. 运行程序：
```bash
# macOS
open QtDemo.app
# 程序将启动并显示图形界面

# Linux
./QtDemo
# 程序将启动并显示图形界面

# Windows
QtDemo.exe
# 程序将启动并显示图形界面
```

### 方法二：使用 Qt Creator
1. 打开 Qt Creator
2. 选择 "File" -> "Open File or Project"
3. 选择项目目录中的 `QtDemo.pro` 文件
4. 点击左下角的运行按钮（绿色三角形）或按 Ctrl+R (Windows/Linux) / Cmd+R (macOS)

## 运行效果

运行程序后，你将看到：

1. 一个标题为 "Qt Demo" 的窗口，大小为 400x300 像素
2. 窗口中央显示文本 "欢迎使用 Qt!"
3. 下方有一个标签为 "点击我" 的按钮
4. 点击按钮后，会弹出一个消息框，显示以下内容：
   ```
   这是一个 Qt 消息框示例！
   展示了以下 Qt 特性：
   - 窗口创建
   - 布局管理
   - 信号槽机制
   - 消息框
   ```

## 项目功能说明

这个示例项目展示了以下 Qt 特性：

1. **窗口管理**
   - 使用 `QMainWindow` 创建主窗口
   - 设置窗口标题和大小

2. **布局系统**
   - 使用 `QVBoxLayout` 实现垂直布局
   - 自动调整控件大小和位置

3. **基本控件**
   - `QLabel`: 显示文本标签
   - `QPushButton`: 可点击的按钮

4. **信号和槽**
   - 按钮点击信号与自定义槽函数的连接
   - 事件处理机制

5. **对话框**
   - 使用 `QMessageBox` 显示消息提示框

## 常见问题解决

1. **如果 qmake 命令找不到**
   ```bash
   echo 'export PATH="/usr/local/opt/qt/bin:$PATH"' >> ~/.zshrc
   source ~/.zshrc
   
   # 验证安装：
   qmake --version
   # 输出示例：
   # QMake version 3.1
   # Using Qt version 6.7.3 in /usr/local/lib
   ```

2. **编译错误：找不到 Qt 头文件**
   - 确保 Qt 安装正确
   - 检查 QtDemo.pro 文件中的配置
   - 确保环境变量设置正确
   ```bash
   # 检查 Qt 环境变量
   echo $PATH | grep qt
   # 应该能看到 Qt 的路径
   ```

3. **运行时缺少动态库**
   - macOS: 确保 Qt 框架已正确安装
     ```bash
     # 检查 Qt 框架安装位置
     ls -l /usr/local/lib/Qt*.framework
     ```
   - Linux: 安装 `libqt6-core` 等必要包
     ```bash
     # Ubuntu/Debian
     sudo apt-get install libqt6core6 libqt6gui6 libqt6widgets6
     ```
   - Windows: 确保 Qt DLL 文件在系统路径中
     ```batch
     # 检查环境变量
     echo %PATH%
     ```

## 进一步学习

1. **Qt 官方文档**
   - [Qt Documentation](https://doc.qt.io/)
   - [Qt Examples](https://doc.qt.io/qt-6/examples-tutorials.html)

2. **推荐的学习路径**
   - 熟悉 Qt Creator IDE
   - 学习更多控件的使用
   - 了解信号槽机制
   - 学习布局管理
   - 探索 Qt 的其他模块（网络、数据库等）

3. **实践建议**
   - 修改这个示例程序，添加新功能
   - 尝试使用不同的控件
   - 实验不同的布局方式
   - 添加菜单栏和工具栏

## 许可证

本项目采用 MIT 许可证。 