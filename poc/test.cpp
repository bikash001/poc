#include <iostream>
#include <fstream>
using namespace std;


//systematic cyclic encoding
int main()
{
	char arr[16] = {
		0x0,0b1101,0b10111,0b11010,0b100011,0b101110,
		0b110100,0b111001,0b1000110,0b1001011,0b1010001,
		0b1011100,0b1100101,0b1101000,0b1110010,0b1111111
	};
	ifstream in("hoffcode",ios::in);
	ofstream out("channelcode",ios::binary);
	char ch,byte,temp,nbyte;
	int i=0;
	int p=0;
	while(in.get(ch)){
		p++;
		temp = ch;
		temp = temp >> 4;
		byte = arr[temp];
		if(i%8==0){
			byte = byte << 1;
			ch = ch & 0xf;
			nbyte = arr[ch];
			temp = nbyte;
			temp = temp >> 6;
			byte = byte | temp;
			nbyte = nbyte << 2;
			out.put(byte);
			i=2;
		}else{
			temp = byte;
			temp = temp >> (8-i-1);
			byte = byte << (i+1);
			nbyte = nbyte | temp;
			out.put(nbyte);
			i++;
			ch = ch & 0xf;
			nbyte = arr[ch];
			temp = nbyte;
			nbyte = nbyte << (i+1);
			temp = temp >> (8-i-1);
			byte = byte | temp;
			out.put(byte);
			i++;
		}
	}
	cout << "char encoded " << p << endl;
	return 0;
}
