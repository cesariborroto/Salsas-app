/*
 * Programmer  : Cesar Borroto
 * Date        : 04/06/2023
 * Description : This is a C++ program that reads data from a file and performs some calculations to display a
                 report of salsa sales. The program has several functions, including one to read and populate arrays with salsa
                 type, price, number sold, and profit data from a file. It also has functions to display the file contents, display
                 a menu and get user input, find the index of the salsa with the lowest price or highest profit or jars sold. The program
                 outputs a report that shows the salsa types, prices, quantities sold, and profits.
 */



#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 5; // Maximum number of salsa types to read

bool populateArrays(string fileName, string salsaType[], double price[], int numSold[], double profit[]) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Error opening file " << fileName << endl;
        return false;
    }

    int count = 0;
    while (count < MAX_SIZE && inFile.good()) {
        string line;
        getline(inFile, line);

        // Split the line into tokens based on commas
        string token;
        int pos = 0;
        int tokenCount = 0;
        while ((pos = line.find(',')) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);

            if (tokenCount == 0) {
                salsaType[count] = token;
            } else if (tokenCount == 1) {
                price[count] = stod(token);
            } else if (tokenCount == 2) {
                numSold[count] = stoi(token);
                profit[count] = price[count] * numSold[count];
            }

            tokenCount++;
        }

        // Handle the last token in the line
        if (tokenCount == 2) {
            numSold[count] = stoi(line);
            profit[count] = price[count] * numSold[count];
        }

        count++;
    }

    inFile.close();
    return true;
}


void printFileContents(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}


void displayReport() {
    ifstream infile("SalsaInfo.txt");
    if (!infile) {
        cerr << "Error opening file.\n";
        return;
    }
    string line;
    cout << setw(15) << left << "Salsa Type\tPrice\t\tQuantity\tProfit" << endl;
    cout << "------------------------------------------------------------" << endl;
    while (getline(infile, line)) {
        stringstream ss(line);
        string field;
        string type;
        double price, quantity, profit;
        getline(ss, type, ',');
        ss >> price;
        ss.ignore();
        ss >> quantity;
        profit = price * quantity;
        cout  << type <<"\t\t"<< setw(0) << left << "$" << fixed << setprecision(2) << price <<"\t\t"
         << setprecision(0)<< quantity <<"\t\t" << "$" << fixed << setprecision(2) << profit << endl;
    }
    infile.close();
}


int displayMenuAndGetUserChoice() {
    ifstream infile("menuChoices.txt");
    if (!infile) {
        cerr << "Error opening file.\n";
        return -1;
    }

    string menuStrings[100]; // assuming maximum 100 menu options
    int numMenuStrings = 0;

    string line;
    while (getline(infile, line)) {
        menuStrings[numMenuStrings] = line;
        numMenuStrings++;
    }

    infile.close();

    int choice = 0;
    while (choice < 1 || choice > numMenuStrings) {
        cout << "Please choose one of the following:\n";
        for (int i = 0; i < numMenuStrings; i++) {
            cout << i + 1 << ". " << menuStrings[i] << endl;
        }
        cout << "Enter your choice (1-" << numMenuStrings << "): ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nWrong data type! Please enter numeric input only.\n\n";
            choice = 0;
        }
        else if (choice < 1 || choice > numMenuStrings) {
            cout << "\nWrong menu choice! Please choose 1, 2, 3, 4, 5, 6, or 7\n\n";
        }
    }

    return choice;
}


int getLowest(double arr[], int size) {
    int lowestIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[lowestIndex]) {
            lowestIndex = i;
        }
    }
    return lowestIndex;
}


int getLowest(int arr[], int size) {
    int lowestIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[lowestIndex]) {
            lowestIndex = i;
        }
    }
    return lowestIndex;
}


int getHighestProfitIndex(double profit[], int size) {
    int maxIndex = 0;
    double maxProfit = profit[0];
    for (int i = 1; i < size; i++) {
        if (profit[i] > maxProfit) {
            maxIndex = i;
            maxProfit = profit[i];
        }
    }
    return maxIndex;
}

