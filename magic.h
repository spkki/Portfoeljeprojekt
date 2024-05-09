#pragma ONCE
#include "qsqlquery.h"
#include "datamanager.h"
#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <unistd.h>
#include <vector>

class Magic
{
private:
    std::string _name;
    int _strength;
    int _selfdamage;
    int _manacost;
    std::string _element;
    int _goldcost;

public:

    Magic(std::string name = "", int strength = 0, int selfdamage = 0, int manacost = 0, std::string element = "Typeless", int goldcost = 0){
        _name = name;
        _strength = strength;
        _selfdamage = selfdamage;
        _manacost = manacost;
        _element = element;
        _goldcost = goldcost;
    }

    void setStrength(int strength){
        _strength = strength;
    }

    int getStrength(){
        return _strength;
    }

    void setSelfdamage(int selfdamage){
        _selfdamage = selfdamage;
    }

    int getSelfdamage(){
        return _selfdamage;
    }

    void setManacost(int manacost){
        _manacost = manacost;
    }

    int getManacost(){
        return _manacost;
    }

    void setElement(std::string element){
        _element = element;
    }

    std::string getElement(){
        return _element;
    }

    void loadMoves(){
        QSqlDatabase database;
        openDatabase (database);
        QSqlQuery query;
        query.prepare("SELECT name, strength, selfdamage, manacost, element, goldcost FROM moves");
        if (query.exec()){
            std::vector<std::tuple<std::string, int, int, int, std::string, int >> moves; //Loads each move into a vector
            typeText("Avaliable moves for purchase: \n");
            //std::cout << "Avaliable moves for purchase: " << std::endl;
            int count = 1;
            while (query.next()){
                std::string name = query.value(0).toString().toStdString();
                int strength = query.value(1).toInt();
                int selfdamage = query.value(2).toInt();
                int manacost = query.value(3).toInt();
                std::string element = query.value(4).toString().toStdString();
                int goldcost = query.value(5).toInt();
                moves.emplace_back(name, strength, selfdamage, manacost, element, goldcost);
                std::cout << count << ". " << name << "(Strength: " << strength << ", Selfdamage: " << selfdamage << ", Manacost: " << manacost << ", Element: " << element << ", Price: " << goldcost << ")" << std::endl; //Add other things into this statement
                count++;
            }
            int choice;
            typeText("Which one would you like to purchase (Enter 0 to exit): ");
            //std::cout << "Which one would you like to purchase: ";
            std::cin >> choice;

            if(choice > 0 && choice <= moves.size()){
                std::tuple<std::string, int, int, int, std::string, int> selectedMove = moves[choice-1];
                _name = std::get <0>(selectedMove);
                _strength = std::get <1>(selectedMove);
                _selfdamage = std::get <2>(selectedMove);
                _manacost = std::get <3>(selectedMove);
                _element = std::get <4>(selectedMove);
                _goldcost = std::get <5>(selectedMove);
                typeText("You have purchased: " + _name + "\n");
            } else {
                typeText("Invalid choice. No move purchased.");
            }
            closeDatabase (database);
        }
    }

    void typeText(std::string text){
        for (std::size_t i=0; i<text.size(); i++)
        {
            std::cout << text[i] << std::flush;
            usleep(30000); //60000 is default
        }
    }
};
