// LeetCode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Solution.h"


int main()
{
    
	Solution soluton;

	////cout << soluton.simplifyPath("/a//b////c/d//././/..") << endl;

	//int arrPreorder[] = { 3, 9, 20, 15, 7 };
	//int arrInorder[] = { 9, 3, 15, 20, 7 };
	//
	//vector<int> preorder(arrPreorder, arrPreorder + sizeof(arrPreorder) / sizeof(int));
	//vector<int> inorder(arrInorder, arrInorder + sizeof(arrInorder) / sizeof(int));

	//TreeNode* tree = soluton.buildTree(preorder, inorder);

	//soluton.maxDepth(tree);

	//vector<vector<int>> trust;
	//int testTrust[] = { 1, 2 };
	//vector<int> v(testTrust, testTrust + sizeof(testTrust) / sizeof(int));
	//
	//trust.push_back(v);
	//cout << soluton.findJudge(2, trust) << endl;

	vector<vector<int>> path;
	vector<int> perPath;

	perPath.push_back(0);
	perPath.push_back(1);
	path.push_back(perPath);

	soluton.canFinish(2, path);

	system("pause");

	return 0;
}

