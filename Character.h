#ifndef CHARACTER_H
#define CHARACTER_H
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <memory>
#include <vector>
#include <cstring>
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;

namespace mtm
{



class Character
{
protected:
typedef std::vector<std::vector<std::shared_ptr<Character>>> Board;
CharacterType type;
Team team;
units_t health;
units_t ammo;
units_t range;
units_t power;
friend class Game;
public:
Character(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power);
virtual ~Character() = default;
Character(const Character& character)=default;
Character& operator=(const Character& character) = delete;
virtual std::shared_ptr<Character> clone() const = 0;
virtual char letter() = 0;
virtual bool checkMove(int src_row,int src_col,int dst_row,int dst_col) = 0;
virtual bool checkAttackRange(int src_row,int src_col,int dst_row,int dst_col) = 0;
virtual bool checkAmmo(std::shared_ptr<Character> character) = 0;
virtual bool checkAttack(std::shared_ptr<Character> character) = 0;
virtual void reload() = 0;
virtual void attackInCell(std::shared_ptr<Character> character, int dst_row, int dst_col, Board& board) = 0;
virtual void attackOutOfCell(int src_row, int src_col, int dst_row, int dst_col, Board& board, int height, int width) = 0;
int getDistance (int src_row, int src_col, int dst_row, int dst_col);
Team getTeam();
units_t& getHealth();


};

}
#endif