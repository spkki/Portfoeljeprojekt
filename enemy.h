//
// Created by Svend on 22-04-2024.
//

#pragma once
#include "hero.h"

class Enemy{
private:
    std::string _name;
    int _hp;
    int _damage;
    int _xp;

public:
    Enemy(std::string name, int hp, int damage, int xp){
        _name = name;
        _hp = hp;
        _damage = damage;
        _xp = xp;
    }

};
