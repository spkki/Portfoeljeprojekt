#include "enemy.h"
#include "hero.h"
#include "datamanager.h"
#include <iostream>
#include <QString>

int main()
{
    Hero Test("John");
    Test.getName();
    Test.getXp();
    Test.getLevel();
    Test.getHp();
    Test.getStrength();
    Test.takeDamage(9);
    Test.getHp();
    Test.gainXp(1000);
    Test.getXp();
    Test.getLevel();



    //Enemy Orc("Orc1", 10, 1, 1);
    //Orc.getXp();

    QSqlDatabase database;
    openDatabase(database);

    Test.saveHero(); // Save hero to database
    Hero loadedHero;
    loadedHero.loadHero("John"); // Load hero from database
    std::cout << "Loaded Hero's " << loadedHero.getName() << std::endl;
    closeDatabase(database);


    return 0;
}
