#include <iostream>

using namespace std;

int A[300], B[300], C[300];
int At, Bt, Ct;

void print(int &m) {
    if(m < 0)
        return;
    int i;

    cout << "A=>";
    for(i = 0; i < At; i++) {
        if(!i)
            cout << "  ";
        cout << " " << A[i];
    }

    cout << "\nB=>";
    for(i = 0; i < Bt; i++) {
        if(!i)
            cout << "  ";
        cout << " " << B[i];
    }

    cout << "\nC=>";
    for(i = 0; i < Ct; i++) {
        if(!i)
            cout << "  ";
        cout << " " << C[i];
    }

    cout << "\n\n";
    m--;
}

void move_disk(char st, char ed, int &m) {
    if(st == 'A' && ed == 'B')
        B[Bt++] = A[--At];
    if(st == 'A' && ed == 'C')
        C[Ct++] = A[--At];
    if(st == 'B' && ed == 'A')
        A[At++] = B[--Bt];
    if(st == 'B' && ed == 'C')
        C[Ct++] = B[--Bt];
    if(st == 'C' && ed == 'A')
        A[At++] = C[--Ct];
    if(st == 'C' && ed == 'B')
        B[Bt++] = C[--Ct];
    print(m);
}

void hanoi(int n, char ch1, char ch2, char ch3, int &m) {
    // for move step by 0
    if(m < 0)
        return;

    // move disk 1
    if(n == 1){
        move_disk(ch1, ch3, m);
        return;
    }
    // move others disk
    else{
        hanoi(n - 1, ch1, ch3, ch2, m);
        move_disk(ch1, ch3, m);
        hanoi(n - 1, ch2, ch1, ch3, m);
    }
}

int main() {
    int n, m, loop = 1;
    while(cin >> n && cin >> m) {
        if(n == 0 && m == 0)
            break;
        
        cout << "Problem #" << loop++ << "\n\n";

        At = 0;
        Bt = 0;
        Ct = 0;

        for(int i = n; i >= 1; i--)
            A[At++] = i;

        print(m);
        hanoi(n, 'A', 'B', 'C', m);
    }

    return 0;
}
