#include <iostream>
#include <fstream>
#include <string>
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


node* prob(string fname)
{
	//ifstream file(fname.c_str(),ios::in | ios::binary);
	FILE *fp = fopen(fname.c_str(),"rb");
	int size = 0;
	int freq[256] = {0};
	unsigned char ch;
	string ss;
	while(!feof(fp)){
		ch = getc(fp);
		freq[(int)ch] += 1;
		++size;
	}
	//file.close();
	fclose(fp);
	return huffman_tree(freq);
}

void decode(string input, string output)
{
	node *top = prob("input");
	FILE *inp = fopen(input.c_str(),"rb");
	FILE *outp = fopen(output.c_str(),"wb");
	//cout << "hi \n";
	//ifstream inp(input.c_str(), ios::binary);
	//ofstream outp(output.c_str(), ios::binary);
	unsigned char ch;
	unsigned char tp = 0b10000000;
	node *curr = top;
	while(!feof(inp)){
		ch = getc(inp);
		for(int i=0; i<8; ++i){
			if(ch & tp){
				curr = curr->right;
			}
			else{
				curr = curr->left;
			}
			if(curr->left == 0){
				//outp.put(curr->ch);
				putc(curr->ch,outp);
				curr = top;
			}
			ch = ch << 1;
		}
	}
	//inp.close();
	//outp.close();
	fclose(inp);
	fclose(outp);
}

int main()
{
	decode("hoffcode","out");
	return 0;
}