//
//  XML.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 07/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include "XML.h"

//Regex:
const string tag_expression = "<([A-Za-z]+)[ ]*([0-9]*)[ ]*?([A-Za-z0-9=\" \\<\\>_\\-]*?)(\\/>|>((.|\\n)*?)<\\/\\1[ ]*?>)";
//1: Tag Name
//2: Tag Number
//3: Tag Variables
//5: Tag Content
const string tag_variable_expression = "([A-Za-z]+)=\"([A-Za-z0-9= \\<\\>_\\-]*?)\"";
//1: Variable Name
//2: Variable Value

string XMLString_RemoveTabs(string string) {
    regex expression = regex("\\t");
    
    return regex_replace(string, expression, "");
}

void XMLString_SplitTags(string string, LinkedList<std::string> * &topLevelElements) {
    topLevelElements = new LinkedList<std::string>;
    
    smatch match;
    regex expression(tag_expression);
    
    while (regex_search(string, match, expression)) {
        topLevelElements->addElement(std::string(match.str()));
        
        string = match.suffix();
    }
}

string XMLString_TagName(string string) {
    smatch match;
    regex expression(tag_expression);
    
    if (regex_match(string, match, expression)) {
        return match[1].str();
    }else{
        return "";
    }
}

int XMLString_TagNumber(string string) {
    smatch match;
    regex expression(tag_expression);
    
    if (regex_match(string, match, expression)) {
        if (match[2].length() < 1) {
            return 0;
        }
        
        return stoi(match[2].str());
    }else{
        return 0;
    }
}

string XMLString_AllTagContents(string string) {
    smatch match;
    regex expression(tag_expression);
    
    if (regex_search(string, match, expression)) {
        return std::string(match[5]);
    }else{
        return "";
    }
}

string XMLString_TagContents(string string) {
    smatch match;
    regex expression(tag_expression);
    
    if (regex_search(string, match, expression) == false) {
        return "";
    }
    
    string = std::string(match[5]);
    string = regex_replace(string, expression, "");
    
    expression = regex("^[\\n]+$");
    
    string = regex_replace(string, expression, "");
    
    return string;
}

void XMLString_TagVariables(string string, LinkedList<std::string> * &variableNames, LinkedList<std::string> * &variableValues) {
    variableNames = new LinkedList<std::string>;
    variableValues = new LinkedList<std::string>;
    
    smatch match;
    regex expression(tag_expression);
    
    if (regex_search(string, match, expression) == false) {
        return;
    }
    
    string = match[3].str();
    
    expression = regex(tag_variable_expression);
    
    while (regex_search(string, match, expression)) {
        variableNames->addElement(match[1].str().c_str());
        variableValues->addElement(match[2].str().c_str());
        
        string = match.suffix();
    }
}

XMLVariable::XMLVariable() {
    name = "";
    value = "";
}

XMLVariable::~XMLVariable() {
}

string XMLVariable::getName() const {
    return name;
}

void XMLVariable::setName(string n) {
    name = n;
}

string XMLVariable::getValue() const {
    return value;
}

void XMLVariable::setValue(string v) {
    value = v;
}

XMLElement::XMLElement() {
    name = "";
    number = 0;
    
    contents = "";
    
    subElements = new LinkedList<XMLElement *>;
    variables = new LinkedList<XMLVariable *>;
}

XMLElement::~XMLElement() {
    for (int i = subElements->count() - 1; i >= 0; i--) {
        delete subElements->removeElement(i);
    }
    
    delete subElements;
    
    subElements = NULL;
    
    for (int i = variables->count() - 1; i >= 0; i--) {
        delete variables->removeElement(i);
    }
    
    delete variables;
    
    variables = NULL;
}

string XMLElement::getName() const {
    return name;
}

void XMLElement::setName(string n) {
    name = n;
}

int XMLElement::getNumber() const {
    return number;
}

void XMLElement::setNumber(int n) {
    if (n < 0) n = 0;
    
    number = n;
}

string XMLElement::getContents() const {
    return contents;
}

