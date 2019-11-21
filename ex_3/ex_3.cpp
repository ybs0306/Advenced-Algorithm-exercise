/*
* create on : 2019-11-20
* create on : kinoshita kenta <ybs0306748@gmail.com>
*/

#include <iostream>
#include <vector>

using namespace std;

//十進位轉2進位存放至陣列
void i2t(int S, int a[]){
    for(int i = 0; i < 13; i++){
        a[i] = S%2;
        S /= 2;
    }
}

//2進位陣列轉換回十進位
int t2i(int a[]){
    int ans = 0;
    for(int i = 12; i >= 0; i--){
        ans *= 2;
        ans += a[i];
    }
    return ans;
}

//(傳遞 t, 傳遞 h, 計算遞迴深度, 棋盤子狀態)
int re_hex(int t[24][2], int h[], int deep, int *array){
    //宣告傳遞用空陣列
    int array_temp[13];

    //當table值未被記錄
    if(h[t2i(array)] == -1){
        //宣告存放下一步的所有可被拿取的棋
        vector<pair<int, int> > situ;
        //相鄰情形
        for(int i = 0; i < 24; i++){
            if((array[t[i][0]] == 1)&&(array[t[i][1]] == 1))
                situ.push_back(make_pair(t[i][0], t[i][1]));
        }
        //單顆情形
        for(int i = 0; i < 13; i++){
            if(array[i] == 1)
                situ.push_back(make_pair(i, -1));
        }

        //當下一步情形有一種以上時
        if(situ.size() > 0){
            int total = 0;
            //所有下一步動作
            for(int i = 0; i < situ.size(); i++){
                //複製一份矩陣狀態
                for(int j = 0; j < 13; j++)
                    array_temp[j] = array[j];
                
                //進行下一步狀態的模擬
                array_temp[situ[i].first] = 0;
                if(situ[i].second != -1)
                    array_temp[situ[i].second] = 0;

                //將勝負期望值進行處理
                total += re_hex(t, h, deep+1, array_temp);
            }

            //當此回合是自己時
            if(deep%2 == 0){
                //所有情形做or運算, 因為自己可以選能贏的那一步
                if(total == 0){
                    h[t2i(array)] = 0;
                    return 0;
                }
                else{
                    h[t2i(array)] = 1;
                    return 1;
                }
            }
            //當此回合是對手時
            else if(deep%2 == 1){
                //所有情形做and運算, 因為對手情形必須都是全贏才算贏
                if(total == situ.size()){
                    //因為table必須要統一存放成在自己回合中的狀態, 方便取用, 所以用互斥還原
                    h[t2i(array)] = (1^1);
                    return 1;
                }
                else{
                    h[t2i(array)] = (0^1);
                    return 0;
                }
            }
        }
        //當下一步情形為0種時, 也就是沒有棋時
        else
            return (1^(deep%2));
    }

    //table值已被記錄
    return (h[t2i(array)]^(deep%2));
}

int main(){

    //給定棋盤24種關係式
    int t[24][2] = {{2,0},{0,3},{1,2},{2,3},{3,4},{1,5},{5,2},{2,6},{6,3},{3,7},{7,4},{5,6},
                    {6,7},{8,5},{5,9},{9,6},{6,10},{10,7},{7,11},{8,9},{9,10},{10,11},{9,12},{12,10}};
    //初始化table
    int h[8192];
    for(int i = 0; i < 8192; i++)
        h[i] = -1;

    int N;
    cin >> N;

    int *S = new int[N];
    int *ans = new int[N];

    for(int i = 0; i < N; i++)
        cin >> S[i];

    for(int i = 0; i < N; i++){
        int array[13];
        //解析input成13bit
        i2t(S[i], array);
        //寫一個function(t, h, deep, array)遞迴
        ans[i] = re_hex(t, h, 0, array);
    }

    //顯示每一組的答案
    for(int i = 0; i < N; i++){
        cout << ans[i] << ' ';
    }

    return 0;
}
