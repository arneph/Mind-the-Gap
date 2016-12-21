//
//  Number.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 11/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "Number.h"

Number::Number() {
    type = NumberTypeInteger;
    
    minimumDefined = false;
    minimumInclusive = false;
    minimum = 0.0;
    
    maximumDefined = false;
    maximumInclusive = false;
    maximum = 0.0;
    
    Gap::setValue("0");
}

Number::~Number() {
}

string Number::getName() const {
    return "number";
}

NumberType Number::getType() const {
    return type;
}

void Number::setType(NumberType t) {
    type = t;
}

bool Number::isMinimumDefined() const {
    return minimumDefined;
}

void Number::setMinimumDefined(bool f) {
    minimumDefined = f;
}

bool Number::isMinimumInclusive() const {
    return minimumInclusive;
}

void Number::setMinimumInclusive(bool f) {
    minimumInclusive = f;
}

double Number::getMinimum() const {
    return minimum;
}

void Number::setMinimum(double m) {
    minimum = m;
}

bool Number::isMaximumDefined() const {
    return maximumDefined;
}

void Number::setMaximumDefined(bool f) {
    maximumDefined = f;
}

bool Number::isMaximumInclusive() const {
    return maximumInclusive;
}

void Number::setMaximumInclusive(bool f) {
    maximumInclusive = f;
}

double Number::getMaximum() const {
    return maximum;
}

void Number::setMaximum(double m) {
    maximum = m;
}

string Number::getRange() const {
    if (isMinimumDefined() == false &&
        isMaximumDefined() == false) {
        return "";
    }
    
    string range = "";
    
    if (isMinimumDefined()) {
        range += to_string(getMinimum());
        range += " ";
        range += (isMinimumInclusive()) ? "<=" : "<";
        range += " ";
    }
    
    range += "X";
    
    if (isMaximumDefined()) {
        range += " ";
        range += (isMaximumInclusive()) ? "<=" : "<";
        range += " ";
        range += to_string(getMaximum());
    }
    
    return range;
}

void Number::setRange(string range) {
    if (range.length() < 1) {
        minimumDefined = false;
        minimumInclusive = false;
        minimum = 0.0;
        
        maximumDefined = false;
        maximumInclusive = false;
        maximum = 0.0;
        
        return;
    }
    
    smatch min_match;
    regex min_exp = regex("[ ]*?((\\+|\\-)?[0-9]+(\\.[0-9]+)?)[ ]*?(\\<\\=|\\<)[ ]*?X.*?");
    
    if (regex_search(range, min_match, min_exp)) {
        minimumDefined = true;
        minimumInclusive = (min_match[4] == "<=");
        minimum = stod(min_match[1]);

    }else{
        minimumDefined = false;
        minimumInclusive = false;
        minimum = 0.0;
    }
    
    smatch max_match;
    regex max_exp = regex(".*?X[ ]*?(\\<\\=|\\<)[ ]*?((\\+|\\-)?[0-9]+(\\.[0-9]+)?)[ ]*?");
    
    if (regex_search(range, max_match, max_exp)) {
        maximumDefined = true;
        maximumInclusive = (max_match[4] == "<=");
        maximum = stod(max_match[1]);
        
    }else{
        maximumDefined = false;
        maximumInclusive = false;
        maximum = 0.0;
    }
}

string Number::getFullDescription() const {
    string description = "Number (";
    
    if (type == NumberTypeInteger) {
        description += "int, ";
    }else if (type == NumberTypeDouble) {
        description += "double, ";
    }
    
    description += getRange();
    description += "); ";
    description += getDescription();
    
    return description;
}

string Number::getValue() const {
    string v = Gap::getValue();
    double value;
    
    try {
        value = stod(v);
    } catch (invalid_argument ex) {
        return "";
    } catch (out_of_range ex) {
        return "";
    }
    
    if (minimumDefined) {
        if (minimumInclusive) {
            if (value < minimum) return "";
        }else{
            if (value <= minimum) return "";
        }
    }
    
    if (maximumDefined) {
        if (maximumInclusive) {
            if (value > maximum) return "";
        }else{
            if (value >= maximum) return "";
        }
    }
    
    if (type == NumberTypeInteger) {
        if (value != (int) value) return "";
    }
    
    return v;
}

void Number::setValue(string v) {
    double value;
    
    try {
        value = stod(v);
    } catch (invalid_argument ex) {
        return;
    } catch (out_of_range ex) {
        return;
    }
    
    setValue(value);
}

void Number::setValue(double value) {
    if (minimumDefined) {
        if (minimumInclusive) {
            if (value < minimum) return;
        }else{
            if (value <= minimum) return;
        }
    }
    
    if (maximumDefined) {
        if (maximumInclusive) {
            if (value > maximum) return;
        }else{
            if (value >= maximum) return;
        }
    }
    
    if (type == NumberTypeInteger) {
        if (value != (int) value) return;
    }
    
    Gap::setValue(to_string(value));
}

XMLElement * Number::getXMLElement() const {
    XMLElement * element = Gap::getXMLElement();
    
    XMLElement * typeAttributeElement = new XMLElement();
    
    typeAttributeElement->setName("attribute");
    
    XMLVariable * typeVariable = new XMLVariable();
    
    typeVariable->setName("type");
    
    if (type == NumberTypeInteger) {
        typeVariable->setValue("Int");
        
    }else if (type == NumberTypeDouble) {
        typeVariable->setValue("Double");
    }
    
    typeAttributeElement->getVariables()->addElement(typeVariable);
    
    XMLElement * rangeAttributeElement = new XMLElement();
    
    rangeAttributeElement->setName("attribute");
    
    XMLVariable * rangeVariable = new XMLVariable();
    
    rangeVariable->setName("range");
    rangeVariable->setValue(getRange());
    
    rangeAttributeElement->getVariables()->addElement(rangeVariable);
    
    element->getSubElements()->insertElement(0, typeAttributeElement);
    element->getSubElements()->insertElement(1, rangeAttributeElement);
    
    return element;
}

void Number::setXMLElement(XMLElement * element) {
    Gap::setXMLElement(element);
    
    for (int i = 0; i < element->getSubElements()->count(); i++) {
        XMLElement * subElement = element->getSubElements()->elementAtIndex(i);
        
        if (subElement->getName() != "attribute") continue;
        
        for (int i = 0; i < subElement->getVariables()->count(); i++) {
            XMLVariable *variable = subElement->getVariables()->elementAtIndex(i);
            
            if (variable->getName() == "type") {
                if (variable->getValue() == "Int") {
                    setType(NumberTypeInteger);
                }else if (variable->getValue() == "Double") {
                    setType(NumberTypeDouble);
                }
                
            }else if (variable->getName() == "range") {
                setRange(variable->getValue());
            }
        }
    }
}
