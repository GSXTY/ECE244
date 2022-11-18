//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;


// The number of shapes in the database, to be incremented 
int shapeCount = 0;
int maxtime = 0; //用来indicate是否为第一次call maxshapes function


// The value of the argument to the maxShapes command
int max_shapes = 0;

int p = 0; ///previouse max size

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
bool size_check(int& shapeCount, int &max_shapes){ /////确保size不超出最大
    if(shapeCount >= max_shapes) return false;
    return true;
}
bool type_check(string type){                 ////确保type是valid
    for(int i = 0; i < NUM_TYPES; i++){
        if(type == shapeTypesList[i]){
            return true;
        }
        
    }
    return false;
}
bool name_check(string name){              ///////不和type重名
    for(int i = 0; i < NUM_TYPES; i++){
        if(name == shapeTypesList[i]){
            return false;
        }
    }
    for(int i = 0; i < NUM_KEYWORDS; i++){
        if(name == keyWordsList[i]){
            return false; 
        }
    }
    return true;
}
bool name_rep(string name){                  ///////没有重复过的
    for(int i = 0; i < shapeCount; i++){
        if (shapesArray[i] == nullptr) continue;
        if(shapesArray[i]->getName() == name){
            return false;
        }
    }
    return true;
}

bool command_check(string command){         //////是valid的command
    for(int i = 0; i < NUM_KEYWORDS; i++){
        if(command == keyWordsList[i]){
            return true;
        }
    }
    return false;
}
bool val_check(int x_p, int x_s, int y_p, int y_s){  //////不为负数
    if((x_p < 0) || (x_s < 0) || (y_p < 0) || (y_s < 0)){
        return false;
    }
    return true;
}
bool cir_check(int x_s, int y_s, string type){ ////正确的角度
    if((type == "circle") && (x_s != y_s)){
        cout << "Error: invalid value" << endl;
        return false;
    }
    return true;
}
bool name_notf(string name){//////搜索是否存在
    for(int i = 0; i < shapeCount; i++){
        if (shapesArray[i] == nullptr) continue;
        if((shapesArray[i]->getName() == name) && (name != "all")){
            return true;
        } 
    }
    return false;
    
}


void max_size(stringstream& rest, int& shapeCount){
    if(rest.fail()) return; //空白指令
    string name;
    string type;
    int x_pos;
    int x_size;
    int y_pos;
    int y_size;
    shapeCount = 0;
    max_shapes = 0;
    rest >> max_shapes;

    if(maxtime == 0){
        shapesArray = new Shape* [max_shapes];
        for(int i = 0; i < max_shapes; i++){         //如果是第一次叫，declare该arr type 的 ptr， assign element 为 nullptr
            shapesArray[i] = nullptr;  
        }

    }
    if(maxtime != 0){
        for(int i = 0; i < p; i++){
            delete shapesArray[i];      //如果是后面再 call maxsize
        }
        delete []shapesArray;
        
        shapesArray = new Shape* [max_shapes];
        for(int i = 0; i < max_shapes; i++){
            shapesArray[i] = nullptr;  
        }
        
    }
    cout << "New database: max shapes is " << max_shapes << endl;
    
    maxtime = 1;        //后面就不是第一次call 了
    p = max_shapes;  // 存储当前的 maxsize
}

