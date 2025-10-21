#include "DuLink.h"

DuLink::DuLink(){
    head=nullptr;
    len=0;
}
DuLink::~DuLink(){

}
int DuLink::length() const {
    return len;
}
int DuLink::getData(const int& location) const{
    if(location < 0 || location > len) return -1;
    node*p=head;
    for(int i = 0; i < location; i++){
        
    }
}
void DuLink::append(const DuLink& append_list){

}
