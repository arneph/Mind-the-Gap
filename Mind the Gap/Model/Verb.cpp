//
//  Verb.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 12/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Verb.h"

Verb::Verb() {
    form = VerbFormInfinitive;
}

Verb::~Verb() {
}

string Verb::getName() const {
    return "verb";
}

VerbForm Verb::getForm() const {
    return form;
}

void Verb::setForm(VerbForm f) {
    form = f;
}

string Verb::getFullDescription() const {
    string description = "Verb (";
    
    if (form == VerbFormInfinitive) {
        description += "infinitive";
    }else if (form == VerbFormProgressive) {
        description += "progressive";
    }
    
    description += "); ";
    description += getDescription();
    
    return description;
}

XMLElement * Verb::getXMLElement() const {
    XMLElement * element = Gap::getXMLElement();
    
    XMLElement * formAttributeElement = new XMLElement();
    
    formAttributeElement->setName("attribute");
    
    XMLVariable * formVariable = new XMLVariable();
    
    formVariable->setName("form");
    
    if (form == VerbFormInfinitive) {
        formVariable->setValue("infinitive");
        
    }else if (form == VerbFormProgressive) {
        formVariable->setValue("progressive");
    }
    
    formAttributeElement->getVariables()->addElement(formVariable);
    
    element->getSubElements()->insertElement(0, formAttributeElement);
    
    return element;
}

void Verb::setXMLElement(XMLElement * element) {
    Gap::setXMLElement(element);
    
    for (int i = 0; i < element->getSubElements()->count(); i++) {
        XMLElement * subElement = element->getSubElements()->elementAtIndex(i);
        
        if (subElement->getName() != "attribute") continue;
        
        for (int i = 0; i < subElement->getVariables()->count(); i++) {
            XMLVariable *variable = subElement->getVariables()->elementAtIndex(i);
            
            if (variable->getName() == "form") {
                if (variable->getValue() == "infinitive") {
                    setForm(VerbFormInfinitive);
                }else if (variable->getValue() == "progressive") {
                    setForm(VerbFormProgressive);
                }
            }
        }
    }
}
