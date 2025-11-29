#include <iostream> 
#include <vector> 
#include <string> 
#include <unordered_map> 
#include <functional> 
#include <climits>
using namespace std;
using ull = unsigned long long;
using u64 = unsigned long long;
using i64 = long long;

inline u64 keyIJ(int i, int j){
    return ( (u64)( (u64)i << 32 ) | (u64)j );
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;

    int N = n + 2; 

    vector<ull> P(N);
    vector<char> C(N);

    P[0] = 1; P[n+1] = 1;
    C[0] = 'T'; C[n+1] = 'T';

    for(int i = 1; i <= n; ++i) cin >> P[i];
    string s; cin >> s;
    for(int i = 1; i <= n; ++i) C[i] = s[i-1];

    static const int AfTable[4][4] = {
        {1, 3, 1, 3},
        {5, 1, 0, 1},
        {0, 1, 0, 4},
        {1, 3, 2, 3}
    };

    auto idx = [](char ch)->int{
        if(ch=='P') return 0;
        if(ch=='N') return 1;
        if(ch=='A') return 2;
        return 3;
    };

    vector<int> classIdx(N);
    for(int i=0;i<N;++i){
        if(C[i]=='T') classIdx[i] = -1;
        else classIdx[i] = idx(C[i]);
    }

    vector<vector<int>> A(N, vector<int>(N));
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(C[i]=='T' || C[j]=='T') A[i][j] = 1;
            else A[i][j] = AfTable[classIdx[i]][classIdx[j]];
        }
    }

    vector<vector<ull>> dp(N, vector<ull>(N, 0));

    vector<vector<char>> valid(N, vector<char>(N, 0));
    for(int i=0;i<N;++i){
        dp[i][i] = 0; valid[i][i] = 1;
        if(i+1 < N){ dp[i][i+1] = 0; valid[i][i+1] = 1; }
    }

    for(int len = 2; len < N; ++len){
        for(int i=0; i + len < N; ++i){
            int j = i + len;
            ull best = 0;
            bool found = false;

            const ull Pi = P[i];
            const ull Pj = P[j];

            for(int k = i+1; k < j; ++k){
                ull contrib = Pi * (ull)A[i][k] * P[k] + P[k] * (ull)A[k][j] * Pj;
                ull cand = dp[i][k] + dp[k][j] + contrib;
                if(!found || cand > best){
                    best = cand;
                    found = true;
                }
            }

            dp[i][j] = best;
            valid[i][j] = found ? 1 : 0;
        }
    }

    unordered_map<u64, vector<int>> memo;
    memo.reserve(1024);

    function<const vector<int>&(int,int)> reconstruct = [&](int i, int j) -> const vector<int>& {
        static const vector<int> empty;
        if(i+1 >= j) return empty;

        u64 key = keyIJ(i,j);
        auto it = memo.find(key);
        if(it != memo.end()) return it->second;

        ull target = dp[i][j];
        vector<int> bestSeq;
        vector<int> leftSeq, rightSeq;

        for(int k = i+1; k < j; ++k){
            ull contrib = P[i] * (ull)A[i][k] * P[k] + P[k] * (ull)A[k][j] * P[j];
            ull candVal = dp[i][k] + dp[k][j] + contrib;
            if(candVal != target) continue;

            const vector<int>& L = reconstruct(i, k);
            const vector<int>& R = reconstruct(k, j);

            vector<int> cand;
            cand.reserve(L.size() + R.size() + 1);
            cand.insert(cand.end(), L.begin(), L.end());
            cand.insert(cand.end(), R.begin(), R.end());
            cand.push_back(k);

            if(bestSeq.empty() || cand < bestSeq){
                bestSeq = std::move(cand);
            }
        }

        auto res = memo.emplace(key, std::move(bestSeq)).first;
        return res->second;
    };

    const vector<int>& result = reconstruct(0, n+1);

    cout << dp[0][n+1] << "\n";
    for(size_t t=0; t<result.size(); ++t){
        if(t) cout << ' ';
        cout << result[t];
    }
    cout << "\n";

    return 0;
}
