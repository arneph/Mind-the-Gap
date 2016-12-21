//
//  Gap.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 08/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Gap.h"

Gap::Gap() {
    number = 0;
    description = "";
    
    value = "";
}

Gap::~Gap() {
}

string Gap::getName() const {
    //This should be overridden by subclasses!
    
    return "gap";
}

int Gap::getNumber() const {
    return number;
}

void Gap::setNumber(int n) {
    if (n < 0) n = 0;
    
    number = n;
}

string Gap::getPlaceholderName() const {
    return getName() + " " + to_string(getNumber());
}

string Gap::getDescription() const {
    return description;
}

void Gap::setDescription(string d) {
    description = d;
}

string Gap::getFullDescription() const {
    return description;
}

string Gap::getValue() const {
    return value;
}

void Gap::setValue(string v) {
    value = v;
}

XMLElement * Gap::getXMLElement() const {
    XMLElement * description = new XMLElement();
    
    description->setName("description");
    description->setNumber(0);
    description->setContents(getDescription());
    
    XMLElement * element = new XMLElement();
    
    element->setName(getName());
    element->setNumber(getNumber());
    element->getSubElements()->addElement(description);
    
    return element;
}

void Gap::setXMLElement(XMLElement * element) {
    if (element->getName() != getName()) {
        return;
    }
    
    setNumber(element->getNumber());

    for (int i = 0; i < element->getSubElements()->count(); i++) {
        XMLElement * subElement = element->getSubElements()->elementAtIndex(i);
        
        if (subElement->getName() == "description") {
            setDescription(subElement->getContents());
            
            break;
        }
    }
}
