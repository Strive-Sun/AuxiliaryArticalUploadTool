#!/bin/bash

# 删除旧的build目录
rm -rf build

# 创建新的build目录
mkdir build
cd build

# 运行CMake配置
cmake ..

# 执行构建
make

# 设置应用程序执行权限
chmod +x AuxiliaryArticalUploadTool.app/Contents/MacOS/AuxiliaryArticalUploadTool

# 返回到原目录
cd ..

echo "重建完成!"
echo "现在您可以通过以下方式运行程序："
echo "open build/AuxiliaryArticalUploadTool.app" 