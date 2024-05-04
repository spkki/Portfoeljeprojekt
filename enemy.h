//
// Created by Svend on 22-04-2024.
//

#pragma once
#include "hero.h"
#include "datamanager.h"
#include <vector>

class Enemy
{
private:
    std::string _name;
    int _damage;
    int _xpdrop;
    int _hp;
    int _ammount;
    Hero currentHero;

public:
    Enemy(){};

    Enemy(std::string name, int hp, int damage, int xpdrop, int ammount = 1):_name(name), _damage(damage), _xpdrop(xpdrop), _hp(hp), _ammount(ammount){}

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

    int getAmmount(){
        return _ammount;
    }

    void setAmmount(int ammount){
        _ammount = ammount;
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

    void loadEnemy(){
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
        }
    }

    void loadCaveEnemy(std::string caveName){
        QSqlDatabase database;
        openDatabase (database);
        QString _caveName = QString::fromStdString(caveName);
        QSqlQuery query;
        query.prepare("SELECT enemy.name, enemy.hp, enemy.damage, enemy.xpdrop, cave_enemies.ammount FROM enemy JOIN cave_enemies ON enemy.id = cave_enemies.enemy_id JOIN caves ON cave_enemies.cave_id = caves.id WHERE caves.name = :name");
        query.bindValue(":name", _caveName);

        if (query.exec()){
            currentHero.typeText("Avaliable enemies in " + _name + ": \n");
            //std::cout << "Avaliable enemies: " << std::endl;
            int count = 1;
            while (query.next()){
                std::string name = query.value(0).toString().toStdString();
                int hp = query.value(1).toInt();
                int damage = query.value(2).toInt();
                int xpdrop = query.value(3).toInt();
                int ammount = query.value(4).toInt();

                std::cout << count << ". " << name << " (HP: " << hp << ", Damage: " << damage << ", XP Drop: " << xpdrop << ", Ammount: " << ammount << ")" << std::endl; //Add other things into this statement
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
            _ammount = query.value(4).toInt();
        }
    }

    //Tried to make it a vector instead to make it possible to fight different enemies in a cave
    std::vector<Enemy> loadCaveEnemyVector(std::string caveName, Enemy& choosenEnemy){
        std::vector<Enemy> enemies;
        QSqlDatabase database;
        openDatabase (database);
        QString _caveName = QString::fromStdString(caveName);
        QSqlQuery query;
        query.prepare("SELECT enemy.name, enemy.hp, enemy.damage, enemy.xpdrop, cave_enemies.ammount FROM enemy JOIN cave_enemies ON enemy.id = cave_enemies.enemy_id JOIN caves ON cave_enemies.cave_id = caves.id WHERE caves.name = :name");
        query.bindValue(":name", _caveName);

        if (query.exec()){
            currentHero.typeText("Avaliable enemies in " + _name + ": \n");
            //std::cout << "Avaliable enemies: " << std::endl;
            int count = 1;
            while (query.next()){
                std::string name = query.value(0).toString().toStdString();
                int hp = query.value(1).toInt();
                int damage = query.value(2).toInt();
                int xpdrop = query.value(3).toInt();
                int ammount = query.value(4).toInt();
                enemies.push_back(Enemy(name,hp,damage,xpdrop,ammount));


                std::cout << count << ". " << name << " (HP: " << hp << ", Damage: " << damage << ", XP Drop: " << xpdrop << ", Ammount: " << ammount << ")" << std::endl; //Add other things into this statement
                count++;
            }

            int choice;
            currentHero.typeText("Choose your enemy: ");
            std::cin >> choice;
            // Make sure choice is within bounds
            if (choice > 0 && choice <= enemies.size()) {
                // Subtract 1 because vector indices start from 0
                choosenEnemy = enemies[choice - 1];
            } else {
                currentHero.typeText("Invalid choice.\n");
            }

        }
        closeDatabase (database);
        return enemies;
    }

};
