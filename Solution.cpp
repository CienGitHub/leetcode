#include "stdafx.h"
#include "Solution.h"

int Solution::evalRPN(vector<string>& tokens) {

	stack<int> stack;
	
	for (int i = 0; i < tokens.size(); i++) {
		if(tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/")
			stack.push(atoi(tokens[i].c_str()));
		else {
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();

			if (tokens[i] == "+") {
				stack.push(a + b);
			}
			else if (tokens[i] == "-") {
				stack.push(a - b);
			}
			else if (tokens[i] == "*") {
				stack.push(a * b);
			}
			else if (tokens[i] == "/") {
				stack.push(a / b);
			}
		}
	}
	return stack.top();
}

string Solution::simplifyPath(string path) {

	string dirName;
	vector<string> dirNameVec;

	for (int i = 0; i < path.length(); i++) {
		
		if (i == 0 && path[i] == '/')
			continue;
		
		if (path[i] != '/') {
			dirName.push_back(path[i]);
		}
		if(path[i] == '/' || i == path.length() - 1) {
			//��⵽'/'�����һ�ζ���Ҫ����
			if (dirName == ".") {
				dirName.clear();
				continue;
			}
			else if (dirName == "..") {
				dirName.clear();
				if (dirNameVec.size() == 0) {
					continue;
				}
				else {
					dirNameVec.pop_back();
					continue;
				}
			}
			else if (dirName.empty())
				continue;
			else {
				dirNameVec.push_back(dirName);
				dirName.clear();
			}
		}
	}

	string ret;
	ret.push_back('/');
	for (int i = 0; i < dirNameVec.size(); i++) {
		ret.append(dirNameVec[i]);
		if(i != dirNameVec.size() - 1)
			ret.push_back('/');
	}

	return ret;
}

vector<int> Solution::inorderTraversal(TreeNode * root) {
	
	vector<int> ret;

	if (root == NULL)
		return ret;

	//���ǿ�
	TreeNode* curNode = root;
	stack<TreeNode*> stack;		//stack�д�ŵ���TreeNode���͵�ָ�����

	while (!stack.empty() || curNode) {
		//ջ��Ϊ�ջ�ǰָ�벻Ϊ��ʱ
		if (curNode) {
			//��ǰָ�벻Ϊ��
			stack.push(curNode);
			curNode = curNode->left;
		}
		else {
			//ָ��Ϊ�գ�ջ��Ϊ��ʱ����ջ������
			curNode = stack.top();
			stack.pop();
			ret.push_back(curNode->val);
			curNode = curNode->right;
		}
	}

	return ret;
}

//��д����leetcode�ϳ���ʱ������
//bool Solution::isPowerOfTwo(int n) {
//
//	int count = 0;	//��¼n��������1����������Ϊ1����Ϊ2��ƽ����
//	while (n > 0) {
//		count += (n & 1);
//		n >> 1;
//	}
//	return count == 1;
//}

bool Solution::isPowerOfTwo(int n) {

	//��n = 8, ������λ1000, 8-1=7(111)
	//   1000
	// & 0111
	//   ��������
	//   0000
	return (n > 0) && (((n - 1) & n) == 0);
}

int Solution::numTrees(int n) {


	return 0;
}

int Solution::maxDepth(TreeNode * root) {
	
	//�ݹ���õķ�������ʱ������
	/*if (root == NULL)
		return 0;
	return maxDepth(root->left) > maxDepth(root->right) ? maxDepth(root->left) + 1 : maxDepth(root->right) + 1;*/

	//�ǵݹ�ʵ�� - �������������
	queue<TreeNode*> queue;

	if (root != NULL)
		queue.push(root);

	int curLevelCount = 1;		//��¼����Ľڵ�������ʼΪ���ڵ�
	int nextLevelCount = 0;		//��¼��һ��Ӧ���еĽڵ���
	int level = 0;				//����

	while (!queue.empty()) {
		
		//���Ӳ�����
		TreeNode* curNode = queue.front();
		queue.pop();
		cout << curNode->val << " --> ";

		curLevelCount--;	//��ǰ�����Ѿ�����һ���ڵ�

		//���Һ������
		if (curNode->left) {
			queue.push(curNode->left);
			nextLevelCount++;	//�²�ڵ���++
		}
			
		if (curNode->right) {
			queue.push(curNode->right);
			nextLevelCount++;	//�²�ڵ���++
		}
			
		if (curLevelCount == 0) {
			//��ǰ��ڵ�ȫ�������꣬������һ����������һ��
			level++;
			curLevelCount = nextLevelCount;
			nextLevelCount = 0;
		}
	}
	cout << endl << endl;
	cout << "the max depth of the tree is " << level << endl;

	return level;
}

TreeNode * Solution::buildTree(vector<int>& preorder, vector<int>& inorder) {
	
	if (preorder.empty())
		return NULL;
	
	//ǰ������ĵ�һ���ڵ�Ϊ���ڵ�
	TreeNode* root = new TreeNode(preorder.front());

	//�ֱ��¼���������ڵ�����
	int leftCount = 0;
	int rightCount = 0;

	//������������ҵ����ڵ㣬��ά��count
	while (inorder[leftCount] != root->val)		//�˴�������  while (inorder[leftCount++] != root->val);  ��д������Ϊ�������ϵ��Ǵ��ж���Ȼִ���� ++ ����
		leftCount++;
	rightCount = inorder.size() - 1 - leftCount;

	//��������ǰ�������������
	vector<int> leftPreorder;
	leftPreorder.assign(preorder.begin() + 1, preorder.begin() + leftCount + 1);
	vector<int> leftInorder;
	leftInorder.assign(inorder.begin(), inorder.begin() + leftCount);

	//��������ǰ�������������
	vector<int> rightPreorder;
	rightPreorder.assign(preorder.end() - rightCount, preorder.end());
	vector<int> rightInorder;
	rightInorder.assign(inorder.end() - rightCount, inorder.end());

	//�ݹ�������������
	root->left = buildTree(leftPreorder, leftInorder);
	root->right = buildTree(rightPreorder, rightInorder);

	return root;
}

int Solution::findJudge(int N, vector<vector<int>>& trust) {
	
	//��¼��ȳ���
	vector<int> in(N, 0);
	vector<int> out(N, 0);

	for (int i = 0; i < trust.size(); i++) {
		out[trust[i][0] - 1] ++;
		in[trust[i][1] - 1] ++;
	}

	for (int i = 0; i < N; i++) {
		if (out[i] == 0 && in[i] == N - 1)
			return i + 1;
	}
	return -1;
}

Node * Solution::cloneGraph(Node * node) {
	
	static map<Node*, Node*> isCloned;  //����Ѿ����ƹ��Ľڵ㣬ԭָ���Ӧ���ƺ��ָ��
	vector<Node*> neighbers;			//��Ÿ��ƺ�����ڽڵ�

	//��һ������Ҫ�Ѹýڵ���Ϊ�Ը���
	Node* newNode = new Node();
	isCloned.emplace(node, newNode);		//���Ϊ�Ѹ���
	
	for (auto item : node->neighbors) {
		//�����������ڽڵ�
		if (isCloned.count(item) == 0) {
			//�ڵ�û�б�����
			Node* tmpNode = cloneGraph(item);
			neighbers.push_back(tmpNode);
		}
		else {
			//�ڵ��Ѿ�������
			neighbers.push_back(isCloned[item]);
		}
	}

	newNode->val = node->val;
	newNode->neighbors = neighbers;

	return newNode;
}

bool Solution::canFinish(int numCourses, vector<vector<int>>& prerequisites) {

	vector<int> in(numCourses, 0);		//��¼���
	vector<vector<int>> g(numCourses, vector<int>());	//��ʼ���ڽӱ�
	stack<int> stack;		//����ջ
	int popCount = 0;		//��¼pop���и���

	for (auto item : prerequisites) {
		//�������нڵ����
		in[item[1]] ++;
		//�����ڽӱ�
		g[item[0]].push_back(item[1]);
	}

	
	for (int v = 0; v < numCourses; v++) {
		if (in[v] == 0) {
			//���Ϊ0��Ԫ�����
			stack.push(v);
		}
	}

	while (!stack.empty()) {
		//ջ��Ϊ�գ���ջ
		int nowV = stack.top();		//��ǰ��Ҫɾ���Ľڵ�
		stack.pop();
		popCount++;		//pop���м�1

		for (int adjV : g[nowV]) {
			//����ջ��Ԫ�ص������ٱ�
			in[adjV] --;		//�ٱ���ȼ�һ
			if (in[adjV] == 0) {
				//in[adjV] = -1;		//�����Ϊ-1����ʾ��ͼ��ɾ���ýڵ�
				stack.push(adjV);
			}
		}
	}

	return popCount == numCourses;
}

vector<int> Solution::findMinHeightTrees(int n, vector<vector<int>>& edges) {
	
	if (n == 1)
		return { 0 };
	
	vector<int> ret;	//�������
	queue<int> queue;	//��������

	//��ʼ���ڽӱ�
	vector<vector<int>> g(n, vector<int>());

	//�����ڽӱ�
	for (auto edge : edges) {
		g[edge[0]].push_back(edge[1]);
		g[edge[1]].push_back(edge[0]);
	}

	for (int v = 0; v < n; v++) {
		//�������нڵ㣬��Ϊ1�Ľڵ����
		if (g[v].size() == 1) {
			queue.push(v);
		}
	}

	while (n > 2) {
		//ͼ�нڵ�������2����ʱ��ѭ��
		int size = queue.size();
		n -= size;

		for (int i = 0; i < size; i++) {
			int curV = queue.front();
			queue.pop();
			for (auto adjV : g[curV]) {
				//�������Ϊ1�Ľڵ���������ڽڵ�
				g[adjV].erase(find(g[adjV].begin(), g[adjV].end(), curV));	//�����ڽڵ�����ڽڵ���ɾ���ýڵ�
				if (g[adjV].size() == 1)
					//ɾ��֮�������Ϊ1�����
					queue.push(adjV);
			}
		}
	}
	
	while (!queue.empty()) {
		ret.push_back(queue.front());
		queue.pop();
	}

	return ret;
}

vector<string> getNexts(string curStr) {

	vector<string> ret;

	for (int i = 0; i < 4; i++) {
		string newStr = curStr;
		newStr[i] == '9' ? newStr[i] = '0' : newStr[i] ++;
		ret.push_back(newStr);
		newStr = curStr;
		newStr[i] == '0' ? newStr[i] = '9' : newStr[i] --;
		ret.push_back(newStr);
	}

	return ret;
}

int Solution::openLock(vector<string>& deadends, string target) {

	if (target == "0000")
		return 0;
	
	unordered_set<string> deadendsSet(deadends.begin(), deadends.end());	//������
	if (deadendsSet.count("0000") != 0 || deadendsSet.count(target) != 0)
		return -1;
	
	queue<string> buffer;		//���л������������Ҫ���ǵ��������
	buffer.push("0000");

	unordered_set<string> visited;	//�Ѿ������ʵ����뼯��
	visited.insert("0000");
	
	int step = 0;	//�������貽��

	while (!buffer.empty()) {

		int size = buffer.size();		//��¼��ǰ������
		while (size-- > 0) {
			vector<string> nexts = getNexts(buffer.front());
			buffer.pop();
			for (auto next : nexts) {
				//������һ�������п���
				if (next == target)
					//����
					return ++step;
				if (deadendsSet.count(next) == 0 && visited.count(next) == 0) {
					//�Ȳ���������Ҳû�б����ʹ�
					visited.insert(next);
					buffer.push(next);		//���
				}
			}
		}
		step++;
	}
	return -1;
}
