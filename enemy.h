//
// Created by Svend on 22-04-2024.
//

#pragma once
#include "hero.h"
#include "datamanager.h"

class Enemy
{
private:
    int _damage;
    int _xpdrop;
    int _hp;
    std::string _name;
    Hero currentHero;

public:
    Enemy(){};
    Enemy(std::string name, int hp, int damage, int xpdrop):_name(name), _damage(damage), _xpdrop(xpdrop), _hp(hp){}

    std::string getName(){
        return _name;
    };

    int dealDamage(){
        return _damage;
    }

    int getHp(){
        //std::cout << "hp: " << _hp << std::endl;
        return _hp;
    }

    int getXpDrop(){
        return _xpdrop;
    }

    void takeDamage(int damage){
        _hp -= damage;
        if (_hp > 0){
            currentHero.typeText(_name + " has ");
            std::cout << _hp;
            currentHero.typeText(" hp left\n");
            //std::cout << _name << " has " << _hp << " hp left" << std::endl;
        } else if (_hp <= 0){
            //std::cout << _name << " IS DEAD!" << std::endl; //Removed because fightmethod handles it
        }
    }

    void loadEnemy(std::string enemyname){
        QSqlDatabase database;
        openDatabase (database);
        QSqlQuery query;
        query.prepare("SELECT name, hp, damage, xpdrop FROM enemy");
        if (query.exec()){
            currentHero.typeText("Avaliable enemies: \n");
            //std::cout << "Avaliable enemies: " << std::endl;
            int count = 1;
            while (query.next()){
                std::string name = query.value(0).toString().toStdString();
                int hp = query.value(1).toInt();
                int damage = query.value(2).toInt();
                int xpdrop = query.value(3).toInt();
                std::cout << count << ". " << name << "(HP: " << hp << ", Damage: " << damage << ", XP Drop: " << xpdrop << ")" << std::endl; //Add other things into this statement
                count++;
            }
            int choice;
            currentHero.typeText("Choose your enemy: ");
            //std::cout << "Choose your enemy: ";
            std::cin >> choice;

            query.seek(choice-1);

            _name = query.value(0).toString().toStdString();
            _hp = query.value(1).toInt();
            _damage = query.value(2).toInt();
            _xpdrop = query.value(3).toInt();

            std::string selectedEnemy = query.value(0).toString().toStdString();
        }
    }

};
