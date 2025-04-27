#pragma once

#include "data.h"

void Data::append_auto(const string &_n, int _b, int _d, const string &_p) {
    if (_n == "None") {
        set_cout_RED();
        cout << "非法姓名：" << _n << "，添加失败！" << endl;
        reset_cout_color();
        return;
    }

    //特例处理。
    if (head == nullptr || _p == "None") {
        if (head == nullptr && _p == "None") {
            head = new Node(_n, _b, _d, _p);
        } else {
            cout << "Wrong information!";
        }
        return;
    }

    Node *new_node = new Node(_n, _b, _d, _p);
    AddChild_toParent(_p, new_node);
}

Node *Data::GetNode_byName(const string &tar) {
    Queue queue;
    queue.push(head);
    Node *tmp = nullptr;
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        if (tmp->val.name == tar) {
            queue.clear();
            return tmp;
        }
        if (tmp->nextBro)
            queue.push(tmp->nextBro);
        if (tmp->nextCld)
            queue.push(tmp->nextCld);
    }
    cout << "Waring: returned a nullptr because of nonexistence of the Name!" << endl;
    return nullptr;
}

void Data::AddChild_toParent(const string &tar, Node *n_nd) {
    if (n_nd->val.name == "None") {
        set_cout_RED();
        cout << "非法姓名：" << n_nd->val.name << "，添加失败！" << endl;
        reset_cout_color();
        return;
    }

    if (n_nd->val.name == n_nd->val.parent) {
        set_cout_RED();
        cout << "自己的名字不能与父亲的姓名相同！添加失败。" << endl;
        reset_cout_color();
        delete n_nd;
        return;
    }

    if (this->IsMemberExist(n_nd->val.name)) {
        set_cout_RED();
        cout << "姓名" << n_nd->val.name << "已存在！添加失败！" << endl;
        reset_cout_color();
        delete n_nd;
        return;
    }

    if (n_nd->nextBro) {
        cout << "Error in func: AddChild_toParent, new node owns its bro!" << endl;
        exit(-1);
    }

    Node *par = GetNode_byName(tar);
    if (!par) {
        delete n_nd;
        return;
    }
    if (!par->nextCld) {
        par->nextCld = n_nd;
        return;
    }

    // 自己是兄弟中最小的一个
    if (par->nextCld->val.birth_year > n_nd->val.birth_year) {
        n_nd->nextBro = par->nextCld;
        par->nextCld = n_nd;
        return;
    }

    // 查找第一个比自己年龄大的兄弟。
    Node *tmp = par->nextCld;
    while (tmp->nextBro && tmp->nextBro->val.birth_year <= n_nd->val.birth_year) {
        tmp = tmp->nextBro;
    }

    n_nd->nextBro = tmp->nextBro;
    tmp->nextBro = n_nd;
}

bool Data::IsLastChild(const string &self, const string &father) {
    Node *father_node = this->GetNode_byName(father);
    if (!father_node) {
        cout << "Test Warning: Error of nullptr in func Data::IsLastChild!" << endl;
        return false;
    }
    Node *bros = father_node->nextCld;
    if (!bros) {
        return false;
    }
    while (bros->nextBro)
        bros = bros->nextBro;
    return bros->val.name == self;
}

bool Data::IsMemberExist(const string &tar) {
    Queue queue;
    queue.push(head);
    Node *tmp;
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        if (tmp->val.name == tar) {
            queue.clear();
            return true;
        }
        if (tmp->nextBro)
            queue.push(tmp->nextBro);
        if (tmp->nextCld)
            queue.push(tmp->nextCld);
    }
    return false;
}

Node *Data::GetNode_before_target(const string &tar) {
    if (head->val.name == tar) {
        return nullptr;
    }
    Queue queue;
    queue.push(head);
    Node *tmp;
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        if ((tmp->nextBro && tmp->nextBro->val.name == tar) || (tmp->nextCld && tmp->nextCld->val.name == tar)) {
            queue.clear();
            return tmp;
        }
        if (tmp->nextBro)
            queue.push(tmp->nextBro);
        if (tmp->nextCld)
            queue.push(tmp->nextCld);
    }
    return nullptr;
}

void Data::del_nodes_after_the_node_given(Node *n, bool showData) {
    if (n == nullptr)
        return;
    if (showData)
        this->show_List_of_single_member(n, false);
    del_nodes_after_the_node_given(n->nextBro, showData);
    del_nodes_after_the_node_given(n->nextCld, showData);
    n->nextBro = nullptr;
    n->nextCld = nullptr;
    delete n;
}

void Data::show_List_title() {
    cout << "┌------┬---------------┬----------------┬-----------------┬----------------┐" << endl;
    cout << "   代\t"
         << left << setw(GAP) << "姓名"
         << left << setw(GAP) << "生年"
         << left << setw(GAP) << "卒年"
         << left << setw(GAP) << "父亲"
         << endl;
    cout << " ------|---------------|----------------|-----------------|----------------" << endl;
}

