#include <stdio.h>

int Board[9]={0, 0, 0,
			  0, 0, 0,
			  0, 0, 0};
const char s[] = "X 0";

void printBoard(int b[]){ // print the board
	for(int i=0;i<9;++i){
		printf("%c", s[ b[i]+1 ] );
		if( i%3==2 ) printf("\n");
	}
}

int checkWin(int b[]){ //return the player that won
	for(int i=0;i<3;++i){
		int z = b[i*3] + b[i*3+1] + b[i*3+2];
		if(z==3 || z==-3) return z/3;
		
		z = b[i] + b[3+i] + b[6+i];
		if(z==3 || z==-3) return z/3;
	}
	
	if( b[0]==b[4] && b[4]==b[8] ) return b[4];
	if( b[2]==b[4] && b[4]==b[6] ) return b[4];
	
	return 0;	// zero means no one
}

void playerMove(int turn){ // ask user for input
	int r;	// to store the input
	printf("Your turn: ");
	while(true){	// test the input possiblity
		if( scanf("%d", &r) ) 
			if(r>0 && r<10)
				if(Board[r-1]==0)
					break;
				else printf("Not possible");
			else printf("Must be between 1&9, ");
		else printf("Not a number, ");
		printf("try again: ");
	}
	Board[r-1] = turn;	// do the legal move
}

struct Data{
	int score=0;
	int position;
};
int h;
Data aiMove(int b[], int turn){ // AI movement
	Data toR;	// to return
	
	int available[9]; // empty positions
	int count=0;
	for(int i=0;i<9;++i)
		if( b[i]==0 )
			available[count++]=i;
	
	if(count==0){
		toR.position = 10;
		return toR;	// no position available
	}
	
	Data result[9];
	for(int i=0;i<count;++i){
		// calculate each available position
		b[ available[i] ] = turn;
		int ws = checkWin(b);
	
		if(ws==turn){  // will this move make me win
			result[ available[i] ].score += 1;
		}else{
			int r = aiMove(b, turn*-1).score;
			result[ available[i] ].score -= r;
			h++;
		}
		result[ available[i] ].position = available[i];
		
		b[ available[i] ] = 0;	// reset table
	}
	
	// Now the moves contain score
	
	toR.score = -100;
	toR.position = 10;
	// select the best move by score
	for(int i=0;i<count;++i)
		if(result[available[i]].score>toR.score){
			toR.score = result[available[i]].score;
			toR.position = available[i];
		}
	return toR;
}

int main(){
	bool stilRunning=true;
	while(stilRunning){
		h=0;
		playerMove(-1);
		
		int won = checkWin(Board);
		if(won==0)
			Board[ aiMove(Board, 1).position ] = 1;
		printBoard(Board);
		printf("Recursion: %d\n", h);
		won = checkWin(Board);
		if( won != 0 ){
			stilRunning=false;
			printf("%c won the game\n", s[won+1]);
			break;
		}
		
		for(int i=0;i<10;i++){
			if(i==9) stilRunning=false;
			if(Board[i]==0) break;
		}
	}
	
	return 0;
}
