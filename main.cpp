#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>

using namespace std;

class NumOp {
	public:
	int num;
	char op;
	int typeIsNum; // 0: op, 1: num
	NumOp(char input);
	NumOp(int input);
	
};
NumOp::NumOp(char input){
	typeIsNum = 0;
	op = input;
}
NumOp::NumOp(int input) {
	typeIsNum = 1;
	num = input;
}

void parse(const string & input, vector<NumOp> & result) {
	result.clear();
	int strLen = input.size();
	int tmpNum = 0;
	char tmpOp;
	int nowNum = 0;
	for (int i = 0; i < strLen; i++) {
		if (isdigit(input[i])) {
			nowNum = 1;
			tmpNum *= 10;
			tmpNum += (input[i] - '0');
		} else {
			if (nowNum == 1) {
				NumOp tmp(tmpNum);
				result.push_back(tmp);
				nowNum = 0;
				tmpNum = 0;
			}
			tmpOp = input[i];
			if (!isspace(tmpOp)) {
				NumOp tmp(tmpOp);
				result.push_back(tmp);
			}
		}
	}
	if (nowNum == 1) {
		NumOp tmp(tmpNum);
		result.push_back(tmp);
		nowNum = 0;
	}
	return;
}
void showExpr(const vector<NumOp> & result) {
	cout << "\nParsing Result:\n";
	for (unsigned int i = 0; i < result.size(); i++) {
		if (result[i].typeIsNum) {
			cout << result[i].num << " ";
		} else {
			cout << result[i].op << " ";
		}
	}
}


int priority(const char x) {
	switch(x) {
	case ')':
		return 0;
	case '+': case '-':
		return 1;
	case '*': case '/':
		return 2;
	case '(':
		return 100;
	}
	return 0;
}

void inToPost(const vector<NumOp> & infix, vector<NumOp> & postfix) {
	stack<NumOp> opStack;
	postfix.clear();
	for (unsigned int i = 0; i < infix.size(); i++) {
		if (infix[i].typeIsNum) {
			postfix.push_back(infix[i]);
		} else {
			int myPriority = priority(infix[i].op);
			if (myPriority == 0) {
				int contLoop = 1;
				while (!opStack.empty() && contLoop) {
					if (opStack.top().op != '(') {
						postfix.push_back(opStack.top());
						opStack.pop();
					} else {
						contLoop = 0;
					}
				}
				opStack.pop();
			} else {
				int contLoop = 1;
				while (!opStack.empty() && contLoop){
					if (priority(opStack.top().op) >= myPriority) {
						postfix.push_back(opStack.top());
						opStack.pop();
					} else {
						contLoop = 0;
					}
				}
				opStack.push(infix[i]);
			}
		}	
	}
	while(!opStack.empty()) {
		switch (opStack.top().op) {
		case '(': case ')': break;
		default:
			postfix.push_back(opStack.top());
			break;
		}
		opStack.pop();
	}

	return;
}

int eval(const string & input) {
	vector<NumOp> infix;
	parse(input, infix);
	
	vector<NumOp> postfix;
	inToPost(infix, postfix);

	showExpr(infix); showExpr(postfix);

	return 0;
}

int main() {
	string inS;
	while (getline(cin, inS)) {
		int ans;
		ans = eval(inS);
		cout << ans;
	}
	return 0;
}