void Data::show_List_title_without_dynasty() {
    cout << "┌---------------┬----------------┬-----------------┬----------------┐" << endl;
    cout << "  "
         << left << setw(GAP) << "姓名"
         << left << setw(GAP) << "生年"
         << left << setw(GAP) << "卒年"
         << left << setw(GAP) << "父亲"
         << endl;
    cout << " ---------------|----------------|-----------------|----------------" << endl;
}

void Data::show_List_tail() {
    cout << "└------┴---------------┴----------------┴-----------------┴----------------┘" << endl;
}

void Data::show_List_tail_without_dynasty() {
    cout << "└---------------┴----------------┴-----------------┴----------------┘" << endl;
}

void Data::show_List_of_single_member(Node *nd, bool showGeneration) {
    if (nd == nullptr) {
        cout << "Test Warning: showing member of a nullptr!" << endl;
        return;
    }
    cout << " ";
    if (showGeneration)
        cout << "第" << nd->Generation_used_ONLY_in_Queue << "代\t";
    else
        cout << " ";
    cout << left << setw(GAP) << nd->val.name
         << left << setw(GAP) << nd->val.birth_year
         << left << setw(GAP) << nd->val.death_year;
    if (nd->val.parent != "None") {
        cout << left << setw(GAP) << nd->val.parent << endl;
    } else {
        cout << endl;
    }
}

void Data::show_List_head_with_age() {
    cout << "┌------┬---------------┬----------------┬-----------------┬----------------┐" << endl;
    cout << "  年龄\t"
         << left << setw(GAP) << "姓名"
         << left << setw(GAP) << "生年"
         << left << setw(GAP) << "卒年"
         << left << setw(GAP) << "父亲"
         << endl;
    cout << " ------|---------------|----------------|-----------------|----------------" << endl;
}

void Data::show_List_of_single_member_with_age(Node *nd) {
    if (nd == nullptr) {
        cout << "Test Warning: showing member of a nullptr!" << endl;
        return;
    }

    cout << "   " << nd->val.death_year - nd->val.birth_year << "\t";
    cout << left << setw(GAP) << nd->val.name
         << left << setw(GAP) << nd->val.birth_year
         << left << setw(GAP) << nd->val.death_year;
    if (nd->val.parent != "None") {
        cout << left << setw(GAP) << nd->val.parent << endl;
    } else {
        cout << endl;
    }
}

void Data::modify_name(Node *n) {
    if (!n) {
        cout << "Test Error: modify name error with nullptr!" << endl;
        exit(-1);
    }
    cout << "你即将修改" << n->val.name << "的姓名，请输入修改后的名字：";
    string new_name;
    cin >> new_name;
    clear_all();

    if (new_name == "None") {
        set_cout_RED();
        cout << "非法姓名：" << new_name << "，修改失败！" << endl;
        reset_cout_color();
        return;
    }

    if (new_name == n->val.name) {
        set_cout_RED();
        cout << "修改失败，新姓名不可与原姓名相同！" << endl;
        reset_cout_color();
        return;
    }

    if (n->nextCld) {
        set_cout_RED();
        cout << "请注意，由于" << n->val.name << "存在孩子，其所有孩子的父亲名字将一并被修改为"
             << new_name << "!" << endl << endl;
        reset_cout_color();
    }

    cout << "  修改" << n->val.name << "的姓名为" << new_name << "成功！" << endl;
    modify_single_name_to(n, new_name);
    n = n->nextCld;
    if (n)
        cout << "同时，\n";
    while (n) {
        cout << "  已将";
        set_cout_RED();
        cout << n->val.name;
        reset_cout_color();
        cout << "的父亲修改为" << new_name << "。" << endl;
        modify_single_father_to(n, new_name);
        n = n->nextBro;
    }
    cout << endl;
}

void Data::modify_single_name_to(Node *node, string n_n) {
    if (!node) {
        cout << "Test Error: modify single name error with nullptr!" << endl;
        exit(-1);
    }

    if (n_n == "None") {
        set_cout_RED();
        cout << "非法姓名：" << n_n << "，添加失败！" << endl;
        reset_cout_color();
        return;
    }

    node->val.name = n_n;
}

void Data::modify_single_father_to(Node *node, string n_n) {
    if (!node) {
        cout << "Test Error: modify single father error with nullptr!" << endl;
        exit(-1);
    }
    node->val.parent = n_n;
}

void Data::modify_birth_year(Node *n) {
    if (!n) {
        cout << "Test Error: modify birth_year error with nullptr!" << endl;
        exit(-1);
    }
    cout << "你即将修改" << n->val.name << "的出生年份，请输入修改后的年份";

    int min_birth_year = 0;
    int max_birth_year = n->val.death_year;

    if (n->val.parent != "None") {
        Node *hisFather = GetNode_byName(n->val.parent);
        min_birth_year = hisFather->val.birth_year;
        max_birth_year = min(hisFather->val.death_year, max_birth_year);
    }

    // 该人物的出生年份需要满足：
    // 1.比父亲的出生年份晚
    // 2.比父亲的死亡年份早
    // 3.比任一儿子的出生年份早

    Node *Sons = n->nextCld;

    while (Sons) {
        max_birth_year = min(max_birth_year, Sons->val.birth_year);
        Sons = Sons->nextBro;
    }

    cout << "(" << min_birth_year << "-" << max_birth_year << "): ";

    int new_birth = GetIndex(min_birth_year, max_birth_year, 1);

    if (new_birth == n->val.birth_year) {
        set_cout_RED();
        cout << "修改失败，新出生年份不可与原出生年份相同！" << endl;
        reset_cout_color();
        return;
    }

    n->val.birth_year = new_birth;
    cout << "修改" << n->val.name << "的出生年份为" << new_birth << "成功！" << endl;
}

