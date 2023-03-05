#include <iostream>
#include "choice1.h"
#include "choice2.h"

using namespace std;

void intro() {
    cout << endl << endl << "In this program you can create a txt file, in which you will enter words seperated by comas only." << endl;
    cout << "The task of this program is to find and reshape a substring you entered in created txt file." << endl;
    cout << "For example you entered text: time timeless sleep food continue." << endl;
    cout << "And you entered a substring: ti." << endl;
    cout << "The program will create two extra files, both of which will contain the result of reshaping the text you entered." << endl;
    cout << "Result 1: [ti-1]me [ti-2]meless sleep food con[ti-3]nue." << endl;
    cout << "Result 1: [1-ti]me [2-ti]meless sleep food con[3-ti]nue." << endl;
    cout << "This program works in two modes:" << endl;
    cout << "1) FilePointer" << endl;
    cout << "2) FileStream" << endl;
    cout << "Please enter 1 to run this program in mode 1 or enter 2 to run this program in mode 2." << endl;
    cout << "To exit this program enter 0." << endl;
}

int main() {
    int choice;
    do {
        intro();
        cin >> choice;
        switch (choice) {
        case 1:
            choice1();
            break;
        case 2:
            choice2();
            break;
        case 0:
            break;
        default:
            cout << "You can enter only 1 or 2. Please try again." << endl;
            break;
        }
    } while (choice != 0);
    return 0;
}