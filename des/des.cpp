#include "des.h"
void DES::init(){
	LR.reset();
	ans.reset();
	L.reset();
	R.reset();
	nextL.reset();
	ex.reset();
	C.reset();
	D.reset();
}
void DES::getSubKey(int j){
	for(int i  = 1;i<=16;i++){
		if(j == 1)
			getnowK(i,subkey1);
		else
			getnowK(i,subkey2);
	}
}
void DES::changeWordToBit(){   //long long to char
	numlen = strlen(num);
	int index = 0;
	char toBeSave[70];
	for(int i = 0;i<numlen ;i++){
		int tc = num[i];
		for(int j = 0;j<8;j++){
			if(tc & 1){
				LR.set(index);
			}
			index++;
			tc = tc >> 1;
		}
		if(index > 63 && i<numlen-1){
			incode();
			strncpy(toBeSave,LR.to_string().c_str(),64);
			write(fp,toBeSave,strlen(toBeSave));
			index = 0;
			//init();
		}
	}
	//incode();
}

void DES::opIP(){
	bitset<64> temp;
	int j = 63; 
	for(int i = 0;i<=63;i++){
		temp[j--] = LR[64 - IP[i]];
	}
	LR = temp;
}

void DES::split(){
	for(int i = 0;i<32;i++){
		R[i] = LR[i];
	}
	for(int i = 32;i<64;i++){
		L[i-32] = LR[i];
	}
	//cout<<"L:"<<L<<endl<<"R:"<<R<<endl;
}
void DES::opE(){
	ex.reset();
	int j = 47;
	for(int i = 0;i<=47;i++){
		ex[j--] = R[32-E[i]];
	}

	//cout<<"ex:"<<ex<<endl;
}
void DES::opK(int i,int witch_key){
	switch (witch_key){
		case 1:
			ex = ex^subkey1[i-1];
			break;
		case 2:
			ex = ex^subkey2[i-1];
			break;
	}
}
void DES::opS(){
	int nowRi = 0;
	for(int i = 0;i<=47;i+=6){
		int group = 7 - i/6;    //which S box
		int beg = i;    //begin
		int end = i+6-1;   //
		int dx = (ex[beg])*pow(2,0)+(ex[end])*pow(2,1);
		int dy = 0;
		for(int k = beg+1;k<end;k++){
			int mi = k - beg-1;
			dy = dy + (ex[k])*pow(2,mi);
		}
		int nownum = S[group][dx*16+dy];
		//cout<<"num:"<<nownum<<endl;
		for(int l = 0;l<4;l++){
			R[nowRi++] = (nownum & 1);
			nownum = nownum >> 1;
		}
	}

}

void DES::opP(){
	bitset<32> temp;
	int j = 31;
	for(int i = 0;i<32;i++){
		
		temp[j--] = R[32-P[i]];
	}
	R = temp;
}
void DES::changeWordToBit(int which){
	int klen;
	int c;
	if(which == 1)
		klen = strlen(Knum1);
	else
		klen = strlen(Knum2);
	int keyIndex = 0;
	for(int i = 0;i<klen;i++){
		if(which == 1)
			c = Knum1[i];
		else
			c = Knum2[i];
		for(int j = 0;j<8;j++){
			if(c & 1){
				K1.set(keyIndex);
			}
			++keyIndex;
			c = c >> 1;
		}
	}
	keyIndex = 0;
	bitset<56> temp;
	int j = 55;
	for(int i = 0;i<56;i++){
		temp[j--] = K[64-PC1[i]];
	}
	for(int i = 0;i<28;i++){
		D[i] = temp[i];
	}
	for(int i = 28;i<56;i++){
		C[i-28] = temp[i];
	}	
}
void DES::getK(){

	getSubKey(1);   //get 16 subkey

	getSubKey(2);
}
void DES::getnowK(int j,bitset<48> &subkey){
	int step = 2;
	bitset<56>temp;
	bitset<48> nowK;
	if(j == 1 || j== 9 || j == 2 || j == 16)
		step = 1;
	for(int i = 0;i<=27;i++){
		temp[(i+step)%28] = C[i];
	}
	for(int i = 0;i<28;i++){
		C[i] = temp[i];
	}
	temp.reset();
	for(int i = 0;i<=27;i++){
		temp[(i+step)%28] = D[i];
	}
	for(int i = 0;i<28;i++){
		D[i] = temp[i];
	}
	temp.reset();
	int k = 0;
	for(int i = 0;i<28;i++){
		temp[k++] = D[i];
	}	
	for(int i = 0;i<28;i++){
		temp[k++] = C[i];
	}
	
	//cout<<"C:"<<C<<endl<<"D:"<<D<<endl;
	k = 47;
	for(int i = 0;i<=47;i++){
		nowK[k--] = temp[56-PC2[i]];
	}
	subkey[j-1] = nowK;
	//cout<<"i:"<<nowK<<endl;
}
void DES::opAndOr(){
	for(int i = 0;i<=31;i++){
		R[i] = R[i]^L[i];
	}
	L = nextL;
}
void DES::polling(bool decodeFlag,int witch_key){
	for(int i = 1;i<=16;i++){
		nextL = R;
		opE();
		if(decodeFlag == true)   //incode
			opK(17-i,witch_key);
		else
			opK(i,witch_key);   //decode
		opS();
		opP();
		opAndOr();
		L = nextL;
	}
}
void DES::incode(bool decodeFlag,int witch_key){
	opIP();
	split();     //split 64 to L0 and R0
	polling(decodeFlag,witch_key);
	swap();
	combination();
	opPI();
}

void DES::swap(){
	nextL = R;
	R = L;
	L = nextL;
}
void DES::combination(){
	int j = 0;
	for(int i = 0;i<32;i++){
		LR[j++] = R[i];
	}
	for(int i = 0;i<32;i++){
		LR[j++] = L[i];
	}

}
void DES::opPI(){
	//cout<<"before PI:"<<LR<<endl;
	int j =63;
	for(int i = 0;i<=63;i++){
		ans[j--] = LR[64-PI[i]];
	}

}
void DES::print(){
	/*for(int i = 0;i<64;i++){
		toFile[63-i] = ans[i] + '0';
	}
	write(fp,toFile,64);*/
	cout<<"after PI:"<<ans<<endl;

}

