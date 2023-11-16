#include<iostream>
#include<ctime>
#include<vector>
using namespace std;

void main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	vector<int> seq;
	vector<int> subseq;
	int n;
	int max = 0;
	int end=0;
	cin >> n;
	cout << "Начальная последовательность:" << endl;
	for (int i = 0; i < n; i++)
	{
		seq.push_back(rand()%20+1);
		cout << seq[i] << "  ";
	}
	vector<int> dp(n, 1);
	vector<int> prev(n, -1);
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (seq[i] > seq[j] && dp[i] < dp[j] + 1)
			{
				dp[i] = dp[j] + 1;
				prev[i] = j;
			}
		}
		if (dp[i] > max)
		{
			max = dp[i];
			end = i;
		}
	}
	while (end != -1)
	{
		subseq.push_back(seq[end]);
		end = prev[end];
	}
	reverse(subseq.begin(), subseq.end());
	cout << endl;
	for (int i = 0; i < subseq.size(); i++)
	{
		cout << subseq[i] << "  ";
	}
}