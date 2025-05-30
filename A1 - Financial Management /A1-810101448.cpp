#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Category {
	string category_name;                  
	vector<string> subcategories; 
	vector<int> category_expenses;
	vector<vector<int>> subcategory_expenses;
};
void CreateCategory(string& command,list<Category>& collection) {
	Category CreatedCategory;
	int possion = command.find(' ')+1;
	int possion2 = command.find(' ',possion);

	if (possion2!=string::npos){
		CreatedCategory.category_name = command.substr(possion , possion2 - possion);

		int start = possion2 + 1;
		while ((possion2 = command.find(' ', start)) != string::npos) {
			CreatedCategory.subcategories.push_back(command.substr(start, possion2 - start));
			start = possion2 + 1;
			}

		CreatedCategory.subcategories.push_back(command.substr(start));
		CreatedCategory.subcategory_expenses.resize(CreatedCategory.subcategories.size());
	}
	else{
		CreatedCategory.category_name = command.substr(possion , command.size() - possion);
	}
	collection.push_back(CreatedCategory);
}
void SubcatExpense(string& command,list<Category>& collection){

	int possion = command.find(' ')+1;
	int possion2 = command.find(' ',possion);
	int expense = 0;

	if(command.find("add_expense")==0)
		expense = stoi(command.substr(possion2 + 1));

	int slash = command.find('/');
	string categoryName;
	if(command.find("/")!=string::npos)
		categoryName = command.substr(possion, slash-possion);
	else
		categoryName = command.substr(possion, possion2-possion);

	for (auto it = collection.begin(); it != collection.end(); ++it) {
		if (it->category_name == categoryName) {
			if(command.find("/")!=string::npos){

				string subcategoryName;
				int start = command.find("/");
				int end = command.find(' ', start);
				string key = command.substr(start+1, end - start-1); 

				auto it2 = find(it->subcategories.begin(), it->subcategories.end(), key);
				int index = distance(it->subcategories.begin(), it2);
					if(command.find("add_expense")==0)
						it->subcategory_expenses[index].push_back(expense);
					if(command.find("remove_expense")==0)
						it->subcategory_expenses[index].pop_back();
			}
			else{

				if(command.find("add_expense")==0)
					it->category_expenses.push_back(expense);
				if(command.find("remove_expense")==0)
					it->category_expenses.pop_back();
			}
		}
	}
}
void Report(string& command,list<Category>& collection){
	if(collection.empty()){
		cout << "\n";
		return;
	}

	collection.sort([](Category& a ,Category& b){
		return a.category_name < b.category_name;
	});

	int sum,sum2=0,MinExpense=0;
	int EndOfCategories = 0;
	vector<vector<string>> expenses;

	if(command.find(' ')!=string::npos){
		int possion = command.find(' ');
		MinExpense = stoi(command.substr(possion+1));
	}

	for (auto it = collection.begin(); it != collection.end(); ++it) {

		expenses.clear();
		sum = 0;
		cout <<"Category: "<<it->category_name <<endl;

		for (auto exp:it->category_expenses) {
        sum += exp;
	    }

		for (int i = 0; i < it->subcategories.size(); ++i) {
			for (auto sub_expense : it->subcategory_expenses[i]) {
				sum2+=sub_expense;
			}

		}
		cout <<"Total expenses: "<< sum+sum2 <<endl;
		cout <<"Subcategories expenses:" << endl;
		sum2=0;
		for (int i = 0; i < it->subcategories.size(); ++i) {
			int sum3 = 0;
																//    snap bus taxi	
			for (auto sub_expense : it->subcategory_expenses[i]) { // [[ ],[ ],[ ]]
				sum3+=sub_expense;							
			}
			expenses.push_back({it->subcategories[i], to_string(sum3)});	// [[snap,'1000'],[bus,'300'],[]]
		}
		sort(expenses.begin(), expenses.end(), []( vector<string>& a, vector<string>& b) {
			if (stoi(a[1]) != stoi(b[1])) {
				return stoi(a[1]) > stoi(b[1]); 
			}
			return a[0] < b[0];
		});
		for (auto it2 = expenses.begin(); it2 != expenses.end(); ++it2) {
    		if (stoi((*it2)[1]) < MinExpense)
				continue;
			else
        		cout << "    - " << (*it2)[0] << ": "<< (*it2)[1] << endl;
		}
			++EndOfCategories;
			if(EndOfCategories == collection.size())
				cout<<"**********"<<endl;
			else
				cout<<"----------"<<endl;
	}
}
int main(){
	list<Category> collection;
	string command;
	while(getline(cin, command)){

		if(command.find("new_category") == 0){
			CreateCategory(command,collection);
		}
		if(command.find("add_expense") == 0 || command.find("remove_expense") == 0){
			SubcatExpense(command , collection);
		}
		if(command.find("report") == 0)
			Report(command,collection);
	}
	return 0;
}

/*
void PrintCategories(const list<Category>& collection) {
	for (const auto& c : collection) {
		cout << c.category_name << ": { ";
		for (const auto& s : c.subcategories) {
			cout << s << " ";
		}
		cout << "}" << endl;
	}
}
void PrintExpense(const list<Category>& collection){
	for (const auto& c : collection) {
		cout << endl;
		cout << c.category_name << " : ";
		for (int i = 0; i < c.category_expenses.size(); ++i) {
			cout << c.category_expenses[i] << " "; 
		}
		for (int i = 0; i < c.subcategory_expenses.size(); ++i) {
			cout << "\n";
			cout << "Subcategory " << c.subcategories[i] << " : ";
			for (const auto& sub_expense : c.subcategory_expenses[i]) {
				cout << sub_expense << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
void AddExpense(string& command,list<Category>& collection){
	
	int possion = command.find(' ');
	int possion2 = command.find(' ',possion+1);
	int slash = command.find('/');
	int expense = stoi(command.substr(possion2 + 1));
	string categoryName;

	if(command.find("/")!=string::npos)
		categoryName = command.substr(possion+1, slash-possion-1);
	else
		categoryName = command.substr(possion+1, possion2-possion-1);

	for (auto &category : collection) {
		if (category.category_name == categoryName) {
			if(command.find("/")!=string::npos){
				string subcategoryName;
				int start = command.find("/");
				int end = command.find(' ', start);
				string key = command.substr(start+1, end - start-1); 
				auto it = find(category.subcategories.begin(), category.subcategories.end(), key);
				if (it != category.subcategories.end()) {
					int index = distance(category.subcategories.begin(), it);
					category.subcategory_expenses[index].push_back(expense);
				}
			}
			else{
				category.category_expenses.push_back(expense);
			}
		}
	}
}
void RemoveExpense(string& command,list<Category>& collection){

	int possion = command.find(' ');
	int possion2 = command.find(' ',possion+1);
	int slash = command.find('/');
	string categoryName;
	
	if(command.find("/")!=string::npos)
		categoryName = command.substr(possion+1, slash-possion-1);
	else
		categoryName = command.substr(possion+1, possion2-possion-1);

	for (auto &category : collection) {
		if (category.category_name == categoryName) {
			if(command.find("/")!=string::npos){
				string subcategoryName;
				int start = command.find("/");
				int end = command.find(' ', start);
				string key = command.substr(start+1, end - start-1); 
				auto it = find(category.subcategories.begin(), category.subcategories.end(), key);
				if (it != category.subcategories.end()) {
					int index = distance(category.subcategories.begin(), it);
					category.subcategory_expenses[index].pop_back();
				}
			}
			else{
				category.category_expenses.pop_back();
			}
		}
	}
}

*/