void Data::modify_death_year(Node *n) {
    if (!n) {
        cout << "Test Error: modify death_year error with nullptr!" << endl;
        exit(-1);
    }
    cout << "你即将修改" << n->val.name << "的去世年份，请输入修改后的年份";

    int min_death_year = n->val.birth_year;

    Node *Sons = n->nextCld;
    while (Sons) {
        min_death_year = max(min_death_year, Sons->val.birth_year);
        Sons = Sons->nextBro;
    }

    cout << "(" << min_death_year << "-now): ";

    int new_death = GetIndex(min_death_year, INF_YEAR, 1);

    if (new_death == n->val.death_year) {
        set_cout_RED();
        cout << "修改失败，新去世年份不可与原去世年份相同！" << endl;
        reset_cout_color();
        return;
    }

    n->val.death_year = new_death;
    cout << "修改" << n->val.name << "的去世年份为" << new_death << "成功！" << endl;
}

void Data::modify_parent_only_when_without_BroORCld(Node *n) {
    if (!n || n->nextBro || n->nextCld) {
        cout << "Test Error: modifying single node's parent, which is illegal!" << endl;
        exit(-1);
    }
    if (n == head) {
        set_cout_RED();
        cout << "无法修改第一代人" << n->val.name << "的父亲名字！" << endl;
        reset_cout_color();
        return;
    }
    cout << "你正在修改" << n->val.name << "的父亲的名字，请输入新的父亲的姓名：";
    string new_parent;
    cin >> new_parent;
    clear_all();

    if (new_parent == n->val.parent) {
        set_cout_RED();
        cout << "修改失败，新父亲姓名不可与原父亲姓名相同！" << endl;
        reset_cout_color();
        return;
    }

    if (!this->IsMemberExist(new_parent)) {
        set_cout_RED();
        cout << "修改失败：" << new_parent << "不存在，请先添加该人物！" << endl;
        reset_cout_color();
        return;
    }

    string _tmp_name = n->val.name;
    int _tmp_birth = n->val.birth_year;
    int _tmp_death = n->val.death_year;

    Node *parent_node_to_check_age = this->GetNode_byName(new_parent);
    if (_tmp_birth < parent_node_to_check_age->val.birth_year) {
        set_cout_RED();
        cout << _tmp_name << "的出生年份早于" << parent_node_to_check_age->val.name << "的出生年份，修改失败！" << endl;
        reset_cout_color();
        return;
    }
    if (_tmp_birth > parent_node_to_check_age->val.death_year) {
        set_cout_RED();
        cout << _tmp_name << "的出生年份晚于" << parent_node_to_check_age->val.name << "的去世年份，修改失败！" << endl;
        reset_cout_color();
        return;
    }

    this->delete_node_which_without_BroORCld(n);

    this->append_auto(_tmp_name, _tmp_birth, _tmp_death, new_parent);

    cout << endl << "已成功将" << _tmp_name << "的父亲修改为" << new_parent << "！" << endl;
}

void Data::modify_pare_with_lrNode(Node *n) {
    if (!n) {
        cout << "Test Error: modifying single node's parent, which is illegal!" << endl;
        exit(-1);
    }

    if (n == head) {
        set_cout_RED();
        cout << "无法修改第一代人" << n->val.name << "的父亲名字！" << endl;
        reset_cout_color();
        return;
    }
    cout << "你正在修改" << n->val.name << "的父亲的名字，请输入新的父亲的姓名：";
    string new_parent;
    cin >> new_parent;
    clear_all();

    if (new_parent == n->val.parent) {
        set_cout_RED();
        cout << "修改失败，新父亲姓名不可与原父亲姓名相同！" << endl;
        reset_cout_color();
        return;
    }

    if (!this->IsMemberExist(new_parent)) {
        set_cout_RED();
        cout << "修改失败：" << new_parent << "不存在，请先添加该人物！" << endl;
        reset_cout_color();
        return;
    }

    string _tmp_name = n->val.name;
    int _tmp_birth = n->val.birth_year;

    Node *parent_node_to_check_age = this->GetNode_byName(new_parent);
    if (_tmp_birth < parent_node_to_check_age->val.birth_year) {
        set_cout_RED();
        cout << _tmp_name << "的出生年份早于" << parent_node_to_check_age->val.name << "的出生年份，修改失败！" << endl;
        reset_cout_color();
        return;
    }
    if (_tmp_birth > parent_node_to_check_age->val.death_year) {
        set_cout_RED();
        cout << _tmp_name << "的出生年份晚于" << parent_node_to_check_age->val.name << "的去世年份，修改失败！" << endl;
        reset_cout_color();
        return;
    }

    //以下为修改部分。

    //独立该节点
    Node *bef = this->GetNode_before_target(n->val.name);
    if (bef->nextBro == n) {
        bef->nextBro = n->nextBro;
    } else if (bef->nextCld == n) {
        bef->nextCld = n->nextBro;
    } else {
        cout << "Error in func GetNode_before_target used in modify_pare_with_lrNode" << endl;
        exit(-1);
    }

    n->nextBro = nullptr;

    n->val.parent = new_parent;

    this->AddChild_toParent(new_parent, n);

    cout << endl << "已成功将" << _tmp_name << "的父亲修改为" << new_parent << "！" << endl;
}

