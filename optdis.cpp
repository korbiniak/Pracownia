#include<bits/stdc++.h>
using namespace std;

char input[10000];
int t[10000]; 

int main() {
	int d;
	scanf("%s", input);
	scanf("%d", &d);
	int len = strlen(input);
	int cnt = 0;
	for(int i = 0 ; i < len ; i++)
		if(input[i] == '1') {
			t[i] = 1;
			cnt++;
		}
	int p = 1, k = d;
	int cur = 0;
	for(int i = p ; i <= k ; i++)
		if(t[i] == 1)
			cur++;
	int best = 1000000;
	for( ; k < len - 1; k++, p++) {
		best = min(best, d + cnt - cur * 2);
		if(t[p] == 1)
			cur--;
		if(t[k + 1] == 1)
			cur++;
	}
	printf("%d\n",  best);
}