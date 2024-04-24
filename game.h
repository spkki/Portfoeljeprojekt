#pragma once
#include <iostream>
#include "hero.h"
#include "datamanager.h"
#include "enemy.h"
#include <unistd.h>

class Game
{
private:
    Hero currentHero;
    Enemy choosenEnemy;

public:
    Game(){};

    int getMenuChoice(){
        int choice;
        typeText("Enter your choice: ");
        //std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }

    Hero createNewCharacter(){
        std::string name;

        typeText("Enter character name: ");
        //std::cout << "Enter character name: ";
        std::cin >> name;

        QSqlDatabase database;
        openDatabase(database);

        currentHero = Hero(name);
        currentHero.getStats(name);

        typeText("New character created and saved!\n");
        //std::cout << "New character created and saved!" << std::endl;

        closeDatabase(database);
        return currentHero;
    }

    void loadExistingCharacter(){
        QSqlDatabase database;
        openDatabase(database);

        QSqlQuery query;
        query.prepare("SELECT name, level, xp, hp, strength FROM hero");
        if(query.exec()){
            typeText("Avaliable characters: \n");
            //std::cout << "Avaliable characters: " << std::endl;
            int count = 1;
            while(query.next()){
                std::string name = query.value(0).toString().toStdString();
                int level = query.value(1).toInt();
                int xp = query.value(2).toInt();
                int hp = query.value(3).toInt();
                int strength = query.value(4).toInt();
                //typeText(count + ". " + name + "(Level: " + level + ", XP: " + xp + ", HP: " + hp + ", Strength: " + strength + ")");
                std::cout << count << ". " << name << "(Level: " << level << ", XP: " << xp << ", HP: " << hp << ", Strength: " << strength << ")" << std::endl;
                count++;
            }
            int choice;
            typeText("Which character do you want to load: ");
            //std::cout << "Which character do you want to load: ";
            std::cin >> choice;

            query.seek(-1);
            for (int i = 0; i < choice && query.next(); i++) {}

            std::string selectedName = query.value(0).toString().toStdString();
            currentHero = Hero(selectedName);
            currentHero.loadHero(selectedName);
            currentHero.getStats(selectedName);
            typeText("You are now playing as: " + currentHero.getName() + "\n");
            //std::cout << "You are now playing as: " << currentHero.getName() << std::endl;
        } else {
            typeText("Failed to retrieve character data from database.\n");
            //std::cout << "Failed to retieve character data from database." << std::endl;
        }
        closeDatabase(database);
    }

    void saveAndExit(){
        typeText("Saving progress and exiting game...\n");
        //std::cout << "Saving progress and exiting game..." << std::endl;
        QSqlDatabase database;
        openDatabase(database);
        currentHero.deleteHero(currentHero.getName());
        currentHero.saveHero();
        typeText("Progress has been saved succesfully!\n");
        //std::cout << "Progress has been saved succesfully!";
        closeDatabase(database);
    }

    void battleMethod(Enemy& enemy){
        bool fightActive = true;
        while (fightActive) {
            typeText(enemy.getName() + " attacked " + currentHero.getName() + "\n");
            //std::cout << enemy.getName() <<" attacked " << currentHero.getName() << std::endl;
            currentHero.takeDamage(enemy.dealDamage());

            bool attackInput = false;

            while(!attackInput){
                typeText("Press 'Enter' to attack: ");
                //std::cout << "Press Enter to attack: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                attackInput = true;
                typeText(currentHero.getName() + " attacked " + enemy.getName() + "\n");
                //std::cout << currentHero.getName() << " attacked " << enemy.getName() << std::endl;
                enemy.takeDamage(currentHero.dealDamage());
            }

            if(currentHero.getCurrentHp() <= 0){
                typeText("You have died!\n");
                //std::cout << "You have died!" << std::endl;
                currentHero.heal(); //Heals the player so the player can continue to play
                fightActive = false;
            } else if(enemy.getHp() <= 0){
                typeText(enemy.getName() + " has died \n");
                //std::cout << enemy.getName() << " has died " << std::endl;
                currentHero.gainXp(enemy.getXpDrop());
                typeText(currentHero.getName() + " gained ");
                std::cout << enemy.getXpDrop();
                typeText("xp\n");
                //std::cout << currentHero.getName() << " gained " << enemy.getXpDrop() << "xp" << std::endl;
                currentHero.heal(); //Heals the player to maxhp
                fightActive = false;
            }
        }
    }

    bool fightMenu(){
        bool runGame = true;

        QSqlDatabase database;
        openDatabase (database);

        typeText("Choose a monster\n");
        //std::cout << "Choose a monster" << std::endl;

        Enemy enemy;
        enemy.loadEnemy("");

        std::string enemyName = enemy.getName();

        if (!enemyName.empty()){
            battleMethod(enemy);
            runGame = !gameMenu();
        } else {
            typeText("No enemy selected. Exiting fight menu.\n");
            //std::cout << "No enemy selected. Exiting fight menu." << std::endl;
        }

        closeDatabase (database);
        return runGame;
    }

    bool gameMenu(){
        bool runGame = true;
        typeText("Your options are: \n");
        typeText("1. Fight monsters.\n");
        typeText("2. Get stats.\n");
        typeText("0. Exit.\n");
        //std::cout << "Your options are: " << std::endl;
        //std::cout << "1. Fight monsters." << std::endl;
        //std::cout << "2. Get stats." << std::endl;
        //std::cout << "0. Exit." << std::endl;

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
            typeText("Invalid choice. Please try again.\n");
            //std::cout << "Invalid choice. Please try again." << std::endl;
            return false;
        }
        return runGame;
    }

    bool mainMenu(){
        bool runGame = true;
        while (runGame){
            typeText("Welcome to Dragon Slayer Simulator!\n");
            typeText("1. Create new character\n");
            typeText("2. Load existing character\n");
            typeText("0. Exit game\n");
            //std::cout << "Welcome to Dragon Slayer Simulator!" << std::endl;
            //std::cout << "1. Create new character" << std::endl;
            //std::cout << "2. Load existing character" << std::endl;
            //std::cout << "0. Exit game" << std::endl;

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
                typeText("Invalid choice. Please try again.\n");
                //std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
        return false;
    }

    void typeText(std::string text){
        for (std::size_t i=0; i<text.size(); i++)
        {
            std::cout << text[i] << std::flush;
            usleep(60000);
        }
    }
};
