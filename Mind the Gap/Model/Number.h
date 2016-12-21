//
//  Number.h
//  Mind the Gap
//
//  Created by A Philipeit on 11/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>

#include "Gap.h"

using namespace std;

typedef enum{
    NumberTypeInteger,
    NumberTypeDouble
}NumberType;

class Number : public Gap {
private:
    NumberType type;
    
    bool minimumDefined;
    bool minimumInclusive;
    double minimum;
    
    bool maximumDefined;
    bool maximumInclusive;
    double maximum;
public:
    Number();
    ~Number();
    
    string getName() const;
    
    NumberType getType() const;
    void setType(NumberType type);
    
    bool isMinimumDefined() const;
    void setMinimumDefined(bool minimumDefined);
    
    bool isMinimumInclusive() const;
    void setMinimumInclusive(bool minimumInclusive);
    
    double getMinimum() const;
    void setMinimum(double minimum);
    
    bool isMaximumDefined() const;
    void setMaximumDefined(bool maximumDefined);
    
    bool isMaximumInclusive() const;
    void setMaximumInclusive(bool maximumInclusive);
    
    double getMaximum() const;
    void setMaximum(double maximum);
    
    string getRange() const;
    void setRange(string range);
    
    string getFullDescription() const;
    
    //Overridden to ensure value is number and in range
    string getValue() const;
    void setValue(string value);
    void setValue(double value);
    
    XMLElement * getXMLElement() const;
    void setXMLElement(XMLElement * element);
};
