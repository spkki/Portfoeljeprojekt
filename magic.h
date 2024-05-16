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

    void puchaseMoves(int hero_id){
        QSqlDatabase database;
        openDatabase (database);
        QSqlQuery query;
        query.prepare("SELECT id, name, strength, selfdamage, manacost, element, goldcost FROM moves");
        if (query.exec()){
            std::vector<std::tuple<int, std::string, int, int, int, std::string, int >> moves; //Loads each move into a vector
            typeText("Avaliable moves for purchase: \n");
            //std::cout << "Avaliable moves for purchase: " << std::endl;
            int count = 1;
            while (query.next()){
                int id = query.value(0).toInt();
                std::string name = query.value(1).toString().toStdString();
                int strength = query.value(2).toInt();
                int selfdamage = query.value(3).toInt();
                int manacost = query.value(4).toInt();
                std::string element = query.value(5).toString().toStdString();
                int goldcost = query.value(6).toInt();
                moves.emplace_back(id, name, strength, selfdamage, manacost, element, goldcost);
                std::cout << count << ". " << name << "(Strength: " << strength << ", Selfdamage: " << selfdamage << ", Manacost: " << manacost << ", Element: " << element << ", Price: " << goldcost << ")" << std::endl; //Add other things into this statement
                count++;
            }
            int choice;
            typeText("Which one would you like to purchase (Enter 0 to exit): ");
            //std::cout << "Which one would you like to purchase: ";
            std::cin >> choice;

            if(choice > 0 && choice <= moves.size()){
                auto selectedMove = moves[choice - 1];
                int move_id = std::get <0>(selectedMove);
                _name = std::get <1>(selectedMove);
                _strength = std::get <2>(selectedMove);
                _selfdamage = std::get <3>(selectedMove);
                _manacost = std::get <4>(selectedMove);
                _element = std::get <5>(selectedMove);
                _goldcost = std::get <6>(selectedMove);
                typeText("You have purchased: " + _name + "\n");

                QSqlQuery moveQuery;
                moveQuery.prepare("INSERT INTO hero_moves (hero_id, move_id) VALUES (:hero_id, :move_id)");
                moveQuery.bindValue(":hero_id", hero_id);
                moveQuery.bindValue(":move_id", move_id);

                if(moveQuery.exec()){
                    typeText("Move purchased succesfully.\n");
                } else {
                    typeText("Falied to purchase move.\n");
                }

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
