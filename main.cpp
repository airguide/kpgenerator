/*********************************************************************************
File     : main.cpp
Author   : VHN <hemal@mail.ru>
Date     : 02.08.2018
Comments : Kenyan number plate identifier Console application
           Kenyan Number plates have 2 formats old is KXX000 and new is KXX000X
           K - is the requirement all number plates start with a K
           X - is the first character
           X - is the second character
           0 - is the first number
           0 - is the second number
           0 - is the third number
           X - is the last character of the new type after 1989

           Chars I and O are not allowed
           Sequence like KAF is forbidden

           This application generates a random kenyan number plate from a sentence
           and assumes that new series is being used
**********************************************************************************/


#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string GetNumberPlate(string strInput) {
    // We want random values from the vector so set seed
    srand(time(NULL));

    // Get a sentence into a string from the console
    string strSentence = "This is a tester for Kenyan Number plates 123 567";
    string strKenyanNumberPlate = ""; // save the output here!

    // Get length
    int iSentenceLen = strInput.length();

    // Insert the sentence as 'chars' into the char vector
    vector<char> vecCharPlates;
    vector<int>  vecIntPlates;

    // Convert all the chars to uppercase, remove whitespaces and remove forbidden chars
    for (int iCounter = 0; iCounter < iSentenceLen; iCounter++) {
        char chCurrentValue = toupper(strInput.at(iCounter));//
        if (!isspace(chCurrentValue) && !isnumber(chCurrentValue) && chCurrentValue != 'I' && chCurrentValue != 'O')
            vecCharPlates.push_back(chCurrentValue);
        if (!isspace(chCurrentValue) && isnumber(chCurrentValue)) {
            vecIntPlates.push_back(int(chCurrentValue) - 48); // ASCII digits start from 48
        }
    }

    // Search for K and see if the ints are enough
    if ( (find(vecCharPlates.begin(), vecCharPlates.end(), 'K') != vecCharPlates.end()) && vecIntPlates.size() != 0) {
        // Get the random second and third plate character from the vector
        strKenyanNumberPlate = "K" + string(1, vecCharPlates.at(rand() % vecCharPlates.size())) +
                               string(1, vecCharPlates.at(rand() % vecCharPlates.size()));
        // Make sure forbidden sequence is not allowed
        while (strKenyanNumberPlate == "KDF")
            strKenyanNumberPlate = "K" + string(1, vecCharPlates.at(rand() % vecCharPlates.size())) +
                                   string(1, vecCharPlates.at(rand() % vecCharPlates.size()));


        // Insert 4th, 5th and 6th numbers
        string numbers = to_string(vecIntPlates.at(rand() % vecIntPlates.size()));
        strKenyanNumberPlate += to_string(vecIntPlates.at(rand() % vecIntPlates.size())) +
                                to_string(vecIntPlates.at(rand() % vecIntPlates.size())) +
                                to_string(vecIntPlates.at(rand() % vecIntPlates.size())) +
                                string(1, vecCharPlates.at(rand() % vecCharPlates.size()));

    } else
        return "The sentence does not include a K";
    return strKenyanNumberPlate;
};

int main() {
    string strUserInput = "";

    cout << "Kenyan Number plate generator\n";
    cout << "=============================\n";
    cout << "Type in a sentence: ";

    getline(cin, strUserInput);

    cout << "Number plate is: " << GetNumberPlate(strUserInput) << endl;


    return 0;
}