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

int n; string buffer;

int NumCvt(string &);

int TakePoints(int **&, string str, int turn);

int Intersections(int **&, int *&, int size);

string OutString(int *arr, int size);

string CheckChar(string str);

int DrawArray(int **ar, int A, int B) {
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            cout << setw(4) << ar[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    getline(cin, buffer);
    n = NumCvt(buffer);
    buffer.clear();

    cout << "n = " << n << endl;

    int **arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int [4];
    }
    int *inters = new int [n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = 0;
        }
        inters[i] = 0;
    }

    DrawArray(arr, n, 4);

    for (int i = 0; i < n; i++) {
        buffer.clear();
        getline(cin, buffer);
        TakePoints(arr, buffer, i);
    }

    cout << "taked points:" << endl;
    DrawArray(arr, n, 4);

    Intersections(arr, inters, n);

    cout << " all intersections of rectangles: ";
    for (int i = 0; i < n; i++) {
        cout << inters[i];
    }
    cout << endl;

    OutString(inters, n);

    return 0;
}

int NumCvt(string &str) {
    int n; string w;
    for (auto ch : str) {
        if (ch != ' ' || ch != '\0') {
            w += ch;
        }

        if (ch == str[str.size()-1]) {
            if (ch != w[w.size()-1]) {
                w += ch;
                n = stoi(w);
            } else {
                n = stoi(w);
            }
        }
    }
    w.clear();

    return n;
}

int TakePoints(int **&arr, string str, int turn) {
    int n = 0; string w; int trnsf; int step = 0;
    char ch;

    cout << "Taked string = " << str << endl;

    for (int i = 0; i < str.size(); i++) {
        ch = str[i];
        w += ch;

        if (ch == ' ') {
            w = CheckChar(w);
            trnsf = stoi(w);
            arr[turn][n] = trnsf;
            w.clear();
            n++;
        } else if (i == str.size() - 1) {
            if (w[w.size()-1] != ch) {
                w += ch;
                w = CheckChar(w);
                trnsf = stoi(w);
                arr[turn][n] = trnsf;
                w.clear();
                n++;
            } else {
                w = CheckChar(w);
                trnsf = stoi(w);
                arr[turn][n] = trnsf;
                w.clear();
                n++;
            }
        }
        step++;
    }
    w.clear();
}

string CheckChar(string str) {
    int _size = str.size(); char check;
    string w;

    char num[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};

    for (int i = 0; i < _size; i++) {
        check = str[i];
        for (int j = 0; j < 11; j++) {
            if (check == num[j]) {
                w += check;
            }
        }
    }

    if (!w.empty()) {
        return w;
    } else {
        return 0;
    }
}

int Intersections(int **&arr, int *&inters, int size) {
    int actual[4];

    for (int i = 0; i < size; i++) {
        cout << "i = " << i << endl;
        cout << "Checkin' rectangle = " << endl;
        for (int j = 0; j < 4; j++) {
            actual[j] = arr[i][j];
            cout << actual[j] << " ";
        }
        cout << endl;
        

        if (i != size-1) {
            for (int j = i+1; j < size; j++) {
                if ((actual[0] < arr[j][0] && actual[2] > arr[j][0]) || (actual[0] < arr[j][2] && actual[2] > arr[j][2])) {
                    cout << "intersection on X" << endl;
                    inters[i]++; inters[j]++;
                    cout << "Number of intersection which have " << i << " rectangle = " << inters[i] << " and " << j << " rectangle = " << inters[j] << endl;
                } else if ((actual[0] < arr[j][0] && actual[2] > arr[j][0]) || (actual[0] < arr[j][2] && actual[2] > arr[j][2])) {
                    cout << "intersection on X" << endl;
                    inters[i]++; inters[j]++;
                    cout << "Number of intersection which have " << i << " rectangle = " << inters[i] << " and " << j << " rectangle = " << inters[j] << endl;
                }
            }
        }
    }
}

string OutString(int *arr, int size) {
    string outer;

    for (int i = 0; i < size; i++) {
        outer += to_string(arr[i]) + " ";
    }

    cout << outer << endl;
}