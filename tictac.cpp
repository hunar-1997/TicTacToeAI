#include <stdio.h>

short Board[9]={1, 0, 1,
				0, 0, 0,
				1, 0, 0};
const char s[] = "X 0";

void printBoard(short b[]){
	printf("-----\n");
	for(short j=0;j<3;++j, printf("\n"))
		for(short i=0;i<3;++i)
			printf("%c", s[ b[i+j*3]+1 ] );
}

short checkWin(short b[]){
	for(short i=0;i<3;++i){
		short z = b[i*3] + b[i*3+1] + b[i*3+2];
		if(z==3 || z==-3) return z/3;
		
		z = b[i] + b[3+i] + b[6+i];
		if(z==3 || z==-3) return z/3;
	}
	
	if( b[0]==b[4] && b[4]==b[8] ) return b[4];
	if( b[2]==b[4] && b[4]==b[6] ) return b[4];
	
	return 0;
}

short playerMove(){
	short r;
	printf("Your turn: ");
	while(true){
		if( scanf("%d", &r) ) 
			if(r>0 && r<10)
				break;
			else printf("Must be between 1&9, ");
		else printf("Not a number, ");
		printf("try again: ");
	}
	return r;
}

short aiMove(short difficulty){
	return 0;
}


int main(){
	bool stillPlaying=true;
	while( stillPlaying ){
		short move = playerMove();
		break;
	}
	printf("no body wins\n");
	
	return 0;
}
