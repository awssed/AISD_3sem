#include"iostream"
using namespace std;

void Hanoi(int n,int source,int target)
{
	if (n == 1)
	{
		cout << "����������� ���� 1 � " << source << " �� " << target << endl;
		return;
	}
	int other = 6 - source - target;
	Hanoi(n - 1, source, other);
	cout << "����������� ���� " << n << " c " << source << " �� " << target << endl;
	Hanoi(n - 1, other, target);
}

void main()
{
	setlocale(LC_ALL, "rus");
	int N, target;
	cout << "N:";
	cin >> N;
	cout << "target:";
	cin >> target;
	if (N == 1 || target==1 || target<0 || N<0)
	{
		cout << "Error" << endl;
	}
	Hanoi(N, 1, target);

}