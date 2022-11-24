//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
bool command_check(string command){
    for(int i = 0; i < NUM_KEYWORDS; i++){
        if(command == keyWordsList[i]) return true;
        
    }
    return false;
}
bool name_check(string name){
    for(int i = 0; i < NUM_TYPES; i++){
        if(name == shapeTypesList[i] || name == "pool"){
            cout << "error: invalid name" << endl;
            return false;
        }
    }
    return true;
}
bool type_check(string type){
    for(int i = 0; i < NUM_TYPES; i++){
        if(type == shapeTypesList[i]){
            return true;
        }
    }
    cout << "Invalid type" << endl;
    return false;
}
void create_shape(stringstream& rest, GroupList* gList, GroupNode* poolGroup){
    string name;
    string type;
    int x_loc;
    int x_size;
    int y_loc;
    int y_size;

    rest >> name;
    if(name_check(name) == false) return;
    
    rest >> type;
    if(type_check(type) == false) return;

    rest >> x_loc;
    rest >> y_loc;
    rest >> x_size;
    rest >> y_size;

    
    ShapeNode* temp = poolGroup->getShapeList()->getHead();
    
    ShapeNode* pre = nullptr;
    GroupNode* ck = gList->getHead();
    while(ck != nullptr){
        if(ck->getName() == name || ck->getShapeList()->find(name) != nullptr){
            cout << "error: name " << name <<" exists" << endl;
            return;
        }
        else{
            ck = ck->getNext();
        }
    }

    while(temp != nullptr && temp->getShape() != nullptr){
        if(temp->getShape()->getName() == name){
            cout << "error: name " << name <<" exists" << endl;
            return;
        }
        pre = temp;
        temp = temp->getNext();
    }
    Shape* newshape = new Shape(name, type, x_loc, y_loc, x_size, y_size);
    ShapeNode* newnode = new ShapeNode();
    if(pre == nullptr){
        poolGroup->getShapeList()->insert(newnode);
        poolGroup->getShapeList()->getHead()->setShape(newshape);
        poolGroup->getShapeList()->getHead()->getShape()->draw();
    }
    else if(pre != nullptr){
        pre->setNext(newnode);
        pre->getNext()->setShape(newshape);
        pre->getNext()->getShape()->draw();
        pre->getNext()->setNext(temp);
    }
    
 
}
void create_group(stringstream& rest, GroupList* gList, GroupNode* poolGroup){
    string group_name;
    rest >> group_name;
    if(name_check(group_name) == false) return;
    
    GroupNode* temp = gList->getHead();
    
    
    while(temp != nullptr){
        if(temp->getName() == group_name || temp->getShapeList()->find(group_name) != nullptr){
            cout << "error: name " << group_name << " exists" << endl;
            return;
        }
        temp = temp->getNext();
    }
    GroupNode* newgroup = new GroupNode(group_name);
    gList->insert(newgroup);
    cout << group_name << ": group " << endl;

}
void move(stringstream& rest, GroupList* gList, GroupNode* poolGroup){
    string name;
    string group;
    bool find = false;
    bool move = false;
    rest >> name;
    rest >> group;
    if(name_check(name) == false || name_check(group) == false) return;
    
    GroupNode* gp = gList->getHead();
    ShapeNode* pre = nullptr;
    ShapeNode* sn = gp->getShapeList()->getHead();
    while(gp != nullptr){

        //cout << gp->getName() << " group name" << endl;

        
        sn = gp->getShapeList()->getHead();
        // if(sn == nullptr) cout << "sn == null " << endl;

        // if(sn != nullptr && sn->getShape() != nullptr) cout << sn->getShape()->getName() << "  1111" << endl;
        
        pre = nullptr;
        while(sn != nullptr){
            
            if(sn->getShape() == nullptr){
                pre = sn;
                sn = sn->getNext();
            }
            else if(sn->getShape()->getName() == name){
                find = true;
                break;
            }
            else if(sn->getShape()->getName() != name){
                pre = sn;
                sn = sn->getNext();
            }
        }
        if(find == true){
            break;
        } 
        if(sn == nullptr){
            gp = gp->getNext();
        }
    }
    if(find == false){
        cout << "error: shape " << name << " not found " << endl;
        return;
    }

    GroupNode* tg = gList->getHead();
    while(tg != nullptr){
        if(tg->getName() == group){
            break;
        }
        else{
            tg = tg->getNext();
        }
    }
    if(tg == nullptr){
        cout << "error: group " << group << " not found " << endl;
        return;
    }
    if(pre == nullptr && sn != nullptr && find){
        gp->getShapeList()->setHead(gp->getShapeList()->getHead()->getNext());
        sn->setNext(nullptr);
    }
    else if(pre != nullptr && sn != nullptr && find){
        pre->setNext(sn->getNext());
        sn->setNext(nullptr);
    }
    if(find && tg != nullptr){
        tg->getShapeList()->insert(sn);
        cout << "moved " << name << " to " << group << endl;
    }

}

