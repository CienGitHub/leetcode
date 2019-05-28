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
			//检测到'/'和最后一次都需要进入
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

	//树非空
	TreeNode* curNode = root;
	stack<TreeNode*> stack;		//stack中存放的是TreeNode类型的指针变量

	while (!stack.empty() || curNode) {
		//栈不为空或当前指针不为空时
		if (curNode) {
			//当前指针不为空
			stack.push(curNode);
			curNode = curNode->left;
		}
		else {
			//指针为空，栈不为空时，出栈并遍历
			curNode = stack.top();
			stack.pop();
			ret.push_back(curNode->val);
			curNode = curNode->right;
		}
	}

	return ret;
}

//该写法在leetcode上超出时间限制
//bool Solution::isPowerOfTwo(int n) {
//
//	int count = 0;	//记录n二进制中1的数量，若为1，则为2的平方数
//	while (n > 0) {
//		count += (n & 1);
//		n >> 1;
//	}
//	return count == 1;
//}

bool Solution::isPowerOfTwo(int n) {

	//若n = 8, 二进制位1000, 8-1=7(111)
	//   1000
	// & 0111
	//   ————
	//   0000
	return (n > 0) && (((n - 1) & n) == 0);
}

int Solution::numTrees(int n) {


	return 0;
}

int Solution::maxDepth(TreeNode * root) {
	
	//递归调用的方法超出时间限制
	/*if (root == NULL)
		return 0;
	return maxDepth(root->left) > maxDepth(root->right) ? maxDepth(root->left) + 1 : maxDepth(root->right) + 1;*/

	//非递归实现 - 层序遍历二叉树
	queue<TreeNode*> queue;

	if (root != NULL)
		queue.push(root);

	int curLevelCount = 1;		//记录本层的节点数，初始为根节点
	int nextLevelCount = 0;		//记录下一层应该有的节点数
	int level = 0;				//层数

	while (!queue.empty()) {
		
		//出队并遍历
		TreeNode* curNode = queue.front();
		queue.pop();
		cout << curNode->val << " --> ";

		curLevelCount--;	//当前层数已经遍历一个节点

		//左右孩子入队
		if (curNode->left) {
			queue.push(curNode->left);
			nextLevelCount++;	//下层节点数++
		}
			
		if (curNode->right) {
			queue.push(curNode->right);
			nextLevelCount++;	//下层节点数++
		}
			
		if (curLevelCount == 0) {
			//当前层节点全部遍历完，层数加一，并进入下一层
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
	
	//前序遍历的第一个节点为根节点
	TreeNode* root = new TreeNode(preorder.front());

	//分别记录左右子树节点数量
	int leftCount = 0;
	int rightCount = 0;

	//在中序遍历中找到根节点，并维护count
	while (inorder[leftCount] != root->val)		//此处不能用  while (inorder[leftCount++] != root->val);  的写法，因为，不符合的那次判断依然执行了 ++ 操作
		leftCount++;
	rightCount = inorder.size() - 1 - leftCount;

	//左子树的前序中序遍历容器
	vector<int> leftPreorder;
	leftPreorder.assign(preorder.begin() + 1, preorder.begin() + leftCount + 1);
	vector<int> leftInorder;
	leftInorder.assign(inorder.begin(), inorder.begin() + leftCount);

	//右子树的前序中序遍历容器
	vector<int> rightPreorder;
	rightPreorder.assign(preorder.end() - rightCount, preorder.end());
	vector<int> rightInorder;
	rightInorder.assign(inorder.end() - rightCount, inorder.end());

	//递归生成左右子树
	root->left = buildTree(leftPreorder, leftInorder);
	root->right = buildTree(rightPreorder, rightInorder);

	return root;
}

int Solution::findJudge(int N, vector<vector<int>>& trust) {
	
	//记录入度出度
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
	
	static map<Node*, Node*> isCloned;  //存放已经复制过的节点，原指针对应复制后的指针
	vector<Node*> neighbers;			//存放复制后的相邻节点

	//这一步就需要把该节点标记为以复制
	Node* newNode = new Node();
	isCloned.emplace(node, newNode);		//标记为已复制
	
	for (auto item : node->neighbors) {
		//遍历所有相邻节点
		if (isCloned.count(item) == 0) {
			//节点没有被复制
			Node* tmpNode = cloneGraph(item);
			neighbers.push_back(tmpNode);
		}
		else {
			//节点已经被复制
			neighbers.push_back(isCloned[item]);
		}
	}

	newNode->val = node->val;
	newNode->neighbors = neighbers;

	return newNode;
}

bool Solution::canFinish(int numCourses, vector<vector<int>>& prerequisites) {

	vector<int> in(numCourses, 0);		//记录入度
	vector<vector<int>> g(numCourses, vector<int>());	//初始化邻接表
	stack<int> stack;		//辅助栈
	int popCount = 0;		//记录pop序列个数

	for (auto item : prerequisites) {
		//生成所有节点入度
		in[item[1]] ++;
		//生成邻接表
		g[item[0]].push_back(item[1]);
	}

	
	for (int v = 0; v < numCourses; v++) {
		if (in[v] == 0) {
			//入度为0的元素入队
			stack.push(v);
		}
	}

	while (!stack.empty()) {
		//栈不为空，出栈
		int nowV = stack.top();		//当前需要删除的节点
		stack.pop();
		popCount++;		//pop序列加1

		for (int adjV : g[nowV]) {
			//遍历栈顶元素的所有临边
			in[adjV] --;		//临边入度减一
			if (in[adjV] == 0) {
				//in[adjV] = -1;		//入度置为-1，表示从图中删除该节点
				stack.push(adjV);
			}
		}
	}

	return popCount == numCourses;
}

vector<int> Solution::findMinHeightTrees(int n, vector<vector<int>>& edges) {
	
	if (n == 1)
		return { 0 };
	
	vector<int> ret;	//结果容器
	queue<int> queue;	//辅助队列

	//初始化邻接表
	vector<vector<int>> g(n, vector<int>());

	//生成邻接表
	for (auto edge : edges) {
		g[edge[0]].push_back(edge[1]);
		g[edge[1]].push_back(edge[0]);
	}

	for (int v = 0; v < n; v++) {
		//遍历所有节点，度为1的节点入队
		if (g[v].size() == 1) {
			queue.push(v);
		}
	}

	while (n > 2) {
		//图中节点数大于2个的时候循环
		int size = queue.size();
		n -= size;

		for (int i = 0; i < size; i++) {
			int curV = queue.front();
			queue.pop();
			for (auto adjV : g[curV]) {
				//遍历入度为1的节点的所有相邻节点
				g[adjV].erase(find(g[adjV].begin(), g[adjV].end(), curV));	//从相邻节点的相邻节点中删除该节点
				if (g[adjV].size() == 1)
					//删除之后如果度为1，入队
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
	
	unordered_set<string> deadendsSet(deadends.begin(), deadends.end());	//死锁集
	if (deadendsSet.count("0000") != 0 || deadendsSet.count(target) != 0)
		return -1;
	
	queue<string> buffer;		//队列缓冲区，存放需要考虑的所有情况
	buffer.push("0000");

	unordered_set<string> visited;	//已经被访问的密码集合
	visited.insert("0000");
	
	int step = 0;	//解锁所需步数

	while (!buffer.empty()) {

		int size = buffer.size();		//记录当前层数量
		while (size-- > 0) {
			vector<string> nexts = getNexts(buffer.front());
			buffer.pop();
			for (auto next : nexts) {
				//遍历下一步的所有可能
				if (next == target)
					//解锁
					return ++step;
				if (deadendsSet.count(next) == 0 && visited.count(next) == 0) {
					//既不会锁死，也没有被访问过
					visited.insert(next);
					buffer.push(next);		//入队
				}
			}
		}
		step++;
	}
	return -1;
}
