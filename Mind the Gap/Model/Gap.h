//
//  Gap.h
//  Mind the Gap
//
//  Created by A Philipeit on 08/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>

#include "LinkedList.h"
#include "XML.h"

using namespace std;

class Gap{
private:
    int number;
    string description;
    
    string value;
public:
    Gap();
    ~Gap();
    
    virtual string getName() const;
    
    int getNumber() const;
    void setNumber(int number);
    
    string getPlaceholderName() const;
    
    string getDescription() const;
    void setDescription(string description);
    
    virtual string getFullDescription() const;
    
    virtual string getValue() const;
    virtual void setValue(string value);
    
    virtual XMLElement * getXMLElement() const;
    virtual void setXMLElement(XMLElement * element);
};
