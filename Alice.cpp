#include <iostream>
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

string W; string inp, outp;
string buffer; int sum = 0; int num = 0; int lngth;
int turn = 0;

string Wcnvrt(string &, int &, string &, int &, string inp);

string NumRotar(int &, int &, string bffr);

char Abs(int num);

int main() {
    setlocale(LC_ALL, "ru");

    ifstream fIn;
    fIn.open("input.txt");

    if(fIn.is_open()) {
        while (!fIn.eof())
        {
            inp.clear();
            getline(fIn, inp);
            
            if (turn == 0) {
                lngth = stoi(inp);
                inp.clear();
            } else {
                outp = Wcnvrt(W, num, buffer, sum, inp);
            }
            turn++;
        }

        cout << outp << " <- out" << endl;
        
    } else {
        cout << "Ошибка открытия файла!" << endl;
    }
    fIn.close();

    ofstream fOut;
    fOut.open("output.txt");

    if(fOut.is_open()) {
        for (auto ch : outp) {
            fOut << ch;
        }
    }

    fOut.close();

    return 0;
}

string Wcnvrt(string &W, int &num, string &buffer, int &sum, string inp) {
    int size = inp.size(); int trueSize = 0;
    for (auto ch : inp) {
        if (ch != ' ' && ch != '\0') {
            buffer += ch;
        } else {
            buffer = NumRotar(num, sum, buffer);
            W += buffer + ' ';
            buffer.clear();
            sum = num;
            num = 0;
        }

        if (trueSize == size - 1) {
            buffer = NumRotar(num, sum, buffer);
            W += buffer + ' ';
            buffer.clear();
            sum = num;
            num = 0;
        }
        trueSize++;
    }
    buffer.clear(); num = 0; sum = 0; trueSize = 0; inp.clear();

    size = W.size();

    for (auto ch : W) {
        if (ch != ' ' && ch != '\n') {
            buffer += ch;
        } else {
            if (buffer.size() != 0) {
                num = stoi(buffer);
                buffer.clear();
                inp += Abs(num);
            }
        }
    }

    return inp;
}

string NumRotar(int &num, int &sum, string bffr) {
    int x = 2;
    num = stoi(bffr);
    bffr.clear();

    for (int i = 0; i < 27; i++) {
        x = 2;
        x = pow(x, i);
        //x += sum;
        if (x + sum == num) {
            bffr = to_string(i);
            return bffr;
        }

        if (x == num) {
            bffr = to_string(i);
            return bffr;
        }

        if (sum - x == num) {
            bffr = to_string(i);
            return bffr;
        }
    }
}

char Abs (int num) {
    char abs[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
    'u', 'v', 'w', 'x', 'y', 'z', ' '};

    for (int i = 0; i < 27; i++) {
        if (i == num) return abs[i];
    }
}