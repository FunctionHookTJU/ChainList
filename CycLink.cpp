#include "CycLink.h"

CycLink::CycLink(){
    head = nullptr;
    tail = nullptr;
    len = 0;
}

CycLink::~CycLink(){
    if (head == nullptr) return;
    
    node* p = head;
    while (p->next != head) {
        node* toDelete = p;
        p = p->next;
        delete toDelete;
    }
    delete p;  // 删除最后一个节点
}

int CycLink::length() const {
    return len;
}

int CycLink::getData(const int& location) const {
    if (location < 0 || location >= len || head == nullptr) {
        return -1;
    }
    
    node* p = head;
    int count = 0;
    while (count < location && p != nullptr) {
        p = p->next;
        count++;
    }
    return (p != nullptr) ? p->value : -1;
}

void CycLink::insert(const int& data, const int& location) {
    if (location < 0 || location > len) {
        return;
    }
    
    node* newNode = new node();
    newNode->value = data;
    newNode->next = nullptr;
    
    // 空链表：创建第一个节点
    if (head == nullptr) {
        newNode->next = newNode;  // 指向自己
        head = newNode;
        tail = newNode;
    }
    // 在头部插入
    else if (location == 0) {
        newNode->next = head;
        head = newNode;
        tail->next = head;  // 更新尾节点的 next
    }
    // 在尾部插入
    else if (location == len) {
        newNode->next = tail->next;  // 指向原来的 head
        tail->next = newNode;
        tail = newNode;
    }
    // 在中间插入
    else {
        node* p = head;
        int count = 0;
        while (count < location - 1) {
            p = p->next;
            count++;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
    
    len++;
}

bool CycLink::remove(const int& location) {
    if (location < 0 || location >= len || head == nullptr) {
        return false;
    }
    
    node* toDelete = nullptr;
    
    // 仅有一个节点
    if (head == tail) {
        toDelete = head;
        delete toDelete;
        head = nullptr;
        tail = nullptr;
        len--;
        return true;
    }
    
    // 删除头节点
    if (location == 0) {
        toDelete = head;
        head = head->next;
        tail->next = head;  // 更新尾节点的 next
        delete toDelete;
    }
    // 删除尾节点
    else if (location == len - 1) {
        node* p = head;
        while (p->next != tail) {
            p = p->next;
        }
        toDelete = tail;
        tail = p;
        tail->next = head;
        delete toDelete;
    }
    // 删除中间节点
    else {
        node* p = head;
        int count = 0;
        while (count < location - 1) {
            p = p->next;
            count++;
        }
        toDelete = p->next;
        p->next = toDelete->next;
        delete toDelete;
    }
    
    len--;
    return true;
}

void CycLink::converse() {
    if (len == 0 || len == 1) {
        return;
    }
    
    node* prev = tail;  // 循环链表从 tail 开始
    node* curr = head;
    node* next = nullptr;
    
    for (int i = 0; i < len; i++) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    head = prev;
    tail = curr;
}

void CycLink::append(const CycLink& append_list) {
    // 如果要追加的链表为空，直接返回
    if (append_list.head == nullptr) {
        return;
    }
    
    // 当前链表为空
    if (head == nullptr) {
        node* p_append = append_list.head;
        for (int i = 0; i < append_list.len; i++) {
            node* new_node = new node();
            new_node->value = p_append->value;
            
            if (head == nullptr) {
                new_node->next = new_node;
                head = new_node;
                tail = new_node;
            } else {
                new_node->next = head;
                tail->next = new_node;
                tail = new_node;
            }
            p_append = p_append->next;
            len++;
        }
        return;
    }
    
    // 当前链表非空：从 tail 开始追加
    node* p_append = append_list.head;
    for (int i = 0; i < append_list.len; i++) {
        node* new_node = new node();
        new_node->value = p_append->value;
        new_node->next = head;  // 新节点指向 head（循环）
        tail->next = new_node;
        tail = new_node;
        p_append = p_append->next;
        len++;
    }
}