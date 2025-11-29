// g++ -std=c++11 -O3 -Wall asaProjeto.cpp -lm
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        return ((size_t)p.first << 32) | (size_t)p.second;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    
    vector<ll> P(n+2);
    vector<char> C(n+2);
    
    // Sentinelas: posições 0 e n+1 são terminais
    P[0] = 1; P[n+1] = 1;
    C[0] = 'T'; C[n+1] = 'T';

    for(int i=1; i<=n; i++) cin >> P[i];
    
    string s; 
    cin >> s;
    for(int i=1; i<=n; i++) C[i] = s[i-1];

    // Tabela de afinidade (linhas = de, colunas = para)
    // Classes: P, N, A, B
    int AfTable[4][4] = {
        {1, 3, 1, 3}, // P
        {5, 1, 0, 1}, // N
        {0, 1, 0, 4}, // A
        {1, 3, 2, 3}  // B
    };
    
    auto idx = [](char ch)->int{
        if(ch=='P') return 0;
        if(ch=='N') return 1;
        if(ch=='A') return 2;
        return 3; // B
    };
    
    auto Af = [&](char a, char b)->int{
        if(a=='T' || b=='T') return 1;
        return AfTable[idx(a)][idx(b)];
    };

    // DP: dp[i][j] = energia máxima para remover todos entre i e j
    int N = n+2;
    vector<vector<ll>> dp(N, vector<ll>(N, LLONG_MIN));
    
    // Base: intervalos vazios ou adjacentes
    for(int i=0; i<N; i++) {
        dp[i][i] = 0;
        if(i+1 < N) dp[i][i+1] = 0;
    }

    // Preencher por comprimento crescente
    for(int len = 2; len <= n+1; ++len){
        for(int i=0; i+len < N; ++i){
            int j = i + len;
            ll best = LLONG_MIN;
            
            for(int k = i+1; k < j; ++k){
                ll contrib = P[i] * (ll)Af(C[i], C[k]) * P[k] +  
                             P[k] * (ll)Af(C[k], C[j]) * P[j];   
                ll cand = dp[i][k] + dp[k][j] + contrib;
                
                if(cand > best){
                    best = cand;
                }
            }
            
            dp[i][j] = best;
        }
    }

    // Reconstrução da sequência lexicograficamente menor
    unordered_map<pair<int,int>, vector<int>, PairHash> memo;
    memo.reserve(N * N / 2);
    
    function<const vector<int>&(int,int)> reconstruct = [&](int i, int j)->const vector<int>&{
        static const vector<int> empty;
        if(i+1 >= j) return empty;
        
        auto key = make_pair(i, j);
        auto it = memo.find(key);
        if(it != memo.end()) return it->second;
        
        ll target = dp[i][j];
        vector<int> bestSeq;
        
        // Apenas testar k's que dão o valor ótimo, começando pelo menor
        for(int k = i+1; k < j; ++k){
            ll contrib = P[i] * (ll)Af(C[i], C[k]) * P[k] + 
                         P[k] * (ll)Af(C[k], C[j]) * P[j];
            ll candVal = dp[i][k] + dp[k][j] + contrib;
            
            if(candVal == target){
                const vector<int>& left = reconstruct(i, k);
                const vector<int>& right = reconstruct(k, j);
                vector<int> cand;
                cand.reserve(left.size() + right.size() + 1);
                cand.insert(cand.end(), left.begin(), left.end());
                cand.insert(cand.end(), right.begin(), right.end());
                cand.push_back(k);
                
                if(bestSeq.empty() || cand < bestSeq){
                    bestSeq = move(cand);
                }
            }
        }
        
        return memo[key] = std::move(bestSeq);
    };
    
    vector<int> result = reconstruct(0, n+1);

    // Output
    cout << dp[0][n+1] << "\n";
    for(size_t t=0; t<result.size(); ++t){
        if(t) cout << ' ';
        cout << result[t];
    }
    cout << "\n";
    
    return 0;
}