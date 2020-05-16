#include<bits/stdc++.h>
using namespace std;

int n;
int sroot;

bool solve(int i, int j, vector<vector<char>>&board, int rows[], int column[], vector<vector<int>>&subgrid) {
    if (i >= n || j >= n) {
        return true;
    }
    if (board[i][j] == '0') {
        for (int k = 1; k <= n; k++) {
            int mask = 1 << (k - 1);
            if (!(rows[i]&mask || column[j]&mask || subgrid[i / sroot][j / sroot]&mask)) {
                rows[i] |= mask;
                column[j] |= mask;
                board[i][j] = k + '0';
                //cout << board[i][j] << endl;
                subgrid[i / sroot][j / sroot] |= mask;
                bool issolved = false;
                if (j == 8) {
                    issolved = solve(i + 1, 0, board, rows, column, subgrid);
                }
                else {
                    issolved = solve(i, j + 1, board, rows, column, subgrid);
                }
                if (issolved) {
                    return true;
                }
                else {
                    rows[i] &= (~mask);
                    column[j] &= (~mask);
                    subgrid[i / sroot][j / sroot] &= (~mask);
                    board[i][j] = '0';
                }
            }
        }
        return false;
    }
    if (j == 8) {
        return solve(i + 1, 0, board, rows, column, subgrid);
    }
    else {
        return solve(i, j + 1, board, rows, column, subgrid);
    }
}

bool init(int n, vector<vector<char>>&board) {
    int rows[n];
    int column[n];
    fill(rows, rows + n, 0);
    fill(column, column + n, 0);
    vector<vector<int>>subgrid(n);
    for (int i = 0; i < n; i++) {
        subgrid[i].resize(n, 0);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int mask = 1 << (board[i][j] - '1');
            rows[i] |= mask;
            column[j] |= mask;
            subgrid[i / sroot][j / sroot] |= mask;
        }
    }

    return solve(0, 0, board, rows, column, subgrid);
}

void PseudoRandomGenerator(int n, vector<vector<char>>&board) {
    srand(time(0));
    char j = '1';
    //Randomly assigning data to each row and one of the columns randomly that too with
    //different data to avoid possibility of invalid sudoku getting generated.
    //example if data was also random than Generator could have selected element [1,2] and
    //[1,8] and assign them 8 but then row 1 would have 2 8's and that would be an invalid
    //sudoku
    for (int i = 0; i < n; i++) {
        int idx = rand() % n;
        board[i][idx] = j;
        j++;
    }

    //First solve this sudoku with very less data
    init(n, board);

    //this controls the no of elements to be kept in the sudoku
    //no of elements will vary in range- [n,n*root(n)]
    int keep = min(rand() % (n * n), n * sroot);
    keep = max(n, keep);

    vector<vector<char>>copy(n);
    for (int i = 0; i < n; i++) {
        copy[i].resize(n, '0');
    }

    while (keep > 0) {
        int i = rand() % n;
        int j = rand() % n;
        if (copy[i][j] == '0') {
            keep--;
            copy[i][j] = board[i][j];
        }
    }
    board = copy;
}
void print(int n, vector<vector<char>>&board) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}
void c_p_c() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

int main() {
    c_p_c();
    cin >> n;

    vector<vector<char>>board(n);
    for (int i = 0; i < n; i++) {
        board[i].resize(n, '0');
    }

    sroot = sqrt(n);

    PseudoRandomGenerator(n, board);

    cout << "PROBLEM-\n\n";
    print(n, board);

    bool issolved = init(n, board);

    cout << "\nSolution-\n\n";
    if (issolved) {
        print(n, board);
    }
    else {
        cout << "Invalid Grid\n";
    }
    return 0;
}


// sample problem for Testing-
// 026000810
// 300708006
// 400050007
// 050107090
// 003905100
// 040302050
// 100030002
// 500204009
// 038000460

// solution-
// 726493815
// 315728946
// 489651237
// 852147693
// 673985124
// 941362758
// 194836572
// 567214389
// 238579461
