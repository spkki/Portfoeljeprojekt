#pragma once
#include <iostream>
#include <unistd.h>
#include "datamanager.h"
#include "enemy.h"





class Cave
{
private:
    std::string _name;
    int _gold;

public:
    Cave(std::string name = "", int gold = 0){
        _name = name;
        _gold = gold;
    }

    std::string getName(){
        return _name;
    }

    void setName(std::string name){
        _name = name;
    }

    int getGold(){
        return _gold;
    }

    void setGold(int gold){
        _gold = gold;
    }

    void loadCave(){
        QSqlDatabase database;
        openDatabase (database);
        QSqlQuery query;
        query.prepare("SELECT name, gold FROM caves");
        if (query.exec()){
            typeText("Avaliable caves: \n");
            //std::cout << "Avaliable caves: " << std::endl;
            int count = 1;
            while (query.next()){
                std::string name = query.value(0).toString().toStdString();
                int gold = query.value(1).toInt();
                std::cout << count << ". " << name << " (Gold: " << gold << ")" << std::endl; //Add other things into this statement
                count++;
            }
            int choice;
            typeText("Choose your cave: ");
            //std::cout << "Choose your cave: ";
            std::cin >> choice;

            query.seek(choice-1);

            _name = query.value(0).toString().toStdString();
            _gold = query.value(1).toInt();
            }
        closeDatabase (database);
    }

    void typeText(std::string text){
        for (std::size_t i=0; i<text.size(); i++)
        {
            std::cout << text[i] << std::flush;
            usleep(30000); //default is 60000
        }
    }
};


