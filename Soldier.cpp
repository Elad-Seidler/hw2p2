#include "Soldier.h"
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;
#include <cmath>


namespace mtm
{


char Soldier::letter()
{
    if (this->team == POWERLIFTERS )
    {
      return 'S';
    }
    else 
    {
      return 's';
    }
}

bool Soldier::checkMove(int src_row, int src_col, int dst_row, int dst_col)
{
    if (Character::getDistance(src_row, src_col,dst_row, dst_col)>3)
    {
        return false;
    }
    return true;
}

void Soldier::reload()
{
    this->ammo+=3;
}

bool Soldier::checkAttackRange(int src_row, int src_col, int dst_row, int dst_col)
{
    if (((src_row!=dst_row)&&(src_col!=dst_col))||
    (Character::getDistance(src_row, src_col,dst_row, dst_col)>this->range))
    {
        return false;
    }
    return true;
}

bool Soldier::checkAmmo(std::shared_ptr<Character> character)
{
    if (this->ammo-1<0)
    {
        return false;
    }
    return true;
}

bool Soldier::checkAttack(std::shared_ptr<Character> character)
{
    return true;
}

void Soldier::attackInCell(std::shared_ptr<Character> character, int dst_row, int dst_col, Board& board)
{
    this->ammo=this->ammo-1;
    if (character==NULL)
    {
        return;
    } 
    if (this==character.get())
    {
        return;
    }
    else
    {
        character->getHealth()=(character->getHealth())-this->power;
        if (character->getHealth()<=0)
        {
            board[dst_row][dst_col].reset();
        }
    }
}

void Soldier::attackOutOfCell(int src_row, int src_col, int dst_row, int dst_col, Board& board, int height, int width)
{
    double rng = (this->range)/3.0;
    rng=std::ceil(rng);
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (Character::getDistance(dst_row, dst_col, i, j)>rng)
            {
                continue;
            }
            if (board[i][j]==NULL)
            {
                continue;
            }
            std::shared_ptr<Character> character = board[i][j];
            if (this==character.get())
            {
                continue;
            }
            if (this->team==character->getTeam())
            {
                continue;
            }
            double damage=(this->power)/2.0;
            character->getHealth()-=std::ceil(damage);
            if (character->getHealth()<=0)
            {
                board[i][j].reset();
            }
        }
    }
}


std::shared_ptr<Character> Soldier::clone() const 
{
 return std::shared_ptr<Soldier>(new Soldier(this->team, this->health, this->ammo, this->range, this->power));
}



}










