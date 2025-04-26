#pragma once

#include "constant_vals_funcs.h"
#include "queue.h"
#include "stack.h"

// �������࣬�Լ����ж���Ĺ��ܺ�����
// headΪ������ͷ��㡣

class Data {
private:
    Node *head;

    // �Զ����ó�Ա��Ϣ��ӵ�head�ĺ���λ��
    void append_auto(const string &, int, int, const string &);

    // ���ݸ��������������ظó�Ա�Ľ��ָ�롣���������ڻ����Warning���档
    Node *GetNode_byName(const string &);

    // ����string���ҵ�nameΪstring�Ľ�㣬���Զ���Node*��Ϊ�ýڵ�ĺ��ӡ�����Node*�ɰ������ӣ���bro����Ϊ�ա�
    void AddChild_toParent(const string &, Node *);

    // �жϵ�һ�������Ƿ�Ϊ�ڶ������������һ�����ӡ�����show_byGraph���ּ�ͷ����ʾ��
    bool IsLastChild(const string &, const string &);

    // �жϸ������Ƿ���ڡ�
    bool IsMemberExist(const string &);

    // ���ݸ��������֣����ظ������ǰһ���ڵ㣬���۸�������ص������bro����childΪ�����������
    Node *GetNode_before_target(const string &);

    // ʹ�õݹ飬���ո����ڵ㣬������������brother��child��
    void del_nodes_after_the_node_given(Node *, bool);

    // ������б�չʾ�ĳ�Ա�ı��⣬����������
    void show_List_title();

    // ������б�չʾ�ĳ�Ա�ı��⣬������������
    void show_List_title_without_dynasty();

    // ������б�չʾ�ı�β������������
    void show_List_tail();

    // ������б�չʾ�ı�β��������������
    void show_List_tail_without_dynasty();

    // ���б�չʾ����������Ϣ��boolΪ�Ƿ�չʾ����������Ϣ��
    void show_List_of_single_member(Node *, bool);

    void show_List_head_with_age();

    void show_List_of_single_member_with_age(Node *);

    void modify_name(Node *);

    // �������ڵ�������޸�Ϊָ���ַ�����
    void modify_single_name_to(Node *, string);

    void modify_single_father_to(Node *, string);

    void modify_birth_year(Node *);

    void modify_death_year(Node *);

    // �������ﲻ����bro��cldʱ�ſ�ʹ�á�ͨ��ɾ������ӵķ�ʽ���ĸ�����ĸ��ס�
    void modify_parent_only_when_without_BroORCld(Node *);

    void modify_pare_with_lrNode(Node *);

    // ֱ��ɾ�������������bro��cldʱ�ſ�ʹ�á�
    void delete_node_which_without_BroORCld(Node *);

    // ��������ѯ��
    void query_by_name();

    void query_by_dynasty();

    // �������������У����������ֵ��
    int get_Max_Dynasty();

    // ���б�ķ�ʽ��չʾ����������ĳ�ض�ֵ�������������Ѱ�����ͷ��β��
    void show_special_dynasty_byLsit(int);

    // ��ѯĳ�˵Ķ��ӡ�
    void query_someone_s_child();

    void query_someone_s_father();

    void query_someone_s_brother();

    // ��չʾ������
    void Show();

    // ���˳�������
    void EXIT();

    // ����������
    void Manage();

    // ͨ���ݹ飬ɾ�����нڵ㣬�ͷ�new���Ŀռ䡣������head���ɡ�
    void delete_memory_before_exit(Node *);

    // ����������Ϣ��txt�ĵ���
    void save_all();

    // ��ѯ�ض�����ε�ƽ������
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

    // �����к������ѵ���init��ȡ��Ϣ����ʼ��head��
    void func();
};