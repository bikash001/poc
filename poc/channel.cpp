#include <iostream>
#include <map>
#include <string>
using namespace std;
/*
int error; //index of error bit
int count;	//total count after last error
//packet size of 56bit, each packet of 7bit
void gen_error(char *msg)
{
	char str[9];
	char byte;
	int temp;
	char eb;
	for(int j=0; j<8; ++j){
		if(count+8 > error){
			temp = 8 - (error-count);
			eb = 0x1;
			eb = eb << temp;
			byte = msg[j];
			byte = byte ^ eb;
			str[j] = byte;
			count = temp;
		}else{
			str[j] = msg[j];
			count += 8;
		}
	}
	str[8]='\0';
	strncpy(msg,str,9);
}
*/


//error check
void check(unsigned char byte){
	unsigned char ch = 0x68;
	// byte = byte << 1;
	// byte = byte >> 1;
	unsigned char cc  = 0x40;
	int i=7;
	while(i>3){
		while(i>3){
			if(byte & cc){
				break;
			}
			cc = cc >> 1;
			ch = ch >> 1;
			i--;
		}
		if(i>3){
			byte = byte ^ ch;	
		}
		else if(byte){
			cout << "error" << endl;
			return;
		}
	}
}

int main()
{
	unsigned char byte = 0b01110011;
	check(byte);
	return 0;
}