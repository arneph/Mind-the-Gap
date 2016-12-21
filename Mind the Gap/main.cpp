//
//  main.cpp
//  Mind the Gap
//
//  Created by A Philipeit on 07/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "XML.h"
#include "Story.h"

using namespace std;

void printStartScreen();
void printMainMenu();
void printStoriesMenu();
void printAbout();

Story * loadStoryFromFile(string path);

void fillStoryGaps(Story * story);
void printStory(Story * story);

int main(int argc, const char * argv[]) {
    string path = "./";
    
    LinkedList<Story *> * stories = new LinkedList<Story *>;
    
    stories->addElement(loadStoryFromFile(path + "Once upon a time.txt"));
    stories->addElement(loadStoryFromFile(path + "The crime scene.txt"));
    stories->addElement(loadStoryFromFile(path + "Budget cuts.txt"));
    stories->addElement(loadStoryFromFile(path + "In class.txt"));
    
    printStartScreen();
    
    while (true) {
        printMainMenu();
        
        int mainMenuOption;
        
        cout << ">";
        cin >> mainMenuOption;
        cin.ignore();
        
        if (mainMenuOption == 1) {
            srand((int) time(NULL));
            
            int n = rand() % stories->count();
            
            Story * story = stories->elementAtIndex(n);
            
            fillStoryGaps(story);
            
            cout << endl << endl;
            
            printStory(story);
            
        }else if (mainMenuOption == 2) {
            printStoriesMenu();
            
            int storiesMenuOption = 0;
            
            while (storiesMenuOption < 1 ||
                   storiesMenuOption > stories->count()) {
                cout << ">";
                cin >> storiesMenuOption;
                cin.ignore();
            }
            
            Story * story = stories->elementAtIndex(storiesMenuOption - 1);
            
            fillStoryGaps(story);
            
            cout << endl << endl;
            
            printStory(story);
            
        }else if (mainMenuOption == 3) {
            printAbout();
            
        }else if (mainMenuOption == 4) {
            break;
        }
    }
    
    delete stories;
    
    return 0;
}

void printStartScreen() {
    cout << "***************************************************" << endl;
    cout << "* *** * ********* *** ** ************************ *" << endl;
    cout << "*  *  *********** *** ** ************************ *" << endl;
    cout << "* * * * *   **    **   *   ***  ***   **   *   ** *" << endl;
    cout << "* *** * * ** * ** *** ** ** * ** * ** * ** * ** ***" << endl;
    cout << "* *** * * ** **   **** * ** **  ***   **   *   ** *" << endl;
    cout << "************************************* ****** ******" << endl;
    cout << "***********************************  ******* ******" << endl;
    cout << "***************************************************" << endl;
    cout << endl;
    cout << "\"Story is king!\" - Someone @ Pixar" << endl;
    cout << endl;
    cout << "In this game you fill in the gaps of stories " << endl;
    cout << "that are already written." << endl;
}

void printMainMenu() {
    cout << endl;
    cout << "- Main menu -" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "1 - Random story" << endl;
    cout << "2 - Select story" << endl;
    cout << "3 - About" << endl;
    cout << "4 - Exit" << endl;
    cout << endl;
}

void printStoriesMenu() {
    cout << endl;
    cout << "- Stories menu -" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "1 - Once upon a time" << endl;
    cout << "2 - The crime scene" << endl;
    cout << "3 - Budget cuts" << endl;
    cout << "4 - In class" << endl;
    cout << endl;
}

void printAbout() {
    cout << endl;
    cout << "This game was written and designed by " << endl;
    cout << "Arne Philipeit." << endl;
    cout << endl;
    cout << "It was created as the final project for " << endl;
    cout << "2E3 Computer Engineering in " << endl;
    cout << "Trinity College Dublin." << endl;
    cout << endl;
    cout << "14.12.2016 3:10am";
    cout << endl;
}

Story * loadStoryFromFile(string path) {
    fstream file;
    
    file.open(path);
    
    string c = "";
    
    while (!file.eof()) {
        string l;
        
        getline(file, l);
        
        c += l + "\n";
    }
    
    file.close();
    
    string name = path.substr(path.find_last_of("/\\") + 1);
    
    name = name.substr(0, name.find_last_of("."));
    
    XMLTree * tree = new XMLTree();
    
    tree->setString(c);
    
    Story * story = new Story();
    
    story->setName(name);
    story->setXMLElement(tree->getRootElements()->elementAtIndex(0));
    
    delete tree;
    
    return story;
}

void fillStoryGaps(Story * story) {
    int n = story->getGaps()->count();
    int * indices = new int[n];
    
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    srand((int) time(NULL));
    
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        
        int t = indices[i];
        
        indices[i] = indices[j];
        indices[j] = t;
    }
    
    for (int i = 0; i < n; i++) {
        Gap * gap = story->getGaps()->elementAtIndex(indices[i]);
        string value;
        
        cin.clear();
        
        cout << gap->getFullDescription() << ": ";
        getline(cin, value);
        
        cin.clear();
        
        gap->setValue(value);
    }
}

void printStory(Story * story) {
    cout << story->getName();
    cout << endl;
    cout << story->getFilledText();
}
