#include "global.hpp"
#include "UserManager.hpp"
#include "DistrictManager.hpp"
#include "RestaurantManager.hpp"


void loadFils(const string& restaurantsFilePath,const string& districtsFilePath, DistrictManager& districtManager, RestaurantManager& restaurantManager){

    string restaurantsFile = restaurantsFilePath; 
    string districtsFile = districtsFilePath;  
    restaurantManager.loadRestaurantsFromCSV(restaurantsFile);
    districtManager.loadFromCSV(districtsFile);
}

void commandHandler(const string& command,UserManager& userManager,DistrictManager& districtManager, RestaurantManager& restaurantManager){
  smatch match;
    if (regex_match(command, match, regexPatterns.at("signup"))) {
        string username = match[1];
        string password = match[2];

        try {
            string result = userManager.signup(username, password, districtManager);
            cout << result << endl;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("login"))) {
        string username = match[1];
        string password = match[2];

        try {
            string result = userManager.login(username, password);
            cout << result << endl;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("logout"))) {
        try {
            string result = userManager.logout();
            cout << result << endl;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("districts"))) {
        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                districtManager.printAllDistricts();
            }
            else {
                throw runtime_error("Permission Denied");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("districtDetail"))) {
        string districtName = match[1];

        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                districtManager.printNeighbors(districtName);
            }
            else {
                throw runtime_error("Permission Denied");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("putDistrict"))) {
        string districtName = match[1];
        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                userManager.assignDistrictToUser(username, districtName);  
                cout << "OK" << endl;
            } else {
                throw runtime_error("Permission Denied");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("getRestaurants"))) {
        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                string userDistrict = userManager.getUserDistrict(username);
                if (userDistrict.empty()) { 
                    throw runtime_error("Not Found");
                }
                restaurantManager.getRestaurantsByProximity(userDistrict);
            } else {
               throw runtime_error("Permission Denied");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("getRestaurantsByFood"))) {
        string foodName = match[1];
        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                string userDistrict = userManager.getUserDistrict(username);
                if (userDistrict.empty()) { 
                    throw runtime_error("Not Found");
                }
                restaurantManager.getRestaurantsByFood(foodName,userDistrict);
            } else {
                throw runtime_error("Permission Denied");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("restaurantDetail"))) {
        string restaurantName = match[1];
        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                try {
                    Restaurant* restaurant = restaurantManager.findRestaurantByName(restaurantName);
                    restaurant->printRestaurantDetails();
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }       
            } else {
                throw runtime_error("Permission Denied");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
            }
    } else if (regex_match(command, match, regexPatterns.at("reserveWithFoods"))) {
        try {
           string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                string restaurantName = match[1];
                int tableId = stoi(match[2]);
                int startTime = stoi(match[3]);
                int endTime = stoi(match[4]);
                vector<pair<string, int>> orderedFoods;

                if (match[5].matched) {
                string foodsStr = match[5];
                map<string, int> foodCounts;

                istringstream ss(foodsStr);
                string food;
                while (getline(ss, food, ',')) {
                    foodCounts[food]++;
                }

                for (const auto& [foodName, count] : foodCounts) {
                  orderedFoods.emplace_back(foodName, count);
                    }
                }
                try {
                    restaurantManager.reserveTable(restaurantName, tableId, startTime, endTime, username, orderedFoods);
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }
            } else {
                throw runtime_error("Permission Denied");
            }
        }catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("reserves"))) {
       try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                restaurantManager.showAllUserReservations(username);
            }else{
                throw runtime_error("Permission Denied");
            }
        }catch (const runtime_error& e) {
            cout << e.what() << endl;
        }  
    } else if (regex_match(command, match, regexPatterns.at("reservesWithDetail"))) {
        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {

                string restaurantName = match[1].matched ? match[1].str() : ""; 
                string reserveId = match[2].matched ? match[2].str() : "";

                if (reserveId.empty()) {
                    restaurantManager.showUserReservations(username, restaurantName);

                } else {
                    restaurantManager.showUserReservationById(username, restaurantName, reserveId);
                }
            }else{
                throw runtime_error("Permission Denied");
            }
        }catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("deleteReserve"))) {
        try {
            string username = userManager.getLoggedInUsername();
            if (!username.empty()) {
                string restaurantName = match[1];
                int reserveId = stoi(match[2]);
                restaurantManager.deleteReservation(username, restaurantName, reserveId);
            }else{
                throw runtime_error("Permission Denied");
            }
        }catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    } else if (regex_match(command, match, regexPatterns.at("BadRequest"))) {
       throw runtime_error("Bad Request");
    } else if (regex_match(command, match, regexPatterns.at("BadRequest2"))) {
       throw runtime_error("Bad Request");
    }
    else{
        cout << "Not Found" << endl;
    }
}


void processCommand(const string& command, UserManager& userManager, DistrictManager& districtManager, RestaurantManager& restaurantManager) {

    const string validMethods[] = {"GET", "POST", "PUT", "DELETE"};
    bool isValid = false;

    for (const auto& method : validMethods) {
        if (command.find(method) == 0) {
            isValid = true;
            break;
        }
    }
    if (!isValid) {
        throw runtime_error("Bad Request");
    }
    commandHandler(command,userManager,districtManager,restaurantManager);
}

int main(int argc, char* argv[]) {
    string command;
    UserManager userManager;
    DistrictManager districtManager;
    RestaurantManager restaurantManager(districtManager); 

    loadFils(argv[1],argv[2],districtManager,restaurantManager);

    while (getline(cin, command)) {
        try {
            processCommand(command, userManager, districtManager, restaurantManager);
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
