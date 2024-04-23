#include "enemy.h"
#include "hero.h"
#include "datamanager.h"
#include "mainMenu.h"
#include <iostream>
#include <QString>

int main()
{

    bool runGame = true;

    while (runGame) {
        mainMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice){
        case 1:
            createNewCharacter();
            break;
        case 2:
            loadExistingCharacter();
            break;
        case 3:
            std::cout << "Exiting game..." << std::endl;
            runGame = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }

    return 0;


/*
    Hero Test("John");
    Test.getName();
    Test.getXp();
    Test.getLevel();
    Test.getHp();
    Test.getStrength();
    Test.takeDamage(9);
    Test.getHp();
    Test.getXp();
    Test.getLevel();




    //Enemy Orc("Orc1", 10, 1, 1);
    //Orc.getXp();

    QSqlDatabase database;
    openDatabase(database);

    Test.saveHero(); // Save hero to database
    Hero loadedHero;
    //loadedHero.loadHero("John"); // Load hero from database
    std::cout << "Loaded Hero's " << loadedHero.getName() << std::endl;
    //Test.deleteHero();
    closeDatabase(database);

*/
}
