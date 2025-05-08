# Genghis-Khan 王的传承

### 简介
- 这是以“王的传承”为主题，使用c++编写的**铁木真家族族谱管理**系统。
- 该项目功能包含以下内容：
  - 对所有成员以图形或列表的样式进行展示；
  - 按多种方案对成员进行查询；
  - 添加新的成员；
  - 修改某成员的具体信息；
  - 删除成员及其后代。

### 注意事项
- 家族族谱原文件保存在[Genghis Khan.txt](https://github.com/qzddmyc/Genghis_Khan/blob/main/resource/Genghis%20Khan.txt)中。
- 该代码的所有操作均使用O(n)或O(n<sup>2</sup>)的复杂度实现，并未进行算法的优化。
- 该项目下包含了两份完整的代码，介绍如下：
  - main.cpp与include、resource、src这三个文件夹共同构成的是一份完整的代码，**供阅读使用**，编码格式为utf-8。注意，不要尝试在Microsoft Visual Studio中运行此代码，会因编码及部分语法问题报错。
  - CONFIGURATION文件夹中是另一份完整的代码，编码格式为GBK，并同时提供了[在CLion 2024.1.1中配置项目的方法](https://github.com/qzddmyc/Genghis_Khan/blob/main/CONFIGURATION/Specification.md)，可按照该文件的指引，将代码放在CLion中正常运行。

### 代码解释
- 族谱信息在代码中以二叉树为数据结构进行存储，左右子树分别存放的是后代与兄弟的信息。
- Genghis Khan.txt文件中，每一行的内容表示：人物姓名、生年、卒年、父亲姓名（第一代人物无此项）。
- main.cpp为主程序。
- 具体模块的介绍见代码中的注释。

### 代码优势
- 逻辑严谨。如对于每个人物的生年与卒年在所有操作中均存在具体的范围判断；在用户的操作会涉及人物的后代（如修改人物的父亲、删除人物）时，会自动对后代进行相应的操作。
- 界面美观。虽然使用控制台作为交互界面，但对信息的输出部分有较为美观的展示。
- 结构清晰。对该项目添加个性化的功能，或删除部分功能较为简易。

### 声明
- 该代码仅以学习交流为目的开源，不建议直接将此代码用作其他任何用途。

### 结语
- 如有任何问题，欢迎与<qzddmyc@163.com>联系
- If you have found this project because of the course design of Data Structures and Algorithm Design in ujs or any other school, I hope you can give it a star, thanks.
