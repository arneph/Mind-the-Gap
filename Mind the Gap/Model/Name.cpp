//
//  Name.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 12/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Name.h"

Name::Name() {
    gender = GGenderUndefined;
}

Name::~Name() {
}

string Name::getName() const {
    return "name";
}

GGender Name::getGender() const {
    return gender;
}

void Name::setGender(GGender g) {
    gender = g;
}

string Name::getFullDescription() const {
    string description = "Name (";
    
    if (gender == GGenderFemale) {
        description += "female";
    }else if (gender == GGenderMale) {
        description += "male";
    }else if (gender == GGenderUndefined) {
        description += "gender undefined";
    }
    
    description += "); ";
    description += getDescription();
    
    return description;
}

XMLElement * Name::getXMLElement() const {
    XMLElement * element = Gap::getXMLElement();
    
    XMLElement * genderAttributeElement = new XMLElement();
    
    genderAttributeElement->setName("attribute");
    
    XMLVariable * genderVariable = new XMLVariable();
    
    genderVariable->setName("gender");
    
    if (gender == GGenderFemale) {
        genderVariable->setValue("female");
        
    }else if (gender == GGenderMale) {
        genderVariable->setValue("male");
        
    }else if (gender == GGenderUndefined) {
        genderVariable->setValue("undefined");
    }
    
    genderAttributeElement->getVariables()->addElement(genderVariable);
    
    element->getSubElements()->insertElement(0, genderAttributeElement);
    
    return element;
}

void Name::setXMLElement(XMLElement * element) {
    Gap::setXMLElement(element);
    
    for (int i = 0; i < element->getSubElements()->count(); i++) {
        XMLElement * subElement = element->getSubElements()->elementAtIndex(i);
        
        if (subElement->getName() != "attribute") continue;
        
        for (int i = 0; i < subElement->getVariables()->count(); i++) {
            XMLVariable *variable = subElement->getVariables()->elementAtIndex(i);
            
            if (variable->getName() == "gender") {
                if (variable->getValue() == "female") {
                    setGender(GGenderFemale);
                }else if (variable->getValue() == "male") {
                    setGender(GGenderMale);
                }else if (variable->getValue() == "undefined") {
                    setGender(GGenderUndefined);
                }
            }
        }
    }
}
