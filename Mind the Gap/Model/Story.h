//
//  Story.h
//  Mind the Gap
//
//  Created by A Philipeit on 07/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>

#include "LinkedList.h"
#include "XML.h"

#include "Gap.h"
#include "Number.h"
#include "Phrase.h"
#include "Name.h"
#include "Noun.h"
#include "Verb.h"
#include "Adjective.h"

using namespace std;

class Story{
private:
    string name;
    
    LinkedList<Gap *> * gaps;
    string text;
public:
    Story();
    ~Story();
    
    string getName() const;
    void setName(string name);
    
    LinkedList<Gap *> * getGaps();
    
    string getText() const;
    void setText(string text);
    
    string getFilledText() const;
    
    XMLElement * getXMLElement() const;
    void setXMLElement(XMLElement * element);
};
