#include <iostream>
#include <vector>

using namespace std;

int myMin(int a, int b){
    return (a < b) ? a : b;
}


int ShayansCost(int i, const vector<int>& a) {
    if (i == 0) return 0;  

    int TotalCost = ShayansCost(i - 1, a) + abs(a[i] - a[i - 1]);

    if (i > 1) {
        TotalCost = myMin(TotalCost, ShayansCost(i - 2, a) + abs(a[i] - a[i - 2]));
    }

    return TotalCost;
}

void handleInput(){
    int numberOfcolleges;
    cin >> numberOfcolleges;
    vector<int> listOfshirini(numberOfcolleges);

    for (int i = 0; i < numberOfcolleges; i++) {
        cin >> listOfshirini[i];
    }

    cout << ShayansCost(numberOfcolleges - 1, listOfshirini) << endl;  
}

int main() {

    handleInput();

    return 0;
}
