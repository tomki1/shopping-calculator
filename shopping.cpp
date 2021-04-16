/*********************************
 * name: Kimberly Tom
 * CS 325
 * Homework 3 - shopping.cpp calculates the maximum price for each family based on inputs and
 * writes the results to results.txt
 * 1/27/19
*********************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


using namespace std;


// this function takes in an array of item weights, item prices, a vector for each family member,
// the max weight a family member can carry, and the number of items
int knapsack(int *Wt, int *Pr, vector<int> &vec, int maxWt, int numItems) {
    // create a table
    int Table[numItems + 1][maxWt + 1];

    // with help from https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
    for (int x = 0; x <= numItems; x++) {
        for (int y = 0; y <= maxWt; y++) {
            if (x == 0 || y == 0) {
                Table[x][y] = 0;
            }
            else if (Wt[x-1] <= y) {
                if (Pr[x-1] + Table[x - 1][y - Wt[x - 1]] > Table[x - 1][y]) {
                    Table[x][y] = Pr[x - 1] + Table[x - 1][y - Wt[x-1]];
                }
                else {
                    Table[x][y] = Table[x - 1][y];
                }
            }
            else {
                Table[x][y] = Table[x - 1][y];
            }
        }
    }

    // with help from https://www.geeksforgeeks.org/printing-items-01-knapsack/
    int result = Table[numItems][maxWt];
    int y = maxWt;

    for (int x = numItems; result > 0 && x > 0; x--) {
        // if result is equivalent to the cell above, continue
        if (result == Table[x-1][y]) {
            continue;
        }
            // else, add item to the knapsack
        else {
            vec.push_back(x);
            // remove its value from the member's max value
            result = result - Pr[x-1];
            // remove its weight from the member's max weight
            y = y - Wt[x - 1];
        }
    }
    // this is the maximum price that can be carried by this particular family member
    return Table[numItems][maxWt];


}

int main() {

        ifstream inputFile;
        ofstream outputFile;


        int testCase; // number of test cases
        int N; // number of items
        int membersFam; // number of people in the family
        int maximumWeight; // max weight that a family member can carry
        int Prices[100]; // 100 prices since N can't be more than 100
        int Weights[100]; // 100 weights since N can't be more than 100

        vector<vector<int> > vectorItems(100); // vector to hold the items held by each family member


        maximumWeight = 0;

        // with help from http://www.cplusplus.com/doc/tutorial/files/

        inputFile.open("shopping.txt");

        if (inputFile.is_open()) {
            cout << "Opened shopping.txt successfully." << endl;
        }
        else {
            cout << "Error. Unable to open the shopping.txt file." << endl;
            return 1;
        }

        outputFile.open("results.txt");
        if (outputFile.is_open()) {
            cout << "Opened results.txt successfully." << endl;

        }
        else {
            cout << "Error. Unable to open the results.txt file." << endl;
            return 1;
        }

        // read the first line and store the number of test cases in testCase
        inputFile >> testCase;

        // loop for testCase number of cases
        for (int cases = 0; cases < testCase; cases++) {
            //  read the number of items from shopping.txt and store it in N
            inputFile >> N;

            // loop for N number of items
            for (int itemCount = 0; itemCount < N; itemCount++) {
                // read the price of each item and the weight of each item from shopping.txt
                // put prices in Prices array and weights in Weights array
                inputFile >> Prices[itemCount];
                inputFile >> Weights[itemCount];
            }

            // create variable to hold maximum price for a family member
            int maximumPrice = 0;

            // read the number of family members and store in membersFam
            inputFile >> membersFam;

            // loop to find the maximum price of items that each person in the family can carry
            for (int i = 0; i < membersFam; i++) {
                // read the maximum weight the ith family member can hold
                inputFile >> maximumWeight;

                // call the knapsack function with the best benefit and add to maximumPrice
                maximumPrice += knapsack(Weights, Prices, vectorItems[i], maximumWeight, N);
            }

            outputFile << "Test Case " << cases + 1 << endl;
            outputFile << "Total Price " << maximumPrice << endl;
            outputFile << "Member Items: " << endl;

            // print the items that each member took
            // with help from https://www.geeksforgeeks.org/sorting-a-vector-in-c/
            for (int member = 0; member < membersFam; member++) {
                outputFile << "" << member + 1 << ": ";
                int vectorLength = vectorItems[member].size();
                sort(vectorItems[member].begin(), vectorItems[member].end());
                for (int items = 0; items < vectorLength; items ++) {
                    outputFile << vectorItems[member][items] << " ";
                }
                outputFile << endl;



                // clear the vector
                for (int items = 0; items < vectorLength; items++) {
                    vectorItems[member][items] = 0;
                            for (int members = 0; members < vectorLength; members++) {
                                vectorItems[member].clear();
                            }
                }
            }
            outputFile << endl;
        }

    inputFile.close();
    outputFile.close();
    return 0;
}
