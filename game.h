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
        QSqlDatabase database;
        openDatabase(database);

        QSqlQuery query;
        query.prepare("SELECT name, level, xp, hp, strength FROM hero");
        if(query.exec()){
            std::cout << "Avaliable characters: " << std::endl;
            int count = 1;
            while(query.next()){
                std::string name = query.value(0).toString().toStdString();
                int level = query.value(1).toInt();
                int xp = query.value(2).toInt();
                int hp = query.value(3).toInt();
                int strength = query.value(4).toInt();
                std::cout << count << ". " << name << "(Level: " << level << ", XP: " << xp << ", HP: " << hp << ", Strength: " << strength << ")" << std::endl;
                count++;
            }
            int choice;
            std::cout << "Which character do you want to load: ";
            std::cin >> choice;

            query.seek(-1);
            for (int i = 0; i < choice && query.next(); i++) {}

            std::string selectedName = query.value(0).toString().toStdString();
            currentHero = Hero(selectedName);
            currentHero.loadHero(selectedName);
            currentHero.getStats(selectedName);
            std::cout << "You are now playing as: " << currentHero.getName() << std::endl;
        } else {
            std::cout << "Failed to retieve character data from database." << std::endl;
        }
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
                std::cout << currentHero.getName() << " gained " << enemy.getXpDrop() << "xp" << std::endl;
                currentHero.heal();
                fightActive = false;
            }
        }
    }

    bool fightMenu(){
        bool runGame = true;

        QSqlDatabase database;
        openDatabase (database);

        std::cout << "Choose a monster" << std::endl;

        Enemy enemy;
        enemy.loadEnemy("");

        std::string enemyName = enemy.getName();

        if (!enemyName.empty()){
            battleMethod(enemy);
            runGame = !gameMenu();
        } else {
            std::cout << "No enemy selected. Exiting fight menu." << std::endl;
        }

        closeDatabase (database);
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
