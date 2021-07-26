#include <bits/stdc++.h>
using namespace std;

const int N = 4;
int grid[N][N];
void print_grid() {
	for (int i = 0; i < ((N + 4) * N + N + 1); cout << "-", i++);
	cout << "\n";
	for (int i = 0; i < N; i++) {
        cout << "|";
		for (int j = 0; j < N; j++) {
			string e = "";
            if (grid[i][j] == 0) {
				for (int t = 0; t < N+4; e += " ", t++);
			}
            else {
                int str_len = to_string(grid[i][j]).size();
                int r1 = ((N+4) - str_len + 1) / 2;
                int r2 = ((N+4) - str_len) - r1;
				for (int t = 0; t < r1; e += " ", t++);
				e += to_string(grid[i][j]);
				for (int t = 0; t < r2; e += " ", t++);
			}
			cout << e << "|";
		}
		cout << "\n";
		for (int t = 0; t < ((N + 4) * N + N + 1); cout << "-", t++);
		cout << "\n";
	}
}

void generate_cell() {
int a=rand()%4;
int b=rand()%4;
while(grid[a][b]!=0){
    a=rand()%4;
    b=rand()%4;
}
int c=rand()%2;
  if(c)
    grid[a][b]=4;
 else
     grid[a][b]=2;
}
void grid_clear() {
for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      grid[i][j]=0;
}

bool check_win() {
for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
        if(grid[i][j]==2048)
           return true;
    return false;
}
void rotate_90() {
	for (int i = 0; i < N/2; i++) {
		for (int j = i; j < N-i-1; j++) {
            int k  = grid[i][j];
            grid[i][j] = grid[N-j-1][i];
            grid[N-j-1][i] = grid[N-i-1][N-j-1];
            grid[N-i-1][N-j-1] = grid[j][N-i-1];
            grid[j][N-i-1] = k;
		}
	}
}


bool check_available_direction() {
for(int i=0;i<N;i++)
    for(int j=0;j<N-1;j++)
    {
        if(grid[i][j]==grid[i][j+1]&&grid[i][j]>0||grid[i][j]>0&&grid[i][j+1]==0)
         return true;
         

    }
    return false;
}
bool check_valid_direction(int i) {
    return (i==1||i==3||i==5||i==2);

}

bool check_available_move(int d) {
    bool res = false;
    //check direction right
    if (d == 3) res = check_available_direction();
    rotate_90();
    //check direction UP
    if (d == 5) res = check_available_direction();
    rotate_90();
    //check direction left
    if (d == 1) res = check_available_direction();
    rotate_90();
    //check direction down
    if (d == 2) res = check_available_direction();
    rotate_90();
    return res;
}

void read_input(int &i) {
    cout << "Enter the direction: ";
	cin >> i;
    while (!check_valid_direction(i) || !check_available_move(i)) {
        cout << "Enter a valid direction: ";
		cin >> i;
	}
}
bool check_full() {
if(check_available_move(2))
    return 0;
if(check_available_move(3))
    return 0;
if(check_available_move(5))
    return 0;
if(check_available_move(1))
    return 0;
return 1;
}

void merge() {
for(int i=0;i<N;i++)
    for(int j=N-1;j>0;j--)
    {
        if(grid[i][j]==grid[i][j-1])
         { grid[i][j]+=grid[i][j-1];
             grid[i][j-1]=0;
         }


    }

}

void merge_direction(int d) {
    //merge direction right
    if (d == 3) merge();
    rotate_90();
    //merge direction up
    if (d == 5) merge();
    rotate_90();
    //merge direction left
    if (d == 1) merge();
    rotate_90();
    //merge direction down
    if (d == 2) merge();
    rotate_90();
}
void move() {
for(int k=0;k<N-1;k++)
for(int i=0;i<N;i++)
    for(int j=N-1;j>0;j--)
    {
        if(grid[i][j]==0)
         { grid[i][j]=grid[i][j-1];
         grid[i][j-1]=0;

         }
    }
}

void move_direction(int d) {
   
    if (d == 3) move();
    rotate_90();
    
    if (d == 5) move();
    rotate_90();
  
    if (d == 1) move();
    rotate_90();
    
    if (d == 2) move();
    rotate_90();
}

void play_game() {
    cout << "2048 Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    while (true) {
     
        generate_cell();
        //Prints the grid
        print_grid();
        //Check if the state of the grid has a tie state
        if (check_full()) {
            cout << "Game Over\n";
            break;
		}
        
		int i;
		read_input(i);
        
        move_direction(i);
        
       merge_direction(i);
       
        move_direction(i);
       
        if (check_win()) {
          
            print_grid();
            
            cout << "Congrats, You won!\n";
            
			char c;
			cout << "Continue [Y/N] ";
			cin >> c;
			if (c != 'y' && c != 'Y')
				break;
		}
	}
}
int main() {
	while (true) {
		grid_clear();
		play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
	}
}

