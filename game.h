#pragma once
#include <iostream>
#include "hero.h"
#include "datamanager.h"
#include "enemy.h"

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

void gameMenu(){
    std::cout << "Your optiens are: " << std::endl;
    std::cout << "1. Fight monsters." << std::endl;
    std::cout << "0. Save and exit." << std::endl;
}

void mainMenu(){
    std::cout << "Welcome to RPG GAME!" << std::endl;
    std::cout << "1. Create new character" << std::endl;
    std::cout << "2. Load existing character" << std::endl;
    std::cout << "0. Save and exit game" << std::endl;

    bool runGame = true;
    Hero currentHero;

    while (runGame) {
        int mainMenuChoice = getMenuChoice();
        switch(mainMenuChoice){
        case 1:
            createNewCharacter();
            break;
        case 2:
            loadExistingCharacter();
            break;
        case 0:
            saveAndExit(currentHero);
            runGame = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

        if(runGame){
            gameMenu();
            int gameMenuChoice = getMenuChoice();
            switch (gameMenuChoice){
            case 1:
                //Fight monster code
                break;
            case 0:
                saveAndExit(currentHero);
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    }
}