void create(stringstream& rest, int& shapeCount){
    string name;
    string type;
    int x_pos;
    int x_size;
    int y_pos;
    int y_size;
    string tom;

    
    rest >> name;
    if(rest.fail() && rest.eof()){ ///空白指令
        cout << "Error: too few arguments" << endl; 
        return;
    } 
    if(name_check(name) == false){
        cout << "Error: invalid shape name" << endl; //不能作为name的
        return;
    } 
    if(name_rep(name) == false){
        cout << "Error: shape " << name << " exists" << endl; //出现过的
        return;
    }

    rest >> type;
    if(rest.fail() && rest.eof()){
        cout << "Error: too few arguments" << endl;  //什么都没有
        return;
    } 

    if(type_check(type) == false){
        cout << "Error: invalid shape type" << endl; //错误的type
        return;
    }

    // if(!rest.fail() && !rest.eof()){
    //     cout << "6Error: invalid argument" << endl; //错误的type
    //     return;
    // }

    //此时为 create name type 

    rest >> x_pos;
    if(rest.fail() && rest.eof()){
        cout << "Error: too few arguments" << endl; //什么都没有，比如name type ()
        return;
    } 

    if(!rest.fail() && (rest.peek() != ' ' && !rest.eof())){
        cout << "Error: invalid argument" << endl; //有一个数字，但不为int 如 name type 1.2
        return;
    }

    ///not solved yet
    if(rest.fail() && !rest.eof()){
        cout << "Error: invalid argument" << endl; //有个char 比如 type name a
        return;
    }
    


    //此时得到正确类型 name type int

    rest >> y_pos;
    if(rest.fail() && rest.eof()){
        cout << "Error: too few arguments" << endl; //什么都没有，比如name type int （）
        return;
    } 

    if(!rest.fail() && (rest.peek() != ' ' && !rest.eof())){
        cout << "Error: invalid argument" << endl; //有一个数字，但不为int 如 name type int 1.2
        return;
    }
    

    ///not solved yet
    if(rest.fail() && !rest.eof()){
        cout << "Error: invalid argument" << endl; //有个char 比如 type name int a
        return;
    }
    

    //此时得到正确类型 name type int int

    rest >> x_size;
    if(rest.fail() &&rest.eof()){
        cout << "Error: too few arguments" << endl; //什么都没有，比如name type int int ()
        return;
    } 


    if(!rest.fail() && (rest.peek() != ' ' && !rest.eof())){
        cout << "Error: invalid argument" << endl; //有一个数字，但不为int 如 name type int int 1.2
        return;
    }
   
    ///not solved yet
    if(rest.fail() && !rest.eof()){
        cout << "Error: invalid argument" << endl; //有个char 比如 type name int int a
        return;
    }

    //此时得到正确类型 name type int int int

    rest >> y_size;

    if(rest.fail() && rest.eof()){
        cout << "Error: too few arguments" << endl; //什么都没有，比如name type int int int ()
        return;
    } 

    if(!rest.fail() && (rest.peek() != ' ' && !rest.eof())){
        cout << "Error: invalid argument" << endl; //有一个数字，但不为int 如 name type int int int 1.2
        return;
    }
  
    ///not solved yet
    if(rest.fail() && !rest.eof()){
        cout << "Error: invalid argument" << endl; //有个char 比如 type name int int int a
        return;
    }
    if(cir_check(x_size, y_size, type) == false) return;

    //此时得到 name type int int int int

    if(val_check(x_pos, x_size, y_pos, y_size) == false){
        cout << "Error: invalid value" << endl; // int 小于 0
        return;
    }

    //此时得到正确类型 name type int int int int
    
    rest >> tom;
    if(!rest.fail()){
        cout << "Error: too many arguments" << endl; //还有其他command
        return;
    }
    if(size_check(shapeCount, max_shapes) == false){
        cout << "Error: shape array is full" << endl;
        return;
    }
    
    if(max_shapes == 0){
        cout << "Error: shape array is full" << endl;
        return;
    }

    if(rest.fail() && max_shapes != 0){
        shapesArray[shapeCount] = new Shape(name, type, x_pos, x_size, y_pos, y_size);
        cout <<"Created " << shapesArray[shapeCount]->getName() << ": " << shapesArray[shapeCount]->getType();
        cout << " " << shapesArray[shapeCount]->getXlocation() << " " << shapesArray[shapeCount]->getYlocation();
        cout << " " << shapesArray[shapeCount]->getXsize() << " " << shapesArray[shapeCount]->getYsize() << endl;

        shapeCount += 1;
        return;
        //创造一个 shape obj
    }
    
}


void move(stringstream& rest, int& shapeCount){
    string name;
    int x_pos;
    int y_pos;
    string tom;

    rest >> name;

    if(name_check(name) == false){
        cout << "Error: invalid shape name" << endl;
        return;
    }

    if(rest.fail()){
        cout << "Error: too few arguments" << endl;  //只有一个move command
        return;
    } 
    if(name_notf(name) == false){
        cout << "Error: shape " << name << " not found" << endl; //找不到对应的shape
        return;
    }

    rest >> x_pos;
    if(rest.fail() && rest.eof()){
        cout << "Error: too few arguments" << endl; //没有坐标
        return;
    } 
    if(!rest.fail() && (rest.peek() != ' ' && !rest.eof())){
        cout << "Error: invalid argument" << endl; //坐标不为int
        return;
    }
    if(x_pos < 0){
        cout << "Error: invalid value" << endl; //错误坐标
        return;
    }

    ///not solved yet
    if(rest.fail() && !rest.eof()){
        cout << "Error: invalid argument" << endl; //坐标为char
        return;
    }

    //此时为 move name int

    rest >> y_pos;
    if(rest.fail() && rest.eof()){
        cout << "Error: too few arguments" << endl; //没有坐标
        return;
    } 
    if(!rest.fail() && (rest.peek() != ' ' && !rest.eof())){
        cout << "Error: invalid argument" << endl; //坐标不为int
        return;
    }

    ///not solved yet
    if(rest.fail() && !rest.eof()){
        cout << "Error: invalid argument" << endl; //坐标为char
    }
    if(y_pos < 0){
        cout << "Error: invalid value" << endl; //错误坐标
        return;
    }
    //此时为 move name int int
    rest >> tom;
    if(!rest.fail()){
        cout << "Error: too many arguments" << endl; //还有其他command
        return;
    }

    if(rest.fail()){
        for(int i = 0; i < shapeCount; i++){
            if (shapesArray[i] == nullptr) continue;
            if(shapesArray[i]->getName() == name){ //找到对应name的element
                shapesArray[i]->setXlocation(x_pos);
                shapesArray[i]->setYlocation(y_pos);
                cout << "Moved " << name << " to " << x_pos << " " << y_pos << endl;
                return; ////更改坐标
            }
        }
    }
    
    

}


