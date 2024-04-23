//
// Created by Svend on 22-04-2024.
//

#pragma once
#include "qsqlquery.h"
#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class Hero
{
private:
    std::string _name;
    int _xp;
    int _level;
    int _hp;
    int _strength;

public:
    Hero(std::string name = "", int xp = 0, int level = 1, int hp = 10, int strength = 2)
    {
        _name = name;
        _xp = xp;
        _level = level;
        _hp = hp;
        _strength = strength;
    }

    void setName(std::string nameinput) { _name = nameinput; };

    std::string getName()
    {
        return _name;
    };

    void setXp(int xp) { _xp = xp; }

    int getXp()
    {
        std::cout << "xp: " << _xp << std::endl;
        return _xp;
    }

    void setLevel(int level) { _level = level; }

    int getLevel()
    {
        std::cout << "Level: " << _level << std::endl;
        return _level;
    }

    void setHp(int hp) { _hp = hp; }

    int getHp()
    {
        std::cout << "hp: " << _hp << std::endl;
        return _hp;
    }

    void setStrength(int strength) { _strength = strength; }

    int getStrength()
    {
        std::cout << "Strength: " << _strength << std::endl;
        return _strength;
    }

    void takeDamage(int damage)
    {
        _hp -= damage;
        if (_hp > 0) {
            std::cout << _name << " has " << _hp << " hp left" << std::endl;
        } else {
            std::cout << _name << " IS DEAD!" << std::endl;
        }
    }

    void dealDamage(int damage) { _strength = damage; }

    void gainXp(int xpGain)
    {
        _xp += xpGain;
        if (_xp >= 1000 * _level) {
            levelUp();
        }
    }

    void levelUp()
    {
        _xp -= 1000 * _level;
        _hp += 2;
        _strength += 1;
        _level++;
        std::cout << "You have leveled up. You are now level: " << _level
                  << std::endl; //Add so it shows how much xp are required for next level.
    }

    void loadHero(std::string heroname){
        QString _heroname = QString::fromStdString(heroname);
        QSqlQuery query;
        query.prepare("SELECT * FROM hero WHERE name = :name");
        query.bindValue(":name", _heroname);
        if(query.exec() && query.next()){
            _name = query.value("name").toString().toStdString();
            _xp = query.value("xp").toInt();
            _level = query.value("level").toInt();
            _hp = query.value("hp").toInt();
            _strength = query.value("strength").toInt();

            std::cout << "Hero loaded succesfully" << std::endl;
        } else {
            std::cout << "Hero could not load" << std::endl;
        }
    }

    void saveHero(){
        QString name = QString::fromStdString(_name);

        QSqlQuery query;
        query.prepare("INSERT INTO hero (name, xp, level, hp, strength) VALUES(:name, :xp, :level, :hp, :strength)");
        query.bindValue(":name", name);
        query.bindValue(":xp", _xp);
        query.bindValue(":level", _level);
        query.bindValue(":hp", _hp);
        query.bindValue(":strength", _strength);

        if (!query.exec()){
            qDebug() << "Falied to save character: " << query.lastError().text();
        }
        qDebug() << "Character saved succesfully!";
    }

    void deleteHero(){
        QString name = QString::fromStdString(_name);

        QSqlQuery query;
        query.prepare("DELETE FROM hero WHERE name = :name");
        query.bindValue(":name", name);

        if (!query.exec()){
            qDebug() << "Failed to delete character: " << query.lastError().text();
        }
        qDebug() << "Character deleted succesfully!";
    }
};
