#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class BranchPredictor {
int history_start_;
	static const int kSize = 128;
	static const int kHistorySize = 12;
	static const int kTheta = static_cast<int>(1.93 * kHistorySize + 14);
	static const int kWeightSize = 8;
	
int history_[kHistorySize];
	int bias_[kSize];
	int weights_[kSize][kHistorySize];
	
	int preds[kSize];
public:
	/*--------------data--------------*/	//33KB MAX
	//eg.    bool prediction[4000]
	bool prediction[kSize];

	/*------Your own structure-------*/
	
	BranchPredictor();
	int sign(int val) {
		return (val > 0) - (val < 0);
	}
	int get_key(int pc) const { return pc % kSize; };
	bool as_boolean(int t) const { return t >= 0; };
	inline int get_history_index(int i) const {
		return (i + history_start_) % kHistorySize;
	}
	bool makePrediction(int address);
	int makeUpdate(int address,bool pred,bool act);
	int ComputePerceptron(int key) ;
	void TrainPerceptron(int key, int y, int t);
};
BranchPredictor::BranchPredictor() {
	history_start_ = 0;
	for(int i=0;i<kSize;i++)prediction[i]=false;
	for(int i=0;i<kSize;i++)bias_[i]=1;
	for(int i=0;i<kHistorySize;i++)history_[i]=-1;
	for(int i=0;i<kSize;i++){
		for(int j=0;j<kHistorySize;j++){
			weights_[i][j]=0;
		}
	}
}
int BranchPredictor::ComputePerceptron(int key) {
	int y = bias_[key];
	for (int i = 0; i < kHistorySize; ++i) {
		int h = get_history_index(i);
		y += weights_[key][i] * history_[h];
	}
	return y;
}

/*
*int address：	预测地址

*RETURN 预测结果
*/
bool BranchPredictor::makePrediction(int address) {
	/*------------------edit-----------------------*/
	preds[address % kSize] = ComputePerceptron(get_key(address));
	return prediction[address % kSize] = as_boolean(preds[address % kSize]);
	/***********************************************/
}

void BranchPredictor::TrainPerceptron(int key, int y, int t) {
  if (sign(y) != t || abs(y) <= kTheta) {
    int ws = 1 << (kWeightSize - 1);
    int b = bias_[key] + t;
    if (abs(b) < ws) {
      bias_[key] = b;
    }
    for (int i = 0; i < kHistorySize; ++i) {
      int h = get_history_index(i);
      int w = weights_[key][i] + t * history_[h];
      if (abs(w) < ws) {
        weights_[key][i] = w;
      }
    }
  }
  history_[history_start_] = t;
  history_start_ = get_history_index(1);
}

/*
*int address：	预测地址
*bool pred：	prediction，预测结果
*bool act：		actually，实际运行结果
*/
int BranchPredictor::makeUpdate(int address, bool pred, bool act) {	
	/*------------------edit-----------------------*/
	TrainPerceptron(get_key(address), preds[address % kSize], act ? 1 : -1);
	/***********************************************/
	return 0;
}
