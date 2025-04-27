# 文件在CLion中的配置方法
### 获取配置好的文件
- 该项目的[Releases-v1.0](https://github.com/qzddmyc/Genghis_Khan/releases/tag/v1.0)中为一份已经配置并编译完成的CLion项目文件，可以下载后尝试使用CLion打开；若无法运行，可以参考下方说明手动建立项目。

### 配置步骤
1. 新建一个项目，语言标准选择C++20

2. 将以下代码替换到初始的main.cpp文件中
```c++
#include "data.h"

int main() {
    Data dat;
    dat.func();

    return 0;
}
```

3. 将[CODE文件夹](https://github.com/qzddmyc/Genghis_Khan/edit/main/CONFIGURATION/CODE)中的所有文件复制粘贴至main.cpp的同一目录下

4. 将[TEXT文件夹](https://github.com/qzddmyc/Genghis_Khan/edit/main/CONFIGURATION/TEXT)中的Genghis Khan.txt文件复制粘贴至自动被创建的cmake-build-debug文件夹下

5. 打开被自动创建的CMakeLists.txt文件（与main.cpp同目录），将以下代码替换掉 `add_executable(项目名称 main.cpp)` 语句。其中项目名称为所建项目的文件夹名
```
add_executable(项目名称 main.cpp
        constant_vals_funcs.h
        constant_vals_funcs.cpp
        person.h
        person.cpp
        node.h
        node.cpp
        queue.h
        queue.cpp
        stack.h
        stack.cpp
        data.h
        data.cpp)
```

6. 右击CMakeLists.txt，选择重新加载CMake项目

7. 点击左侧工具栏“运行”（若无此按钮，在顶部运行一下项目即可），点击其中的三个点，选择“修改运行配置”，如图所示；再勾选上“在输出控制台中模拟终端”，点击“应用”
- <img src="https://github.com/user-attachments/assets/e4f57338-11c7-41be-ad04-236661f95b40" style="width: 300px;"/>

8. 正常运行项目即可

### 可能的报错及解决方案
- 如果在运行后提示"File lost!"，可以尝试在第四步中，将txt文件放在main.cpp的同一目录下。实际上，该.txt文件应该与生成的.exe执行文件放在同一目录下，编译器生成该执行文件的位置可能会有所不同。
- 在CLion中打开所添加的文件时，可能会显示“文件以错误的编码加载”，此时点击“以'GBK'重新加载”即可。注意，**不可以**点击“将项目编码设置为'GBK'”，否则会出现乱码。
