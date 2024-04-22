//
// Created by Svend on 22-04-2024.
//

#pragma once

class Hero{
private:
    std::string _name;
    int _xp;
    int _level;
    int _hp;
    int _strength;
public:
    Hero(std::string name, int xp, int level, int hp, int strength){
        _name = name;
        _xp = xp;
        _level = level;
        _hp = hp;
        _strength = strength;
    }

    void setName(std::string nameinput){
        _name = nameinput;
    };

    std::string getName(){
        std::cout << "Name: " << _name << std::endl;
        return _name;
    };

    void setXp(int xp){
        _xp = xp;
    }

    int getXp(){
        std::cout << "xp: " << _xp << std::endl;
        return _xp;
    }

    void setLevel(int level){
        _level = level;
    }

    int getLevel(){
        std::cout << "Level: " << _level << std::endl;
        return _level;
    }

    void setHp(int hp){
        _hp = hp;
    }

    int getHp(){
        std::cout << "hp: " << _hp << std::endl;
        return _hp;
    }

    void setStrength(int strength){
        _strength = strength;
    }

    int getStrength(){
        std::cout << "Strength: " << _strength << std::endl;
        return _strength;
    }

    void takeDamage(int damage){
        _hp -= damage;
        if (_hp > 0){
            std::cout << _name << " has " << _hp << " hp left" << std::endl;
        }
        else {
            std::cout << _name << " IS DEAD!" << std::endl;
        }
    }

    void dealDamage(int damage){
        _strength = damage;
    }

};
