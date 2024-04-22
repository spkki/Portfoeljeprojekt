#include "enemy.h"
#include "hero.h"
#include <iostream>

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
    //test
    return 0;
}
