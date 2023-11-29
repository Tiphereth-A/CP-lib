#include <bits/stdc++.h>
using namespace std;
#define F(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)

const int N = 10000005;
const int P = 1e9+7;

int n, K;
int v[N], pr[N / 10], tot;
int pwk[N / 10], sig[N], x[N], y[N];
int sum;

int pw(int x, int y) {
	int m = 1;
	for (; y > 0; y >>= 1, x = 1LL * x * x % P)
		if (y & 1) m = 1LL * m * x % P;
	return m;
}

int main(void) {
	scanf("%d %d", &n, &K);
	
	v[1] = 1, sig[1] = 1;
	F(i, 2, n) {
		if (!v[i]) {
			pr[++tot] = i;
			pwk[tot] = pw(i, K);
			sig[i] = 1 + pwk[tot];
			x[i] = 1;
			y[i] = sig[i];
		}
		for (int j = 1; j <= tot && i * pr[j] <= n; j++) {
			int t = i * pr[j];
			v[t] = 1;
			if (i % pr[j] != 0) {
				sig[t] = 1LL * sig[i] * sig[pr[j]] % P;
				x[t] = sig[i];
				y[t] = sig[pr[j]];
			}
			else {
				x[t] = x[i];
				y[t] = (1LL * y[i] * pwk[j] + 1) % P;
				sig[t] = 1LL * x[t] * y[t] % P;
				break;
			}
		}
	}
	F(i, 1, n) sum = (sum + sig[i]) % P; printf("%d\n", sum);
	
	return 0;
}
