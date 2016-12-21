//
//  Noun.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 12/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Noun.h"

Noun::Noun() {
    number = GNumberSingular;
    type = NounTypeObject;
}

Noun::~Noun() {
}

string Noun::getName() const {
    return "noun";
}

GNumber Noun::getNumber() const {
    return number;
}

void Noun::setNumber(GNumber n) {
    number = n;
}

NounType Noun::getType() const {
    return type;
}

void Noun::setType(NounType t) {
    type = t;
}


string Noun::getFullDescription() const {
    string description = "Noun (";
    
    if (number == GNumberSingular) {
        description += "singular, ";
    }else if (number == GNumberPlural) {
        description += "plural, ";
    }
    
    if (type == NounTypeObject) {
        description += "object";
    }else if (type == NounTypePerson) {
        description += "person";
    }
    
    description += "); ";
    description += getDescription();
    
    return description;
}

XMLElement * Noun::getXMLElement() const {
    XMLElement * element = Gap::getXMLElement();
    
    {//Add number attribute
        XMLElement * numberAttributeElement = new XMLElement();
        
        numberAttributeElement->setName("attribute");
        
        XMLVariable * numberVariable = new XMLVariable();
        
        numberVariable->setName("number");
        
        if (number == GNumberSingular) {
            numberVariable->setValue("singular");
            
        }else if (type == GNumberPlural) {
            numberVariable->setValue("plural");
        }
        
        numberAttributeElement->getVariables()->addElement(numberVariable);
        
        element->getSubElements()->insertElement(0, numberAttributeElement);
    }
    
    {//Add type attribute
        XMLElement * typeAttributeElement = new XMLElement();
        
        typeAttributeElement->setName("attribute");
        
        XMLVariable * typeVariable = new XMLVariable();
        
        typeVariable->setName("type");
        
        if (type == NounTypeObject) {
            typeVariable->setValue("object");
            
        }else if (type == NounTypePerson) {
            typeVariable->setValue("person");
        }
        
        typeAttributeElement->getVariables()->addElement(typeVariable);
        
        element->getSubElements()->insertElement(1, typeAttributeElement);
    }
    
    return element;
}

void Noun::setXMLElement(XMLElement * element) {
    Gap::setXMLElement(element);
    
    for (int i = 0; i < element->getSubElements()->count(); i++) {
        XMLElement * subElement = element->getSubElements()->elementAtIndex(i);
        
        if (subElement->getName() != "attribute") continue;
        
        for (int i = 0; i < subElement->getVariables()->count(); i++) {
            XMLVariable *variable = subElement->getVariables()->elementAtIndex(i);
            
            if (variable->getName() == "number") {
                if (variable->getValue() == "singular") {
                    setNumber(GNumberSingular);
                }else if (variable->getValue() == "plural") {
                    setNumber(GNumberPlural);
                }
                
            }else if (variable->getName() == "type") {
                if (variable->getValue() == "object") {
                    setType(NounTypeObject);
                }else if (variable->getValue() == "person") {
                    setType(NounTypePerson);
                }
            }
        }
    }
}