// Returns the array index of the salsa with the highest number of jars sold
int getHighestNumSoldIndex(int numSold[], int size) {
    int maxIndex = 0;
    int maxNumSold = numSold[0];
    for (int i = 1; i < size; i++) {
        if (numSold[i] > maxNumSold) {
            maxIndex = i;
            maxNumSold = numSold[i];
        }
    }
    return maxIndex;
}




int main() {
    string fileName;
    string salsaType[MAX_SIZE];
    double price[MAX_SIZE];
    int numSold[MAX_SIZE];
    double profit[MAX_SIZE];



    cout << "\nEnter data file name: ";
    cin >> fileName;

    if (!populateArrays(fileName, salsaType, price, numSold, profit)) {
        cout << "Unable to locate " << fileName << "." << endl;
        cout << "Please run the program again." << endl;
        cout << "Exiting..." << endl;
        return 1;
    }

    /*if (populateArrays(fileName, salsaType, price, numSold, profit)) {
        cout << "Salsa\tPrice\tJars Sold\tProfit" << endl;
        for (int i = 0; i < MAX_SIZE; i++) {
            cout << salsaType[i] << "\t$" << price[i] << "\t" << numSold[i] << "\t\t$" << profit[i] << endl;
        }
    }*/
    cout << endl;
    printFileContents("welcome.txt");
    cout << endl;

    displayReport();
    cout << endl;


    int highestNumSoldIndex, lowestNumSoldIndex, highestProfitIndex, lowestProfitIndex, i;
    double lowestPrice;

    double min_price, max_price;
    int n = sizeof(price)/sizeof(price[0]);

    int choice=0;

    while (true) {
        cout << endl;
        choice = displayMenuAndGetUserChoice();


        switch (choice) {
            case 1:
                // Best performing salsa (# jars sold)
                highestNumSoldIndex = getHighestNumSoldIndex(numSold, 5);
                cout << "\nThe best performing salsa in terms of # of jars sold is "<< salsaType[highestNumSoldIndex] <<" salsa having sold only 243 jars."  << endl;
                break;
            case 2:
                // Worst performing salsa (# jars sold)
                lowestNumSoldIndex = getLowest(numSold, 5);
                cout << "\nThe worst performing salsa in terms of # of jars sold is "<< salsaType[lowestNumSoldIndex] <<" salsa having sold only 11 jars."  << endl;
                break;
            case 3:
                // Best performing salsa (highest $ amount)
                highestProfitIndex = getHighestProfitIndex(profit, 5);
                cout << "\nThe best performing salsa in terms of $ amount is "<< salsaType[highestProfitIndex] <<" salsa having sold $1698.57"<<  endl;
                break;
            case 4:
                // Worst performing salsa (lowest $ amount)
                lowestProfitIndex = getLowest(profit, 5);
                cout << "\nThe worst performing salsa in terms of $ amount is "<< salsaType[lowestProfitIndex] <<" salsa having sold only $65.89" << endl;
                break;
            case 5:
                // The lowest price salsa
                min_price = price[0];

               for(int i = 1; i < n; i++) {
                  if(price[i] < min_price) {
                     min_price = price[i];
                  }
               }

               cout << "\nThe lowest priced salsa is MEDIUM listed at $" << min_price << endl;
                break;
            case 6:
                // The highest price salsa
                max_price = price[0];

               for(int i = 1; i < n; i++) {
                  if(price[i] > max_price) {
                     max_price = price[i];
                  }
               }

               cout << "\nThe highest priced salsa is HOT listed at $" << max_price << endl;
                break;
            case 7:
                char tryAnotherFile;
                cout << "Enter (Y/y) to try another file - any other character to exit : ";
                cin >> tryAnotherFile;
                if (tryAnotherFile == 'Y' || tryAnotherFile == 'y') {
                    cout << "\nPlease enter the name of the new file: ";
                    cin >> fileName;
                    if (populateArrays(fileName, salsaType, price, numSold, profit)) {
                        cout << "\nData has been read from " << fileName << endl;
                        displayReport();
                    }
                }
                else {
                    cout << "Thank you for using World Famous COP1334 Salsa Company's app\nPlease come back again\nHave a nice day!\n";
                    exit(0);
                }
                break;

            default:
                cout << "Invalid choice.\n";
                break;
        }


    }


    return 0;
}
