//
//  Verb.h
//  Mind the Gap
//
//  Created by A Philipeit on 12/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>

#include "Gap.h"

using namespace std;

typedef enum{
    VerbFormInfinitive,
    VerbFormProgressive
}VerbForm;

class Verb : public Gap {
private:
    VerbForm form;
public:
    Verb();
    ~Verb();
    
    string getName() const;
    
    VerbForm getForm() const;
    void setForm(VerbForm form);
    
    string getFullDescription() const;
    
    XMLElement * getXMLElement() const;
    void setXMLElement(XMLElement * element);
};