void Data::delete_node_which_without_BroORCld(Node *n) {
    if (!n || n->nextBro || n->nextCld) {
        cout << "Test Error: deleting single last node which is illegal!" << endl;
        exit(-1);
    }

    Node *n_parent_node = this->GetNode_before_target(n->val.name);
    if (!n_parent_node) {
        cout << "Test Error: deleting single last node which parent do not exist!" << endl;
        exit(-1);
    }
    if (n_parent_node->nextBro == n) {
        n_parent_node->nextBro = nullptr;
    } else if (n_parent_node->nextCld == n) {
        n_parent_node->nextCld = nullptr;
    } else {
        cout << "Test Error: function Data::GetNode_before_target have something wrong!" << endl;
        exit(-1);
    }
    delete n;
}

void Data::query_by_name() {
    cout << "请输入需要查询的人物姓名：";
    string q_name;
    cin >> q_name;
    clear_all();
    if (!this->IsMemberExist(q_name)) {
        set_cout_RED();
        cout << "该成员不存在，查询结束！" << endl;
        reset_cout_color();
        return;
    }
    Node *q_tmp = this->GetNode_byName(q_name);
    if (!q_tmp) {
        cout << "Test Error in func Data::query_by_name" << endl;
        exit(-1);
    }
    cout << "\n查询到信息如下：" << endl;

    this->show_List_title_without_dynasty();
    this->show_List_of_single_member(q_tmp, false);
    this->show_List_tail_without_dynasty();
}

void Data::query_by_dynasty() {
    int max_dynasty = this->get_Max_Dynasty();
    if (max_dynasty == 0) {
        cout << "Test Error: unreachable place reached with Zero dynasty!" << endl;
        exit(-1);
    }
    cout << "请输入需要查询第几代的人物(1-" << max_dynasty << ")：";
    int search_dynasty = GetIndex(1, max_dynasty, 0);
    cout << "查询到信息如下：" << endl;
    this->show_special_dynasty_byLsit(search_dynasty);
}

int Data::get_Max_Dynasty() {
    if (head == nullptr) {
        return 0;
    }
    int ans = 0;
    Queue queue;
    Node *tmp;
    queue.push(head, 1);
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        ans = max(ans, tmp->Generation_used_ONLY_in_Queue);
        while (tmp) {
            if (tmp->nextCld)
                queue.push(tmp->nextCld, tmp->Generation_used_ONLY_in_Queue + 1);

            if (tmp->nextBro)
                tmp->nextBro->Generation_used_ONLY_in_Queue = tmp->Generation_used_ONLY_in_Queue;

            tmp = tmp->nextBro;
        }
    }
    return ans;
}

void Data::show_special_dynasty_byLsit(int target) {
    this->show_List_title();

    Queue queue;
    Node *tmp;
    queue.push(head, 1);
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        while (tmp) {
            if (tmp->Generation_used_ONLY_in_Queue == target)
                this->show_List_of_single_member(tmp, true);

            if (tmp->nextCld)
                queue.push(tmp->nextCld, tmp->Generation_used_ONLY_in_Queue + 1);

            if (tmp->nextBro) {
                tmp->nextBro->Generation_used_ONLY_in_Queue = tmp->Generation_used_ONLY_in_Queue;
            }
            tmp = tmp->nextBro;
        }
    }

    this->show_List_tail();
}

void Data::query_someone_s_child() {
    cout << "请输入需要查询人物的父亲姓名：";
    string q_pare;
    cin >> q_pare;
    clear_all();

    if (!this->IsMemberExist(q_pare)) {
        set_cout_RED();
        cout << q_pare << "不存在，查询失败！" << endl;
        reset_cout_color();
        return;
    }

    Node *pare_node = this->GetNode_byName(q_pare);

    if (!pare_node->nextCld) {
        set_cout_RED();
        cout << "查询到" << q_pare << "无任何孩子！" << endl << endl;
        reset_cout_color();
        cout << "查询结束！" << endl;
        return;
    }

    cout << "查询到" << q_pare << "的所有孩子信息如下：" << endl;
    this->show_List_title_without_dynasty();
    Node *child_node = pare_node->nextCld;
    while (child_node) {
        this->show_List_of_single_member(child_node, false);
        child_node = child_node->nextBro;
    }
    this->show_List_tail_without_dynasty();
}

