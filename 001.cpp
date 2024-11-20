#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
using namespace std;

template<typename T,typename Comp=less<T>>
class BiTree
{
public:
	BiTree()
		:root_(nullptr)
	{}
	~BiTree()
	{}
	//递归前序遍历
	void preOrder()
	{
		cout << "递归前序遍历:";
		pre_Order(root_);
		cout << endl;
	}
	//递归中序遍历
	void inOrder()
	{
		cout << "递归前序遍历:";
		in_Order(root_);
		cout << endl;
	}
	//递归后序遍历
	void postOrder()
	{
		cout << "递归后序遍历:";
		post_Order(root_);
		cout << endl;
	}
	//二叉树深度
	int high()
	{
		return high(root_);
	}
	//递归层序遍历
	void levelOrder()
	{
		cout << "递归层序遍历:";
		int h = high();
		for (int i = 0; i < h; ++i)
		{
			level_Order(root_, i);
		}
		cout << endl;
	}
	//二叉树宽度
	int width()
	{
		return width(root_);
	}
	//统计
	void countNode()
	{
		int degree0 = 0, degree1 = 0, degree2 = 0;
		count_Node(root_, degree0, degree1, degree2);
		cout << "度为0的节点数:" << degree0 << endl;
		cout << "度为1的节点数:" << degree1 << endl;
		cout << "度为2的节点数:" << degree2 << endl;
	}
	//构建二叉树(前序和中序）
	void build(char pre[], int i, int j, char in[], int m, int n)
	{
		root_ = _build(pre, i, j, in, m, n);
	}
	//二叉树的构造
	void Creat()
	{
		root_= new Node('A');
		root_->left_ = new Node('B');
		root_->right_ = new Node('C');
		root_->left_->left_ = new Node('D');
		root_->left_->right_ = new Node('E');
		root_->right_->left_ = new Node('F');
		root_->right_->right_ = new Node('G');
	}
private:
	struct Node
	{
		Node(T data = T())
			:data_ (data)
			,left_(nullptr)
			,right_(nullptr)
		{}
		Node* left_;
		Node* right_;
		T data_;
	};
	//递归前序遍历的实现
	void pre_Order(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";
			pre_Order(node->left_);
			pre_Order(node->right_);
		}
	}
	//递归中序遍历的实现
	void in_Order(Node* node)
	{
		if (node != nullptr)
		{
			in_Order(node->left_);
			cout << node->data_<<" ";
			in_Order(node->right_);
		}
	}
	//递归后序遍历的实现
	void post_Order(Node* node)
	{
		if (node != nullptr)
		{
			post_Order(node->left_);
			post_Order(node->right_);
			cout << node->data_ << " ";
		}
	}
	//递归求二叉树层数
	int high(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = high(node->left_);
		int right = high(node->right_);
		return left > right ? left + 1: right + 1;
	}
	//递归层序遍历的实现
	void level_Order(Node* node,int i)
	{
		if (node == nullptr)
		{
			return;
		}
		if (i == 0)
		{
			cout << node->data_<<" ";
			return;
		}
		level_Order(node->left_, i - 1);
		level_Order(node->right_, i - 1);
	}
	//二叉树的宽度
	int width(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int maxWidth = 0;
		queue<Node*> q;
		q.push(node);

		while (!q.empty())
		{
			int count = q.size();
			maxWidth = max(maxWidth, count);
			for (int i = 0; i < count; i++)
			{
				Node* tmp = q.front();
				q.pop();
				if (tmp->left_)
				{
					q.push(tmp->left_);
				}
				if (tmp->right_)
				{
					q.push(tmp->right_);
				}

			}
		}
		return maxWidth;
	}
	//统计的递归实现
	void count_Node(Node* node, int& degree0, int& degree1, int& degree2)
	{
		if (node == nullptr)
		{
			return;
		}
		int degree = (node->left_ != nullptr) + (node->right_ != nullptr);
		if (degree == 0)
		{
			degree0++;
		}
		else if (degree == 1)
		{
			degree1++;
		}
		else if (degree == 2)
		{
			degree2++;
		}
		count_Node(node->left_, degree0, degree1, degree2);
		count_Node(node->right_, degree0, degree1, degree2);
	}
	//构建二叉树的递归实现
	void _build(char pre[], int i, int j, char in[], int m, int n)
	{
		if (i >= j || m >= n)
		{
			return nullptr;
		}
		//创建当前子树的根节点
		Node* node = new Node(pre[i]);
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k])
			{
				node->left_ = _build(pre, i + 1, i + (k - m), in, m, k - 1);
				node->right_ = _build(pre, i + (k - m) + 1, j, in, k + 1, n);
				return node;
			}
		}
		return node;
	}
	Node* root_;
	Comp comp_;
};

int main()
{
	BiTree<char> bt;
	bt.Creat();

	cout << "按1继续测试，按0停止测试" << endl;
	cout << "2输出二叉树的前序遍历" << endl;
	cout << "3输出二叉树的中序遍历" << endl;
	cout << "4输出二叉树的后序遍历" << endl;
	cout << "5输出二叉树的层序遍历" << endl;
	cout << "6输出二叉树的深度" << endl;
	cout << "7输出二叉树的宽度" << endl;
	cout << "8输出二查树各统计度节点的个数" << endl;

	while (1)
	{
		int flag;
		cin >> flag;
		if (flag == 0)
		{
			break;
		}
		else
		{
			int num;
			cin >> num;
			switch (num)
			{
			case 2:
				bt.preOrder();
				break;
			case 3:
				bt.inOrder();
				break;
			case 4:
				bt.postOrder();
				break;
			case 5:
				bt.levelOrder();
				break;
			case 6:
				cout<<bt.high()<<endl;
				break;
			case 7:
				cout<<bt.width()<<endl;
				break;
			case 8:
				bt.countNode();
				break;
			}
		}
	}

}