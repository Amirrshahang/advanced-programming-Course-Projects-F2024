#include<iostream>
#include<string>
using namespace std;
string findURL(string& GitUrl){
		GitUrl.insert(5, "://");
		GitUrl.insert(GitUrl.find("github"), ".");
		GitUrl.insert(GitUrl.find("github")+6, ".");
		GitUrl.insert(GitUrl.find("github")+9, "/");
		if(GitUrl.find("query")!= string::npos){
			GitUrl.insert(GitUrl.find("query"), "/");
			GitUrl.insert(GitUrl.find("query")+5, "=");
			}

	return GitUrl;
}
int main()
{
	string input;
	cin >> input ;
	cout << findURL(input) << endl ;	
}



