#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 棋盘规模 scale × scale
const int scale = 8;

long cntPreDFS = 0;
long cntDFS = 0;
long cntBF = 0;

// 打印格式
void print(vector<int> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << "(" << i + 1 << ", " << vec[i] + 1 << ")" << " ";
    }
    cout << endl;
}

// 优化前的回溯法
void preVersionDFS(int row, int n, vector<int> &nowPosition) {
    for (int col = 0; col < n; ++col) {
        bool ok = true;

        cntPreDFS++;

        // 检查冲突
        for (int i = 0; i < row; ++i) {
            if (col == nowPosition[i] ||
                    col - nowPosition[i] == row - i ||
                    col - nowPosition[i] == i - row) {
                ok = false;
                break;
            }
        }

        if (!ok) continue;

        if (row != n - 1) {
            // 记录当前行皇后的位置
            nowPosition[row] = col;
            // 继续试探下一行
            preVersionDFS(row + 1, n, nowPosition);
        }
    }
}

// 优化后的回溯法
void DFS(int row, bool *shu, bool *pie, bool *na, int n, vector<int> &nowCols) {
    // 当前位置所在的撇、捺编号
    int pieNum, naNum;

    for (int col = 0; col < n; ++col) {
        pieNum = row + col;
        naNum = n - 1 - row + col;

        cntDFS++;
        // 检查冲突
        if (shu[col] || pie[pieNum] || na[naNum]) {
            continue;
        }

        nowCols.push_back(col);

        if (row == n - 1) { // 已放到最后一行, 找到一组解
//            print(nowCols);
        } else {
            // 标记当前竖、撇、捺已被占用
            shu[col] = pie[pieNum] = na[naNum] = true;
            // 继续试探下一行
            DFS(row + 1, shu, pie, na, n, nowCols);
            // 清除标记
            shu[col] = pie[pieNum] = na[naNum] = false;
        }

        nowCols.pop_back();
    }
}

// 判断皇后的位置是否摆放正确的判断模块
bool isValid(vector<int> &positions) {
    long n = positions.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (positions[i] == positions[j] ||
                i - j == positions[i] - positions[j] ||
                i - j == positions[j] - positions[i]) {
                return false;
            }
        }
    }

    return true;
}

// 蛮力法
void BF(vector<int> &positions) {
    do {
        cntBF += 4;
        if (isValid(positions)) {
//            print(positions);
        }
    }
    /*
     * next_permutation函数将按字母表顺序生成给定序列的
     * 下一个较大的序列，直到整个序列为减序为止
     */
    while (next_permutation(positions.begin(),
                            positions.end()));
}


int main() {
    int n = scale;
    // 标记每一竖、撇、捺是否被占用
    bool *shu = new bool[n];
    bool *pie = new bool[2 * n + 1];
    bool *na = new bool[2 * n + 1];
    for (int i = 0; i < n; ++i) {
        shu[i] = false;
    }
    for (int i = 0; i < 2 * n + 1; ++i) {
        pie[i] = na[i] = false;
    }

    // 已放置的皇后的列号
    vector<int> nowPosition;
    for (int i = 0; i < n; ++i) {
        nowPosition.push_back(0);
    }

    vector<int> nowCols;

    vector<int> positions;
    for (int i = 0; i < n; ++i) {
        positions.push_back(i);
    }

    cout << n << "皇后问题" << endl;
    cout << "----------------------" << endl;

    cout << "回溯法" << endl;
    long tic, toc;
    tic = clock();
    preVersionDFS(0, n, nowPosition); // 从第 0 行开始试探
    toc = clock();
    cout << "优化前 遍历节点个数：" << cntPreDFS << endl;
    cout << "      耗时：" << toc -tic << " us" << endl;
    tic = clock();
    DFS(0, shu, pie, na, n, nowCols);
    toc = clock();
    cout << "优化后 遍历节点个数：" << cntDFS << endl;
    cout << "      耗时：" << toc -tic << " us" << endl;

    cout << "----------------------" << endl;
    cout << "蛮力法" << endl;
    tic = clock();
    BF(positions);
    toc = clock();
    cout << "遍历节点个数：" << cntBF << endl;
    cout << "耗时：" << toc -tic << " us" << endl;

    cout << "--------------------------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "测试3组八皇后问题数据：" << endl;

    int time = 3;
    n = 8;
    int testArr1[8] = {4, 7, 3, 8, 2, 5, 1, 6};
    int testArr2[8] = {5, 2, 4, 7, 3, 8, 6, 1};
    int testArr3[8] = {4, 2, 7, 3, 6, 8, 5, 1};

    for (int t = 0; t < time; ++t) {
        vector<int> testPositions;
        if (t == 0) {
            for (int i = 0; i < n; ++i) {
                testPositions.push_back(testArr1[i]);
            }
        }
        if (t == 1) {
            for (int i = 0; i < n; ++i) {
                testPositions.push_back(testArr2[i]);
            }
        }
        if (t == 2) {
            for (int i = 0; i < n; ++i) {
                testPositions.push_back(testArr3[i]);
            }
        }

        print(testPositions);

        if (isValid(testPositions)) {
            cout << "-> Yes" << endl;
        } else {
            cout << "-> No" << endl;
        }
    }

    return 0;
}
