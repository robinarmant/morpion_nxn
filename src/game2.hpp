#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <list>
#include <map>
#include <cmath>
#include <vector>

namespace game{
  typedef std::vector<int> Board;
  typedef std::vector<int> Spot; //trois composantes: le score, la ligne, la colonne à jouer
  typedef int size_board; // taille du côté du carré

  //constructeur de plateau
  inline Board board(size_board s){

    Board board;
    int number_spot = s*s;
    board.reserve(number_spot);
    for(int i=0;i<number_spot;i++)
    board.push_back(0);

    return board;


  }
  inline void printBoard(Board& board){
    std::cout << "* * * M O R P I O N * * *" << std::endl;
    std::cout<<"   ";
    int number_spot = board.size();
    int size_board = sqrt(number_spot);
    for (int i=0; i< size_board;i++)
    std::cout <<"--"<< i+1;

    std::cout<<"--"<<std::endl;
    for (int i = 0; i< size_board;i++){
      std::cout<< i+1 << " - ";
      for (int j = 0; j< size_board;j++){
        if(board[j+i*size_board]==-1){std::cout<<" 0 ";}
        else if(board[j+i*size_board]==1){std::cout<<" X ";}
        else{std::cout<<" * ";}
        //std::cout<< if(board[j+i]=-1){" O "}else if(board[j+i]=1){" X "}else{" * "};
      }
      std::cout<<" - "<<std::endl<<std::endl;
    }

  }

  inline Board play1(Board& board,int line, int row){
    Board new_board;
    int number_spot = board.size();
    int size_board = sqrt(number_spot);
    new_board = board;
    if(new_board[(row-1) + (line-1)*size_board]==0){

      new_board[(row-1) + (line-1)*size_board ] = -1;
      Board::iterator it;
      //test
      for (it=new_board.begin();it!=new_board.end();++it)
      std::cout<<*it<<" ";

      std::cout<<" "<<std::endl;

      return new_board;
    }else{std::cout<<"can't play here moron, anyway you lost your turn baaaaa"<<std::endl<<std::endl;return board;}

  }

