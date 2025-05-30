#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <regex>
#include <map>

using namespace std;

struct carsCSV
{
	string CarsModel;
	int size;
};
struct ParkingMap
{
	int id;
	int size;
	string type;
	int daysUsed = 0;
	bool isOccupied = false;
};
struct PriceMap
{
	int size;
	int static_price;
	int price_per_day;
};
struct ParkingSystemData
{
	vector<carsCSV> Carsvector;
	vector<ParkingMap> Parkingvector;
	vector<PriceMap> Pricevector;
};

vector<string> SplitCSVLine(const string &line)
{
	vector<string> tokens;
	regex findComma(",");
	sregex_token_iterator it(line.begin(), line.end(), findComma, -1);
	sregex_token_iterator end;
	while (it != end)
	{
		tokens.push_back(*it++);
	}
	return tokens;
}
void sortingVector(ParkingSystemData &data)
{
	std::sort(data.Parkingvector.begin(), data.Parkingvector.end(), [](const ParkingMap &a, const ParkingMap &b)
			  { return a.id < b.id; });
}

void createCarsStruct(carsCSV &newcarsCSV, vector<string> &tokens)
{
	newcarsCSV.CarsModel = tokens[0];
	newcarsCSV.size = stoi(tokens[1]);
}
void createSpotsStruct(ParkingMap &newparking, vector<string> &tokens)
{
	newparking.id = stoi(tokens[0]);
	newparking.size = stoi(tokens[1]);
	newparking.type = tokens[2];
}
void createPriceStruct(PriceMap &newPrice, vector<string> &tokens)
{
	newPrice.size = stoi(tokens[0]);
	newPrice.static_price = stoi(tokens[1]);
	newPrice.price_per_day = stoi(tokens[2]);
}

void carsDataToStruct(const string &line, ParkingSystemData &data)
{
	carsCSV newcarsCSV;
	vector<string> tokens = SplitCSVLine(line);
	createCarsStruct(newcarsCSV, tokens);
	data.Carsvector.push_back(newcarsCSV);
}
void parkingDataToStruct(const string &line, ParkingSystemData &data)
{
	ParkingMap newparking;
	vector<string> tokens = SplitCSVLine(line);
	createSpotsStruct(newparking, tokens);
	data.Parkingvector.push_back(newparking);
}
void pricesDataToStruct(const string &line, ParkingSystemData &data)
{
	PriceMap newPrice;
	vector<string> tokens = SplitCSVLine(line);
	createPriceStruct(newPrice, tokens);
	data.Pricevector.push_back(newPrice);
}
void LoadCarsData(const string &carsFile, ParkingSystemData &data)
{
	string line;
	ifstream file(carsFile);
	getline(file, line);
	while (getline(file, line))
		carsDataToStruct(line, data);
}
void LoadSpotData(const string &spotFile, ParkingSystemData &data)
{
	string line;
	ifstream file(spotFile);
	getline(file, line);
	while (getline(file, line))
		parkingDataToStruct(line, data);
	sortingVector(data);
}
void LoadPriceData(const string &priceFile, ParkingSystemData &data)
{
	ifstream file(priceFile);
	string line;
	getline(file, line);
	while (getline(file, line))
		pricesDataToStruct(line, data);
}

void LoadData(const string &carsFile, const string &spotFile,
			  const string &priceFile, ParkingSystemData &data)
{
	LoadCarsData(carsFile, data);
	LoadSpotData(spotFile, data);
	LoadPriceData(priceFile, data);
}
pair<int, int> CalculatePrices(int size, string type,ParkingSystemData &data)
{
	int staticPrice = 0;
	int pricePerday = 0;
	for (const auto &price_entry : data.Pricevector)
	{
		if (price_entry.size == size)
		{
			staticPrice = price_entry.static_price;
			pricePerday = price_entry.price_per_day;

			if (type == "covered")
			{
				staticPrice += 50;
				pricePerday+=30;
			}
			if (type == "CCTV")
			{
				staticPrice += 80;
				pricePerday+=60;
			}
		}
	}

	return {staticPrice, pricePerday};
}
void showParkingInfo(const int &carSize, ParkingSystemData &data)
{
	for (auto it = data.Parkingvector.begin(); it != data.Parkingvector.end(); ++it)
	{
		if (it->size == carSize && !it->isOccupied)
		{
			auto [static_price, price_per_day] = CalculatePrices(it->size, it->type,data);
			cout << it->id << ": " << it->type << " " << static_price << " " << price_per_day << endl;
		}
	}
}
int findEmptyParkings(string &line, ParkingSystemData &data)
{
	int carSize;
	string carmodel = line.substr(line.find(' ') + 1);
	for (auto it = data.Carsvector.begin(); it != data.Carsvector.end(); ++it)
	{
		if (it->CarsModel == carmodel)
		{
			carSize = it->size;
			break;
		}
	}
	return carSize;
}
void RequestSpot(string &line, ParkingSystemData &data)
{
	int carSize = findEmptyParkings(line, data);
	showParkingInfo(carSize, data);
}
void AssignSpot(string &line, ParkingSystemData &data)
{
	int AssignedID = stoi(line.substr(line.find(' ') + 1));
	for (auto it = data.Parkingvector.begin(); it != data.Parkingvector.end();)
	{
		if (it->id == AssignedID && it->isOccupied == false)
		{
			it->isOccupied = true;
			cout << "Spot " << AssignedID << " is occupied now." << endl;
		}
		else
			++it;
	}
}
void PassTime(string &line, ParkingSystemData &data)
{
	int findSpace= line.find(" ");
	int dayPassed = stoi(line.substr(findSpace + 1));
	for (auto it = data.Parkingvector.begin(); it != data.Parkingvector.end(); ++it)
	{
		if (it->isOccupied)
			it->daysUsed = dayPassed + it->daysUsed;
	}
}
int FreeSpot(const vector<ParkingMap>::iterator &it,ParkingSystemData &data)
{
	int static_price = 0;
	int price_per_day = 0;
	pair<int, int> prices = CalculatePrices(it->size, it->type,data);
	static_price = prices.first;
	price_per_day = prices.second * it->daysUsed;
	it->isOccupied = false;
	return static_price + price_per_day;
}
void PrintCost(const int &AssignedOutID, const int &totalCost)
{

	cout << "Spot " << AssignedOutID << " is free now." << endl;
	cout << "Total cost: " << totalCost << endl;
}
void CheckOut(string &line, ParkingSystemData &data)
{
	int totalCost;
	int AssignedOutID = stoi(line.substr(line.find(' ') + 1));
	for (auto it = data.Parkingvector.begin(); it != data.Parkingvector.end(); ++it)
	{
		if (it->id == AssignedOutID && it->isOccupied)
			totalCost = FreeSpot(it,data);
	}
	PrintCost(AssignedOutID, totalCost);
}
map<string, function<void(string &, ParkingSystemData &)>> inputMap()
{
	return {
		{"request_spot", RequestSpot},
		{"assign_spot", AssignSpot},
		{"pass_time", PassTime},
		{"checkout", CheckOut},
	};
}
void processInput(ParkingSystemData &data)
{
	string command;
	while (getline(cin, command))
	{
		for (const auto &[cmd, func] : inputMap())
		{
			if (command.find(cmd) == 0)
			{
				func(command, data);
				break;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	ParkingSystemData data;
	LoadData(argv[1], argv[2], argv[3], data);
	processInput(data);

	return 0;
}