void XMLElement::setContents(string c) {
    contents = c;
}

LinkedList<XMLElement *> * XMLElement::getSubElements() {
    return subElements;
}

LinkedList<XMLVariable *> * XMLElement::getVariables() {
    return variables;
}

string XMLElement::getString() const {
    string s = "";
    
    s += "<" + name;
    
    if (number > 0) {
        s+= " " + to_string(number);
    }
    
    for (int i = 0; i < variables->count(); i++) {
        XMLVariable * variable = variables->elementAtIndex(i);
        
        s += " " + variable->getName() + "=\"" + variable->getValue() + "\"";
    }
    
    if (subElements->count() == 0 && contents == "") {
        s += "/>";
        
        return s;
    }else{
        s += ">";
        
        for (int i = 0; i < subElements->count(); i++) {
            XMLElement * subElement = subElements->elementAtIndex(i);
            
            string subElementString = subElement->getString();
            
            s += "\n\t";
            
            for (char c : subElementString) {
                s += c;
                
                if (c == '\n') {
                    s += "\t";
                }
            }
        }
        
        if (contents != "") {
            s += "\n\t";
            
            for (char c : contents) {
                s += c;
                
                if (c == '\n') {
                    s += "\t";
                }
            }
        }
        
        s += "\n";
        s += "</" + name + ">";
    }
    
    return s;
}

void XMLElement::setString(string s) {
    name = XMLString_TagName(s);
    number = XMLString_TagNumber(s);
    
    contents = XMLString_TagContents(s);
    
    
    string allContents = XMLString_AllTagContents(s);
    
    
    //SubElements:
    for (int i = subElements->count() - 1; i >= 0; i--) {
        delete subElements->removeElement(i);
    }
    
    LinkedList<std::string> * subElementStrings;
    
    XMLString_SplitTags(allContents, subElementStrings);
    
    for (int i = 0; i < subElementStrings->count(); i++) {
        string subElementString = subElementStrings->elementAtIndex(i);
        XMLElement * subElement = new XMLElement();
        
        subElement->setString(subElementString);
        
        subElements->addElement(subElement);
    }
    
    
    //Variables:
    for (int i = variables->count() - 1; i >= 0; i--) {
        delete variables->removeElement(i);
    }
    
    LinkedList<std::string> * variableNames;
    LinkedList<std::string> * variableValues;
    
    XMLString_TagVariables(s, variableNames, variableValues);
    
    for (int i = 0; i < variableNames->count(); i++) {
        string variableName = variableNames->elementAtIndex(i);
        string variableValue = variableValues->elementAtIndex(i);
        XMLVariable * variable = new XMLVariable();
        
        variable->setName(variableName);
        variable->setValue(variableValue);
        
        variables->addElement(variable);
    }
}

XMLTree::XMLTree() {
    rootElements = new LinkedList<XMLElement *>;
}

XMLTree::~XMLTree() {
    for (int i = rootElements->count() - 1; i >= 0; i--) {
        delete rootElements->removeElement(i);
    }
    
    delete rootElements;
    
    rootElements = NULL;
}

LinkedList<XMLElement *> * XMLTree::getRootElements() {
    return rootElements;
}

string XMLTree::getString() const {
    string s = "";
    
    for (int i = 0; i < rootElements->count(); i++) {
        XMLElement * rootElement = rootElements->elementAtIndex(i);
        
        s += rootElement->getString();
        s += "\n";
    }
    
    return s;
}

void XMLTree::setString(string s) {
    for (int i = rootElements->count() - 1; i >= 0; i--) {
        delete rootElements->removeElement(i);
    }
    
    s = XMLString_RemoveTabs(s);
    
    LinkedList<std::string> * rootElementStrings;
    
    XMLString_SplitTags(s, rootElementStrings);
    
    for (int i = 0; i < rootElementStrings->count(); i++) {
        string rootElementString = rootElementStrings->elementAtIndex(i);
        XMLElement * rootElement = new XMLElement();
        
        rootElement->setString(rootElementString);
        
        rootElements->addElement(rootElement);
    }
}