void Data::query_someone_s_father() {
    cout << "请输入需要查询人物的孩子姓名：";
    string q_child;
    cin >> q_child;
    clear_all();

    if (!this->IsMemberExist(q_child)) {
        set_cout_RED();
        cout << q_child << "不存在，查询失败！" << endl;
        reset_cout_color();
        return;
    }

    Node *child_node = this->GetNode_byName(q_child);

    if (child_node->val.parent == "None") {
        set_cout_RED();
        cout << "查询到" << q_child << "不存在父亲的信息！" << endl << endl;
        reset_cout_color();
        cout << "查询结束！" << endl;
        return;
    }

    cout << "查询到" << q_child << "的父亲信息如下：" << endl;

    Node *pare_node = this->GetNode_byName(child_node->val.parent);

    this->show_List_title_without_dynasty();
    this->show_List_of_single_member(pare_node, false);
    this->show_List_tail_without_dynasty();

}

void Data::query_someone_s_brother() {
    cout << "请输入需要查询人物的兄弟姓名：";
    string q_bro;
    cin >> q_bro;
    clear_all();

    if (!IsMemberExist(q_bro)) {
        set_cout_RED();
        cout << q_bro << "不存在，查询失败！" << endl;
        reset_cout_color();
        return;
    }

    Node *q_bro_node = this->GetNode_byName(q_bro);

    if (q_bro_node->val.parent == "None") {
        set_cout_RED();
        cout << "查询到" << q_bro << "无兄弟信息!" << endl << endl;
        reset_cout_color();
        cout << "查询结束！" << endl;
        return;
    }

    Node *q_pare = this->GetNode_byName(q_bro_node->val.parent);
    if (q_pare->nextCld->val.name == q_bro and !q_pare->nextCld->nextBro) {
        set_cout_RED();
        cout << "查询到" << q_bro << "为" << q_pare->val.name << "的独生子，无兄弟信息!" << endl << endl;
        reset_cout_color();
        cout << "查询结束！" << endl;
        return;
    }

    Node *q_cld = q_pare->nextCld;
    cout << "查询到" << q_bro << "的兄弟信息如下：" << endl;

    this->show_List_title_without_dynasty();
    while (q_cld) {
        if (q_cld->val.name != q_bro) {
            this->show_List_of_single_member(q_cld, false);
        }
        q_cld = q_cld->nextBro;
    }
    this->show_List_tail_without_dynasty();
}

void Data::Show() {
    cout << "┌-------------------------------------------┐" << endl;
    cout << "\t家族谱展示系统" << endl;
    cout << "   1.按图形展示" << endl;
    cout << "   2.按列表展示" << endl;
    cout << "   3.返回上一级" << endl;
    cout << "└-------------------------------------------┘" << endl;
    cout << "请输入操作序号：";

    int show_idx = GetIndex(1, 3, 0);

    system("cls");

    switch (show_idx) {
        case 1:
            this->show_byGraph();
            break;
        case 2:
            this->show_byList();
            break;
        case 3:
            break;
        default:
            cout << "Test Error: Wrong parameter in Switch-case from Show!" << endl;
            exit(-1);
    }
    if (show_idx != 3)
        system("pause");
}

void Data::EXIT() {
    cout << "┌-------------------------------------------┐" << endl;
    cout << "  即将退出系统，请确认是否保存所有的修改？" << endl;
    set_cout_GREEN();
    cout << "   1.保存修改内容，并退出" << endl;
    set_cout_RED();
    cout << "   2.舍弃所有修改，直接退出" << endl;
    reset_cout_color();
    cout << "└-------------------------------------------┘" << endl;
    cout << "请输入你的选择：";
    int handle = GetIndex(1, 2, 0);

    system("cls");
    if (handle == 1) {
        this->save_all();
        cout << "保存成功！系统已退出。" << endl;
    } else if (handle == 2) {
        cout << "修改已舍弃！系统已退出" << endl;
    }

    this->delete_memory_before_exit(head);
}

void Data::Manage() {
    cout << "┌-------------------------------------------┐" << endl;
    cout << "\t信息修改系统" << endl;
    cout << "   1.添加成员" << endl;
    cout << "   2.修改成员信息" << endl;
    cout << "   3.删除成员" << endl;
    cout << "   4.返回上一级" << endl;
    cout << "└-------------------------------------------┘" << endl;
    cout << "请输入操作序号：";

    int manage_idx = GetIndex(1, 4, 0);

    system("cls");

    switch (manage_idx) {
        case 1:
            this->add_member();
            break;
        case 2:
            this->modify();
            break;
        case 3:
            this->del_member();
            break;
        case 4:
            break;
        default:
            cout << "Test Error: Wrong parameter in Switch-case from Show!" << endl;
            exit(-1);
    }
    if (manage_idx != 4)
        system("pause");
}

void Data::delete_memory_before_exit(Node *n) {
    if (n == nullptr) {
        return;
    }
    delete_memory_before_exit(n->nextBro);
    delete_memory_before_exit(n->nextCld);
    delete n;
}

