#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

const int Height = 20;
const int Width = 40;
bool GameOver;
int x,y,fx,fy,score;
enum direction {STOP, LEFT, RIGHT, UP, DOWN};
direction dir;

void setup()
{
  GameOver = false;
  x = Height/2;
  y = Width/2;
  fx = rand() % Height;
  fy = rand() % Width;
  dir = STOP;
  score=0;
}

void draw()
{
  system("clear");
  for(int i=0;i<Width;i++){
    printf("#");
  }
  printf("\n");
  for(int i=1;i<Height-1;i++){
    for(int j=0;j<Width;j++){
      //print snake head
      if(i==x && j==y){
        printf("O");
      }
      else if(i==fx && j==fy)
        printf("@");
      else{
        if(j==0 || j==Width-1)
          printf("#");
        else
          printf(" ");
      }
    }
    printf("\n");
  }
  for(int i=0;i<Width;i++){
    printf("#");
  }
  printf("\n");
}

//controls are w(up),a(left),s(down),d(right)
void input()
{
  system("stty raw");
  char press=getchar();
  system("stty cooked");
  switch(press){
    case 'a':{
      dir=LEFT;
      break;
    }
    case 'w':{
      dir=UP;
      break;
    }
    case 'd':{
      dir=RIGHT;
      break;
    }
    case 's':{
      dir=DOWN;
      break;
    }
    default:
      dir=STOP;
  }
}

void logic()
{
  switch(dir){
    case LEFT:
      y--;
      break;
    case RIGHT:
      y++;
      break;
    case UP:
      x--;
      break;
    case DOWN:
      x++;
      break;
    case STOP:
      break;
  }
  if(x==fx && y==fy){
    score+=10;
    fx = rand() % Height;
    if(fx<=0 || fx>=Height-1)
      fx=Height/2;
    fy = rand() % Width;
    if(fy<=0 || fy>=Width-1)
      fy=Width/2;
  }
  if(x==0 || x==Height || y==0 || y==Width)
    GameOver=true;
}

int main()
{
  setup();
  while(!GameOver){
    draw();
    printf("Score : %d\n",score);
    input();
    logic();
  }
  printf("\nGAME OVER");
  return 0;
}
