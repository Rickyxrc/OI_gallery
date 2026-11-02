#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ll N;
	cin >> N;
	
	auto calc=[&](int a, int n){
		int ok=0,ng=1e9;
		while(ng-ok>1){
			int mid=(ok+ng)/2;
			ll s=N;
			for(int i=0;i<n;i++)s/=a+i*mid;
			if(s)ok=mid;
			else ng=mid;
		}
		return ok;
	};
	
	ll ans=0;
	for(int a=1;a<=1e6;a++){
		int n=3;
		ll NN=N/a/(a+1)/(a+2);
		while(NN){
			ans+=calc(a,n);
			NN/=a+n;
			n++;
		}
	}
	cout << ans << endl;
}
