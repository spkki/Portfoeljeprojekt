#pragma once
#include <iostream>
#include "hero.h"
#include "datamanager.h"
#include "enemy.h"

class Game
{
private:
    Hero currentHero;

public:
    int getMenuChoice(){
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        return choice;
    }

    Hero createNewCharacter(){
        std::string name;

        std::cout << "Enter character name: ";
        std::cin >> name;

        QSqlDatabase database;
        openDatabase(database);

        currentHero = Hero(name);
        currentHero.getStats(name);

        std::cout << "New character created and saved!";

        closeDatabase(database);
        return currentHero;
    }

    void loadExistingCharacter(){
        std::string name;
        std::cout << "Input name of character to be loaded: ";
        std::cin >> name;

        QSqlDatabase database;
        openDatabase(database);

        currentHero = Hero(name);
        currentHero.loadHero(name);
        currentHero.getStats(name);
        std::cout << "You are now playing as: " << currentHero.getName() << std::endl;

        closeDatabase(database);
    }

    void saveAndExit(){
        std::cout << "Saving progress and exiting game." << std::endl;
        QSqlDatabase database;
        openDatabase(database);
        currentHero.deleteHero(currentHero.getName());
        currentHero.saveHero();
        std::cout << "Progress has been saved succesfully!";
        closeDatabase(database);
    }

    bool gameMenu(){
        bool runGame = true;
        std::cout << "Your optiens are: " << std::endl;
        std::cout << "1. Fight monsters." << std::endl;
        std::cout << "0. Exit." << std::endl;

        int choice = getMenuChoice();
        switch (choice) {
        case 1:
            //Fight monster code
            runGame = false;
            break;
        case 0:
            saveAndExit(); //Does not work correctly so just exit instead
            runGame = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            return false;
        }
        return runGame;
    }

    bool mainMenu(){
        bool runGame = true;
        while (runGame){
            std::cout << "Welcome to RPG GAME!" << std::endl;
            std::cout << "1. Create new character" << std::endl;
            std::cout << "2. Load existing character" << std::endl;
            std::cout << "0. Exit game" << std::endl;

            int choice = getMenuChoice();
            switch(choice){
            case 1:
                createNewCharacter();
                runGame = !gameMenu();
                break;
            case 2:
                loadExistingCharacter();
                runGame = !gameMenu();
                break;
            case 0:
                saveAndExit(); //Does not work yet so just exit
                runGame = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
        return false;
    }
};
