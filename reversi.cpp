#include <bits/stdc++.h>
using namespace std;
#define size 8

void show (char board[size][size]) {
  cout << "\n   ";
  for (int col = 0; col < size; col++){
    cout << char(col + 'a') << "  ";
  }
  for (int row = 0; row < size; row++){
    cout << "\n " << char(row + '1');
    for (int col = 0; col < size; col++){
      if (board[row][col] == 1){
        cout << " o ";
      }
      else if (board[row][col] == -1){
        cout << " x ";
      }
      else {
        cout << " . ";
      }
    }
    cout << "\n";
  }
  cout << "\n";
}

int calculate(char board[size][size], int number[size][size], char level){
  int x, y, step = 0;
  char enemy = (level == 1) ? -1 : 1;
  char player = -1 * enemy;
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      number[row][col] = 0;
    }
  }
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      if (board[row][col] != 0) continue;
      for (int Row = -1; Row <= 1; Row++){
        for (int Col = -1; Col <= 1; Col++){
          if (row + Row < 0 || row + Row >= size || col + Col >= size || (Row == 0 && Col == 0)) continue;
          if (board[row + Row][col + Col] == enemy){
            x = row + Row;
            y = col + Col;
            while (1){
              x += Row;
              y += Col;
              if (x < 0 || x >= size || y < 0 || y >= size) break;
              if (board[x][y] == 0) break;
              if (board[x][y] == player){
                number[row][col] = 1;
                step++;
                break;
              }
            }
          }
        }
      }
    }
  }
  return step;
}

void print(char board[size][size], int row, int col, char level){
  int x, y;
  char enemy = (level == 1) ? -1 : 1;
  char player = -1 * enemy;
  board[row][col] = player;
  for (int Row = -1; Row <= 1; Row++){
    for (int Col = -1; Col <= 1; Col++){
      if (row + Row < 0 || row + Row >= size || col + Col < 0 || col + Col >= size || (Row == 0 && Col == 0)) continue;
      if (board[row + Row][col + Col] == enemy){
        x = row + Row;
        y = col + Col;
        while (1){
          x += Row;
          y += Col;
          if (x < 0 || x >= size || y < 0 || y >= size) break;
          if (board[x][y] == 0) break;
          if (board[x][y] == player){
            while (board[x -= Row][y -= Col] == enemy){
              board[x][y] = player;
            }
            break;
          }
        }
      }
    }
  }
}

int calscore(char board[size][size], char level){
  int score = 0;
  char enemy = (level == 1) ? -1 : 1;
  char player = -1 * enemy;
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      score -= (board[row][col] == enemy);
      score += (board[row][col] == player);
    }
  }
  return score;
}

int best(char board[size][size], int number[size][size], char level){
  int maxscore = 0, score = 0;
  char Board[size][size];
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      if (!number[row][col]) continue;
      for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
          Board[i][j] = board[i][j];
        }
      }
      print(Board, row, col, level);
      score = calscore(Board, level);
      maxscore = max(score, maxscore);
    }
  }
  return maxscore;
}

void computer(char board[size][size], int number[size][size], char level){
  int Row, Col, score, minscore = 100;
  char Board[size][size];
  int Number[size][size];
  char enemy = (level == 1) ? -1 : 1;
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      if (number[row][col] == 0) continue;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          Board[i][j] = board[i][j];
        }
      }
      print(Board, row, col, level);
      calculate(Board, Number, enemy);
      score = best(Board, Number, enemy);
      if (row == 0 || row == size - 1 || col == 0 || col == size - 1 || score < minscore){
        minscore = score;
        Row = row;
        Col = col;
      }
    }
  }
  print(board, Row, Col, level);
}

int main(){
  char board[size][size];
  int number[size][size] = {};
  int score[2];
  int mode, level = -1, cross = 0;
  string input;

  cout << "===============REVERSI===============\n";
  cout << "Player will be (x), and computer will be (o).\n";
  cout << "Enter your move by typing the coordinate of the point. (ex:1a)\n";
  cout << "Press 1 to go first, and 2 to go second.\n";

  while (level == -1){
    cin >> mode;
    if (mode == 1) {
      level = 1;
    }
    else if (mode == 2){
      level = 0;
    }
    else {
      cout << "Not a valid number, please try again!\n";
    }
  }

  int count = 4;
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      board[row][col] = 0;
    }
  }
  board[size / 2 - 1][size / 2 - 1] = board[size / 2][size / 2] = -1;
  board[size / 2 - 1][size / 2] = board[size / 2][size / 2 - 1] = 1;
  cout << "Game start!\n";
  show(board);

  while(count < (size * size)){
    if (level == 1){
      level = 0;
      if (calculate(board, number, 2)){
        cross = 0;
        while (1){
          cout << "Please enter your move. (ex:1a)\n";
          cin >> input;
          int x = input[0] - '0' - 1;
          int y = (input[1] >= 'a') ? input[1] - 'a' : input[1] - 'A';
          if (x >= 0 && y >= 0 && x < size && y < size && number[x][y]){
            print(board, x, y, 2);
            count++;
            break;
          }
          else {
            cout << "Not a valid move, please try again!\n";
          }
        }
        show(board);
      }
      else if (cross != 2){
        cross = 1;
        cout << "Cannot move, computer go.\n";
      }
      else {
        cout << "Both cannot move, game over!\n";
      }
    }
    else {
      level = 1;
      if (calculate(board, number, 1)){
        cross = 0;
        computer(board, number, 1);
        count++;
        show(board);
      }
      else {
        if (cross != 1){
          cross = 2;
          cout << "Cannot move, player go.\n";
        }
        else {
          cout << "Both cannot move, game over!\n";
        }
      }
    }
  }
  show(board);

  score[0] = score[1] = 0;
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      score[0] += board[row][col] == -1;
      score[1] += board[row][col] == 1;
    }
  }
  cout << "Final Score:\n";
  cout << "Player: " << score[0] << " Computer: " << score[1] << "\n";
  if (score[0] > score[1]){
    cout << "Player wins! Congratulations!\n";
  }
  else if (score[0] < score[1]){
    cout << "Computer wins! Better luck next time!\n";
  }
  else {
    cout << "Player and computer tied!\n";
  }
  cout << "===============REVERSI===============\n";
  return 0;
}