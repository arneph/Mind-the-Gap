//
//  XML.h
//  Mind the Gap
//
//  Created by A Philipeit on 07/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <regex>

#include "LinkedList.h"

using namespace std;

class XMLVariable{
private:
    string name;
    string value;
public:
    XMLVariable();
    ~XMLVariable();
    
    string getName() const;
    void setName(string name);
    
    string getValue() const;
    void setValue(string vaue);
};

class XMLElement{
private:
    string name;
    int number;
    
    string contents; //The string between the opening and closing bracket
    LinkedList<XMLElement *> * subElements; //A list of sub elements between the opening and closing bracket
    LinkedList<XMLVariable *> * variables; //A list of variables defined in the opening bracket
public:
    XMLElement();
    ~XMLElement();
    
    string getName() const;
    void setName(string name);
    
    int getNumber() const;
    void setNumber(int number);
    
    string getContents() const;
    void setContents(string contents);
    
    LinkedList<XMLElement *> * getSubElements();
    LinkedList<XMLVariable *> * getVariables();
    
    string getString() const;
    void setString(string string);
};

class XMLTree{
private:
    LinkedList<XMLElement *> * rootElements;
public:
    XMLTree();
    ~XMLTree();
    
    LinkedList<XMLElement *> * getRootElements();
    
    string getString() const;
    void setString(string string);
};
