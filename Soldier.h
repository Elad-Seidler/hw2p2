#ifndef SOLDIER_H
#define SOLDIER_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Game.h"
#include <memory>
#include <vector>



namespace mtm
{


class Soldier : public Character
{
    public:
    Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power):Character(SOLDIER, team, health, ammo, range, power){}
    ~Soldier()=default;
    Soldier(const Soldier&)=default;
    Soldier& operator=(const Soldier& soldier)=delete;
    std::shared_ptr<Character> clone() const override;
    char letter() override;
    bool checkMove(int src_row, int src_col, int dst_row, int dst_col) override;
    void reload() override;
    bool checkAttackRange(int src_row, int src_col, int dst_row, int dst_col) override;
    bool checkAmmo(std::shared_ptr<Character> character) override;
    bool checkAttack(std::shared_ptr<Character> character) override;
    void attackInCell(std::shared_ptr<Character> character, int dst_row, int dst_col, Board& board) override;
    void attackOutOfCell(int src_row, int src_col, int dst_row, int dst_col, Board& board, int height, int width) override;
};
}




#endif
