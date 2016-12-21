//
//  Noun.h
//  Mind the Gap
//
//  Created by A Philipeit on 12/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>

#include "Gap.h"

#include "Grammar.h"

using namespace std;

typedef enum{
    NounTypeObject,
    NounTypePerson
}NounType;

class Noun : public Gap {
private:
    GNumber number;
    NounType type;
public:
    Noun();
    ~Noun();
    
    string getName() const;
    
    GNumber getNumber() const;
    void setNumber(GNumber number);

    NounType getType() const;
    void setType(NounType type);
    
    string getFullDescription() const;
    
    XMLElement * getXMLElement() const;
    void setXMLElement(XMLElement * element);
};
