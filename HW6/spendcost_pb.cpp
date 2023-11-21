#include <iostream>
#include <algorithm>

using namespace std;
#define OUT_FILE = "spendcost_pb_out.txt"

class TestSet {
public:
    int* aSal;
    int* bSal;
    int n;
    int F, Da, Db;

    TestSet(int* newASal, int* newBSal, int newN, int newF, int newDa, int newDb)
    : aSal(newASal), bSal(newBSal), n(newN), F(newF), Da(newDa), Db(newDb) {}

    friend std::ostream& operator<<(std::ostream& os, const TestSet& data) {
        os << "aSal: ";
        for (int i = 0; i < 4; ++i) {
            os << data.aSal[i] << " ";
        }

        os << "\nbSal: ";
        for (int i = 0; i < 4; ++i) {
            os << data.bSal[i] << " ";
        }

        os << "\nF: " << data.F << " Da: " << data.Da << " Db: " << data.Db << "\n";

        return os;
    }
};

int findLowestCost(int (*optSols)[2], int* aSals, int* bSals, int n, int F, int Da, int Db){
    // Fill the starting values into the table.
    optSols[0][0] = aSals[0];
    optSols[1][0] = bSals[0];

    // For each subsequent week, find the next most optimal solution.
    for(int i = 1; i < n; i++){ // starts at one since 0 is already determined
        // Determine the next val for optSols[A] (Current state is A)
        cout << "Handling week: " << i << endl;
        int atAPrevDayAtA = optSols[0][i-1] - Da;
        int atAPrevDayAtB = optSols[1][i-1] + F;
        if (atAPrevDayAtA <= atAPrevDayAtB){ // If it was better to be at A the previous day
            optSols[0][i] = atAPrevDayAtA + aSals[i];
            cout << "at A, A was better the previous day. optSols[0][" << i << "]: " << optSols[0][i];
        }
        else { // If it was better to be at B the previous day
            optSols[0][i] = atAPrevDayAtB + aSals[i];
            cout << "at A, B was better the previous day. optSols[0][" << i << "]: " << optSols[0][i];

        }
        
        // Determine the next val for optSols[B] (Current state is B)
        int atBPrevDayAtA = optSols[0][i-1] + F;
        int atBPrevDayAtB = optSols[1][i-1] - Db;
        if (atBPrevDayAtA <= atBPrevDayAtB){ // If it was better to be at A the previous day
            optSols[1][i] = atBPrevDayAtA + bSals[i];
            cout << "at B, A was better the previous day. optSols[1][" << i << "]: " << optSols[1][i];

        }
        else { // If it was better to be at B the previous day
            optSols[1][i] = atBPrevDayAtB + bSals[i];\
            cout << "at B,  was better the previous day. optSols[1][" << i << "]: " << optSols[1][i];
        }
    }

    // Return the final Value
    if (optSols[0][n-1] >= optSols[1][n-1]){ // If the last week being A is cheaper, return its price
        return optSols[0][n-1];
    }
    else { // Otherwise return the price of B
       return optSols[0][n-1];
    }
}


// Wrapper func for find lowest cost, creates the table and calls the func with a test case.
void findLowestCost(TestSet test){
    int optSols [2][test.n];
    int lowestCost = findLowestCost(optSols, test.aSal, test.bSal, test.n, test.F, test.Da, test.Db);
    cout << "Lowest Cost: " << lowestCost << endl;
}

int main() {
    int aSalArray[] = {3500, 1500, 2000, 1500};
    int bSalArray[] = {2500, 1000, 3500, 2000};
    TestSet defaultTestSet = TestSet(
        aSalArray,
        bSalArray,
        4, 200, 500, 400
    );

    TestSet testSet = defaultTestSet;

    cout << defaultTestSet;
    findLowestCost(testSet);
    return 0;
}
