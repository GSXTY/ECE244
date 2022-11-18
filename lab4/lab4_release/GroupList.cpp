//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
#include "GroupList.h"

GroupList::GroupList(){
    head = nullptr;
}

GroupList::~GroupList(){
    GroupNode* temp = head;
    while(head != nullptr){
        temp = head;
        head = head->getNext();
        
        delete temp;
    }
    
    
}

GroupNode* GroupList::getHead() const{
    return head;
}

void GroupList::setHead(GroupNode* ptr){
    head = ptr;
}

void GroupList::insert(GroupNode* s){
    GroupNode* temp = head;
    GroupNode* pre = nullptr;
    while(temp != nullptr){
        pre = temp;
        temp = temp->getNext();
    }
    if(pre == nullptr){
        head = s;
    }
    else if(pre != nullptr){
        pre->setNext(s);
        //s->setNext(temp);
    }

}

GroupNode* GroupList::remove(string name){

   return head;
   
    //problem
}

void GroupList::print() const{
    GroupNode* temp = head;
    if(temp == nullptr){
        cout << "head is null" << endl;
    }
    while(temp != nullptr){
        temp->print();
        temp = temp->getNext();
    }
}