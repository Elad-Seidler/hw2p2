#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <cstring>
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <memory>
#include <vector>

namespace mtm
{ 
    typedef std::vector<std::vector<std::shared_ptr<Character>>> Board;
    typedef std::vector<std::vector<char>> PrintBoard;


class Game
{
    int height;
    int width;
    Board board;
    friend class Character;

    public:
    Game(int height, int width);
    ~Game()=default;
    Game(const Game& other)=default;
    Game& operator=(const Game& other)=default;
    void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
    static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power);
    void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
    void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
    void reload(const GridPoint & coordinates);
    bool isOver(Team* winningTeam=NULL) const;
    friend std::ostream& operator<<(std::ostream &os, const Game& game);

};

}

#endif