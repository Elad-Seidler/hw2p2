#include "Sniper.h"
#include <iostream>
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;


namespace mtm
{

 char Sniper::letter()
   {
    if (this->team == POWERLIFTERS )
    {
      return 'N';
    }
    else
    {
      return 'n';
    }
   }

bool Sniper::checkMove(int src_row, int src_col, int dst_row, int dst_col)
{
    if (Character::getDistance(src_row, src_col,dst_row, dst_col)>4)
    {
        return false;
    }
    return true;
}

void Sniper::reload()
{
    this->ammo+=2;
}

bool Sniper::checkAttackRange(int src_row, int src_col, int dst_row, int dst_col)
{
    if ((Character::getDistance(src_row, src_col,dst_row, dst_col)<(this->range)/2)||
    (Character::getDistance(src_row, src_col,dst_row, dst_col)>this->range))
    {
        return false;
    }
    return true;
}

bool Sniper::checkAmmo(std::shared_ptr<Character> character)
{
    if (this->ammo-1<0)
    {
        return false;
    }
    return true;
}

bool Sniper::checkAttack(std::shared_ptr<Character> character)
{
  if (character==nullptr)
  {
    return false;
  }
  if (character->getTeam()==this->team)
  {
    return false;
  }
  return true;
}

void Sniper::attackInCell(std::shared_ptr<Character> character, int dst_row, int dst_col, Board& board)
{
    this->ammo=this->ammo-1;
    this->counter_attack++;
    if (this->counter_attack%3==0)
    {
      character->getHealth()-=(this->power)*2;
    }
    else
    {
      character->getHealth()-=this->power;
    }
    if (character->getHealth()<=0)
    {
      board[dst_row][dst_col].reset();
    }
}

void Sniper::attackOutOfCell(int src_row, int src_col, int dst_row, int dst_col, Board& board, int height, int width)
{
  return;
}


std::shared_ptr<Character> Sniper::clone() const 
{
  return std::shared_ptr<Sniper>(new Sniper(this->team, this->health, this->ammo, this->range, this->power));
}

}