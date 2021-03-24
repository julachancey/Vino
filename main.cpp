#include "AVLTree.h"
#include "adjacencyList.h"
#include <fstream> 
#include <chrono>

void readDataTree(string wineType, string location, string budget);
void readDataList(string wineType, string location, string budget);
 Tree tree = Tree(); // AVL Tree
string myTime;

int main(){

    string wineType;
    string location;
    string budget;

    int option = 0;

    while (option != 5){
        cout << "======================================================================" << endl;
        cout << "      Welcome to VINO! Please select one of the following options:" << endl << endl;
        cout << "                  1. Variety             2. Country " << endl; 
        cout << "                  3. Budget              4. Show me!" << endl;
        cout << "                              5. Exit" << endl; 
        cout << "======================================================================" << endl;

        cout <<"Option: ";
        cin >> option;

        if (option > 5 || option < 1){
            cout << "Come on now. Don't be rude." << endl;
        }
        else{
            if (option == 1){
                cout << "Excellent! What variety shall we go with today?" << endl;
                cin.ignore(); // gets rid of any extra whitespace before entry 
                getline(cin, wineType);
            }

            if (option == 2){
                cout << "Fantastic! What lovely country shall you choose?" << endl;
                cin.ignore();
                getline(cin, location);
            }

            if (option == 3){
                cout << "Magnificent! What's your budget looking like today?" << endl;
                cin.ignore();
                getline(cin, budget);
            }

            if (option == 4){
                if (wineType != "" && location != "" && budget != ""){
                    readDataList(wineType, location, budget);
                    readDataTree(wineType, location, budget);
                    
                    return 0;
                }
                else{
                    cout << "Wait! You forgot to enter something!" << endl;
                }
            }

            if (option == 5){
                cout << "Sounds good. Have a great day!" << endl << endl;
                cout << "        |       |" << endl;
                cout << "        \\      / " << endl;
                cout << "         \\    /" << endl;
                cout << "          \\  /" << endl;
                cout << "           ||" << endl;
                cout << "           ||" << endl;
                cout << "           ||" << endl;
                cout << "        --------" << endl;
                return 0;
            }
        }
    }

    return 0;
}

void readDataTree(string wineType, string location, string budget){
    string country, province, region, title, variety, points, price, ppp;
    float pricePerPoint;
    int myCount = 0;

   
    
    
    auto treeStart = std::chrono::high_resolution_clock::now();

    ifstream loadedFile("winemag-data-130k-v2.csv");
    string fileLine;
    getline(loadedFile, fileLine); 
    getline(loadedFile, fileLine); // ^^ getting rid of headers 
    
    while (getline(loadedFile, fileLine)){
        istringstream streem(fileLine); // turns line into stream 

        getline(streem, country, ','); 
        getline(streem, points, ','); 
        getline(streem, price, ','); 
        getline(streem, province, ','); 
        getline(streem, region, ','); 
        getline(streem, title, ',');
        getline(streem, variety, ','); 
        getline(streem, ppp);

        try{
            if (variety == wineType && country == location && stoi(price) <= stoi(budget)){ // only add values that match the variety, location and budget
                tree.addNode(title, variety, country, province, region, stof(ppp), stoi(price));
                //myCount += list.addVino(country, title, points, price, province, region, variety, ppp); 
            } 
        }
        catch(exception e){ } // skips adding any "problem entries" (missing data, incorrect data, etc.)
        
    }
    auto treeEnd = std::chrono::high_resolution_clock::now();
    // timing help from https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
    cout << "                           RESULTS"<< endl;


    tree.print();
    cout << endl;

cout << "                           AVL TREE TIME"<< endl;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(treeEnd - treeStart ).count();
    cout << "\n                TOTAL TIME TAKEN: " << duration << " MICROSECONDS" << endl;

    cout << endl;

    cout << "                           ADJACENCY LIST TIME"<< endl;
    
    cout << myTime << endl;
    cout << endl;





}

void readDataList(string wineType, string location, string budget){
    string country, province, region, title, variety, points, price, ppp;
    float pricePerPoint;
    int myCount = 0;

    
    Lista list; // adjacency list
    
    auto listStart = std::chrono::high_resolution_clock::now();

    ifstream loadedFile("winemag-data-130k-v2.csv");
    string fileLine;
    getline(loadedFile, fileLine); 
    getline(loadedFile, fileLine); // ^^ getting rid of headers 
    
    while (getline(loadedFile, fileLine)){
        istringstream streem(fileLine); // turns line into stream 

        getline(streem, country, ','); 
        getline(streem, points, ','); 
        getline(streem, price, ','); 
        getline(streem, province, ','); 
        getline(streem, region, ','); 
        getline(streem, title, ',');
        getline(streem, variety, ','); 
        getline(streem, ppp);

        try{
            if (variety == wineType && country == location && stoi(price) <= stoi(budget)){ // only add values that match the variety, location and budget
                //tree.addNode(title, variety, country, province, region, stof(ppp), stoi(price));
                myCount += list.addVino(country, title, points, price, province, region, variety, ppp); 
            } 
        }
        catch(exception e){ } // skips adding any "problem entries" (missing data, incorrect data, etc.)
        
    }
    auto listEnd = std::chrono::high_resolution_clock::now();
    // timing help from https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
    //cout << "                           ADJACENCY LIST TIME"<< endl;

    //auto treeStart = std::chrono::high_resolution_clock::now();
    //tree.print();
    //auto treeEnd = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(listEnd - listStart ).count();
    myTime = "\n                TOTAL TIME TAKEN: " + to_string(duration) + " MICROSECONDS";
}