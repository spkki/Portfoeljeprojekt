#pragma once
#include <iostream>
#include "hero.h"
#include "datamanager.h"
#include "enemy.h"

class Game
{
private:
    Hero currentHero;
    Enemy choosenEnemy;

public:
    Game(){};

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

    void battleMethod(Enemy& enemy){
        bool fightActive = true;
        while (fightActive) {
            std::cout << enemy.getName() <<" attacked " << currentHero.getName() << std::endl;
            currentHero.takeDamage(enemy.dealDamage());
            std::cout << currentHero.getName() << " attacked " << enemy.getName() << std::endl;
            enemy.takeDamage(currentHero.dealDamage());
            if(currentHero.getCurrentHp() <= 0){
                std::cout << "You have died!" << std::endl;
                currentHero.heal();
                fightActive = false;
            } else if(enemy.getHp() <= 0){
                std::cout << enemy.getName() << " has died " << std::endl;
                currentHero.gainXp(enemy.getXpDrop());
                std::cout << "You gained " << enemy.getXpDrop() << "xp" << std::endl;
                currentHero.heal();
                fightActive = false;
            }
        }
    }

    bool fightMenu(){
        bool runGame = true;

        QSqlDatabase database; //Open and find from database
        openDatabase(database);
        std::cout << "Choose a monster: " << std::endl;
        std::cout << "1. Hest" << std::endl;
        std::cout << "2. Weak Goblin" << std::endl;
        std::cout << "3. Strong Goblin" << std::endl;
        std::cout << "4. Stronger Goblin" << std::endl;
        std::cout << "5. Den stærkeste Goblin" << std::endl;
        std::cout << "6. Abe Kongen" << std::endl;
        std::cout << "7. Enhjørning" << std::endl;
        std::cout << "8. Drage" << std::endl;
        std::cout << "0. Exit" << std::endl;

        int choice = getMenuChoice();
        switch (choice) {
        case 1:
            choosenEnemy.loadEnemy("Hest");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
            break;
        case 2:
            choosenEnemy.loadEnemy("Weak Goblin");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
            break;
        case 3:
            choosenEnemy.loadEnemy("Strong Goblin");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
            break;
        case 4:
            choosenEnemy.loadEnemy("Stronger Goblin");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
            break;
        case 5:
            choosenEnemy.loadEnemy("Den stærkeste Goblin");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
            break;
        case 6:
            choosenEnemy.loadEnemy("Abe Kongen");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
            break;
        case 7:
            choosenEnemy.loadEnemy("Enhjørning");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
        case 8:
            choosenEnemy.loadEnemy("Drage");
            battleMethod(choosenEnemy);
            runGame = !gameMenu();
            break;
        case 0:
            saveAndExit();
            runGame = false;
            break;
        default:
            std::cout << "Invalid choice. Please try agian." << std::endl;
            break;
        }
        closeDatabase(database);
        return runGame;
    }

    bool gameMenu(){
        bool runGame = true;
        std::cout << "Your optiens are: " << std::endl;
        std::cout << "1. Fight monsters." << std::endl;
        std::cout << "2. Get stats." << std::endl;
        std::cout << "0. Exit." << std::endl;

        int choice = getMenuChoice();
        switch (choice) {
        case 1:
            runGame = !fightMenu();
            break;
        case 2:
            currentHero.getStats();
            gameMenu();
            break;
        case 0:
            saveAndExit();
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
