#include <stdio.h>

int Board[9]={0, 0, 1,
			  0, 1, 0,
			  0, 0, 0};
const char s[] = "X 0";

void printBoard(int b[]){ // print the board
	printf("-----\n");
	for(int j=0;j<3;++j, printf("\n"))
		for(int i=0;i<3;++i)
			printf("%c", s[ b[i+j*3]+1 ] );
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
	
	return 0; // zero means no one
}

int playerMove(){ // ask user for input
	int r;
	printf("Your turn: ");
	while(true){
		if( scanf("%d", &r) ) 
			if(r>0 && r<10)
				if(Board[r]==0)
					break;
				else printf("Not possible");
			else printf("Must be between 1&9, ");
		else printf("Not a number, ");
		printf("try again: ");
	}
	return r; // return the selected move's position
}

struct Data{
	int score=0;
	int position;
};

int aiMove(int b[], int turn){ // AI movement
	int available[9]; // empty positions
	int count=0;
	
	for(int i=0;i<9;++i)
		if( b[i]==0 )
			available[count++]=i;
	
	if(count==0) return 10; // no move available
	
	Data result[9];
	for(int i=0;i<count;++i){
		// calculate this position
		b[ available[i] ] = turn;
		int ws = checkWin(b);
	
		if(ws==turn){
			result[ available[i] ].score += 100;
			result[ available[i] ].position = available[i];
		}
		// reset table
		b[ available[i] ] = 0;
	}
	
	int highest = -100, pos=10; // select the one with highest score
	for(int i=0;i<count;++i)
		if(result[available[i]].score>highest){
			highest = result[available[i]].score;
			pos = result[available[i]].position;
		}
	
	return pos;
}


int main(){
	bool stillPlaying=true;
	
	printf( "win location %d", aiMove(Board, 1)+1 );
	
	while( stillPlaying ){
		break;
		int move = playerMove();
	}
	
	return 0;
}