  inline Spot findSpot(Board& board){
    std::vector<int> score;
    score.push_back(0);
    //variables temporaires pour la boucle
    std::vector<int> score_hor;
    score_hor.push_back(0);
    std::vector<int> score_ver;
    score_ver.push_back(0);
    std::vector<int> score_dia;
    score_dia.push_back(0);
    std::vector<int> h;
    std::vector<int> v;
    std::vector<int> d;
    h.push_back(0);
    v.push_back(0);
    d.push_back(0);

    int size_board = sqrt(board.size());
    //on va commencer par calculer le meilleur spot possible ver hor et dia et stocké les indices ou ce meilleur score est arrivé

    //on commence par le négatif pour la défense
    for(int i=0;i<size_board;i++){
      for(int j=0;j<size_board;j++){
        std::cout <<"j:"<<j<<std::endl;
        std::cout <<"i:"<<i<<std::endl;

        if(score_hor[0]>score_hor[0] + board[i+j]){

          score_hor[0]=score_hor[0] + board[i+j];
          std::cout<<"score horizontal " << score_hor[0]<<std::endl;
          score_hor.push_back(i);
          score_hor.push_back(j);
        }
        if(score_ver[0]> score_ver[0]  + board[ i+ j*size_board]){
          score_ver[0] = score_ver[0]  + board[ i+ j*size_board];
          std::cout<<"score vertical " << score_ver[0]<<std::endl;

          score_ver.push_back(i);
          score_ver.push_back(j);
          std::cout<<"dans la boucle ona mis dans score-ver "<<score_ver[1]<< " "<< score_ver[2]<<" avec un score de " << score_ver[0] << std::endl;


        }
        if(score_dia[0] > score_dia[0]  + board[(j+i)%size_board + j*size_board]){
          score_dia[0] = score_dia[0]  + board[(j+i)%size_board + j*size_board];
          std::cout<<"score diagonal " << score_dia[0]<<std::endl;

          score_dia.push_back(i);
          score_dia.push_back(j);
        }
      }
      if(h[0]>score_hor[0]){h=score_hor;}
      if(v[0]>score_ver[0]){v=score_ver;}
      std::cout<<"ona mis dans v "<<v[1]<< " "<< v[2]<<" avec un score de " << v[0] << std::endl;
      if(d[0]>score_dia[0]){d=score_dia;}
      score_hor[0]=0;
      score_ver[0]=0;
      score_dia[0]=0;

    }
    //stratégie de défense, on check d'abord si le joueur n'est pas à un coup de gagner

    if(h[0]==(1-size_board)){
      if(h[2]+1==size_board){ //si le j est le dernier spot de la ligne alors on place le spot juste avant la rangée
        h[2]=h[2]-abs(h[0]);
      }else{
        h[2]=h[2]+1;
      }
      return h;
    }

    if(v[0]==(1-size_board)){
      if(v[1]+1==size_board){ //si le j est le dernier spot de la ligne alors on place le spot juste avant la rangée
        v[1]=v[1]-abs(v[0]);
      }else{
        v[1]=v[1]+1;
      }
      return v;
    }

    if(d[0]==(1-size_board)){
      if(d[1]+1==size_board){ //si le j est le dernier spot de la ligne alors on place le spot juste avant la rangée
        d[1]=0;
        d[2]=0;
      }else{
        d[1]=size_board-1;
        d[2]=size_board-1;
      }
      return d;
    }
//stratégie d'attaque on recommence la boucle
h[0]=0;
v[0]=0;
d[0]=0;
for(int i=0;i<size_board;i++){
  for(int j=0;j<size_board;j++){
    /*std::cout <<"j:"<<j<<std::endl;
    std::cout <<"i:"<<i<<std::endl;*/

    if(score_hor[0]<score_hor[0] + board[i+j]){

      score_hor[0]=score_hor[0] + board[i+j];
      std::cout<<"score horizontal " << score_hor[0]<<std::endl;
      score_hor.push_back(i);
      score_hor.push_back(j);
    }
    if(score_ver[0]< score_ver[0]  + board[ i+ j*size_board]){
      score_ver[0] = score_ver[0]  + board[ i+ j*size_board];
      std::cout<<"score vertical " << score_ver[0]<<std::endl;

      score_ver.push_back(i);
      score_ver.push_back(j);
    }
    if(score_dia[0] < score_dia[0]  + board[(j+i)%size_board + j*size_board]){
      score_dia[0] = score_dia[0]  + board[(j+i)%size_board + j*size_board];
      std::cout<<"score diagonal " << score_dia[0]<<std::endl;

      score_dia.push_back(i);
      score_dia.push_back(j);
    }
  }
  if(h[0]<score_hor[0]){h=score_hor;}
  if(v[0]<score_ver[0]){v=score_ver;}
  if(d[0]<score_dia[0]){d=score_dia;}
  score_hor[0]=0;
  score_ver[0]=0;
  score_dia[0]=0;
}

if((h[0]>0)||(v[0]>0)||(d[0]>0)){
    score=d;//bonne stratégie diagonale uniquement si on est sur la diagonale du plateau
    if(score[1]!=score[2]){

      score=v;//on affecte le meilleur score vertical
      if(score[1]+1==size_board){ //si le i est le dernier spot de la colonne alors on place le spot juste avant la rangée
        score[1]=score[1]-score[0];
      }else{
        score[1]=score[1]+1;
      }

      if(score[0]<h[0]){
        score=h;
        if(score[2]+1==size_board){ //si le j est le dernier spot de la ligne alors on place le spot juste avant la rangée
          score[2]=score[2]-score[0];
        }else{
          score[2]=score[2]+1;
        }
      }

    }else if(score[1]==score[2]){
      if(score[1]+1==size_board){
        score[1]=score[1]-score[0];
        score[2]=score[2]-score[0];
      }else{
        score[1]=score[1]+1;
        score[2]=score[2]+1;
      }


    }

  }else{
    int j = 0;
    while(board[j]!=0){
      j++;
      std::cout<<"compteur du vecteur "<<j<<std::endl;
    }
    score[2]=j%size_board;
    //score[2]=1;
    //score[1]=1;
    std::cout<<"l'indice de colonne du score trouvé "<<score[2]<<std::endl;
    score[1]=(j-j%size_board)/size_board;
    std::cout<<"l'indice de ligne du score trouvé "<<score[1]<<std::endl;

  }
    std::cout<<"le score final trouvé est en "<<score[1]<<" "<<score[2]<<" avec un score de " << score[0]<<std::endl;
    return score;

  }




