#include <iostream>
#include <ctime>
#include <cstdlib>

#define SUIT_NER 3

using namespace std;

void delay(int i)
{
	time_t t;
	t = clock();
	while (clock() - t < ((i * CLOCKS_PER_SEC)/1000));
}
struct Cell {
  int x, y;
  char live;
} cell[32][32];

struct AXES {
  int x;
  int y;
};

int num = 1;

void out() {
  for (int x = 0; x < 32; x++) {
    for (int y = 0; y < 32; y++) {
      if (cell[x][y].live == 't') {
        cout << "■ ";
      } else
        cout << "□ ";
    }
    cout << endl;
  }
  cout << num<<endl;
  num++;
}

void init_cell() {
	srand(time(NULL));
  for (int x = 0; x < 32; x++) {
    for (int y = 0; y < 32; y++) {
      cell[x][y].x = x;
      cell[x][y].y = y;
      if (rand() % 2) {
        cell[x][y].live = 't';
      } else
        cell[x][y].live = 'f';
    }
  }
}

int check_cell(Cell cell[][32], int cx, int cy) {
  int ner_live = 0;
  
  AXES ner[8];
  
  ner[0].x = cell[cx][cy].x - 1;
  ner[0].y = cell[cx][cy].y - 1;

  ner[1].x = cell[cx][cy].x - 1;
  ner[1].y = cell[cx][cy].y;

  ner[2].x = cell[cx][cy].x - 1;
  ner[2].y = cell[cx][cy].y + 1;

  ner[3].x = cell[cx][cy].x;
  ner[3].y = cell[cx][cy].y + 1;

  ner[4].x = cell[cx][cy].x + 1;
  ner[4].y = cell[cx][cy].y + 1;

  ner[5].x = cell[cx][cy].x + 1;
  ner[5].y = cell[cx][cy].y;

  ner[6].x = cell[cx][cy].x + 1;
  ner[6].y = cell[cx][cy].y - 1;

  ner[7].x = cell[cx][cy].x;
  ner[7].x = cell[cx][cy].y - 1;
  
  for (int i = 0; i < 8; i++) {
    if (ner[i].x >= 0 && ner[i].y >= 0 && ner[i].x<32 && ner[i].y <32) {
      int nx = ner[i].x, ny = ner[i].y;
      if (cell[nx][ny].live == 't') {
        ner_live++;
      }
    }
  }
  
    return ner_live;
}

int main() {
	int ner_live = 0;
  init_cell();
  out();
  while (1) {
    for (int x = 0; x < 32; x++) {
      for (int y = 0; y < 32; y++) {
      	ner_live = check_cell(cell,x,y);
        if (ner_live == SUIT_NER) {
          cell[x][y].live = 't';
        } else if (ner_live !=SUIT_NER && ner_live !=SUIT_NER-1)
        {
        	cell[x][y].live = 'f';
        }
      }
    }
    delay(200);
    system("clear");
    out();
  }
}
