#pragma once

#include "data.h"

void Data::append_auto(const string &_n, int _b, int _d, const string &_p) {
    if (_n == "None") {
        set_cout_RED();
        cout << "�Ƿ�������" << _n << "�����ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    //��������
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
        cout << "�Ƿ�������" << n_nd->val.name << "�����ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    if (n_nd->val.name == n_nd->val.parent) {
        set_cout_RED();
        cout << "�Լ������ֲ����븸�׵�������ͬ�����ʧ�ܡ�" << endl;
        reset_cout_color();
        delete n_nd;
        return;
    }

    if (this->IsMemberExist(n_nd->val.name)) {
        set_cout_RED();
        cout << "����" << n_nd->val.name << "�Ѵ��ڣ����ʧ�ܣ�" << endl;
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

    // �Լ����ֵ�����С��һ��
    if (par->nextCld->val.birth_year > n_nd->val.birth_year) {
        n_nd->nextBro = par->nextCld;
        par->nextCld = n_nd;
        return;
    }

    // ���ҵ�һ�����Լ��������ֵܡ�
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
    cout << "��------��---------------��----------------��-----------------��----------------��" << endl;
    cout << "   ��\t"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << endl;
    cout << " ------|---------------|----------------|-----------------|----------------" << endl;
}

void Data::show_List_title_without_dynasty() {
    cout << "��---------------��----------------��-----------------��----------------��" << endl;
    cout << "  "
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << endl;
    cout << " ---------------|----------------|-----------------|----------------" << endl;
}

void Data::show_List_tail() {
    cout << "��------��---------------��----------------��-----------------��----------------��" << endl;
}

void Data::show_List_tail_without_dynasty() {
    cout << "��---------------��----------------��-----------------��----------------��" << endl;
}

void Data::show_List_of_single_member(Node *nd, bool showGeneration) {
    if (nd == nullptr) {
        cout << "Test Warning: showing member of a nullptr!" << endl;
        return;
    }
    cout << " ";
    if (showGeneration)
        cout << "��" << nd->Generation_used_ONLY_in_Queue << "��\t";
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
    cout << "��------��---------------��----------------��-----------------��----------------��" << endl;
    cout << "  ����\t"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
         << left << setw(GAP) << "����"
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
    cout << "�㼴���޸�" << n->val.name << "���������������޸ĺ�����֣�";
    string new_name;
    cin >> new_name;
    clear_all();

    if (new_name == "None") {
        set_cout_RED();
        cout << "�Ƿ�������" << new_name << "���޸�ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    if (new_name == n->val.name) {
        set_cout_RED();
        cout << "�޸�ʧ�ܣ�������������ԭ������ͬ��" << endl;
        reset_cout_color();
        return;
    }

    if (n->nextCld) {
        set_cout_RED();
        cout << "��ע�⣬����" << n->val.name << "���ں��ӣ������к��ӵĸ������ֽ�һ�����޸�Ϊ"
             << new_name << "!" << endl << endl;
        reset_cout_color();
    }

    cout << "  �޸�" << n->val.name << "������Ϊ" << new_name << "�ɹ���" << endl;
    modify_single_name_to(n, new_name);
    n = n->nextCld;
    if (n)
        cout << "ͬʱ��\n";
    while (n) {
        cout << "  �ѽ�";
        set_cout_RED();
        cout << n->val.name;
        reset_cout_color();
        cout << "�ĸ����޸�Ϊ" << new_name << "��" << endl;
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
        cout << "�Ƿ�������" << n_n << "�����ʧ�ܣ�" << endl;
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
    cout << "�㼴���޸�" << n->val.name << "�ĳ�����ݣ��������޸ĺ�����";

    int min_birth_year = 0;
    int max_birth_year = n->val.death_year;

    if (n->val.parent != "None") {
        Node *hisFather = GetNode_byName(n->val.parent);
        min_birth_year = hisFather->val.birth_year;
        max_birth_year = min(hisFather->val.death_year, max_birth_year);
    }

    // ������ĳ��������Ҫ���㣺
    // 1.�ȸ��׵ĳ��������
    // 2.�ȸ��׵����������
    // 3.����һ���ӵĳ��������

    Node *Sons = n->nextCld;

    while (Sons) {
        max_birth_year = min(max_birth_year, Sons->val.birth_year);
        Sons = Sons->nextBro;
    }

    cout << "(" << min_birth_year << "-" << max_birth_year << "): ";

    int new_birth = GetIndex(min_birth_year, max_birth_year, 1);

    if (new_birth == n->val.birth_year) {
        set_cout_RED();
        cout << "�޸�ʧ�ܣ��³�����ݲ�����ԭ���������ͬ��" << endl;
        reset_cout_color();
        return;
    }

    n->val.birth_year = new_birth;
    cout << "�޸�" << n->val.name << "�ĳ������Ϊ" << new_birth << "�ɹ���" << endl;
}

void Data::modify_death_year(Node *n) {
    if (!n) {
        cout << "Test Error: modify death_year error with nullptr!" << endl;
        exit(-1);
    }
    cout << "�㼴���޸�" << n->val.name << "��ȥ����ݣ��������޸ĺ�����";

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
        cout << "�޸�ʧ�ܣ���ȥ����ݲ�����ԭȥ�������ͬ��" << endl;
        reset_cout_color();
        return;
    }

    n->val.death_year = new_death;
    cout << "�޸�" << n->val.name << "��ȥ�����Ϊ" << new_death << "�ɹ���" << endl;
}

void Data::modify_parent_only_when_without_BroORCld(Node *n) {
    if (!n || n->nextBro || n->nextCld) {
        cout << "Test Error: modifying single node's parent, which is illegal!" << endl;
        exit(-1);
    }
    if (n == head) {
        set_cout_RED();
        cout << "�޷��޸ĵ�һ����" << n->val.name << "�ĸ������֣�" << endl;
        reset_cout_color();
        return;
    }
    cout << "�������޸�" << n->val.name << "�ĸ��׵����֣��������µĸ��׵�������";
    string new_parent;
    cin >> new_parent;
    clear_all();

    if (new_parent == n->val.parent) {
        set_cout_RED();
        cout << "�޸�ʧ�ܣ��¸�������������ԭ����������ͬ��" << endl;
        reset_cout_color();
        return;
    }

    if (!this->IsMemberExist(new_parent)) {
        set_cout_RED();
        cout << "�޸�ʧ�ܣ�" << new_parent << "�����ڣ�������Ӹ����" << endl;
        reset_cout_color();
        return;
    }

    string _tmp_name = n->val.name;
    int _tmp_birth = n->val.birth_year;
    int _tmp_death = n->val.death_year;

    Node *parent_node_to_check_age = this->GetNode_byName(new_parent);
    if (_tmp_birth < parent_node_to_check_age->val.birth_year) {
        set_cout_RED();
        cout << _tmp_name << "�ĳ����������" << parent_node_to_check_age->val.name << "�ĳ�����ݣ��޸�ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }
    if (_tmp_birth > parent_node_to_check_age->val.death_year) {
        set_cout_RED();
        cout << _tmp_name << "�ĳ����������" << parent_node_to_check_age->val.name << "��ȥ����ݣ��޸�ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    this->delete_node_which_without_BroORCld(n);

    this->append_auto(_tmp_name, _tmp_birth, _tmp_death, new_parent);

    cout << endl << "�ѳɹ���" << _tmp_name << "�ĸ����޸�Ϊ" << new_parent << "��" << endl;
}

void Data::modify_pare_with_lrNode(Node *n) {
    if (!n) {
        cout << "Test Error: modifying single node's parent, which is illegal!" << endl;
        exit(-1);
    }

    if (n == head) {
        set_cout_RED();
        cout << "�޷��޸ĵ�һ����" << n->val.name << "�ĸ������֣�" << endl;
        reset_cout_color();
        return;
    }
    cout << "�������޸�" << n->val.name << "�ĸ��׵����֣��������µĸ��׵�������";
    string new_parent;
    cin >> new_parent;
    clear_all();

    if (new_parent == n->val.parent) {
        set_cout_RED();
        cout << "�޸�ʧ�ܣ��¸�������������ԭ����������ͬ��" << endl;
        reset_cout_color();
        return;
    }

    if (!this->IsMemberExist(new_parent)) {
        set_cout_RED();
        cout << "�޸�ʧ�ܣ�" << new_parent << "�����ڣ�������Ӹ����" << endl;
        reset_cout_color();
        return;
    }

    string _tmp_name = n->val.name;
    int _tmp_birth = n->val.birth_year;

    Node *parent_node_to_check_age = this->GetNode_byName(new_parent);
    if (_tmp_birth < parent_node_to_check_age->val.birth_year) {
        set_cout_RED();
        cout << _tmp_name << "�ĳ����������" << parent_node_to_check_age->val.name << "�ĳ�����ݣ��޸�ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }
    if (_tmp_birth > parent_node_to_check_age->val.death_year) {
        set_cout_RED();
        cout << _tmp_name << "�ĳ����������" << parent_node_to_check_age->val.name << "��ȥ����ݣ��޸�ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    //����Ϊ�޸Ĳ��֡�

    //�����ýڵ�
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

    cout << endl << "�ѳɹ���" << _tmp_name << "�ĸ����޸�Ϊ" << new_parent << "��" << endl;
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
    cout << "��������Ҫ��ѯ������������";
    string q_name;
    cin >> q_name;
    clear_all();
    if (!this->IsMemberExist(q_name)) {
        set_cout_RED();
        cout << "�ó�Ա�����ڣ���ѯ������" << endl;
        reset_cout_color();
        return;
    }
    Node *q_tmp = this->GetNode_byName(q_name);
    if (!q_tmp) {
        cout << "Test Error in func Data::query_by_name" << endl;
        exit(-1);
    }
    cout << "\n��ѯ����Ϣ���£�" << endl;

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
    cout << "��������Ҫ��ѯ�ڼ���������(1-" << max_dynasty << ")��";
    int search_dynasty = GetIndex(1, max_dynasty, 0);
    cout << "��ѯ����Ϣ���£�" << endl;
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
    cout << "��������Ҫ��ѯ����ĸ���������";
    string q_pare;
    cin >> q_pare;
    clear_all();

    if (!this->IsMemberExist(q_pare)) {
        set_cout_RED();
        cout << q_pare << "�����ڣ���ѯʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    Node *pare_node = this->GetNode_byName(q_pare);

    if (!pare_node->nextCld) {
        set_cout_RED();
        cout << "��ѯ��" << q_pare << "���κκ��ӣ�" << endl << endl;
        reset_cout_color();
        cout << "��ѯ������" << endl;
        return;
    }

    cout << "��ѯ��" << q_pare << "�����к�����Ϣ���£�" << endl;
    this->show_List_title_without_dynasty();
    Node *child_node = pare_node->nextCld;
    while (child_node) {
        this->show_List_of_single_member(child_node, false);
        child_node = child_node->nextBro;
    }
    this->show_List_tail_without_dynasty();
}

void Data::query_someone_s_father() {
    cout << "��������Ҫ��ѯ����ĺ���������";
    string q_child;
    cin >> q_child;
    clear_all();

    if (!this->IsMemberExist(q_child)) {
        set_cout_RED();
        cout << q_child << "�����ڣ���ѯʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    Node *child_node = this->GetNode_byName(q_child);

    if (child_node->val.parent == "None") {
        set_cout_RED();
        cout << "��ѯ��" << q_child << "�����ڸ��׵���Ϣ��" << endl << endl;
        reset_cout_color();
        cout << "��ѯ������" << endl;
        return;
    }

    cout << "��ѯ��" << q_child << "�ĸ�����Ϣ���£�" << endl;

    Node *pare_node = this->GetNode_byName(child_node->val.parent);

    this->show_List_title_without_dynasty();
    this->show_List_of_single_member(pare_node, false);
    this->show_List_tail_without_dynasty();

}

void Data::query_someone_s_brother() {
    cout << "��������Ҫ��ѯ������ֵ�������";
    string q_bro;
    cin >> q_bro;
    clear_all();

    if (!IsMemberExist(q_bro)) {
        set_cout_RED();
        cout << q_bro << "�����ڣ���ѯʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }

    Node *q_bro_node = this->GetNode_byName(q_bro);

    if (q_bro_node->val.parent == "None") {
        set_cout_RED();
        cout << "��ѯ��" << q_bro << "���ֵ���Ϣ!" << endl << endl;
        reset_cout_color();
        cout << "��ѯ������" << endl;
        return;
    }

    Node *q_pare = this->GetNode_byName(q_bro_node->val.parent);
    if (q_pare->nextCld->val.name == q_bro and !q_pare->nextCld->nextBro) {
        set_cout_RED();
        cout << "��ѯ��" << q_bro << "Ϊ" << q_pare->val.name << "�Ķ����ӣ����ֵ���Ϣ!" << endl << endl;
        reset_cout_color();
        cout << "��ѯ������" << endl;
        return;
    }

    Node *q_cld = q_pare->nextCld;
    cout << "��ѯ��" << q_bro << "���ֵ���Ϣ���£�" << endl;

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
    cout << "��-------------------------------------------��" << endl;
    cout << "\t������չʾϵͳ" << endl;
    cout << "   1.��ͼ��չʾ" << endl;
    cout << "   2.���б�չʾ" << endl;
    cout << "   3.������һ��" << endl;
    cout << "��-------------------------------------------��" << endl;
    cout << "�����������ţ�";

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
    cout << "��-------------------------------------------��" << endl;
    cout << "  �����˳�ϵͳ����ȷ���Ƿ񱣴����е��޸ģ�" << endl;
    set_cout_GREEN();
    cout << "   1.�����޸����ݣ����˳�" << endl;
    set_cout_RED();
    cout << "   2.���������޸ģ�ֱ���˳�" << endl;
    reset_cout_color();
    cout << "��-------------------------------------------��" << endl;
    cout << "���������ѡ��";
    int handle = GetIndex(1, 2, 0);

    system("cls");
    if (handle == 1) {
        this->save_all();
        cout << "����ɹ���ϵͳ���˳���" << endl;
    } else if (handle == 2) {
        cout << "�޸���������ϵͳ���˳�" << endl;
    }

    this->delete_memory_before_exit(head);
}

void Data::Manage() {
    cout << "��-------------------------------------------��" << endl;
    cout << "\t��Ϣ�޸�ϵͳ" << endl;
    cout << "   1.��ӳ�Ա" << endl;
    cout << "   2.�޸ĳ�Ա��Ϣ" << endl;
    cout << "   3.ɾ����Ա" << endl;
    cout << "   4.������һ��" << endl;
    cout << "��-------------------------------------------��" << endl;
    cout << "�����������ţ�";

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
    cout << "������0��" << MAX_AGE << "�е�һ�����䷶Χ" << endl;
    cout << "��������С���䣺";
    int min_age = GetIndex(0, MAX_AGE, 0);
    cout << "������������䣺";
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
        cout << "δ��ѯ���������" << fro << "��" << to << "����Ա��" << endl;
        reset_cout_color();
        return;
    }

    cout << endl << "��ѯ���������" << fro << "��" << to << "����Ա" << cnt << "λ�����£�" << endl;

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

    cout << "���ǵ�ƽ������Ϊ" << ave_age << endl << endl;
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
        cout << "��ע�⣡��ǰGenghis Khan.txt�ļ��в������κγ�Ա��Ϣ��" << endl;
        cout << "��ȷ�Ϻ����������ϵͳ��" << endl;
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
    cout << "  ���б�չʾ���£�" << endl;
    if (head == nullptr) {
        cout << "��----------------------------------------------------------��" << endl;
        cout << "  �޳�Ա��Ϣ��" << endl;
        cout << "��----------------------------------------------------------��" << endl;
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
    cout << "  ��ͼ��չʾ���£�" << endl;
    cout << "��----------------------------------------------------------��" << endl;
    if (head == nullptr) {
        cout << "  �޳�Ա��Ϣ��" << endl;
        cout << "��----------------------------------------------------------��" << endl;
        return;
    }
    Stack stack;
    Node *tmp;
    stack.push(head, 1);
    while (!stack.IsEmpty()) {
        tmp = stack.pop();
        while (tmp) {
            cout << "  ��" << tmp->Generation_used_ONLY_in_Stack << "��\t";
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
                        cout << "��-->";
                    else
                        cout << "��-->";
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
    cout << "��----------------------------------------------------------��" << endl;
}

void Data::add_member() {
    string _name;
    int _birth_year, _death_year;

    if (head == nullptr) {
        set_cout_RED();
        cout << "��ǰ����������Ա����";
        reset_cout_color();
        cout << "������������Ҫ��ӵ���Ա��������";
        cin >> _name;
        cout << "������" << _name << "�ĳ�����ݣ�";
        _birth_year = GetIndex(0, INF_YEAR, 1);
        cout << "������" << _name << "��ȥ����ݣ�";
        _death_year = GetIndex(_birth_year, INF_YEAR, 1);
        this->append_auto(_name, _birth_year, _death_year, "None");
        cout << "��Ա" << _name << "��ӳɹ���" << endl;
        return;
    }
    bool is_parent_exist;
    string _pare;
    do {
        cout << "������������Ҫ��ӵĳ�Ա�ĸ���������";
        cin >> _pare;
        clear_all();
        is_parent_exist = IsMemberExist(_pare);
        if (!is_parent_exist) {
            set_cout_RED();
            cout << "����" << _pare << "�����ڣ����������룡" << endl;
            reset_cout_color();
        }
    } while (!is_parent_exist);

    Node *parent_node = this->GetNode_byName(_pare);

    bool is_name_suitable;
    do {
        cout << "������ó�Ա�����֣�";
        cin >> _name;
        if (_name == _pare) {
            is_name_suitable = false;
            set_cout_RED();
            cout << "��Ա���������븸��������ͬ�����������룡" << endl;
            reset_cout_color();
        } else if (this->IsMemberExist(_name)) {
            is_name_suitable = false;
            set_cout_RED();
            cout << "�ó�Ա���Ѵ��ڣ����������룡" << endl;
            reset_cout_color();
        } else {
            is_name_suitable = true;
        }
    } while (!is_name_suitable);

    clear_all();

    cout << "������" << _name << "�ĳ�����ݣ�";
    _birth_year = GetIndex(parent_node->val.birth_year, parent_node->val.death_year, 1);
    cout << "������" << _name << "��ȥ����ݣ�";
    _death_year = GetIndex(_birth_year, INF_YEAR, 1);

    this->append_auto(_name, _birth_year, _death_year, _pare);
    cout << "��Ա" << _name << "��ӳɹ���" << endl;
}

void Data::del_member() {
    string _name;
    cout << "��������Ҫɾ���ĳ�Ա��������";
    cin >> _name;
    clear_all();
    if (!this->IsMemberExist(_name)) {
        set_cout_RED();
        cout << "��Ա" << _name << "�����ڣ�ɾ��ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }
    Node *to_del = this->GetNode_byName(_name);

    Node *the_node_before_to_del = this->GetNode_before_target(_name);

    //����_nameһ�����ڣ���ָ��Ϊ��ʱ��ʾҪ��ɾ����Ϊͷ��㡣
    if (!the_node_before_to_del) {
        if (!to_del->nextBro && !to_del->nextCld) {
            head = nullptr;
            cout << to_del->val.name << "ɾ����ɣ�" << endl;
            delete to_del;
            return;
        } else if (!to_del->nextBro) { // û���ֵܣ�ֻ�к��ӡ�
            head = nullptr;
        } else if (!to_del->nextCld) {   // ֻ���ֵܣ�û�к��ӡ�
            head = to_del->nextBro;
            cout << to_del->val.name << "ɾ����ɣ�" << endl;
            delete to_del;
            return;
        } else {
            head = to_del->nextBro;
            to_del->nextBro = nullptr;
        }
    } else {
        //ΪTrue��ʾǰ�ýڵ��nextBroΪ��ɾ�ڵ㣬False��ʾǰ�õ�nextCldΪ��ɾ�ڵ㡣
        bool bro_or_child = the_node_before_to_del->nextBro == to_del;

        // ��ɾ���Ľڵ��޺�׺�ڵ㣬��ô����֮�佫��ǰһ���ڵ��ÿգ�Ȼ��ɾ���ýڵ㼴�ɡ�
        if (!to_del->nextBro && !to_del->nextCld) {
            if (bro_or_child)
                the_node_before_to_del->nextBro = nullptr;
            else
                the_node_before_to_del->nextCld = nullptr;
            cout << to_del->val.name << "ɾ����ɣ�" << endl;
            delete to_del;
            return;
        } else if (!to_del->nextBro) {  // û���ֵܣ�ֻ�к���
            if (bro_or_child)
                the_node_before_to_del->nextBro = nullptr;
            else
                the_node_before_to_del->nextCld = nullptr;
        } else if (!to_del->nextCld) {    // ֻ���ֵܣ�û�к��ӡ�
            if (bro_or_child)
                the_node_before_to_del->nextBro = to_del->nextBro;
            else
                the_node_before_to_del->nextCld = to_del->nextBro;
            to_del->nextBro = nullptr;
            cout << to_del->val.name << "ɾ����ɣ�" << endl;
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

    //�ڴ�ʱ��δreturn�����ʾto_del���к�����Ҫһ��ɾ����
    //ʵ���ϴ�ʱɾ����������ɣ�to_delΪһ��������head����ʱto_del��nextBroΪ�գ�nextCld�нڵ㡣
    set_cout_RED();
    cout << endl << "��ע�⣺�ó�Ա�к��ӡ���ɾ����������ʾ�����г�Ա����һ��ɾ����" << endl;
    reset_cout_color();

    string name_backup = to_del->val.name;

    set_cout_RED();
    this->del_nodes_after_the_node_given(to_del, true);
    reset_cout_color();
    cout << endl << name_backup << "���亢�ӵ���Ϣɾ����ɣ�" << endl << endl;
}

void Data::modify() {
    string _name;
    cout << "��������Ҫ�޸ĵĳ�Ա��������";
    cin >> _name;
    clear_all();

    if (!this->IsMemberExist(_name)) {
        set_cout_RED();
        cout << "��Ա" << _name << "�����ڣ�����ʧ�ܣ�" << endl;
        reset_cout_color();
        return;
    }
    Node *to_modify = this->GetNode_byName(_name);

    cout << "��-------------------------------------------��" << endl;
    cout << "\t�޸ĳ�Ա��Ϣѡ��" << endl;
    cout << "   1.����" << endl;
    cout << "   2.�������" << endl;
    cout << "   3.ȥ�����" << endl;
//    if (CanModifyParent)
    cout << "   4.��������" << endl;
    cout << "��-------------------------------------------��" << endl;
    cout << "��������Ҫ�޸ĵ����ݣ�";

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
        cout << "�������޳�Ա���޷���ѯ��" << endl << endl;
        reset_cout_color();
        system("pause");
        return;
    }
    cout << "��-------------------------------------------��" << endl;
    cout << "\t��ѯϵͳ" << endl;
    cout << "   1.�����������ض�����" << endl;
    cout << "   2.��ѯĳ������������" << endl;
    cout << "   3.��ѯ�ض���������к���" << endl;
    cout << "   4.��ѯ�ض�����ĸ���" << endl;
    cout << "   5.��ѯ�ض�����������ֵ�" << endl;
    cout << "   6.��ѯ�ض�����ε�ƽ������" << endl;
    cout << "   7.������һ��" << endl;
    cout << "��-------------------------------------------��" << endl;
    cout << "����������Ҫ�Ĳ��ҷ�ʽ��";

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
        cout << "��-------------------------------------------��" << endl;
        cout << "\t�����׹���ϵͳ" << endl;
        cout << "   1.����չʾ" << endl;
        cout << "   2.��ѯϵͳ" << endl;
        cout << "   3.��Ϣ�޸�ϵͳ" << endl;
        cout << "   4.�˳�" << endl;
        cout << "��-------------------------------------------��" << endl;
        cout << "�����������ţ�";

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