void Data::save_all() {
    fstream f;
    f.open("Genghis Khan.txt", ios::out);
    if (!f) {
        cout << "Creating file ERROR at the end of program!";
        exit(-1);
    }

    Queue queue;
    Node *tmp;
    queue.push(head);
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        while (tmp) {
            f << tmp->val.name << ' ' << tmp->val.birth_year << ' ' << tmp->val.death_year;

            if (tmp->val.parent != "None")
                f << ' ' << tmp->val.parent;

            f << '\n';

            if (tmp->nextCld)
                queue.push(tmp->nextCld);

            if (tmp->nextBro) {
                tmp->nextBro->Generation_used_ONLY_in_Queue = tmp->Generation_used_ONLY_in_Queue;
            }
            tmp = tmp->nextBro;
        }
    }
    f.close();
}

void Data::query_get_average_age() {
    cout << "请输入0至" << MAX_AGE << "中的一段年龄范围" << endl;
    cout << "请输入最小年龄：";
    int min_age = GetIndex(0, MAX_AGE, 0);
    cout << "请输入最大年龄：";
    int max_age = GetIndex(min_age, MAX_AGE, 0);
    this->cout_and_show_average_age(min_age, max_age);
}

void Data::cout_and_show_average_age(int fro, int to) {
    int cnt = 0;

    Queue queue;
    Node *tmp;
    queue.push(head);
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        while (tmp) {
            int tmp_age = tmp->val.death_year - tmp->val.birth_year;

            if (fro <= tmp_age && tmp_age <= to) {
                cnt++;
            }

            if (tmp->nextCld)
                queue.push(tmp->nextCld);

            tmp = tmp->nextBro;
        }
    }

    if (cnt == 0) {
        set_cout_RED();
        cout << "未查询到年龄段在" << fro << "至" << to << "的人员！" << endl;
        reset_cout_color();
        return;
    }

    cout << endl << "查询到年龄段在" << fro << "至" << to << "的人员" << cnt << "位，如下：" << endl;

    int sum_age = 0;

    this->show_List_head_with_age();
    Queue queue2;
    Node *tmp2;
    queue2.push(head);
    while (!queue2.IsEmpty()) {
        tmp2 = queue2.pop();
        while (tmp2) {
            int tmp_age = tmp2->val.death_year - tmp2->val.birth_year;

            if (fro <= tmp_age && tmp_age <= to) {
                this->show_List_of_single_member_with_age(tmp2);
                sum_age += tmp_age;
            }

            if (tmp2->nextCld)
                queue2.push(tmp2->nextCld);

            tmp2 = tmp2->nextBro;
        }
    }
    this->show_List_tail();

    double ave_age = (sum_age * 1.0) / cnt;

    cout << "他们的平均年龄为" << ave_age << endl << endl;
}

void Data::init() {
    fstream f;
    f.open("Genghis Khan.txt", ios::in);
    if (!f) {
        cout << "File lost!";
        exit(-1);
    }

    string line;
    string _n, _p;
    int _b, _d;

    getline(f, line);   //init the first line, which without parent.
    stringstream ss(line);

    if (ss.str().empty()) {
        f.close();
        set_cout_RED();
        cout << "请注意！当前Genghis Khan.txt文件中不存在任何成员信息！" << endl;
        cout << "请确认后进入家族管理系统！" << endl;
        reset_cout_color();
        system("pause");
        return;
    }

    ss >> _n >> _b >> _d;

    this->append_auto(_n, _b, _d, "None");

    while (getline(f, line)) {
        stringstream sss(line);
        sss >> _n >> _b >> _d >> _p;
        this->append_auto(_n, _b, _d, _p);
    }
    f.close();
}

void Data::show_byList() {
    cout << "  按列表展示如下：" << endl;
    if (head == nullptr) {
        cout << "┌----------------------------------------------------------┐" << endl;
        cout << "  无成员信息！" << endl;
        cout << "└----------------------------------------------------------┘" << endl;
        return;
    }
    this->show_List_title();
    Queue queue;
    Node *tmp;
    queue.push(head, 1);
    while (!queue.IsEmpty()) {
        tmp = queue.pop();
        while (tmp) {
            this->show_List_of_single_member(tmp, true);

            if (tmp->nextCld)
                queue.push(tmp->nextCld, tmp->Generation_used_ONLY_in_Queue + 1);

            if (tmp->nextBro) {
                tmp->nextBro->Generation_used_ONLY_in_Queue = tmp->Generation_used_ONLY_in_Queue;
            }
            tmp = tmp->nextBro;
        }
    }
    this->show_List_tail();
}

