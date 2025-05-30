#include <iostream>
#include <string>
#include <vector>

using namespace std;
const char Addition = '+' ;
const char Subtraction = '-' ;
const char Multiplication = '*' ;
const char ZeroString = '0' ;

int checkingOperator(int leftNumber, int rightNumber, char oprator) {
     switch(oprator) {
        case Addition: return leftNumber + rightNumber;
        case Subtraction: return leftNumber - rightNumber;
        case Multiplication: return leftNumber * rightNumber;
        default: return 0;
            }
}
vector<int> removeDuplicates(const vector<int>& DuplicatedVector) {
    vector<int> result;
    for (int num : DuplicatedVector) {
        if (find(result.begin(), result.end(), num) == result.end()) {
            result.push_back(num);
        }
    }
    return result;
}

vector<int> calculateResult(const string &expression, int start, int end) {
    vector<int> results;

    bool isNumber = true;
    int number = 0;

    for (int i = start; i <= end; ++i) {
        if (!isdigit(expression[i])) {
            isNumber = false;
            break;
        }
        number = number * 10 + (expression[i] - ZeroString);
    }

    if (isNumber) {
        results.push_back(number);
        return results;
    }

    for (int i = start; i <= end; ++i) {
        if (expression[i] == Addition || expression[i] == Subtraction || expression[i] == Multiplication) {

            auto leftResults = calculateResult(expression, start, i - 1);
            auto rightResults = calculateResult(expression, i + 1, end);

            for (auto left = leftResults.begin(); left != leftResults.end(); ++left) {
                for (auto right = rightResults.begin(); right != rightResults.end(); ++right) {
                    results.push_back(checkingOperator(*left, *right, expression[i]));
                }
            }
        }
    }
    return results;
}

void handleInputs(){
    int number;
    string expression;
    
    cin >> number;
    cin >> expression;

    vector<int> results = removeDuplicates(calculateResult(expression, 0, expression.size() - 1));
    cout << results.size() << endl;
}

int main() {

    handleInputs();

    return 0; 

}
