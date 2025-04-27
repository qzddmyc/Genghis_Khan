#pragma once

#include "constant_vals_funcs.h"
#include "queue.h"
#include "stack.h"

// 二叉树类，以及所有额外的功能函数。
// head为二叉树头结点。

class Data {
private:
    Node *head;

    // 自动将该成员信息添加到head的合适位置
    void append_auto(const string &, int, int, const string &);

    // 根据给到的姓名，返回该成员的结点指针。姓名不存在会输出Warning警告。
    Node *GetNode_byName(const string &);

    // 根据string，找到name为string的结点，并自动将Node*设为该节点的孩子。其中Node*可包含孩子，但bro必须为空。
    void AddChild_toParent(const string &, Node *);

    // 判断第一个参数是否为第二个参数的最后一个儿子。用于show_byGraph区分箭头的显示。
    bool IsLastChild(const string &, const string &);

    // 判断该姓名是否存在。
    bool IsMemberExist(const string &);

    // 根据给到的名字，返回该人物的前一个节点，无论该人物（返回的人物）的bro还是child为给定名字人物。
    Node *GetNode_before_target(const string &);

    // 使用递归，回收给定节点，并回收其所有brother与child。
    void del_nodes_after_the_node_given(Node *, bool);

    // 输出按列表展示的成员的标题，含“代”。
    void show_List_title();

    // 输出按列表展示的成员的标题，不含“代”。
    void show_List_title_without_dynasty();

    // 输出按列表展示的表尾，含“代”。
    void show_List_tail();

    // 输出按列表展示的表尾，不含“代”。
    void show_List_tail_without_dynasty();

    // 按列表展示单条人物信息。bool为是否展示“代”的信息。
    void show_List_of_single_member(Node *, bool);

    void show_List_head_with_age();

    void show_List_of_single_member_with_age(Node *);

    void modify_name(Node *);

    // 将单个节点的姓名修改为指定字符串。
    void modify_single_name_to(Node *, string);

    void modify_single_father_to(Node *, string);

    void modify_birth_year(Node *);

    void modify_death_year(Node *);

    // 仅该人物不存在bro或cld时才可使用。通过删除再添加的方式更改该人物的父亲。
    void modify_parent_only_when_without_BroORCld(Node *);

    void modify_pare_with_lrNode(Node *);

    // 直接删除人物，仅人物无bro或cld时才可使用。
    void delete_node_which_without_BroORCld(Node *);

    // 按姓名查询。
    void query_by_name();

    void query_by_dynasty();

    // 返回所有人物中，朝代的最大值。
    int get_Max_Dynasty();

    // 按列表的方式，展示仅朝代符合某特定值的所有人物，输出已包含表头表尾。
    void show_special_dynasty_byLsit(int);

    // 查询某人的儿子。
    void query_someone_s_child();

    void query_someone_s_father();

    void query_someone_s_brother();

    // “展示”函数
    void Show();

    // “退出”函数
    void EXIT();

    // “管理”函数
    void Manage();

    // 通过递归，删除所有节点，释放new出的空间。参数传head即可。
    void delete_memory_before_exit(Node *);

    // 保存所有信息至txt文档。
    void save_all();

    // 查询特定年龄段的平均年龄
    void query_get_average_age();

    void cout_and_show_average_age(int, int);

public:
    Data()
            : head(nullptr) {}

    void init();

    void show_byList();

    void show_byGraph();

    void add_member();

    void del_member();

    void modify();

    void query();

    // 总运行函数，已调用init读取信息，初始化head。
    void func();
};