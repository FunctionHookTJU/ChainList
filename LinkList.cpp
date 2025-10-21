/*******************************************************************************
* FileName:         LinkList.cpp
* Author:           Your_Name
* Student Number:   3022244xxx
* Date:             2023/02/26 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #2
*                   作业在这个文件中完成，需要补全LinkList类的实现，
*                   写明必要的注释
*******************************************************************************/

#include "LinkList.h"

LinkList::LinkList(){
    head = nullptr;
    len = 0;
}

LinkList::~LinkList(){
}

int LinkList::length() const{
    
    return len;
}

int LinkList::getData(const int& location) const{
    if(location<0||location >=len||head==nullptr){
        return -1;
    }
    node *p=head;
    int count=0;
    while(count<location&&p!=nullptr){
        p=p->next;
        count++;
    }
    return p->value;
}

void LinkList::insert(const int& data, const int& location){
    
    if(location < 0 || location > len) {
        return; 
    }

    node* newNode = new node();
    newNode->value = data;
    newNode->next = nullptr;
    
    if (head == nullptr || location == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        node* p = head;
        int count = 0;
        while (count < location - 1 && p->next != nullptr) {
            p = p->next;
            count++;
        }
        
        newNode->next = p->next;
        p->next = newNode;
    }
    
    len++;
}

bool LinkList::remove(const int& location){
    if(location<0||location >=len||head==nullptr){
        return false;
    }

    node *toDelete=nullptr;
    int count=0;
    if(location==0){
        toDelete=head;
        head=head->next;
    }
    else{
        node*p=head;
        int count=0;
        while(count<location-1&&p->next!=nullptr){
            p=p->next;
            count++;
        }
        if(p->next==nullptr)return false;
        toDelete=p->next;
        p->next=toDelete->next;
    }
    delete toDelete;

    len--;
    return true;
}

void LinkList::converse(){
    
    if(len==0||len==1){
        return;
    }

    int *num=new int[len];
    node *p=head;
    
    for(int i=0;i<len;i++){
        num[i]=p->value;
        p=p->next;
    }
    for(int i=0; i<len/2; i++){
        int temp = num[i];
        num[i] = num[len-1-i];
        num[len-1-i] = temp;
    }
    p=head;
    for(int i=0;i<len;i++){
        p->value=num[i];
        p=p->next;
    }
    delete[] num;
}

void LinkList::append(const LinkList& append_list){
    if (append_list.head == nullptr) {
        return; 
    }
    
    if (head == nullptr) {
        node *p_append = append_list.head;
        // 创建新的头节点
        head = new node();
        head->value = p_append->value;
        head->next = nullptr;
        len++;
        
        node *p_current = head;
        p_append = p_append->next;
        
        // 复制剩余节点
        while (p_append != nullptr) {
            node *new_node = new node();
            new_node->value = p_append->value;
            new_node->next = nullptr;
            p_current->next = new_node;
            p_current = new_node;
            p_append = p_append->next;
            len++;
        }
        return;
    }
    
    node *p_current = head;
    while (p_current->next != nullptr) {
        p_current = p_current->next;
    }
    
    node *p_append = append_list.head;
    while (p_append != nullptr) {
        node *new_node = new node();
        new_node->value = p_append->value;
        new_node->next = nullptr;
        
        p_current->next = new_node;
        p_current = new_node;
        
        p_append = p_append->next;
        
        // 更新长度计数
        len++;
    }
}