void rotate(stringstream& rest, int& shapeCount){
    string name;
    int angle;
    string tom;
    rest >> name;
    if(name_check(name) == false){
        cout << "Error: invalid shape name" << endl;
        return;
    }

    if(rest.fail()){
        cout << "Error: too few arguments" << endl;  //只有一个rotate command
        return;
    } 
    

    //此时为 rotate name

    rest >> angle;
    if(!rest.fail() && (rest.peek() != ' ' && !rest.eof())){
        cout << "Error: invalid argument" << endl; //angle不为int
        return;
    }

    ///not solved yet
    if(rest.fail() && !rest.eof()){
        cout << "Error: invalid argument" << endl; //angle为char
        return;
    }
    if(name_notf(name) == false){
        cout << "Error: shape " << name << " not found" << endl; //找不到对应的shape
        return;
    }

    if(angle < 0 || angle > 360){
        cout << "Error: invalid value" << endl; //错误角度
        return;
    }

    if(rest.fail() && rest.eof()){
        cout << "Error: too few arguments" << endl;  //没有提供angle
        return;
    } 


    //此时为 rotate name angle
    rest >> tom;
    if(!rest.fail()){
        cout << "Error: too many arguments" << endl; //还有其他command
        return;
    }

    if(rest.fail()){
        for(int i = 0; i < shapeCount; i++){
            if (shapesArray[i] == nullptr) continue;
            if(shapesArray[i]->getName() == name){ //找到对应name的element
                shapesArray[i]->setRotate(angle);
                
                cout << "Rotated " << name << " by " << angle <<" degrees" << endl;
                return; ////更改angle
            }
        }
    }
    
    

}

void draw(stringstream& rest, int& shapeCount){
    string name;
    string tom;

    rest >> name;
    
    if(name_check(name) == false && name != "all"){
        cout << "Error: invalid shape name" << endl;
        return;
    }

    if(rest.fail()){
        cout << "Error: too few arguments" << endl;  //只有一个draw command
        return;
    } 
    if(name_notf(name) == false && name != "all"){
        cout << "Error: shape " << name << " not found" << endl; //找不到对应的shape
        return;
    }
    //此时为 draw name

    rest >> tom;
    if(!rest.fail()){
        cout << "Error: too many arguments" << endl; //还有其他command
        return;
    }

    if(rest.fail()){
        if(name != "all"){ //某一个shape
            for(int i = 0; i < shapeCount; i++){
                if (shapesArray[i] == nullptr) continue;
                if(shapesArray[i]->getName() == name){
                    cout << "Drew" << " ";
                    shapesArray[i]->draw();
                    return;
                }
            }
        }
        if(name == "all"){  //所有shape
            cout << "Drew all shapes" << endl;
            for(int i = 0; i < shapeCount; i++){
                if(shapesArray[i] != nullptr){
                    //cout << "cannnot" << i << endl;
                    shapesArray[i]->draw();                  
                }
                
            }
            return;
        }
    }
    return;
}

void Delete(stringstream& rest, int& shapeCount){
    string name;
    string newname;
    string type;
    int x_pos;
    int x_size;
    int y_pos;
    int y_size;
    string tom;
    rest >> name;
    if(rest.fail()){
        cout << "Error: too few arguments" << endl;  //只有一个delete command
        return;
    } 
    if(name_notf(name) == false && name != "all"){
        cout << "Error: shape " << name << " not found" << endl; //找不到对应的shape
        return;
    }

    rest >> tom;
    if(!rest.fail()){
        cout << "Error: too many arguments" << endl; //还有其他command
        return;
    }

    //此时为 delete name
    if(rest.fail()){
        if(name != "all"){ //某一个shape
            for(int i = 0; i < shapeCount; i++){
                if (shapesArray[i] == nullptr) continue;
                if(shapesArray[i]->getName() == name){
                    delete shapesArray[i];
                    
                    shapesArray[i] = nullptr;
                    cout << "Deleted shape " << name << endl; //设为空的
                    return;
                }
            }
        }
        if(name == "all"){  //所有shape
            cout << "Deleted: all shapes " << endl;
            for(int i = 0; i < max_shapes; i++){
                delete shapesArray[i];
                shapesArray[i] = nullptr;     
            }
            return;
        }
    }
    else if(!rest.eof()){
        cout << "Error: too many arguments" << endl; //还有其他command
        return;
    }
    return;

}


void end_program(int& max_shapes){
    for(int i = 0; i < max_shapes; i++){
        delete shapesArray[i];
    }
    delete []shapesArray;
}



int main() {

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
      
            if(command == "maxShapes") max_size(lineStream, shapeCount);
            
            if(command == "create") create(lineStream, shapeCount);
            
            if(command == "move") move(lineStream, shapeCount);
            
            if(command == "rotate") rotate(lineStream, shapeCount);

            if(command == "draw") draw(lineStream, shapeCount);
                
            if(command == "delete") Delete(lineStream, shapeCount);
            
            if(command_check(command) == false) cout << "Error: invalid command" << endl;

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    end_program(max_shapes);
    return 0;
}

