#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<queue>
using namespace std;
struct Node
{
	char ch;
	double freq;
	Node* left, * right;
};
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};
Node* getNode(char ch, double freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}
void BuildCodeMap(Node* root, string code, unordered_map<char, string>& CodeMap)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right)
	{
		CodeMap[root->ch] = code;
	}
	BuildCodeMap(root->left, code + '1', CodeMap);
	BuildCodeMap(root->right, code + '0', CodeMap);
}
unordered_map<char, string> buildHufman(unordered_map<char, double>* charCount)
{
	priority_queue<Node*, vector<Node*>, comp> pq;
	for (auto& pair : *charCount)
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}
	while (pq.size() != 1)
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	unordered_map<char, string> CodeMap;
	BuildCodeMap(pq.top(), "", CodeMap);
	for (auto pair : CodeMap)
	{
		cout << pair.first << "-->" << pair.second<<endl;
	}
	return CodeMap;
}
string encodeString(string str, unordered_map<char, string> CodeMap)
{
	string result="";
	for (int i = 0; i < str.size(); i++)
	{
		result += CodeMap[str[i]];
	}
	return result;
}

void main()
{
	string str;
	getline(std::cin, str);
	unordered_map<char, double> charCount;
	for (char c : str)
	{
		charCount[c]++;
	}
	for (auto& pair : charCount)
	{
		cout << pair.first << ":";
		pair.second = pair.second / str.size();
		cout << pair.second << endl;
	}
	string codedString;
	codedString=encodeString(str, buildHufman(&charCount));
	cout << codedString;
}