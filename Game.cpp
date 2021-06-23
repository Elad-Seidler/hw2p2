#include "Game.h"
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;

namespace mtm
{

Game::Game(int height, int width) : height(height), width(width)
    {
        if ((height<=0)||(width<=0))
        {
            throw IllegalArgument();
        }
        else
        {
            board.resize(height);
            for (auto& row: board)
            {
                row.assign(width, nullptr);
            }
        }
    }


void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
{
    int row=coordinates.row;
    int col=coordinates.col;
    if ((row<0)||(col<0))
    {
        throw IllegalCell();
    }
    if ((row>=height)||(col>=width))
    {
        throw IllegalCell();
    }
    if (board[row][col].get() != nullptr)
    {
        throw CellOccupied();
    }
    board[row][col] = character;
}

std::shared_ptr<Character>
Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power)
{
    if ((health<=0)||(type<0)||(team<0)||(health<0)||(ammo<0)||(range<0)||(power<0))
    {
        throw IllegalArgument();
    }
    if(type == SOLDIER)
    {
        return std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
    }
    else if(type == MEDIC)
    {
        return std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));
    }
    else if(type == SNIPER)
    {
        return std::shared_ptr<Character>(new Sniper(team, health,ammo,range,power));
    }
    else
    {
        throw IllegalArgument();
    }
    return nullptr;
}

void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    int src_row=src_coordinates.row;
    int src_col=src_coordinates.col;
    int dst_row=dst_coordinates.row;
    int dst_col=dst_coordinates.col;
    if ((src_row<0)||(src_col<0))
    {
        throw IllegalCell();
    }
     if ((dst_row<0)||(dst_col<0))
    {
        throw IllegalCell();
    }
    if ((src_row>=height)||(src_col>=width)||(dst_row>=height)||(dst_col>=width))
    {
        throw IllegalCell();
    }
    if (board[src_row][src_col]==NULL)
    {
        throw CellEmpty();
    }
    std::shared_ptr<Character> character= board[src_row][src_col];
    if (!character->checkMove(src_row, src_col, dst_row, dst_col))
    {
        throw MoveTooFar();
    }
    if (board[dst_row][dst_col]!=NULL)
    {
        throw CellOccupied();
    }
    board[dst_row][dst_col]=board[src_row][src_col];
    board[src_row][src_col]=NULL;   
}

void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    int src_row=src_coordinates.row;
    int src_col=src_coordinates.col;
    int dst_row=dst_coordinates.row;
    int dst_col=dst_coordinates.col;
    if ((src_row<0)||(src_col<0))
    {
        throw IllegalCell();
    }
     if ((dst_row<0)||(dst_col<0))
    {
        throw IllegalCell();
    }
    if ((src_row>=height)||(src_col>=width)||(dst_row>=height)||(dst_col>=width))
    {
        throw IllegalCell();
    }
    if (board[src_row][src_col]==NULL)
    {
        throw CellEmpty();
    }

    std::shared_ptr<Character> src_character=board[src_row][src_col];
    std::shared_ptr<Character> dst_character=board[dst_row][dst_col];
    if (!src_character->checkAttackRange(src_row, src_col, dst_row, dst_col))
    {
       throw OutOfRange();
    }
    if (!src_character->checkAttack(dst_character))
    {
        throw IllegalTarget();
    }
     if (!src_character->checkAmmo(dst_character))
    {
        throw OutOfAmmo();
    }
    src_character->attackInCell(dst_character,dst_row, dst_col,board);
    src_character->attackOutOfCell(src_row, src_col, dst_row, dst_col, board, height, width);
}

void Game::reload(const GridPoint & coordinates)
{
    int row=coordinates.row;
    int col=coordinates.col;
    if ((row>=height)||(col>=width))
    {
        throw IllegalCell();
    }
    if ((row<0)||(col<0))
    {
        throw IllegalCell();
    }
    if (board[row][col]==NULL)
    {
        throw CellEmpty();
    }
    std::shared_ptr<Character> character = board[row][col];
    character->reload();
}


std::ostream& operator<<(std::ostream& os, const Game& game)
{
    char* print_board = new char[game.width*game.height];
    for (int i = 0; i < game.height; i++)
    {
        for(int j = 0; j< game.width; j++)
         {
           if(game.board[i][j]==nullptr)
           {
               print_board[i*game.width+j]=' ';
           }
           else
           {
               print_board[i*game.width+j] = game.board[i][j]->letter();
           }
         }
     }
 printGameBoard(os, print_board, print_board+(game.width*game.height), game.width);
 delete[] print_board;
 return os;
}



bool Game::isOver(Team* winningTeam) const
{
    int counter_POWERLIFTERS=0;
    int counter_CROSSFITTERS=0;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            std::shared_ptr<Character> character= board[i][j];
            if (character==nullptr)
            {
                continue;
            }
            if (character->getTeam()==POWERLIFTERS) counter_POWERLIFTERS++;
            if (character->getTeam()==CROSSFITTERS) counter_CROSSFITTERS++;
        }
    }
    if ((counter_POWERLIFTERS==0)&&(counter_CROSSFITTERS>0))
    {
        if (winningTeam!=NULL)
        {
            *winningTeam=CROSSFITTERS;
        }
        return true;
    }
    if ((counter_CROSSFITTERS==0)&&(counter_POWERLIFTERS>0))
    {
        if (winningTeam!=NULL)
        {
            *winningTeam=POWERLIFTERS;
        }
        return true;
    }
    return false;
}

}
