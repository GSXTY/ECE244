//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below
#include "ShapeList.h"

ShapeList::ShapeList(){
    head = nullptr;
}

ShapeList::~ShapeList(){
    ShapeNode* temp = head;
    while(head != nullptr){
        temp = head;
        head = head->getNext();
        delete temp;
        
    }
    
}

ShapeNode* ShapeList::getHead() const{
    return head;
}

void ShapeList::setHead(ShapeNode* ptr){
    head = ptr;
}

ShapeNode* ShapeList::find(string name) const{
    ShapeNode* temp = head;
    if(temp == nullptr || temp->getShape() == nullptr) return nullptr;
    while(temp != nullptr){ 
        if(temp->getShape()->getName() == name){
            return temp;
        }
        temp = temp->getNext();
    }
    return nullptr;
}

void ShapeList::insert(ShapeNode* s){
    ShapeNode* temp = head;
    ShapeNode* pre = nullptr;

    while(temp != nullptr && temp->getShape() != nullptr){
        pre = temp;
        temp = temp->getNext();
        
        
    }
    
    if(pre == nullptr){
        temp = s;
        head = temp;
    }
    else if(pre != nullptr){
        pre->setNext(s);
        //s->setNext(temp);
    }
   
}

ShapeNode* ShapeList::remove(string name){ ////still have issue
    return head;
}

void ShapeList::print() const{
    ShapeNode* temp = head;
    while(temp != nullptr){
        temp->print();
        temp = temp->getNext();
    } 
    //not solve
}