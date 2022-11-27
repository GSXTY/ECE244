//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.
#include "Shape.h"

class Triangle : public Shape {
private:
    float x1;                  // The width of the rec
    float y1;
    float x2;                  // The width of the rec
    float y2;
    float x3;                  // The width of the rec
    float y3;

public:
    // Constructor
    Triangle (string n, float xcent, float ycent, float x1p, float y1p, float x2p, float y2p, float x3p, float y3p);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessor
    float getX1() const;       // Returns the radius of the circle
    float getY1() const;
    float getX2() const;       // Returns the radius of the circle
    float getY2() const;
    float getX3() const;       // Returns the radius of the circle
    float getY3() const;

    // Mutator
    void setX1(float x1p);       // Sets the radius of the circle
    void setY1(float y1p);
    void setX2(float x2p);       // Sets the radius of the circle
    void setY2(float y2p);
    void setX3(float x3p);       // Sets the radius of the circle
    void setY3(float y3p);
    
    // Utility methods
    virtual void draw() const;     // Draws thye circle; for the assignment it
                                   // prints the information of the circle
    
    virtual float computeArea() const;   // Computes the area of the circle
    
    virtual Shape* clone() const;  // Clones the object
};




#endif /* Triangle_h */


