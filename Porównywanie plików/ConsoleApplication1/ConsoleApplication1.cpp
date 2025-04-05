/*
Małgorzata Dąbrowska
Grupa 4 Podstawy programowania
PRojekt 6:
-> Porównywanie tekstu z plików wejśiowych (tekstowych/ .txt) z wykorzystaniem algorytmu Levensthteina
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int levenshteinDistance(string word1, string word2) {
    unsigned int length1 = word1.length();
    unsigned int length2 = word2.length();

    vector<vector<int>> distanceMatrix(length1 + 1, vector<int>(length2 + 1, 0));

    for (int i = 0; i <= length1; ++i) {
        distanceMatrix[i][0] = i;
    }

    for (int j = 0; j <= length2; ++j) {
        distanceMatrix[0][j] = j;
    }

    for (int i = 1; i <= length1; ++i) {
        for (int j = 1; j <= length2; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                distanceMatrix[i][j] = distanceMatrix[i - 1][j - 1];
            }
            else {
                distanceMatrix[i][j] = 1 + min(distanceMatrix[i - 1][j], min(distanceMatrix[i][j - 1], distanceMatrix[i - 1][j - 1]));
            }
        }
    }

    return distanceMatrix[length1][length2];
}

int main() {
    cout << "This code allows you to compare .txt two files. \nPlease only use English characters." << endl;
    string file1, file2;
    bool fileOpenSuccess = false;
    string text1, text2;
    while (!fileOpenSuccess) {
        fileOpenSuccess = true;
        cout << "\nEnter the name of the first file: " << endl;
        cout << " -> ";
        getline(cin, file1);
        if (cin.fail()) {
            if (cin.bad()) {
                cout << "Unrepairable error encountered. Closing the program.";
                return -1;
            }
            cout << "Failed to interpret input. Try again." << endl;
            cin.clear();
            continue;
        }

        ifstream file1Stream(file1);
        if (!file1Stream.is_open()) {
            cout << "Failed to open file " << file1 << ". Please try again." << endl;
            fileOpenSuccess = false;
            continue;
        }

        cout << "Enter the name of the second file: " << endl;
        cout << " -> ";
        getline(cin, file2);
        if (cin.fail()) {
            if (cin.bad()) {
                cout << "Unrepairable error encountered. Closing the program.";
                return -1;
            }
            cout << "Failed to interpret input. Try again." << endl;
            cin.clear();
            continue;
        }

        ifstream file2Stream(file2);
        if (!file2Stream.is_open()) {
            cout << "Failed to open file " << file2 << ". Please try again." << endl;
            fileOpenSuccess = false;
            continue;
        }

        ifstream inputFile1(file1);
        ifstream inputFile2(file2);
        string s;

        if (inputFile1.is_open()) {
            while (inputFile1.good()) {
                getline(inputFile1, s);
                text1 += s;
            }
        }
        else {
            fileOpenSuccess = false;
            cout << "Failed to open first file, please try again.\n";
            cin.clear();
            continue;
        }

        if (inputFile2.is_open()) {
            while (inputFile2.good()) {
                getline(inputFile2, s);
                text2 += s;
            }
        }
        else {
            fileOpenSuccess = false;
            cout << "Failed to open first file, please try again.\n";
            cin.clear();
            continue;
        }

        cout << "\nText from the first file: \n -> " << text1 << endl;
        cout << "\nText from the second file: \n -> " << text2 << endl;
    }
    cout << "\nWord Similarity: " << 100 - ((levenshteinDistance(text1, text2)) / (double)max(text1.length(), text2.length())) * 100 << "%" << endl;
    cout << "Exiting the program...";
    return 0;
}
