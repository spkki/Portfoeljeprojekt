#pragma ONCE
#include "qsqlquery.h"
#include "datamanager.h"
#include "hero.h"
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
    int _id;
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

    void setName(std::string name){
        _name = name;
    }

    std::string getName(){
        return _name;
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

    bool checkPrerequisites(int move_id, int hero_id) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM move_requirements WHERE move_id = :move_id AND requirement_id NOT IN (SELECT move_id FROM hero_moves WHERE hero_id = :hero_id)");
        query.bindValue(":move_id", move_id);
        query.bindValue(":hero_id", hero_id);

        if (query.exec() && query.next()) {
            int missingRequirementsCount = query.value(0).toInt();
            return missingRequirementsCount == 0;
        }

        return false; // Error occurred or no result
    }

    void puchaseMoves(int hero_id, Hero& currentHero){
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

                if (!currentHero.hasMove(id) && checkPrerequisites(id, hero_id)) {
                    moves.emplace_back(id, name, strength, selfdamage, manacost, element, goldcost);
                    std::cout << count << ". " << name << " (Strength: " << strength << ", Selfdamage: " << selfdamage << ", Manacost: " << manacost << ", Element: " << element << ", Price: " << goldcost << ")" << std::endl;
                    count++;
                }
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

                if(_goldcost <= currentHero.getGold()){
                    currentHero.setGold(- _goldcost);

                    QSqlQuery moveQuery;
                    moveQuery.prepare("INSERT INTO hero_moves (hero_id, move_id) VALUES (:hero_id, :move_id)");
                    moveQuery.bindValue(":hero_id", hero_id);
                    moveQuery.bindValue(":move_id", move_id);

                    if(moveQuery.exec()){
                        typeText("You have purchased: " + _name + "\n");
                    } else {
                        typeText("Falied to purchase move.\n");
                        //If insuffecient fund refund
                        currentHero.setGold(_goldcost);
                    }
                } else {
                    typeText("Not enough gold to purchase this move. \n");
                }
            } else {
                typeText("Invalid choice. No move purchased.");
            }
            closeDatabase (database);
        }
    }

    void loadMagicBattle(int hero_id){
        QSqlDatabase database;
        openDatabase(database);
        QSqlQuery query;
        query.prepare(
            "SELECT moves.id, moves.name, moves.strength, moves.selfdamage, moves.manacost, moves.element "
            "FROM moves "
            "JOIN hero_moves ON moves.id = hero_moves.move_id "
            "WHERE hero_moves.hero_id = :hero_id"
            );
        query.bindValue(":hero_id", hero_id);

        if(query.exec()){
            std::cout << "Available Moves: " << std::endl;
            int count = 1;
            while(query.next()){
                int id = query.value(0).toInt();
                std::string name = query.value(1).toString().toStdString();
                int strength = query.value(2).toInt();
                int selfdamage = query.value(3).toInt();
                int manacost = query.value(4).toInt();
                std::string element = query.value(5).toString().toStdString();

                std::cout << "(" << count << ") Move: " << name << " With: " << strength << " Strength, " << selfdamage << " Self-damage, " << manacost << " Manacost. It is: " << element << " Type " << std::endl;
                count++;
            }

            int choice;
            std::cout << "Pick a move: ";
            std::cin >> choice;

            // Reset the query to the first row
            if (query.seek(choice - 1)) {
                _id = query.value(0).toInt();
                _name = query.value(1).toString().toStdString();
                _strength = query.value(2).toInt();
                _selfdamage = query.value(3).toInt();
                _manacost = query.value(4).toInt();
                _element = query.value(5).toString().toStdString();
            } else {
                std::cout << "Invalid choice." << std::endl;
            }
        } else {
            qDebug() << "Failed to load player moves:" << query.lastError().text();
        }

        closeDatabase(database);
    }


    void typeText(std::string text){
        for (std::size_t i=0; i<text.size(); i++)
        {
            std::cout << text[i] << std::flush;
            usleep(30000); //60000 is default
        }
    }
};
