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

#include <thread>

using namespace std;

bool open;

string str;

int TakeNum(string str);

int GetNum(string &str);

string CorectStr(string str);

int SearchNOD(int **&qst, int *answ, int num);

int TakeAnsw(int trgt[2], int point, int max, int min);

int Pnum(int num, int max);

int DrawArray(int **ar, int A, int B) {
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            cout << setw(3) << ar[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int num; char ch;
    ifstream inF;

    inF.open("input.txt");
    
    if (inF.is_open()) {
        open = true;
        cout << "File is successfully open" << endl;
    } else {
        open = false;
        cout << "Can't open the file" << endl;
    }

    if (open != false) {
        getline(inF, str);

        cout << "Target string :" << endl << str << endl; 
        num = TakeNum(str);

        cout << "Taked num : " << num << endl;
        str.clear();

        int **quests = new int* [num];
        for (int i = 0; i < num; i++) {
            quests[i] = new int [2];
        }

        int *answer = new int [num];

        for (int i = 0; i < num; i++) {
            str.clear();
            getline(inF, str);

            cout << "Target string :" << endl << str << endl; 

            for (int j = 0; j < 2; j++) {
                quests[i][j] = GetNum(str);
                str = CorectStr(str);
            }
        }

        cout << "taked array : " << endl;
        DrawArray(quests, num, 2);

        //system("Pause");

        SearchNOD(quests, answer, num);

        cout << "Answer : ";
        for (int i = 0; i < num; i++) {
            if (i != num - 1) {
                cout << answer[i] << ", ";
            } else {
                cout << answer[i] << ";" << endl;
            }
        }

        //system("Pause");
    }
}

int TakeNum(string str) {
    int num;
    int size = str.size();

    string bffr;
    char ch;

    for (int i = 0; i < size; i++) {
        ch = str[i];

        if (i < size-1) {
            bffr += ch;
        } else if (i == size-1) {
            bffr += ch;

            num = stoi(bffr);
            bffr.clear();
        }
    }

    return num;
}

int GetNum(string &str) {
    int num;
    int size = str.size();

    string bffr;
    char ch;

    cout << "start takin' nums" << endl;
    for (int i = 0; i < size; i++) {
        ch = str[i];;

        if (ch != ' ' && i != size-1) {
            bffr += ch;
        }

        if (ch == ' ') {
            num = stoi(bffr);
            bffr.clear();

            return num;
        }

        if (i == size-1) {
            if (bffr[bffr.size()-1] != ch) {
                bffr += ch;

                num = stoi(bffr);
                bffr.clear();

                return num;
            } else {
                num = stoi(bffr);
                bffr.clear();

                return num;
            }
        }
    }
}

string CorectStr(string str) {
    int size = str.size();

    bool turn = false;

    char ch;

    string bffr;

    cout << "Start corect str" << endl;

    for (int i = 0; i < size; i++) {
        ch = str[i];

        if (ch == ' ') {
            turn = true;
            continue;
        }

        if (turn != false) {
            bffr += ch;

            if (i == size-1) {
                str = bffr;
            }
        }
    }

    return bffr;
}

int Pnum(int num, int max) {
    int check = 0; int point = 0;

    //cout << "Take num for * " << endl;
    for (int i = num + 1; num <= i < max; i++) {
        for (int j = 1; j <= i; j++) {
            if (i % j == 0) check++;
        }

        if (check == 2) {
            return i;
        } else {
            check = 0;
        }
    }
}

int TakeAnsw(int trgt[2], int point, int max, int min) {
    int num = 1; int check = 0;

    //bool end = false;

    cout << "Start take num for *" << endl;

    if (min > 1000) {
        for (int i = 0; i <= min; i++) {
            num = Pnum(num, max);

            for (int j = 1; j <= min; j++) {
                if ((max * num) % min == 0) {
                    check = (max * num) / min;
                }
            }
        }
    }

    for (int i = 1; i <= max; i++) {
        num = Pnum(num, max); 

        for (int j = 1; j <= max; j++) {
            if ((min * num) % j == 0 && max % j == 0) {
                if (j > check) {
                    check = j;
                }
            }
        }
    }

    if (check > point) {
        return check;
    } else {
        return point;
    }
}

int SearchNOD(int **&qst, int *answ, int num) {
    int arN[2]; int check = 1; int point = 0;

    int min, max;

    bool end = false; int step = 0; int LeadCh = 0;

    cout << "|start search NOD|" << endl;

    for (int i = 0; i < num; i++) {
        arN[0] = qst[i][0];
        arN[1] = qst[i][1];

        if (arN[0] > arN[1]) {
            max = arN[0]; min = arN[1];
        } else {
            max = arN[1]; min = arN[0];
        }

        cout << "Num of ex : " << i+1 << "Ex's body : " << arN[0] << " & " << arN[1] << endl;
        cout << "Min : " << min << "; Max : " << max << endl;

        //system("Pause");

        for (int j = 1; !end; j++) {
            if (arN[0] % j == 0 && arN[1] % j == 0) {
                if (j > point) {
                    point = j;
                    cout << "Point : " << point << endl;
                }
            }

            if (j == max) {
                check = TakeAnsw(arN, check, max, min);
                cout << "Taked new check num : " << check << endl;
                //system("Pause");

                j = 0; step++;

                if (min * check == max) {
                    break;
                }

                if (check > point) {
                    cout << "check : " << check << "; point : " << point << endl;
                    break;
                }
            }
        }

        if (check > point) {
            answ[i] = check;
        } else {
            answ[i] = point;
        }

        cout << "Taked " << i+1 << " st answer : " << answ[i] << endl;
        check = 1;
        point = 0;
    }
}

// !end >> !true = false || !false = true