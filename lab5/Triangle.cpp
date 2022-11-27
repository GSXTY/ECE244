//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

Triangle::Triangle(string n, float xcent, float ycent, float x1p, float y1p, float x2p, float y2p, float x3p, float y3p):Shape(n, xcent, ycent){
    x1 = x1p;
    y1 = y1p;
    x2 = x2p;
    y2 = y2p;
    x3 = x3p;
    y3 = y3p;
}

Triangle::~Triangle(){

}

float Triangle::getX1() const{
    return x1;
}

float Triangle::getY1() const{
    return y1;
}

float Triangle::getX2() const{
    return x2;
}

float Triangle::getY2() const{
    return y2;
}

float Triangle::getX3() const{
    return x3;
}

float Triangle::getY3() const{
    return y3;
}

void Triangle::setX1(float x1p){
    x1 = x1p;
}

void Triangle::setY1(float y1p){
    y1 = y1p;
}

void Triangle::setX2(float x2p){
    x2 = x2p;
}

void Triangle::setY2(float y2p){
    y2 = y2p;
}

void Triangle::setX3(float x3p){
    x3 = x3p;
}

void Triangle::setY3(float y3p){
    y3 = y3p;
}




void Triangle::draw() const{
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << computeArea()
         << endl;
}

float Triangle::computeArea() const{
    return abs((((x1 * (y2 - y3))+ (x2 * (y3 - y1)) + (x3 * (y1 - y2))) * 0.5));
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}
