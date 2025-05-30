#include<iostream>
#include<string>
#include <regex>
#include<vector>
#include<cmath>
using namespace std;

vector<double> Operations(vector<string> v){
	int num1;
	int num2;
	double po ;
	vector <double> result;
	regex pattern(R"(\d+\s?[\+\-\/\*\^]\s?\d+)");

		for(int j =0; j < v.size();++j){ 
		  	if(regex_match(v[j],pattern)){
				if(v[j].find('+')!=string::npos){
 					po = v[j].find('+');
 					num1 = stoi(v[j].substr(0, po)); 
            		num2 = stoi(v[j].substr(po + 1));
 					result.push_back(num1 + num2);
	 			}
	 			if(v[j].find('-')!=string::npos){
 					po = v[j].find('-');
 					num1 = stoi(v[j].substr(0, po)); 
            		num2 = stoi(v[j].substr(po + 1));
 					result.push_back(num1 - num2);
 				}
 				if(v[j].find('/')!=string::npos){
 					po = v[j].find('/');
 					num1 = stoi(v[j].substr(0, po)); 
            		num2 = stoi(v[j].substr(po + 1));
 					if (num2 != 0) 
 					result.push_back(floor(num1 / num2));
              	 }
 				if(v[j].find('*')!=string::npos){
 					po = v[j].find('*');
 					num1 = stoi(v[j].substr(0, po)); 
            		num2 = stoi(v[j].substr(po + 1));
 					result.push_back(num1 * num2);
 				}
 				if(v[j].find('^')!=string::npos){
 					po = v[j].find('^');
 					num1 = stoi(v[j].substr(0, po)); 
           	 		num2 = stoi(v[j].substr(po + 1));
 			   		result.push_back(pow(num1,num2));

 				}
 			}
 			else
 				cout<<"error";
 		}
		return result;
	}
int main(){
	vector<string> v;
	int NumberOfInputs;
	string operation;
	cin >> NumberOfInputs;
	cin.ignore();

	for(int i = 0 ; i < NumberOfInputs ; ++i){
		getline(cin,operation);
		v.push_back(operation);
	}
	for(int i =0; i < v.size();++i)
		cout << Operations(v)[i] << endl;
	
}
