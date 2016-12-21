//
//  Adjective.h
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
    AdjectiveComprarisonPositive,
    AdjectiveComprarisonComparative,
    AdjectiveComprarisonSuperlative
}AdjectiveComprarison;

class Adjective : public Gap {
private:
    AdjectiveComprarison comparison;
public:
    Adjective();
    ~Adjective();
    
    string getName() const;
    
    AdjectiveComprarison getComparison() const;
    void setComprarison(AdjectiveComprarison comparison);
    
    string getFullDescription() const;
    
    XMLElement * getXMLElement() const;
    void setXMLElement(XMLElement * element);
};
