#include <stdio.h>
#include <string.h>
#define SIZE 757

int error = 20;
int count = 0;

void gen_error(char *msg)
{
	char str[9];
	char byte;
	int temp,j;
	char eb;
	for(j=0; j<8; ++j){
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

int check(unsigned char byte){
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
			//cout << "error" << endl;
			return 0;
		}
	}
	return 1;
}

int main()
{
	FILE *fp = fopen("output","rb");
	char mesg[SIZE];
	fread(mesg,1,SIZE,fp);
	fclose(fp);

	int i=0;
	unsigned char ch = 0x0;
	unsigned char byte,temp;
	int count=7;
	while(i<SIZE){
		temp = mesg[i];
		temp = temp >> (8-count);
		byte = ch ^ temp;
		if(!check(byte)){
				printf("errror %d\n",i);
		}
		ch = mesg[i];
		ch = ch << count;
		ch = ch >> 1;
		if(count == 1){
			//printf("%d %c\n",i,mesg[i+1]);
			if(!check(byte)){
				printf("errror count %d\n",i);
			}
			ch = 0x0;
			count = 7;
		}
		else{
			--count;
		}
		++i;
	}
	// FILE *fp = fopen("out","wb");
	// unsigned char ch = 0xff;
	// int i,j;
	// for(i=0; i<2; i++){
	// 	ch = i;
	// 	for(j=0; j<7; j++){
	// 		fputc(ch,fp);
	// 	}
	// }
	return 0;
}
