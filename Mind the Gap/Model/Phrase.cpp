//
//  Phrase.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 12/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Phrase.h"

Phrase::Phrase() {
    type = PhraseTypeQuote;
}

Phrase::~Phrase() {
}

string Phrase::getName() const {
    return "phrase";
}

PhraseType Phrase::getType() const {
    return type;
}

void Phrase::setType(PhraseType t) {
    type = t;
}

string Phrase::getFullDescription() const {
    string description = "Phrase (";
    
    if (type == PhraseTypeQuote) {
        description += "quote";
    }else if (type == PhraseTypeAdvice) {
        description += "advice";
    }
    
    description += "); ";
    description += getDescription();
    
    return description;
}

XMLElement * Phrase::getXMLElement() const {
    XMLElement * element = Gap::getXMLElement();
    
    XMLElement * typeAttributeElement = new XMLElement();
    
    typeAttributeElement->setName("attribute");
    
    XMLVariable * typeVariable = new XMLVariable();
    
    typeVariable->setName("type");
    
    if (type == PhraseTypeQuote) {
        typeVariable->setValue("quote");
        
    }else if (type == PhraseTypeAdvice) {
        typeVariable->setValue("advice");
    }
    
    typeAttributeElement->getVariables()->addElement(typeVariable);
    
    element->getSubElements()->insertElement(0, typeAttributeElement);
    
    return element;
}

void Phrase::setXMLElement(XMLElement * element) {
    Gap::setXMLElement(element);
    
    for (int i = 0; i < element->getSubElements()->count(); i++) {
        XMLElement * subElement = element->getSubElements()->elementAtIndex(i);
        
        if (subElement->getName() != "attribute") continue;
        
        for (int i = 0; i < subElement->getVariables()->count(); i++) {
            XMLVariable *variable = subElement->getVariables()->elementAtIndex(i);
            
            if (variable->getName() == "type") {
                if (variable->getValue() == "quote") {
                    setType(PhraseTypeQuote);
                }else if (variable->getValue() == "advice") {
                    setType(PhraseTypeAdvice);
                }
            }
        }
    }
}
