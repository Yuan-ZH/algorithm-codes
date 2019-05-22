#include<iostream>
#include<string>
using namespace std;
using ull=unsigned long long;
class HashList {
	//��ϣ��
public:
	HashList(int maxs = 100007) {
		maxsize = maxs;
		array = new string[maxs];
		bin = new ull[maxs];
		bin[0] = 1;
		for (int a = 1; a < maxs; ++a) {
			bin[a] = bin[a - 1] * hashP;
		}
	}
	~HashList() {
		delete[]bin;
		delete[]array;
	}
	void add(string s) {
		if (!array[hash(s) % maxsize].empty())cerr << "hash crashed" << endl;
		array[hash(s) % maxsize] = s;
		cout << "��ϣֵ" << hash(s) << endl;
	}
	ull hash(string& s) {
		ull hashint = 0;
		for (auto& x : s) {
			hashint = (x - 'a'+1) + hashint * hashP;
		}
		return hashint;
	}
	string& find(ull hashint) {
		return array[hashint % maxsize];
	}
	ull getsub(int l, int r, ull * hasha) {
		if (r < l)return 0;
		return hasha[r] - (l - 1 >= 0 ? hasha[l - 1] : 0) * bin[r - l + 1]; }
	ull * bin;
	int maxsize = 100007;
	const ull hashP = 131;
private:
	string* array;


};
int hashDone[100008];
int main() {
	int n;
	cin >> n;
	HashList hashstr;
	for (int a = 1; a <= n; ++a) {
		string s;
		cin >> s;
		hashstr.add(s);
	}

	int m;
	cin >> m;
	for (int ac = 1; ac <= m; ++ac) {
		ull hashP = hashstr.hashP;
		string s;
		cin >> s;
		ull* hasharray = new ull[s.length()];
		hasharray[0] = s[0] - 'a'+1;
		int len = s.length();
		for (int a = 1; a < len; ++a) {
			hasharray[a] = hasharray[a - 1] * hashP + s[a] - 'a'+1;
		}

		for (int a = 0; a <=len; ++a) {
			for (int chr = 'a'; chr <= 'z'; ++chr) {
				//change
				if(a<len)
				{
					ull hashi = hasharray[len - 1] + (chr - s[a]) * hashstr.bin[len - 1 - a];
					if (hashDone[hashi % hashstr.maxsize] != ac) {
						string& ans = hashstr.find(hashi);
						if (!ans.empty()) {
							cout << ans << endl;
						}
						hashDone[hashi % hashstr.maxsize] = ac;
					}

				}
				//insert
				{
					ull hashi = ((a - 1 >= 0) ? hasharray[a - 1] * hashstr.bin[len  - (a - 1) ] : 0) + (chr - 'a'+1) * hashstr.bin[len - a] + hashstr.getsub(a, len - 1, hasharray);
					if (hashDone[hashi % hashstr.maxsize] != ac) {
						string& ans = hashstr.find(hashi);
						if (!ans.empty()) {
							cout << ans << endl;
						}
						hashDone[hashi % hashstr.maxsize] = ac;
					}
				}
			}
			
			//delete
			{
				ull hashi = ((a - 1 >= 0) ? hasharray[a - 1] * hashstr.bin[len - 1 - (a - 1) - 1] : 0) + hashstr.getsub(a + 1, len - 1, hasharray);
				if (hashDone[hashi % hashstr.maxsize] != ac) {
					string& ans = hashstr.find(hashi);
					if (!ans.empty()) {
						cout << ans << endl;
					}
					hashDone[hashi % hashstr.maxsize] = ac;
				}
			}
		}
		delete[]hasharray;
	}

}