#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int Height = 20;
const int Width = 40;
bool GameOver;
int x,y,fx,fy,score;
enum direction {STOP, LEFT, RIGHT, UP, DOWN};
direction dir;
int tx[100],ty[100],nt=0;
char f='0';

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
      if(j==0 || j==Width-1){
        printf("#");
        continue;
      }
      if(i==x && j==y){
        printf("%c",f);
        continue;
      }
      else if(i==fx && j==fy){
        printf("$");
        continue;
      }
      int check=0;
      for(int k=0;k<nt;k++){
        if(tx[k]==i && ty[k]==j){
          printf("o");
          check=1;
        }
      }
      if(check==0)
        printf(" ");
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
  int oldx,oldy,temp;
  if(nt>1){
    oldx=tx[0];
    oldy=ty[0];
    tx[0]=x;
    ty[0]=y;
    for(int i=1;i<nt;i++){
      temp=tx[i];
      tx[i]=oldx;
      oldx=temp;
      temp=ty[i];
      ty[i]=oldy;
      oldy=temp;
    }
  }
  else if(nt==1){
    tx[0]=x;
    ty[0]=y;
  }
  switch(dir){
    case LEFT:{
      y--;
      //f='<';
      break;
    }
    case RIGHT:{
      y++;
      //f='>';
      break;
    }
    case UP:{
      x--;
      //f='^';
      break;
    }
    case DOWN:{
      x++;
      //f='*';
      break;
    }
    case STOP:
      break;
  }
  if(x==fx && y==fy){
    score+=10;
    nt++;
    fx = rand() % Height;
    if(fx<=0 || fx>=Height-1)
      fx=Height/2;
    fy = rand() % Width;
    if(fy<=0 || fy>=Width-1)
      fy=Width/2;
  }
  if(x==0 || x==Height-1 || y==0 || y==Width-1)
    GameOver=true;
  for(int i=0;i<nt;i++){
    if(tx[i]==x && ty[i]==y)
      GameOver=true;
  }
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
