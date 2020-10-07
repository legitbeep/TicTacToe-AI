#include<bits/stdc++.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

using namespace std;

#define maxl 500000
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef long long int lli;

#define nl printf("\n");
#define pp pair<ll,ll>

class game{

char board[3][3] ;
char human , ai ;
int spots = 9;
map<char,int> score ;

public :

game();
void display();
int checkWinner();
void start();
void bestMove();
void humanMove();
int minimax(bool maxi, int depth );

};

game :: game( ){
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j<3 ; j++){
            board[i][j] = ' ';
        }
    }
    human = 'O';
    ai = 'X' ;

    score[human] = -10;
    score[ai] = 10;
    score['t'] = 0 ; // tie
}

void game :: display(){
    system("CLS");
    cout << "\n";
    for(int  i= 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            if( j < 2 )
                cout << " " << board[i][j] <<" |" ;
            else
                cout << " " << board[i][j] ;
        }
        cout << "\n";
        if( i < 2 ){
            for(int j = 0 ; j < 3 ; j++){
                cout << "---";
                if( j < 2 ){
                    cout << "+";
                }
            }
            cout << "\n";
        }
    }
}

void game::humanMove(){
    int x , i , j ;
    redo :
    cout << "\nEnter your move (numpad) : " ;
    cin >> x;
    if( x >= 7 && x <= 9 ){
        i = 0;
        j = x - 7 ;
    }else if( x >= 4 && x <= 6){
        i = 1;
        j = x - 4;
    }else if( x >= 1 && x <= 3 ){
        i = 2;
        j = x - 1 ;
    }else {
        cout << "Invalid try again \n";
        goto redo;
    }
    if( board[i][j] == ' ' )
        board[i][j] = human;
    else {
        cout << "Invalid try again \n";
        goto redo;
    }
}


// main code to play
void game::start(){
    while( true ){
        display();
        humanMove();
        spots--;
        if( checkWinner() != -100 ){
            display();
            break;
        }
        bestMove();
        spots--;
        if( checkWinner() != -100 ){
            display();
            break;
        }
    }
    if( checkWinner() == -10 ) cout << "\nYou Win!";
    else if( checkWinner() == 0 ) cout << "\nDraw!";
    else cout << "\nComputer Wins!";
    getch();
    return ;
}
///////////////////////////////////
int game::checkWinner(){

    for(int i = 0 ; i < 3 ; i++){
        if( board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ' )
        {
            return score[ board[i][0] ];
        }
    }

    for(int i = 0 ; i < 3 ; i++ ){
        if( board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ' ){
            return score[ board[1][i] ];
        }
    }

    if( board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ' ){
        return score[ board[1][1] ];
    }

    if( board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' '  ){
        return score[ board[1][1] ];
    }

    if( spots ) return -100;

    return 0;
}

void game::bestMove(){

int bestscore = INT_MIN ;
int x , y ;
x = y = 1 ;
for(int i = 0 ; i<3 ; i++){
    for(int j = 0 ; j<3 ; j++){
        if( board[i][j] == ' '){
            board[i][j] = ai;
            spots--;
            int score = minimax( false , 0 );
            spots++;
            board[i][j] = ' ';
            if( score > bestscore ){
                bestscore = score;
                x = i ;
                y = j ;
                cout << x << " " << y << "\n";
            }
        }
    }
}

board[x][y] = ai;

}

int game::minimax(bool maxi,int depth = 0 ){

int winner = checkWinner();

if( winner != -100 ){
        return winner ;
}

if( maxi ){
    int bestscore = INT_MIN  ;
    for(int i = 0 ; i<3 ; i++){
        for(int j = 0 ; j<3 ; j++){
            if( board[i][j] == ' ' ){
                board[i][j] = ai;
                spots--;
                int score = minimax( false , depth+1);
                board[i][j] = ' ';
                spots++;
                bestscore = max( bestscore ,score );
            }
        }
    }
    return bestscore ;
}else {
    int bestscore = INT_MAX ;
    for(int i = 0 ; i<3 ; i++){
        for(int j = 0 ; j<3 ; j++){
            if( board[i][j] == ' ' ){
                board[i][j] = human;
                spots--;
                int score = minimax( true , depth+1 );
                spots++;
                board[i][j] = ' ';
                bestscore = min( bestscore , score );
            }
        }
    }
    return bestscore ;
}

}

int main(){
game obj;
obj.start();

return 0;
}
