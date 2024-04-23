#pragma once
#include <iostream>

void mainMenu(){
    std::cout << "Welcome to RPG GAME!" << std::endl;
    std::cout << "1. Create new character" << std::endl;
    std::cout << "2. Load existing character" << std::endl;
    std::cout << "3. Exit game" << std::endl;
}

int getMenuChoice(){
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

void createNewCharacter(){
    std::cout << "Creating new character" << std::endl;
    // code for creating a new character
}

void loadExistingCharacter(){
    std::string heroName;
    std::cout << "Input name of character to be loaded: ";
    std::cin >> heroName;
    // code for loading an existing character
}
