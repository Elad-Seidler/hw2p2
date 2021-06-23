#include "Character.h"
#include "Auxiliaries.h"
#include "Medic.h"
#include <iostream>
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;

namespace mtm
{



/**Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power):Character(MEDIC, team, health, ammo, range, power){};
Medic::~Medic()=default;
Medic::Medic(const Medic& Medic):Character(const Character& character);
Medic& Medic::operator=(const  Medic&  Medic):Character& operator=(const Character& character);**/

char Medic::letter()
{
    if (this->team == POWERLIFTERS )
    {
      return 'M';
    }
    else
    {
      return 'm';
    }
}

bool Medic::checkMove(int src_row, int src_col, int dst_row, int dst_col)
{
    if (Character::getDistance(src_row, src_col, dst_row, dst_col)>5)
    {
        return false;
    }
    return true;
}

void Medic::reload()
{
    this->ammo+=5;
}

bool Medic::checkAttackRange(int src_row, int src_col, int dst_row, int dst_col)
{
  if (Character::getDistance(src_row, src_col, dst_row, dst_col)>this->range)
    {
        return false;
    }
  return true;
}

 bool Medic::checkAmmo(std::shared_ptr<Character> character)
{
  if (this->team==character->getTeam())
  {
    if (this->ammo>0)
    {
      return true;
    }
    return false;
  }
  else
  {
    if (this->ammo-1>=0)
    {
      return true;
    }
    return false;
  }
  
}

bool Medic::checkAttack(std::shared_ptr<Character> character)
{
  if (character==NULL)
  {
    return false;
  }
  return true;
}

void Medic::attackInCell(std::shared_ptr<Character> character, int dst_row, int dst_col, Board& board)
{
    if (this==character.get())
    {
      throw IllegalTarget();
    }
    if (character->getTeam()==this->team)
    {
      character->getHealth()+=this->power;
    }
    else
    {
      this->ammo--;
      character->getHealth()-=this->power;
      if (character->getHealth()<=0)
      {
        board[dst_row][dst_col].reset();
      }
    }
}

void Medic::attackOutOfCell(int src_row, int src_col, int dst_row, int dst_col, Board& board, int height, int width)
{
    return;
}

std::shared_ptr<Character> Medic::clone() const 
{
 return std::shared_ptr<Medic>(new Medic(this->team, this->health, this->ammo, this->range, this->power));
}


}