  inline Board play2(Board& board){
    Board new_board;
    new_board = board;
    int number_spot = board.size();
    int size_board = sqrt(number_spot);
    new_board = board;

    Spot goodSpot;
    std::cout<<"on récupère "<<findSpot(board)[1]<<" "<<findSpot(board)[2]<<std::endl;
    goodSpot = findSpot(board);
    std::cout<<"the spot i found is situated in "<< goodSpot[1] << " " << goodSpot[2] << "with a score of " << goodSpot[0] << std::endl;
    if(new_board[(goodSpot[2]) + (goodSpot[1])*size_board]==0){
      new_board[(goodSpot[2]) + (goodSpot[1])*size_board] = 1;

      Board::iterator it;
      //test
      for (it=new_board.begin();it!=new_board.end();++it)
      std::cout<<*it<<" ";

      std::cout<<" "<<std::endl;
      return new_board;
    }else{std::cout<<"can't play here moron, anyway you lost your turn baaaaa"<<std::endl<<std::endl;return board;}

  }

  inline int checkBoard(Board& board){

    int score_hor=0;
    int score_ver=0;
    int score_dia=0;
    int number_spot = board.size();
    int size_board = sqrt(number_spot);

    for(int i=0;i<size_board;i++){
      for(int j=0;j<size_board;j++){
        /*std::cout <<"j:"<<j<<std::endl;
        std::cout <<"i:"<<i<<std::endl;*/
        score_hor= score_hor + board[i+j];
        score_ver= score_ver + board[i+j*size_board];
        score_dia= score_dia + board[(j+i)%size_board+j*size_board];
        //std::cout<<"l'indice vaut"<<(j+i)%size_board+j*size_board<<std::endl;
        /*std::cout<<"le score diagonale vaut "<<score_dia<<std::endl;
        std::cout<<"le score horizontal vaut "<<score_hor<<std::endl;
        std::cout<<"le score vertical vaut "<<score_ver<<std::endl;
        std::cout<<"la size vaut "<<size_board<<std::endl;*/



        if(score_ver==size_board||(score_hor==size_board)||(score_dia==size_board)){
          /*std::cout<<"c'est la merde dude"<<std::endl;*/
          return 1;
        }else if((score_ver==-size_board)||(score_hor==-size_board)||(score_dia==-size_board)){
          return -1;
        }

      }
      score_hor=0;
      score_ver=0;
      score_dia=0;
    }
    return 0;
    score_hor=0;
    score_ver=0;
    score_dia=0;


    /*
    for(int i=0;i<dim-1;i++){
    for(int j=0;j<dim-1;i++){
    if(score==dim){
    throw 1;
    }else if(score== int(-dim)){
    throw -1;
    }else{
    score= score + board[j][(j+i)%dim];
    }
    }
    }
    score = 0;

    */
  }





  inline bool checkVictory1(Board& board){
    return (checkBoard(board)==-1);

  }

  inline bool checkVictory2(Board& board){
    return (checkBoard(board)==1);

  }

  inline bool checkNothing(Board& board){
    return (checkBoard(board)==0);

  }

}
