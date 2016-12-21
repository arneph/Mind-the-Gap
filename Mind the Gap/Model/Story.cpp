//
//  Story.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 07/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Story.h"

void find_and_replace(string& source, string const& find, string const& replace) {
    for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;) {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

Story::Story() {
    name = "";
    
    gaps = new LinkedList<Gap *>;
    text = "";
}

Story::~Story() {
    delete gaps;
}

string Story::getName() const {
    return name;
}

void Story::setName(string n) {
    name = n;
}

LinkedList<Gap *> * Story::getGaps() {
    return gaps;
}

string Story::getText() const {
    return text;
}

void Story::setText(string t) {
    text = t;
}

string Story::getFilledText() const {
    string filledText = string(text);
    
    for (int i = 0; i < gaps->count(); i++) {
        Gap * gap = gaps->elementAtIndex(i);
        
        find_and_replace(filledText,
                         "[" + gap->getPlaceholderName() + "]",
                         gap->getValue());
    }
    
    return filledText;
}

XMLElement * Story::getXMLElement() const {
    XMLElement * storyElement = new XMLElement();
    
    storyElement->setName("story");
    storyElement->setNumber(0);
    
    XMLElement * gapsElement = new XMLElement();
    
    gapsElement->setName("gaps");
    gapsElement->setNumber(0);
    
    for (int i = 0; i < gaps->count(); i++) {
        Gap * gap = gaps->elementAtIndex(i);
        
        XMLElement * gapElement = gap->getXMLElement();
        
        gapsElement->getSubElements()->addElement(gapElement);
    }
    
    XMLElement * textElement = new XMLElement();
    
    textElement->setName("text");
    textElement->setNumber(0);
    textElement->setContents(getText());
    
    storyElement->getSubElements()->addElement(gapsElement);
    storyElement->getSubElements()->addElement(textElement);
    
    return storyElement;
}

void Story::setXMLElement(XMLElement * element) {
    if (element->getName() != "story" ||
        element->getSubElements()->count() != 2) {
        return;
    }
    
    XMLElement * gapsElement = element->getSubElements()->elementAtIndex(0);
    
    if (gapsElement->getName() != "gaps") {
        return;
    }
    
    for (int i = 0; i < gapsElement->getSubElements()->count(); i++) {
        XMLElement * gapElement = gapsElement->getSubElements()->elementAtIndex(i);
        Gap * gap = NULL;
        
        if (gapElement->getName() == "number") {
            gap = new Number();
            
        }else if (gapElement->getName() == "phrase") {
            gap = new Phrase();
            
        }else if (gapElement->getName() == "name") {
            gap = new Name();
            
        }else if (gapElement->getName() == "noun") {
            gap = new Noun();
            
        }else if (gapElement->getName() == "verb") {
            gap = new Verb();
            
        }else if (gapElement->getName() == "adjective") {
            gap = new Adjective();
        }
        
        if (gap == NULL) {
            continue;
        }
        
        gap->setXMLElement(gapElement);
        
        getGaps()->addElement(gap);
    }
    
    XMLElement * textElement = element->getSubElements()->elementAtIndex(1);
    
    if (textElement->getName() != "text") {
        return;
    }
    
    setText(textElement->getContents());
}
