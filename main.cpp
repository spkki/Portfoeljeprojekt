#include <iostream>
#include "hero.h"
#include "enemy.h"

int main() {
    Hero Test("Name Test",1,1,1,1);
    Test.getName();
    Test.setXp(20);
    Test.getXp();
    Test.setLevel(10);
    Test.getLevel();
    Test.setHp(10);
    Test.getHp();
    Test.setStrength(10);
    Test.getStrength();
    Test.takeDamage(9);
    Test.getHp();
    return 0;
}
