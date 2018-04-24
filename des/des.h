#include "table.h"
#include<string.h>
#include<bitset>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#define MAXN 100000
class DES{
private:
	bitset<64> LR,ans;
	bitset<32> L,R,nextL;
	bitset<48> ex,subkey1[16],subkey2[16];
	bitset<64> K1;
	bitset<64> K2;
	char toFile[64];
	bitset<28>C;
	bitset<28>D;
	char num[MAXN];
	char Knum1[16];    //8 bytes keyword1
	char Knum2[16];    //8 bytes keyword2
	int numlen;
	int fp;
public:
	DES(char *_num,char *_Knum1,char *_Knum2){
		memset(num,0,sizeof(num));
		strcpy(num,_num);
		strcpy(Knum1,_Knum1);
		strcpy(Knum2,_Knum2);
		fp = open("key.txt",O_RDWR|O_CREAT|O_TRUNC,0);
	}
	
	void changeWordToBit();  //char to bitset and save to file
	void changeKeyToBit(int which);
	void polling(bool decodeFlag); //use 16 subkeys poll
	void opIP();
	void split();   //64 bits to 2*32 bits
	void opE();   // 32 bits to 48 bits
	void opP();
	void getK();
	void getSubKey(int j);
	void getnowK1(int j);
	void getnowK2(int j);
	void init();
	void opK(int i);
	void opS();   // 48 to 32
	void opAndOr();
	void incode(bool decodeFlag,int which_key);
	void swap();
	void combination();
	void opPI();
	void print();
	void decode();
	~DES(){
		close(fp);
	}
};
void getnum(char *,char *);
