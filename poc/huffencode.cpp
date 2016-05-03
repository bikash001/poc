#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <map>
#include <queue>
#include <cmath>
using namespace std;

struct node{
	char ch;
	node *left;
	node *right;
	int freq;
	node(int f,node *l, node* r,char c='\0'){
		ch = c;
		freq = f;
		left = l;
		right = r;
	}
};


struct compare
{
    bool operator()(node* l, node* r)
    {
        return (l->freq > r->freq);
    }
};

void codeword(node *top,map<unsigned char,string> &map,string ss)
{
	if(top->left != 0){
		codeword(top->left,map,ss+"0");
	}
	else{
		map[top->ch] = ss;
	}
	if(top->right != 0){
		codeword(top->right,map,ss+"1");
	}
	else{
		map[top->ch] = ss;
	}
}

node* huffman_tree(int freq[])
{
	priority_queue<node*, vector<node*>, compare> minHeap;
	for(int i=0; i<256; ++i){
		if(freq[i]>0){
			minHeap.push(new node(freq[i],0,0,(char)i));
		}
	}
	int size = minHeap.size();
	node *l, *r, *temp;
	for(int i=1; i<size; ++i){
		r = minHeap.top();
		minHeap.pop();
		l = minHeap.top();
		minHeap.pop();
		temp = new node(r->freq+l->freq,l,r);
		minHeap.push(temp);
	}
	
	node* top = minHeap.top();
	return top;
}

void huffman(int arr[],string fname, string output)
{
	node* top = huffman_tree(arr);
	
	std::map<unsigned char, string> map;
	codeword(top,map,"");
	std::map<unsigned char,string>::iterator it,end;
	end = map.end();
	string sp = "codebook";
	ofstream outp;
	//FILE *outp;
	//outp = fopen(sp.c_str(),"wb");
	outp.open(sp.c_str());

	for(int i=0; i<256; ++i){
		it = map.find((unsigned char)i);
		if(it != end){
			outp << it->first << " " << it->second << endl;
		}
	}
	outp.close();
	
	//outp.open(output.c_str(),ios::binary);
	FILE *out = fopen(output.c_str(),"wb");
	FILE *inp = fopen(fname.c_str(),"rb");
	//ifstream inp(fname.c_str(),ios::binary);
	unsigned char ch = 0x0;
	string ss="0";
	string::iterator begin,endl;
	unsigned char byte = 0x0;
	unsigned char temp = 0x1;
	int count=0;
	int counter = 0;

	int no=0;

	while(!feof(inp)){
		ch = getc(inp);
		no++;
		it = map.find(ch);
		if(it == map.end()){
			cout << "not found" << no << std::endl;
			continue;
		}
		ss = it->second;
		begin = ss.begin();
		endl = ss.end();
		while(begin != endl){
			++count;
			if(*begin == '1'){
				byte = byte | temp;
			}
			if(count == 8){
				count = 0;
				putc(byte,out);
				//outp << byte;
			}
			byte = byte << 1;
			++begin;
		}
	}
	fclose(out);
	fclose(inp);
	//outp.close();
	//inp.close();
}

void prob(string fname)
{
	//ifstream file(fname.c_str(),ios::binary);
	FILE *fp = fopen(fname.c_str(),"rb");
	int size = 0;
	int freq[256] = {0};
	unsigned char ch;
	string ss;
	int pp=0;
	while(!feof(fp)){
		ch = getc(fp);
		freq[(int)ch] += 1;
		++size;
	}
	fclose(fp);
	huffman(freq,fname,"hoffcode");
}

int main()
{
	prob("input");
	return 0;
}
