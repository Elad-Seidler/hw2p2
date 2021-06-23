#include "Character.h"
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;


namespace mtm
{

Character::Character(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power)
{
    this->type=type;
    this->team=team;
    this->health=health;
    this->ammo=ammo;
    this->range=range;
    this->power=power;
}


/**Character::Character(const Character& character)
{
    this->type=character.type;
    this->team=character.team;
    this->health=character.health;
    this->ammo=character.ammo;
    this->range=character.range;
    this->power=character.power;
}**/

/**Character& Character::operator=(const Character& character)
{
    this->type=character.type;
    this->team=character.team;
    this->health=character.health;
    this->ammo=character.ammo;
    this->range=character.range;
    this->power=character.power;
    return *this;
}**/

  /**virtual std::shared_ptr<Character> Character::clone(Character character)
  {
   Character clone = new Character;
    clone->type = character.type;
    clone->team = character.team;
    clone->health = character.health;
    clone->ammo = character.ammo;
    clone->range = character.range;
    clone->power = character.power
  }**/

int Character::getDistance (int src_row, int src_col, int dst_row, int dst_col)
{
    int distance_x= src_row-dst_row;
    if (distance_x<0)
    {
        distance_x=distance_x*(-1);
    }
    int distance_y= src_col-dst_col;
    if (distance_y<0)
    {
        distance_y=distance_y*(-1);
    }
    return distance_x+distance_y;
}

Team Character::getTeam()
{
    return this->team;
}

units_t& Character::getHealth()
{
    return this->health;
}


}