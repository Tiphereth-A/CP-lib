#include <bits/stdc++.h>
using namespace std;

const int N = 1e7;
const int K = 1e7;

int main(void) {
	srand(time(0));
	
	double t = clock();
	
	int n = N - rand() % 10;
	int k = K - rand() % 10;
	printf("%d %d\n", n, k);
	
	while (clock() - t < 1000.0 * 1000);
	
	return 0;
}
