//
// Created by Svend on 22-04-2024.
//

#pragma once
#include "hero.h"

class Enemy: public Hero
{
private:
    int _damage;
    int _xpdrop;

public:
    Enemy(std::string name, int hp, int damage, int xpdrop): Hero(name, 0, 0, hp), _damage(damage), _xpdrop(xpdrop)
    {
    }
};
