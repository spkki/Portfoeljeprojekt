cmake_minimum_required(VERSION 3.27)
project(Portfoeljeprojekt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

add_executable(Portfoeljeprojekt main.cpp
        hero.h
        enemy.h
        datamanager.h
        mainMenu.h)

target_link_libraries(Portfoeljeprojekt Qt5::Core Qt5::Quick Qt5::Sql)

include(GNUInstallDirs)
install(TARGETS Portfoeljeprojekt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
