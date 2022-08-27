#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>

#include <stdlib.h>
#include <time.h>
#include <ctime>
//#include<conio.h>

#include <math.h>
#include <stdio.h>

#include <fstream>

using namespace std;

string inp;

int A, B;

int TakeNum(string str, int &, int &);

int DrawArray(char **ar, int A, int B) {
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            cout << setw(2) << ar[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

char Transform(char **&, int A, int B);

char FixChar(char **&, int A, int B);

int main() {
    ifstream inF;
    inF.open("input.txt");
    if(inF.is_open()) {
        cout << "Input file is successfully opened" << endl;
        getline(inF, inp);
        cout << "Taked string : " << inp << endl;
        TakeNum(inp, A, B);
        inp.clear();
        cout << "taked nums: " << A << " | " << B << endl;

        char **pict = new char* [A];
        for (int i = 0; i < A; i++) {
            pict[i] = new char [B];
        }

        for (int i = 0; i < A; i++) {
            inp.clear();
            getline(inF, inp);
            for (int j = 0; j < B; j++) {
                pict[i][j] = inp[j];
            }
        }
        cout << "Taked array of chars :" << endl;
        DrawArray(pict, A, B);

        system("pause");

        Transform(pict, A, B);

        cout << "Pict after transform operation : " << endl;
        DrawArray(pict, A, B);

        system("pause");

        FixChar(pict, A, B);

        cout << "Pict after fix operation : " << endl;
        DrawArray(pict, A, B);

        system("pause");

        ofstream outF;
        outF.open("output.txt");

        if(outF.is_open()) {
            for (int i = 0; i < A; i++) {
                for (int j = 0; j < B; j++) {
                    outF << pict[i][j];
                }
                outF << endl;
            }
            cout << "|Output process is successfully complete|" << endl;
        }

        outF.close();
    }
    inF.close();

    system("pause");
    return 0;
}

int TakeNum(string str, int &A, int &B) {
    char nums[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int size = str.size();
    string bffr;
    char ch;

    for (int n = 0; n < size; n++) {
        ch = str[n];
        for (int i = 0; i < 10; i++) {
            if (ch == nums[i]) {
                bffr += ch;
            }
        }

        if (ch == ' ') {
            A = stoi(bffr);
            bffr.clear();
        } else if (n == size-1) {
            B = stoi(bffr);
            bffr.clear();
        }
    }

    bffr.clear();
}

char Transform(char **&pict, int A, int B) {
    char *bffr = new char [B];
    char **arr = new char* [A];
    for (int i = 0; i < A; i++) {
        arr[i] = new char [B];
    }
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            bffr[j] = pict[i][j];
        }

        for (int j = 0; j < B; j++) {
            arr[(A-1) - i][j] = bffr[j];
        }
    }

    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            pict[i][j] = arr[i][(B-1)-j];
        }
    }

    for (int i = 0; i < A; i++) {
        delete [] arr[i];
    }
    delete arr;

    delete bffr;

    cout << "|Transform is complete|" << endl;
}

char FixChar(char **&pict, int A, int B) {
    char *bffr = new char [B];
    char sym;
    char base[] = {'_', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    cout << "|Start fix pict process|" << endl;
    for (int i = 0; i < A; i++) {
        cout << "i : " << i << endl;
        for (int j = 0; j < B; j++) {
            for (int x = 0; x < 27; x++) {
                if (pict[i][j] == base[x]) {
                    sym = pict[i][j];
                    pict[i-1][j] = sym;
                    if (pict[i+1][j] == '.') {
                        pict[i][j] = '.';
                    }

                    DrawArray(pict, A, B);
                    cout << "+" << endl;
                }
            }
        }
    }

    cout << "half process result is :" << endl;
    DrawArray(pict, A, B);

    for (int i = A-2; i >= 0; i--) {
        for (int j = 0; j < B; j++) {
            bffr[j] = pict[i][j];
            pict[i+1][j] = bffr[j];
        }
    }

    for (int i = 0; i < B; i++) {
        if (pict[0][i] == '_') pict[0][i] = '.';
    }

    delete bffr;

    cout << "|Fix process is complete|" << endl;
}