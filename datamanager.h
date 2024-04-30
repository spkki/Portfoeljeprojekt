//
// Created by Svend on 23-04-2024.
//

#pragma once

#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>

bool openDatabase(QSqlDatabase& database){ //Open database function
    QSqlDatabase query;
    if(QSqlDatabase::contains()){
        database = QSqlDatabase::database();
        qDebug() << "Database being reused";
        return true;
    }

    database = QSqlDatabase::addDatabase("QSQLITE");
    //QString currentPath = QDir::currentPath();
    //qDebug() << "Current path:" << currentPath;
    database.setDatabaseName("../../database");

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
