#include<cstdlib>
#include<vector>
#include<queue>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<stack>
#define BLACK false
#define WHITE true
#define NONE 0
#define MATE 1
#define PAT 2
#define x first
#define y second
using namespace std;

int dirX[] = {1, 1, 1, 0, 0, -1, -1, -1};
int dirY[] = {1, 0, -1, 1, -1, 1, 0, -1};
map<pair<int, bool>, pair<int, bool>> prevPos;

int Hash(pair<int, int> pos) {
	return pos.x * 10 + pos.y;
}

pair<int, int> Hash(string pos) {
	return make_pair(pos[0] - 'a' + 1, pos[1] - '0');
}

void wait() {
	string waiter;
	getline(cin, waiter);
}

struct position {
	pair<int,int> wk;
	pair<int,int> wt;
	pair<int,int> bk;
	bool color;
	position() {}
	position(string sWk, string sWt, string sBk, string iColor) {
		wk = Hash(sWk);
		wt = Hash(sWt);
		bk = Hash(sBk);
		if(iColor == "black")	color = BLACK;
		else					color = WHITE;
	}
};

pair<int, bool> Hash(position pos) {
 	int h = Hash(pos.wk) * 10000 + Hash(pos.wt) * 100 + Hash(pos.bk);
	return make_pair(h, pos.color);
}	

bool isPosLegal(pair<int, int> p) {
	if(p.x < 1 || p.x > 8 || p.y < 1 || p.y > 8)
		return false;
	return true;
}

bool kingsTooClose(position pos) {
	for(int i = 0 ; i < 8 ; i++) 
		if(pos.bk.x + dirX[i] == pos.wk.x) 
			if(pos.bk.y + dirY[i] == pos.wk.y)
				return true;
	return false;
}

//sprawdza, czy czarny moze sie gdziekolwiek ruszyc
//true if can, false if not
bool checkBlackMove(position pos) {
	if(pos.color == WHITE) {
		cout << "Cos nie tak!\n";
		return false;
	}
	position move;
	for(int i = 0 ; i < 8 ; i++) {
		move = pos;
		move.bk.x += dirX[i];
		move.bk.y += dirY[i];
		if(isPosLegal(move.bk) == false)
			continue;
		//jesli wieza nie czekuje krola
		if((move.bk.x == move.wt.x && move.bk.y == move.wt.y) ||
			(move.bk.x != move.wt.x && move.bk.y != move.wt.y)) 
				//jesli krolowie nie sa za blisko
				if(kingsTooClose(move) == false)
					return true;
	}
	return false;
}

void d(int i) {
	cout << "deb " << i << "\n";
}

int checkMate(position pos) {
	if(pos.color == WHITE)	return NONE;
	//if black can make a move, then its not mate nor pat
	if(checkBlackMove(pos))	return NONE;
	//if tower is chechkin king, then its mate
	if(pos.bk.x == pos.wt.x || pos.bk.y == pos.wt.y) return MATE;
	//its pat
	return PAT;
}

void debug(pair<int, int> p) {
	cout << (char)(p.x + 'a' - 1) << p.y << " ";
}

void debug(position pos) {
	if(pos.color == BLACK)
		cout << "black ";
	else
		cout << "white ";
	debug(pos.wk);
	debug(pos.wt);
	debug(pos.bk);
	cout << endl;
}

position unHash(pair<int, bool> h) {
	position ans;
	ans.bk.y = h.first % 10;
	ans.bk.x = (h.first % 100 - (h.first % 10)) / 10;
	ans.wt.y = (h.first % 1000 - (h.first % 100)) / 100;
	ans.wt.x = (h.first % 10000 - (h.first % 1000)) / 1000;
	ans.wk.y = (h.first % 100000 - (h.first % 10000)) / 10000;
	ans.wk.x = (h.first % 1000000 - (h.first % 100000)) / 100000;
	ans.color = h.second;
	return ans;
}

void debugBack(pair<int, bool> pos, pair<int, bool> beg, bool ifDebug) {
	stack<pair<int, bool>> S;
	while(pos.first != beg.first) {
		// debug(pos);
		S.push(pos);
		pos = prevPos[pos];
	}
	if(ifDebug == false)  {
		cout << S.size() << "\n";
		return;
	}
	cout << "Moves required: " << S.size() << "\n";
	S.push(beg);
	while(!S.empty()) {
		debug(unHash(S.top()));
		S.pop();
	}
}

void go(bool ifDebug) {
	string color, wk, wt, bk;
	cin >> color >> wk >> wt >> bk;
	position curPos(wk, wt, bk, color);
	position beg = curPos;
	queue<position> q;
	q.push(curPos);
	prevPos.clear();
	prevPos[Hash(curPos)] = make_pair(-1, 0);
	while(checkMate(curPos) != MATE) {
		curPos = q.front(); 
		q.pop();
		if(curPos.color == BLACK) {
			for(int i = 0 ; i < 8 ; i++) {
				position move = curPos;
				move.bk.x += dirX[i];
				move.bk.y += dirY[i];
				move.color = WHITE;
				if(prevPos.count(Hash(move)) != 0) 						continue;
				if(isPosLegal(move.bk) == false)						continue;
				if(kingsTooClose(move) == true)							continue;
				if(move.wt.x == move.bk.x || move.wt.y == move.bk.y)	continue;
				prevPos[Hash(move)] = Hash(curPos);
				q.push(move);
			}
		}
		if(curPos.color == WHITE) {
			for(int i = 0 ; i < 8 ; i++) {
				position move = curPos;
				move.wk.x += dirX[i];
				move.wk.y += dirY[i];
				move.color = BLACK;
				if(prevPos.count(Hash(move)) != 0) 						continue;
				if(isPosLegal(move.wk) == false)						continue;
				if(kingsTooClose(move) == true)							continue;
				if(move.wt.x == move.wk.x && move.wt.y == move.wk.y)	continue;
				prevPos[Hash(move)] = Hash(curPos);
				q.push(move);
			}
			//tower
			for(int j = 0 ; j < 4 ; j++) {
				for(int i = 1; i <= 7 ; i++) {
					position move = curPos;
					if(j == 0)	move.wt.x += i;
					if(j == 1)	move.wt.x -= i;
					if(j == 2) 	move.wt.y += i;
					if(j == 3) 	move.wt.y -= i;
					move.color = BLACK;
					if(prevPos.count(Hash(move)) != 0) 					continue;
					if(isPosLegal(move.wt) == false)					break; 
					if(move.wt.x == move.wk.x && move.wt.y == move.wk.y)break;
					prevPos[Hash(move)] = Hash(curPos);
					q.push(move);
				}
			}
		}		
	}
	debugBack(Hash(curPos), Hash(beg), ifDebug);
}

int main(int argc, char * argv []) {
	cin.tie();
	int n;
	cin >> n;
	for(int i = 0 ; i < n ; i++)
		go(atoi(argv[1]));
}