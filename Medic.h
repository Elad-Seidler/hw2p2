#ifndef MEDIC_H
#define MEDIC_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <memory>
#include <vector>
#include "Game.h"

namespace mtm
{


//enum Team { POWERLIFTERS, CROSSFITTERS };
//enum CharacterType {SOLDIER, MEDIC, SNIPER};
//typedef int units_t;


class Medic : public Character
{
  public:

  Medic(Team team, units_t health, units_t ammo, units_t range, units_t power):Character(MEDIC, team, health, ammo, range, power){}
  ~Medic()=default;
  Medic(const Medic& Medic)=default;
  Medic& operator=(const  Medic&  Medic)=delete;
  std::shared_ptr<Character> clone() const override;
  char letter() override;
  bool checkMove(int src_row, int src_col, int dst_row, int dst_col) override;
  void reload() override;
  bool checkAttackRange(int src_row, int src_col, int dst_row, int dst_col)override;
  bool checkAmmo(std::shared_ptr<Character> character) override;
  bool checkAttack(std::shared_ptr<Character> character) override;
  void attackInCell(std::shared_ptr<Character> character, int dst_row, int dst_col, Board& board) override;
  void attackOutOfCell(int src_row, int src_col, int dst_row, int dst_col, Board& board, int height, int width) override;

};

}
#endif