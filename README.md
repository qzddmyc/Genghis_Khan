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
- 该项目被分为多个文件夹与多个文件进行存储。实际运行时，可以**将include、resource、src三个文件夹内的所有文件与main.cpp放至同一目录下**；否则，需要进行适当的配置并修改代码中的文件路径，代码才可正常运行。
- 所有文件的编码格式均为utf-8，如果遇到编码错误问题，可以尝试利用记事本更换文件编码方式。且由于编码的问题，可能会导致文件的编译错误，建议将项目在CLion中使用。

### 代码解释
- 族谱信息在代码中以二叉树为数据结构进行存储，左右子树分别存放的是后代与兄弟的信息。
- Genghis Khan.txt文件中，每一行的内容表示：人物姓名、生年、卒年、父亲姓名（第一代人物无此项）。
- main.cpp为主程序。
- 具体模块的介绍见代码中的注释。

### 声明
- 该代码仅以学习交流为目的开源，不建议直接将此代码用作其他任何用途。

### 结语
- 如有任何问题，欢迎与<qzddmyc@163.com>联系
- If you have found this project because of the course design of Data Structures and Algorithm Design in ujs, I hope you can give it a star, thanks : )
