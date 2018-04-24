#include<iostream>
#include<bitset>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
using namespace std;
int main(){
	int fp;
	/*fp = open("key.txt",O_RDWR|O_CREAT,0);
	string a("10011");
	bitset<10> bt(a);
	char ans[10];
	for(int i = 0;i<10;i++)
		ans[9-i] = bt[i] + '0';
	write(fp,ans,sizeof(ans));
	close(fp);*/

	/*char a = 'A';
	int aa = a;
	cout<<aa<<endl;
	if(aa <=57 && aa>=48)
			aa = aa - 48;
	while(aa){

		if(aa & 1)
			cout<<1;
		else
			cout<<0;
		aa = aa >> 1;
	}*/
	/*char a1[10],a2[10];
	cin>>a1>>a2;
	cout<<a1<<endl<<a2<<endl;*/
	string s("10011");
	bitset<10> b(s);
	for(int i = 0;i<10;i++)
		cout<<b[i];
	return 0;
}
