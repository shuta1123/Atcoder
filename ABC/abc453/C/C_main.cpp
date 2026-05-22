#include<bits/stdc++.h>

using namespace std;
using ll=long long;

ll sgn(ll x){
  if(x>0){return 1;}
  else if(x<0){return -1;}
  return 0;
}

int main(){
  ll n;
  cin >> n;
  vector<ll> l(n);
  for(auto &nx : l){
    cin >> nx;
    nx*=2;
  }
  ll best=0;
  for(ll i=0;i<(1ll<<n);i++){
    ll pos=1,cur=0;
    for(ll j=0;j<n;j++){
      ll npos=pos;
      if(i&(1ll<<j)){npos+=l[j];}
      else{npos-=l[j];}
      if(sgn(pos)*sgn(npos)<0){cur++;}
      pos=npos;
    }
    best=max(best,cur);
  }
  cout << best << "\n";
  return 0;
}
