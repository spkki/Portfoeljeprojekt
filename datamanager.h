//
// Created by Svend on 23-04-2024.
//

#pragma once

#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

bool openDatabase(QSqlDatabase& database){ //Open database function
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("/home/spkki/workspace/software-udvikling/portfolio/Portfoeljeprojekt/database");

    if (!database.open()){
        qWarning() << "Could not open database:" << database.lastError().text();
        return false;
    }

    qDebug() << "Database succesfully opened";
    return true;
}

void closeDatabase(QSqlDatabase& database){
    database.close();
    qDebug() << "Database succesfully closed";
}
