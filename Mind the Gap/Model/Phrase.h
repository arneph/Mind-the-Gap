//
//  Phrase.h
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
    PhraseTypeQuote,
    PhraseTypeAdvice
}PhraseType;

class Phrase : public Gap {
private:
    PhraseType type;
public:
    Phrase();
    ~Phrase();
    
    string getName() const;
    
    PhraseType getType() const;
    void setType(PhraseType type);
    
    string getFullDescription() const;
    
    XMLElement * getXMLElement() const;
    void setXMLElement(XMLElement * element);
};
