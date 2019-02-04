// MLHW8.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include<math.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char theline [100] ;

	double data[100][10];
	double test[1000][10];
	double gamma[5] = {0.001,0.1,1,10,100};

	//read file
	fstream fin;
	fin.open("train.txt",ios::in);

	//分割字串存入二維陣列
	char *token = NULL;
	char *next_token = NULL;
	char seps[]   = " ,\t\n";
	int a=0;
	while(fin.getline(theline,sizeof(theline),'\n')){
		int b = 0;
		token = strtok_s( theline, seps, &next_token);
		while (token != NULL){
			data[a][b] = atof(token);
            token = strtok_s( NULL, seps, &next_token);
			b++;
		}
		a++;
	}
	fin.close();

	//read file
	fin.open("test.txt",ios::in);

	//分割字串存入二維陣列
	char *token2 = NULL;
	char *next_token2 = NULL;
	a=0;
	while(fin.getline(theline,sizeof(theline),'\n')){
		int b = 0;
		token2 = strtok_s( theline, seps, &next_token2);
		while (token2 != NULL){
			test[a][b] = atof(token2);
            token2 = strtok_s( NULL, seps, &next_token2);
			b++;
		}
		a++;
	}

	// calculate g_uniform
	double g_uniform[1000][5];
	// initial
	for(int i=0; i<1000; i++){
		for(int j=0; j<5; j++){
			g_uniform[i][j] = 0;
		}
	}
	for(int g=0; g<5; g++){
		for(int i=0; i<1000; i++){
			for(int j=0; j<100; j++){
				double temp = 0;			// ||x-xm||^2
				for(int d=0; d<9; d++){
					temp = temp + (test[i][d]-data[j][d])*(test[i][d]-data[j][d]);
				}
				temp = temp * ((-1)*gamma[g]);
				temp = exp(temp);
				temp = data[j][9]*temp;
				g_uniform[i][g] = g_uniform[i][g] + temp;
			}
			if(g_uniform[i][g]>0){
				g_uniform[i][g] = 1;
			}else{
				g_uniform[i][g] = -1;
			}
		}
	}
	
	
	// calculate eout
	double eout[5] = {0,0,0,0,0};
	for(int g=0; g<5; g++){
		for(int i=0; i<1000; i++){
			if(test[i][9]!=g_uniform[i][g]){
				eout[g]++;
			}
		}
		eout[g] = eout[g]/1000;
	}
	for(int i=0; i<5; i++){
		cout<<eout[i]<<endl;
	}

	system("pause");
	return 0;
}