/*
* create on : 2019-12-25
* create on : kinoshita kenta <ybs0306748@gmail.com>
*/
#include <iostream>
#include <vector>

using namespace std;

int main(){
    int loop, N, s, bias;
    vector <int> ans;

    cin >> loop;

    for(; loop > 0; loop--){
        ans.clear();

        cin >> N;
        s = 2;
        while(N >= s){
            N -= s;
            ans.push_back(s);
            s++;
        }

        for(int i = 0; i < ans.size(); i++){
            if(i == ans.size()-1 && N == ans.size()+1) bias = 2;
            else if(ans.size()-i <= N) bias = 1;
            else bias = 0;

            if(i != 0) cout << ' ';
            cout << ans[i] + bias;
        }

        cout << "\n";
        if(loop > 1) cout << "\n";
    }

    return 0;
}
