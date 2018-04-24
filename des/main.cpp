#include "des.h"
int main(){
	char  num[100000];
	char _K[16];
	scanf("%s",num) ;
	fflush(stdin);
	scanf("%s",_K);
	//cout<<"out:"<<num<<" "<<_K<<endl;
	DES obj(num,_K);
	//obj.change();
	obj.change();
	//obj.opIP();
	//obj.split();
	//obj.opE();

}
