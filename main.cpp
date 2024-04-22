#include <iostream>
#include "hero.h"
#include "enemy.h"

int main() {
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
    return 0;
}
