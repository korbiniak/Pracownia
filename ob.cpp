#include<bits/stdc++.h>
using namespace std;

const int M = (1<<15);
int tree[M * 2];

void update(int where, int val) {
	where += M;
	while(where > 0) {
		tree[where] += val;
		where /= 2;
	}
}

int query(int from, int to) {
	if(from > to)	return 0;
	from += M;
	to += M;
	int res = tree[from];
	if(from != to)	res += tree[to];
	while(from / 2 != to / 2) {
		if(from % 2 == 0) 	res += tree[from + 1];
		if(to % 2 == 1)		res += tree[to - 1];
		from /= 2;
		to /= 2;	
	}
	return res;
}

char input[10000];

int main() {
	int d;
	scanf("%s", input);
	int len = strlen(input);
	for(int i = 0 ; i < len ; i++)
		if(input[i] == '1')
			update(i, 1);
	scanf("%d", &d);
	int best = 1000000000;
	for(int i = 1 ; i < len - d; i++) {
		int qur = (d - query(i, i + d - 1)) + query(0, i - 1) + query(i + d, len - 1);
		best = min(qur, best);
	}
	printf("%d\n", best);
}