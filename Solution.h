#pragma once

#include <iostream>
#include <cassert>

#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

//Definition for a graph node.
class Node {
public:
	int val;
	vector<Node*> neighbors;

	Node() {}

	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};



class Solution {

private:

public:
	/*
	 * No.150 逆波兰表达式求值
	 * date: 2019/5/16 
	 */
	int evalRPN(vector<string>& tokens);

	/*
	* No.71 简化路径
	* date: 2019/5/17
	*/
	string simplifyPath(string path);

	/*
	* No.94 中序遍历二叉树（使用非递归算法实现）
	* date: 2019/5/20
	*/
	vector<int> inorderTraversal(TreeNode* root);

	/*
	* No.231 Power of Two
	* date: 2019/5/20
	*/
	bool isPowerOfTwo(int n);

	/*
	* No.96 Unique Binary Search Trees
	* desc: Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?
	* date: 2019/5/20
	*/
	int numTrees(int n);

	/*
	* No.104 Maximum Depth of Binary Tree
	* desc: Given a binary tree, find its maximum depth.
	* date: 2019/5/20
	*/
	/*
	* No.102 & No.107 Binary Tree Level Order Traversal
	* desc: Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
	* date: 2019/5/21
	*/
	int maxDepth(TreeNode* root);

	/*
	* No.105 Construct Binary Tree from Preorder and Inorder Traversal
	* desc: Given preorder and inorder traversal of a tree, construct the binary tree.
	* date: 2019/5/21
	*/
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);

	/*
	* No.997 Find the Town Judge
	* desc: In a town, there are N people labelled from 1 to N.  There is a rumor that one of these people is secretly the town judge.
	*
	* If the town judge exists, then:
	*
	*	The town judge trusts nobody.
	*	Everybody (except for the town judge) trusts the town judge.
	*	There is exactly one person that satisfies properties 1 and 2.
	* You are given trust, an array of pairs trust[i] = [a, b] representing that the person labelled a trusts the person labelled b.
	*
	* If the town judge exists and can be identified, return the label of the town judge.  Otherwise, return -1.
	* date: 2019/5/22
	*/
	int findJudge(int N, vector<vector<int>>& trust);

	/*
	* No.133 Clone Graph
	* desc: Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph. Each node in the graph contains a val (int) and a list (List[Node]) of its neighbors.
	* date: 2019/5/23
	*/
	Node* cloneGraph(Node* node);

	/*
	* No.133 Course Schedule
	* desc: here are a total of n courses you have to take, labeled from 0 to n-1.
	*
	* Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
	*
	* Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
	* date: 2019/5/23
	*/
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites);
};


/*
* No.155 最小栈
* date: 2019/5/17
*/
class MinStack {
private:
	struct Node {
		int data;
		Node* next;
		Node(int data) {
			this->data = data;
			next = NULL;
		}
	};
	int size;
	Node* topNode;
	stack<int> min;

public:
	/** initialize your data structure here. */
	MinStack() {
		size = 0;
		topNode = NULL;
	}

	void push(int x) {
		Node* node = new Node(x);
		node->next = topNode;
		topNode = node;
		size++;
		//条件的前后顺序不能换，如果栈为空，则top()会越界
		if (min.empty() || min.top() >= node->data) {
			min.push(node->data);
		}
	}

	void pop() {

		assert(size > 0);
		Node* tmp = topNode;
		topNode = topNode->next;
		size--;
		if (tmp->data == min.top())
			min.pop();
		delete tmp;
	}

	int top() {
		return topNode->data;
	}

	int getMin() {
		return min.top();
	}
};

