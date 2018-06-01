#pragma once

#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#define MAX_SIZE 8000

using namespace std;



class BranchPredictor {

public:

	/*--------------data--------------*/	//33KB MAX

	//eg.    bool prediction[4000]

	bool prediction[8000];

	char state[MAX_SIZE];	

	static const double threshold = 3.0 / 4.0;

	/*------Your own structure-------*/



	BranchPredictor();



	bool makePrediction(int address);

	int makeUpdate(int address,bool pred,bool act);

};

BranchPredictor::BranchPredictor() {

	for(int i = 0; i < 8000; i++){

		prediction[i] = false;

	}
	for(int i = 0; i < MAX_SIZE; i++){
		state[i] = (char)(0);
	}

}





/*

*int address：	预测地址



*RETURN 预测结果

*/

bool BranchPredictor::makePrediction(int address) {
	/*------------------edit-----------------------*/
	int temp = (int)(state[address % MAX_SIZE]);
	if(temp < 2){
		prediction[address % 8000] = false;
		return false;
	}
	else{
		prediction[address % 8000] = true;
		return true;
	}
	/***********************************************/
}





/*

*int address：	预测地址

*bool pred：	prediction，预测结果

*bool act：		actually，实际运行结果

*/

int BranchPredictor::makeUpdate(int address, bool pred, bool act) {	
	/*------------------edit-----------------------*/
	int temp = (int)(state[address % MAX_SIZE]);	
	cout<<prediction[address % 8000]<<" "<<pred<<endl;
	if(temp == 0){
		if(pred == act)temp = 1;
		else temp = 0;
	}
	else if(temp == 1){
		if(pred == act)temp = 3;
		else temp = 0;
	}
	else if(temp == 2){
		if(pred == act)temp = 3;
		else temp = 0;
	}
	else{
		if(pred == act)temp = 2;
		else temp = 3;
	}
	state[address % MAX_SIZE] = (char)(temp);
	/***********************************************/
	return 0;
}
