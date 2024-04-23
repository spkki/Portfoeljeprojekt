#pragma once
#include <iostream>
#include "hero.h"
#include "datamanager.h"

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
    std::string name;

    std::cout << "Enter character name: ";
    std::cin >> name;

    QSqlDatabase database;
    openDatabase(database);

    Hero newCharacter(name);
    newCharacter.saveHero();

    std::cout << "New character created and saved!";

    closeDatabase(database);
}

void loadExistingCharacter(){
    std::string heroName;
    std::cout << "Input name of character to be loaded: ";
    std::cin >> heroName;

    QSqlDatabase database;
    openDatabase(database);

    Hero loadedHero;
    loadedHero.loadHero(heroName);
    std::cout << "You are now playing as: " << loadedHero.getName() << std::endl;

    closeDatabase(database);
}

void saveAndExit(Hero& currentHero){
    std::cout << "Saving progress and exiting game." << std::endl;
    QSqlDatabase database;
    openDatabase(database);
    currentHero.setHp(100); //HAS TO BE REMOVED
    currentHero.saveHero();
    std::cout << "Progress has been saved succesfully!";
    closeDatabase(database);
}
