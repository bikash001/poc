#include <iostream>
#include <map>
#include <string>
#include <cstdio>
using namespace std;

void decode(string input, string output)
{
	FILE *inp = fopen(input.c_str(),"rb");
	FILE *outp = fopen(output.c_str(),"wb");
	std::map<unsigned char, unsigned char> map;
	std::map<unsigned char, unsigned char>::iterator begin,end;
	unsigned char arr[16] = {
		0x0,0xc,0x17,0x1a,0x23,0x2e,0x34,0x39,
		0x46,0x4b,0x51,0x5c,0x65,0x68,0x72,0x7f
	};
	for(int i=0; i<16; i++){
		map[arr[i]] = i;
	}
	end = map.end();
	unsigned char ch,byte,nbyte,chnext=0,temp;

	int count = 1;
	while((temp=getc(inp))){
		if(feof(inp)){
			return;
		}
		if(count % 2 == 1){
			ch = temp;
			byte = ch;
			ch = ch << (8-count);
			ch = ch >> 1;			
			if(count == 7){
				byte = byte >> 7;
				byte = byte | chnext;
				begin = map.find(byte);
				if(begin != end){
					nbyte = begin->second;
					nbyte = nbyte << 4;
				}else{
					cout << "error 0" << endl;
				}
				begin = map.find(ch);
				if(begin != end){
					ch = begin->second;
					nbyte = nbyte | ch;
					putc(nbyte,outp);
				}else{
					cout << "error 0" << endl;
				}
				count = 1;
			}else{
				byte = byte >> count;
				byte = byte | chnext;
				begin = map.find(byte);
				if(begin != end){
					nbyte = begin->second;
					nbyte = nbyte << 4;
				}else{
					cout << "error 0" << endl;
				}
				count++;
			}
		}else{
			chnext = temp;
			byte = chnext;
			chnext = chnext << (8-count);
			chnext = chnext >> 1;
			byte = byte >> count;
			byte = byte | ch;
			begin = map.find(byte);
			if(begin != end){
				byte = begin->second;
				nbyte = nbyte | byte;
				putc(nbyte,outp);
			}
			else{
				cout << "error" << endl;
			}
			count++;
		}
	}
}

int main()
{
	decode("testout","chdecode");
	return 0;
}