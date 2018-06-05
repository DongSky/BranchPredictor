#pragma once
#include <iostream>
#include <time.h>
#include <map>
using namespace std;

class BranchPredictor {
 public:
	/*------data------*/	//33KB MAX
  //map<unsigned long, char> prediction;
	bool prediction[4000];  	
	char pre[4000];
	BranchPredictor();
	bool makePrediction(unsigned long address);
	void makeUpdate(unsigned long address, bool predict, bool act);
};

BranchPredictor::BranchPredictor()
{
}

/*
 *int address：	预测地址

 *RETURN 预测结果
 */
bool BranchPredictor::makePrediction(unsigned long address)
{
	/*------------------edit-----------------------*/
  return prediction[address % 4000] = (pre[address % 4000] >= 2);
}


/*
 *int address：	预测地址
 *bool pred：	prediction，预测结果
 *bool act：		actually，实际运行结果
 */
void BranchPredictor::makeUpdate(unsigned long address, bool predict, bool act)
{
	/*------------------edit-----------------------*/
  if(act){
    pre[address % 4000]=((pre[address % 4000]<<1)+1)%4;
  } else{
    pre[address % 4000]=(pre[address % 4000]<<1)%4;
  }
}

