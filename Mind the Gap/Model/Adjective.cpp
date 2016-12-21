//
//  Adjective.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 12/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Adjective.h"

Adjective::Adjective() {
    comparison = AdjectiveComprarisonPositive;
}

Adjective::~Adjective() {
}

string Adjective::getName() const {
    return "adjective";
}

AdjectiveComprarison Adjective::getComparison() const {
    return comparison;
}

void Adjective::setComprarison(AdjectiveComprarison c) {
    comparison = c;
}

string Adjective::getFullDescription() const {
    string description = "Adjective (";
    
    if (comparison == AdjectiveComprarisonPositive) {
        description += "positive";
    }else if (comparison == AdjectiveComprarisonComparative) {
        description += "comparative";
    }else if (comparison == AdjectiveComprarisonSuperlative) {
        description += "superlative";
    }
    
    description += "); ";
    description += getDescription();
    
    return description;
}

XMLElement * Adjective::getXMLElement() const {
    XMLElement * element = Gap::getXMLElement();
    
    XMLElement * comparisonAttributeElement = new XMLElement();
    
    comparisonAttributeElement->setName("attribute");
    
    XMLVariable * comparisonVariable = new XMLVariable();
    
    comparisonVariable->setName("comparison");
    
    if (comparison == AdjectiveComprarisonPositive) {
        comparisonVariable->setValue("positive");
        
    }else if (comparison == AdjectiveComprarisonComparative) {
        comparisonVariable->setValue("comprarative");
        
    }else if (comparison == AdjectiveComprarisonSuperlative) {
        comparisonVariable->setValue("superlative");
    }
    
    comparisonAttributeElement->getVariables()->addElement(comparisonVariable);
    
    element->getSubElements()->insertElement(0, comparisonAttributeElement);
    
    return element;
}

void Adjective::setXMLElement(XMLElement * element) {
    Gap::setXMLElement(element);
    
    for (int i = 0; i < element->getSubElements()->count(); i++) {
        XMLElement * subElement = element->getSubElements()->elementAtIndex(i);
        
        if (subElement->getName() != "attribute") continue;
        
        for (int i = 0; i < subElement->getVariables()->count(); i++) {
            XMLVariable *variable = subElement->getVariables()->elementAtIndex(i);
            
            if (variable->getName() == "comparison") {
                if (variable->getValue() == "positive") {
                    setComprarison(AdjectiveComprarisonPositive);
                }else if (variable->getValue() == "comparative") {
                    setComprarison(AdjectiveComprarisonComparative);
                }else if (variable->getValue() == "superlative") {
                    setComprarison(AdjectiveComprarisonSuperlative);
                }
            }
        }
    }
}
