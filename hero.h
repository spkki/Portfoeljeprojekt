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
#include <unistd.h>

class Hero
{
private:
    int _id;
    std::string _name;
    int _xp;
    int _level;
    int _hp;
    int _strength;
    int _gold;
    int _mana;
    std::vector<int> _moveIDs;

public:
    Hero(std::string name = "", int xp = 0, int level = 1, int hp = 10, int strength = 2, int gold = 0, int mana = 10){
        _id = -1;
        _name = name;
        _xp = xp;
        _level = level;
        _hp = hp;
        _strength = strength;
        _gold = gold;
        _mana = mana;
    }

    void setId(int id){
        _id = id;
    }

    int getId(){
        return _id;
    }

    void setName(std::string nameinput){
        _name = nameinput;
    }

    std::string getName(){
        return _name;
    }

    std::string printName(){
        typeText("Name: " + _name + "\n");
        //std::cout << "Name: " << _name << std::endl;
        return _name;
    }

    void setXp(int xp){
        _xp = xp;
    }

    int getXp(){
        typeText("XP: ");
        std::cout << _xp << std::endl;
        //std::cout << "xp: " << _xp << std::endl;
        return _xp;
    }

    void setLevel(int level){
        _level = level;
    }

    int getLevel()
    {
        typeText("Level: ");
        std::cout << _level << std::endl;
        //std::cout << "Level: " << _level << std::endl;
        return _level;
    }

    void setHp(int hp){
        _hp = hp;
    }

    int getHp(){
        return _hp;
    }

    int getHpStats(){
        typeText("HP: ");
        std::cout << _hp << std::endl;
        //std::cout << "hp: " << _hp << std::endl;
        return _hp;
    }

    void heal(){
        _hp = 8+_level*2;
    }

    void setStrength(int strength){
        _strength = strength;
    }

    int getStrength(){
        typeText("Strength: ");
        std::cout << _strength << std::endl;
        //std::cout << "Strength: " << _strength << std::endl;
        return _strength;
    }

    void setGold(int gold){
        _gold += gold;
    }

    int getGold(){
        typeText("Gold: ");
        std::cout << _gold << std::endl;
        return _gold;
    }

    void setMana(int mana){
        _mana = mana;
    }

    int getMana(){
        typeText("Mana: ");
        std::cout << _mana << std::endl;
        return _mana;
    }

    void addMove(int moveID){
        _moveIDs.push_back(moveID);
    }

    std::vector<int> getMoveIDs(){
        return _moveIDs;
    }

    int getStats(std::string name){
        _name = name;
        printName();
        getLevel();
        getXp();
        getHpStats();
        getStrength();
        getGold();
        getMana();
        return 0;
    }

    int getStats(){
        printName();
        getLevel();
        getXp();
        getHpStats();
        getStrength();
        getGold();
        getMana();
        return 0;
    }

    void takeDamage(int damage){
        _hp -= damage;
        if (_hp > 0) {
            typeText(_name + " has ");
            std::cout << _hp;
            typeText(" hp left\n");
            //std::cout << _name << " has " << _hp << " hp left" << std::endl; //Måske tilføje max hp
        } else if (_hp <= 0){
            //std::cout << _name << " IS DEAD!" << std::endl; //Removed because fightmethod handles it
        }
    }

    int dealDamage(){
        return _strength;
    }

    void gainXp(int xpGain){
        _xp += xpGain;
        if (_xp >= 1000 * _level) {
            levelUp();
        }
    }

    void levelUp(){
        _xp -= 1000 * _level;
        _hp += 2;
        _mana +=2;
        _strength += 1;
        _level++;
        typeText("You have leveled up. You are now level: ");
        std::cout << _level << std::endl;
        //std::cout << "You have leveled up. You are now level: " << _level << std::endl; //Add so it shows how much xp are required for next level.
    }

    void loadHero(std::string heroname){
        QSqlQuery query;
        query.prepare("SELECT * FROM hero WHERE name = :name");
        query.bindValue(":name", QString::fromStdString(heroname));
        if(query.exec() && query.next()){
            _id = query.value("id").toInt();
            _name = query.value("name").toString().toStdString();
            _xp = query.value("xp").toInt();
            _level = query.value("level").toInt();
            _hp = query.value("hp").toInt();
            _strength = query.value("strength").toInt();
            _gold = query.value("gold").toInt();
            _mana = query.value("mana").toInt();

            QSqlQuery moveQuery;
            moveQuery.prepare("SELECT move_id FROM hero_moves WHERE hero_id = :hero_id");
            moveQuery.bindValue(":hero_id", _id);
            if (moveQuery.exec()){
                _moveIDs.clear();
                while (moveQuery.next()){
                    _moveIDs.push_back(moveQuery.value(0).toInt());
                }
            }

            std::cout << "Hero loaded succesfully" << std::endl;
        } else {
            std::cout << "Hero could not load" << std::endl;
        }
    }

    void saveHero(){
        QSqlQuery query;
        if (_id == -1){ //If new hero
            query.prepare("INSERT INTO hero (name, xp, level, hp, strength, gold, mana) VALUES(:name, :xp, :level, :hp, :strength, :gold, :mana)");
        } else { //If hero already exists
            query.prepare("UPDATE hero SET xp = :xp, level = :level, hp = :hp, strength = :strength, gold = :gold, :mana = :mana WHERE id = :id");
            query.bindValue(":id", _id);
        }
        query.bindValue(":name", QString::fromStdString(_name));
        query.bindValue(":xp", _xp);
        query.bindValue(":level", _level);
        query.bindValue(":hp", _hp);
        query.bindValue(":strength", _strength);
        query.bindValue(":gold", _gold);
        query.bindValue(":mana,", _mana);

        if (!query.exec()){
            qDebug() << "Falied to save character: " << query.lastError().text();
        }
        qDebug() << "Character saved succesfully!";

        if (_id == -1){ //Only run if new character
            _id = query.lastInsertId().toInt();
        }

        //Savning moves on hero
        for (int moveID : _moveIDs){
            QSqlQuery moveQuery;
            moveQuery.prepare("INSERT INTO hero_moves (hero_id, move_id) VALUES (:hero_id, :move_id)");
            moveQuery.bindValue(":hero_id", _id);
            moveQuery.bindValue(":move_id", moveID);
        }

    }

    void deleteHero(std::string _name){
        QString name = QString::fromStdString(_name);

        QSqlQuery query;
        query.prepare("DELETE FROM hero WHERE name = :name");
        query.bindValue(":name", name);

        if (!query.exec()){
            qDebug() << "Failed to delete character: " << query.lastError().text();
        }
        qDebug() << "Character deleted succesfully!";
    }

    void typeText(std::string text){
        for (std::size_t i=0; i<text.size(); i++)
        {
            std::cout << text[i] << std::flush;
            usleep(30000); //60000 is default
        }
    }
};