void Data::show_byGraph() {
    cout << "  按图形展示如下：" << endl;
    cout << "┌----------------------------------------------------------┐" << endl;
    if (head == nullptr) {
        cout << "  无成员信息！" << endl;
        cout << "└----------------------------------------------------------┘" << endl;
        return;
    }
    Stack stack;
    Node *tmp;
    stack.push(head, 1);
    while (!stack.IsEmpty()) {
        tmp = stack.pop();
        while (tmp) {
            cout << "  第" << tmp->Generation_used_ONLY_in_Stack << "代\t";
            int mask = stack.GetIndexExistInStack_byBitmap();

            bool isLastBro;
            if (tmp != head)
                isLastBro = this->IsLastChild(tmp->val.name, tmp->val.parent);
            else
                isLastBro = true;

            mask |= (1 << tmp->Generation_used_ONLY_in_Stack);
            while (tmp != head && mask) {
                if (mask == 1) {
                    if (isLastBro)
                        cout << "└-->";
                    else
                        cout << "├-->";
                } else {
                    if (mask & 1)
                        cout << "|";
                    else
                        cout << " ";
                }
                mask >>= 1;
                if (mask)
                    cout << "    ";
            }
            if (tmp == head) {
                cout << "    ";
                cout << "    ";
            }
            cout << tmp->val.name << endl;

            if (tmp->nextBro)
                stack.push(tmp->nextBro, tmp->Generation_used_ONLY_in_Stack);
            if (tmp->nextCld)
                tmp->nextCld->Generation_used_ONLY_in_Stack = tmp->Generation_used_ONLY_in_Stack + 1;
            tmp = tmp->nextCld;
        }
    }
    cout << "└----------------------------------------------------------┘" << endl;
}

void Data::add_member() {
    string _name;
    int _birth_year, _death_year;

    if (head == nullptr) {
        set_cout_RED();
        cout << "当前族谱中无人员存在";
        reset_cout_color();
        cout << "，请输入你需要添加的人员的姓名：";
        cin >> _name;
        cout << "请输入" << _name << "的出生年份：";
        _birth_year = GetIndex(0, INF_YEAR, 1);
        cout << "请输入" << _name << "的去世年份：";
        _death_year = GetIndex(_birth_year, INF_YEAR, 1);
        this->append_auto(_name, _birth_year, _death_year, "None");
        cout << "成员" << _name << "添加成功！" << endl;
        return;
    }
    bool is_parent_exist;
    string _pare;
    do {
        cout << "请输入你所需要添加的成员的父亲姓名：";
        cin >> _pare;
        clear_all();
        is_parent_exist = IsMemberExist(_pare);
        if (!is_parent_exist) {
            set_cout_RED();
            cout << "父亲" << _pare << "不存在，请重新输入！" << endl;
            reset_cout_color();
        }
    } while (!is_parent_exist);

    Node *parent_node = this->GetNode_byName(_pare);

    bool is_name_suitable;
    do {
        cout << "请输入该成员的名字：";
        cin >> _name;
        if (_name == _pare) {
            is_name_suitable = false;
            set_cout_RED();
            cout << "成员姓名不能与父亲姓名相同！请重新输入！" << endl;
            reset_cout_color();
        } else if (this->IsMemberExist(_name)) {
            is_name_suitable = false;
            set_cout_RED();
            cout << "该成员名已存在！请重新输入！" << endl;
            reset_cout_color();
        } else {
            is_name_suitable = true;
        }
    } while (!is_name_suitable);

    clear_all();

    cout << "请输入" << _name << "的出生年份：";
    _birth_year = GetIndex(parent_node->val.birth_year, parent_node->val.death_year, 1);
    cout << "请输入" << _name << "的去世年份：";
    _death_year = GetIndex(_birth_year, INF_YEAR, 1);

    this->append_auto(_name, _birth_year, _death_year, _pare);
    cout << "成员" << _name << "添加成功！" << endl;
}

void Data::del_member() {
    string _name;
    cout << "请输入需要删除的成员的姓名：";
    cin >> _name;
    clear_all();
    if (!this->IsMemberExist(_name)) {
        set_cout_RED();
        cout << "成员" << _name << "不存在，删除失败！" << endl;
        reset_cout_color();
        return;
    }
    Node *to_del = this->GetNode_byName(_name);

    Node *the_node_before_to_del = this->GetNode_before_target(_name);

    //由于_name一定存在，该指针为空时表示要求删除的为头结点。
    if (!the_node_before_to_del) {
        if (!to_del->nextBro && !to_del->nextCld) {
            head = nullptr;
            cout << to_del->val.name << "删除完成！" << endl;
            delete to_del;
            return;
        } else if (!to_del->nextBro) { // 没有兄弟，只有孩子。
            head = nullptr;
        } else if (!to_del->nextCld) {   // 只有兄弟，没有孩子。
            head = to_del->nextBro;
            cout << to_del->val.name << "删除完成！" << endl;
            delete to_del;
            return;
        } else {
            head = to_del->nextBro;
            to_del->nextBro = nullptr;
        }
    } else {
        //为True表示前置节点的nextBro为待删节点，False表示前置的nextCld为待删节点。
        bool bro_or_child = the_node_before_to_del->nextBro == to_del;

        // 待删除的节点无后缀节点，那么我们之间将其前一个节点置空，然后删除该节点即可。
        if (!to_del->nextBro && !to_del->nextCld) {
            if (bro_or_child)
                the_node_before_to_del->nextBro = nullptr;
            else
                the_node_before_to_del->nextCld = nullptr;
            cout << to_del->val.name << "删除完成！" << endl;
            delete to_del;
            return;
        } else if (!to_del->nextBro) {  // 没有兄弟，只有孩子
            if (bro_or_child)
                the_node_before_to_del->nextBro = nullptr;
            else
                the_node_before_to_del->nextCld = nullptr;
        } else if (!to_del->nextCld) {    // 只有兄弟，没有孩子。
            if (bro_or_child)
                the_node_before_to_del->nextBro = to_del->nextBro;
            else
                the_node_before_to_del->nextCld = to_del->nextBro;
            to_del->nextBro = nullptr;
            cout << to_del->val.name << "删除完成！" << endl;
            delete to_del;
            return;
        } else {
            if (bro_or_child)
                the_node_before_to_del->nextBro = to_del->nextBro;
            else
                the_node_before_to_del->nextCld = to_del->nextBro;
            to_del->nextBro = nullptr;
        }
    }

    //在此时还未return，则表示to_del仍有孩子需要一并删除。
    //实际上此时删除操作已完成，to_del为一个独立的head。此时to_del的nextBro为空，nextCld有节点。
    set_cout_RED();
    cout << endl << "请注意：该成员有孩子。在删除后，如下所示的所有成员将被一并删除！" << endl;
    reset_cout_color();

    string name_backup = to_del->val.name;

    set_cout_RED();
    this->del_nodes_after_the_node_given(to_del, true);
    reset_cout_color();
    cout << endl << name_backup << "及其孩子的信息删除完成！" << endl << endl;
}

