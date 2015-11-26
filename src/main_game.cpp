#include <iostream>
#include <string>
#include "game2.hpp"

int main(){

  game::Board board;
  board=game::board(4);
  std::cout<<"let's play Morpion duuudes!"<<std::endl;
  game::printBoard(board);
  int line;
  int row;
  //if(game::checkNothing(board)){std::cout<<"le checkNothing est à true"<<std::endl;}
  while(game::checkNothing(board)){
    std::cout<<"Dude, play now !"<<std::endl;
    std::cout<<"Enter a line sir :"<<std::endl;
    std::cin>>line;
    std::cout<<"Now enter a row Dude :"<<std::endl;
    std::cin>>row;
    board = game::play1(board,line,row);
    game::printBoard(board);
    if(game::checkVictory1(board))
    break;

    std::cout<<"I play now, gonna kick your moron ass"<<std::endl;
    board = game::play2(board);
    game::printBoard(board);
    std::cout<<"What do you think of that, smart ass?"<<std::endl;
    if(game::checkVictory2(board))
    break;



  }
  if(game::checkVictory1(board)){std::cout << "Dude wins!"<< std::endl <<std::endl;}
  if(game::checkVictory2(board)){std::cout << "I win"<< std::endl <<std::endl;}
  std::cout << "M O R P I O N * * * * * *" << std::endl;
  std::cout << "* M O R P I O N * * * * *" << std::endl;
  std::cout << "* * M O R P I O N * * * *" << std::endl;
  std::cout << "* * * M O R P I O N * * *" << std::endl;
  std::cout << "* * * * M O R P I O N * *" << std::endl;
  std::cout << "* * * * * M O R P I O N *" << std::endl;
  std::cout << "* * * * * * M O R P I O N" << std::endl;


}
