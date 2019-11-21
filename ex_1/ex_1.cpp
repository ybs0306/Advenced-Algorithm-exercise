/*
* create on : 2019-10-01
* create on : kinoshita kenta <ybs0306748@gmail.com>
*/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

//(傳遞p_len, 傳遞k, 傳遞prob陣列, 記錄目前遞迴深度, 紀錄連續1的數量, 目前bit字串, 傳遞datas, 紀錄目前bit乘下來的機率)
void re_bit(int p_len, int k, double prob[], int deep, int cmp, string str, vector<pair<string, double> > &datas, double w){
    //recursive深度符合bit長度, 資料push進去datas
    if(deep == p_len){
        datas.push_back(make_pair(str, w));
        /*check bit str*/
        //cout << str << endl;
    }
    else{
        //未連續重複k-1個1(不能讓連續k個發生), 給予0與1兩個情形
        if(cmp < k-1){
            re_bit(p_len, k, prob, deep+1, 0    , str+'0', datas, w*(1-prob[deep]));
            re_bit(p_len, k, prob, deep+1, cmp+1, str+'1', datas, w*(prob[deep])  );
        }
        //已連續重複k-1個1, 接下的的組合不會給1
        else if(cmp == k-1){
            re_bit(p_len, k, prob, deep+1, 0    , str+'0', datas, w*(1-prob[deep]));
        }
    }
}

int main(){
    int p_len, k;   //題目input
    vector<pair<string, double> > datas;  //儲存規則內的所有資料, first為bit字串, second為機率
    double ans;    //最後機率加總
    
    while(cin >> p_len && p_len){
        cin >> k;

        datas.clear();  //清空datas
        double *prob = new double[p_len];   //動態宣告儲存機率的陣列
        ans = 0;    //清空機率加總

        for(int i = 0; i < p_len; i++)
            cin >> prob[i];
        
        //recursive start, bit起始給予空值, 機率給0
        re_bit(p_len, k, prob, 0, 0, "", datas, 1);

        //機率加總
        for(int i = 0; i < datas.size(); i++){
            /*check datas*/
            //cout << datas[i].first << "\t" << datas[i].second << endl;
            ans += datas[i].second;
        }

        //顯示到小數點下5位
        if(p_len < k)
            cout << fixed << setprecision(5) << 1 << endl;
        else
            cout << fixed << setprecision(5) << ans << endl;
        cout.unsetf(ios::fixed);

        //free出prob的陣列
        delete []prob;
    }

    return 0;
}
