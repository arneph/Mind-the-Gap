//
//  Name.h
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

class Name : public Gap {
private:
    GGender gender;
public:
    Name();
    ~Name();
    
    string getName() const;
    
    GGender getGender() const;
    void setGender(GGender gender);
    
    string getFullDescription() const;
    
    XMLElement * getXMLElement() const;
    void setXMLElement(XMLElement * element);
};
