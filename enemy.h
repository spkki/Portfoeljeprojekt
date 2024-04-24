//
// Created by Svend on 22-04-2024.
//

#pragma once
#include "hero.h"

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
        if (_hp > 0) {
            std::cout << _name << " has " << _hp << " hp left" << std::endl;
        } else if (_hp <= 0){
            //std::cout << _name << " IS DEAD!" << std::endl;
        }
    }

    void loadEnemy(std::string enemyname){
        QString _enemyname = QString::fromStdString(enemyname);
        QSqlQuery query;
        query.prepare("SELECT * FROM enemy WHERE name = :name");
        query.bindValue(":name", _enemyname);
        if(query.exec() && query.next()){
            _name = query.value("name").toString().toStdString();
            _xpdrop = query.value("xpdrop").toInt();
            _hp = query.value("hp").toInt();
            _damage = query.value("damage").toInt();

            std::cout << "Enemy loaded succesfully" << std::endl;
        } else {
            std::cout << "Enemy could not load" << std::endl;
        }
    }
};
