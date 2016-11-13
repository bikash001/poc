#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <cmath>
using namespace std;

double entropy(int a[],int size)
{	
	double b[256];
	double entp = 0;
	for(int i=0; i<256; ++i){
		b[i] = (double)a[i]/size;
	}
	for(int i=0; i<256; ++i){
		if(b[i]>0){
			entp += b[i]*log2(b[i]);
		}
	}
	entp *= -1;
	return entp;
}

void prob(string fname)
{
	ifstream file(fname.c_str(),ios::in | ios::binary);
	int size = 0;
	int freq[256] = {0};
	char ch;
	string ss;
	while(file.get(ch)){
		freq[(int)ch] += 1;
		++size;
	}
	file.close();
	cout << entropy(freq,size) << endl;
}

int main()
{
	prob("input4");
	return 0;
}