void del(stringstream& rest, GroupList* gList, GroupNode* poolGroup){
    string target;
    rest >> target;
    if(name_check(target) == false) return;
    GroupNode* mv = gList->getHead();
    GroupNode* pre = nullptr;
    bool findg = false;
    bool findn = false;
    while(mv != nullptr){
        if(mv->getName() == target){
            findg = true;
            break;
        }
        else if(mv->getName() != target){
            pre = mv;
            mv = mv->getNext();
        }
    }
    if(findg){
        pre->setNext(mv->getNext());
        mv->setNext(nullptr);
        cout << target << ": deleted" << endl;
        poolGroup->getShapeList()->insert(mv->getShapeList()->getHead());
       
        mv-> getShapeList() -> setHead(nullptr);
        delete mv;
    }
    if(findg == false){
        GroupNode* hd = gList->getHead();
        ShapeNode* sp = nullptr;
        ShapeNode* pre2 = nullptr;
        while(hd != nullptr){
            pre2 = nullptr;
            sp = hd->getShapeList()->getHead();
            while(sp != nullptr){
                if(sp->getShape() != nullptr && sp->getShape()->getName() == target){
                    findn = true;
                    break;
                }
                else{
                    pre2 = sp;
                    sp = sp->getNext();
                    
                }
            }
            if(findn == true){
                break;
            }
            else if(sp == nullptr){
                hd = hd->getNext();
            }
        }
        if(findn){
            if(pre2 == nullptr && sp != nullptr){
                hd->getShapeList()->setHead(hd->getShapeList()->getHead()->getNext());
                delete sp;
                cout << target << ": deleted" << endl;
            }
            if(pre2 != nullptr && sp != nullptr){
                pre2->setNext(sp->getNext());
                delete sp;
                cout << target << ": deleted" << endl;
            }
        }
    }
    if(findg == false && findn == false){
        cout << "error: shape " << target << " not found " << endl;
    }
}

void draw(){
    cout << "drawing:" << endl;
    GroupNode* group = gList->getHead();
    ShapeNode* shape = group->getShapeList()->getHead();
    while(group != nullptr){
        cout << group->getName() << ": " << endl;
        while(shape != nullptr && shape->getShape() != nullptr){
            shape->getShape()->draw();
            shape = shape->getNext();
        }
        group = group->getNext();
        if(group != nullptr){
            shape = group->getShapeList()->getHead();
        }
    }   
}
void end(){
   delete gList;
}


int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]); //设置pool
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if(command_check(command) == false){
            cout << "invalid command" << endl;
        }
        else if(command == "shape") create_shape(lineStream, gList, poolGroup);
        else if(command == "draw") draw();
        else if(command == "group") create_group(lineStream, gList, poolGroup);
        else if(command == "move") move(lineStream, gList, poolGroup);
        else if(command == "delete") del(lineStream, gList, poolGroup);
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    end();
    
    return 0;
}