void Data::modify() {
    string _name;
    cout << "请输入需要修改的成员的姓名：";
    cin >> _name;
    clear_all();

    if (!this->IsMemberExist(_name)) {
        set_cout_RED();
        cout << "成员" << _name << "不存在，操作失败！" << endl;
        reset_cout_color();
        return;
    }
    Node *to_modify = this->GetNode_byName(_name);

    cout << "┌-------------------------------------------┐" << endl;
    cout << "\t修改成员信息选择" << endl;
    cout << "   1.姓名" << endl;
    cout << "   2.出生年份" << endl;
    cout << "   3.去世年份" << endl;
//    if (CanModifyParent)
    cout << "   4.父亲姓名" << endl;
    cout << "└-------------------------------------------┘" << endl;
    cout << "请输入需要修改的内容：";

    int operation_idx = GetIndex(1, 4, 0);

    system("cls");

    switch (operation_idx) {
        case 1:
            this->modify_name(to_modify);
            break;
        case 2:
            this->modify_birth_year(to_modify);
            break;
        case 3:
            this->modify_death_year(to_modify);
            break;
        case 4:
            if (!to_modify->nextBro && !to_modify->nextCld)
                this->modify_parent_only_when_without_BroORCld(to_modify);
            else
                this->modify_pare_with_lrNode(to_modify);
            break;
        default:
            cout << "Test Error: Wrong parameter in Switch-case from modify!" << endl;
            exit(-1);
    }
}

void Data::query() {
    if (!this->head) {
        set_cout_RED();
        cout << "族谱中无成员，无法查询！" << endl << endl;
        reset_cout_color();
        system("pause");
        return;
    }
    cout << "┌-------------------------------------------┐" << endl;
    cout << "\t查询系统" << endl;
    cout << "   1.按姓名查找特定人物" << endl;
    cout << "   2.查询某代的所有人物" << endl;
    cout << "   3.查询特定人物的所有孩子" << endl;
    cout << "   4.查询特定人物的父亲" << endl;
    cout << "   5.查询特定人物的所有兄弟" << endl;
    cout << "   6.查询特定年龄段的平均年龄" << endl;
    cout << "   7.返回上一级" << endl;
    cout << "└-------------------------------------------┘" << endl;
    cout << "请输入所需要的查找方式：";

    int operation_idx = GetIndex(1, 7, 0);

    system("cls");

    switch (operation_idx) {
        case 1:
            this->query_by_name();
            break;
        case 2:
            this->query_by_dynasty();
            break;
        case 3:
            this->query_someone_s_child();
            break;
        case 4:
            this->query_someone_s_father();
            break;
        case 5:
            this->query_someone_s_brother();
            break;
        case 6:
            this->query_get_average_age();
            break;
        case 7:
            break;
        default:
            cout << "Test Error: Wrong parameter in Switch-case from query!" << endl;
            exit(-1);
    }
    if (operation_idx != 7)
        system("pause");
}

void Data::func() {
    this->init();

    bool RUN = true;
    while (RUN) {
        system("cls");
        cout << "┌-------------------------------------------┐" << endl;
        cout << "\t家族谱管理系统" << endl;
        cout << "   1.族谱展示" << endl;
        cout << "   2.查询系统" << endl;
        cout << "   3.信息修改系统" << endl;
        cout << "   4.退出" << endl;
        cout << "└-------------------------------------------┘" << endl;
        cout << "请输入操作序号：";

        int func_idx = GetIndex(1, 4, 0);

        system("cls");

        switch (func_idx) {
            case 1:
                this->Show();
                break;
            case 2:
                this->query();
                break;
            case 3:
                this->Manage();
                break;
            case 4:
                this->EXIT();
                RUN = false;
                break;
            default:
                cout << "Test Error: Wrong parameter in Switch-case from func!" << endl;
                exit(-1);
        }
    }
}