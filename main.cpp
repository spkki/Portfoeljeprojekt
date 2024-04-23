#include "enemy.h"
#include "hero.h"
#include "datamanager.h"
#include <iostream>
#include <QString>

int main()
{
    Hero Test("Name Test");
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

    QSqlDatabase database;
    openDatabase(database);

    closeDatabase(database);

    Enemy Orc("Orc1", 10, 1, 1);
    Orc.getXp();
    //test
    return 0;
}
