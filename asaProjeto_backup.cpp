// g++ -std=c++11 -O3 -Wall asaProjeto.cpp -lm
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
    vector<vector<int>> choice(N, vector<int>(N, -1));
    
    for(int len = 2; len <= n+1; ++len){
        for(int i=0; i+len < N; ++i){
            int j = i + len;
            ll best = LLONG_MIN;
            int bestK = -1;
            
            for(int k = i+1; k < j; ++k){
                ll contrib = P[i] * (ll)Af(C[i], C[k]) * P[k] + 
                             P[k] * (ll)Af(C[k], C[j]) * P[j];
                ll cand = dp[i][k] + dp[k][j] + contrib;
                
                if(cand > best){
                    best = cand;
                    bestK = k;
                }
            }
            
            dp[i][j] = best;
            choice[i][j] = bestK;
        }
    }

    // Reconstrução com memoização usando índices ao invés de cópias
    map<pair<int,int>, pair<bool, int>> memo; // {processado, índice_inicio_no_result}
    vector<int> result;
    result.reserve(n);
    
    function<int(int,int)> build = [&](int i, int j) -> int {
        if(i+1 >= j) return result.size();
        
        auto key = make_pair(i, j);
        if(memo.count(key)) return memo[key].second;
        
        ll target = dp[i][j];
        int startIdx = result.size();
        int bestK = -1;
        int bestStartIdx = -1;
        
        for(int k = i+1; k < j; ++k){
            ll contrib = P[i] * (ll)Af(C[i], C[k]) * P[k] + 
                         P[k] * (ll)Af(C[k], C[j]) * P[j];
            if(dp[i][k] + dp[k][j] + contrib == target){
                // Tentar este k
                int tmpSize = result.size();
                build(i, k);
                build(k, j);
                result.push_back(k);
                
                if(bestK == -1){
                    // Primeira solução
                    bestK = k;
                    bestStartIdx = tmpSize;
                } else {
                    // Comparar sequências
                    bool isBetter = false;
                    int len1 = result.size() - bestStartIdx;
                    int len2 = result.size() - tmpSize;
                    
                    for(int idx = 0; idx < min(len2, len1); ++idx){
                        if(result[tmpSize + idx] < result[bestStartIdx + idx]){
                            isBetter = true;
                            break;
                        } else if(result[tmpSize + idx] > result[bestStartIdx + idx]){
                            break;
                        }
                    }
                    
                    if(isBetter){
                        // Nova sequência é melhor, descartar a antiga
                        result.erase(result.begin() + bestStartIdx, result.begin() + tmpSize);
                        bestStartIdx = result.size() - len2;
                        bestK = k;
                    } else {
                        // Manter antiga, descartar nova
                        result.erase(result.begin() + tmpSize, result.end());
                    }
                }
            }
        }
        
        memo[key] = {true, bestStartIdx};
        return bestStartIdx;
    };
    
    build(0, n+1);

    // Output
    cout << dp[0][n+1] << "\n";
    for(size_t t=0; t<result.size(); ++t){
        if(t) cout << ' ';
        cout << result[t];
    }
    cout << "\n";
    
    return 0;
}
