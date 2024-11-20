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
	//�ݹ�ǰ�����
	void preOrder()
	{
		cout << "�ݹ�ǰ�����:";
		pre_Order(root_);
		cout << endl;
	}
	//�ݹ��������
	void inOrder()
	{
		cout << "�ݹ�ǰ�����:";
		in_Order(root_);
		cout << endl;
	}
	//�ݹ�������
	void postOrder()
	{
		cout << "�ݹ�������:";
		post_Order(root_);
		cout << endl;
	}
	//���������
	int high()
	{
		return high(root_);
	}
	//�ݹ�������
	void levelOrder()
	{
		cout << "�ݹ�������:";
		int h = high();
		for (int i = 0; i < h; ++i)
		{
			level_Order(root_, i);
		}
		cout << endl;
	}
	//���������
	int width()
	{
		return width(root_);
	}
	//ͳ��
	void countNode()
	{
		int degree0 = 0, degree1 = 0, degree2 = 0;
		count_Node(root_, degree0, degree1, degree2);
		cout << "��Ϊ0�Ľڵ���:" << degree0 << endl;
		cout << "��Ϊ1�Ľڵ���:" << degree1 << endl;
		cout << "��Ϊ2�Ľڵ���:" << degree2 << endl;
	}
	//����������(ǰ�������
	void build(char pre[], int i, int j, char in[], int m, int n)
	{
		root_ = _build(pre, i, j, in, m, n);
	}
	//�������Ĺ���
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
	//�ݹ�ǰ�������ʵ��
	void pre_Order(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";
			pre_Order(node->left_);
			pre_Order(node->right_);
		}
	}
	//�ݹ����������ʵ��
	void in_Order(Node* node)
	{
		if (node != nullptr)
		{
			in_Order(node->left_);
			cout << node->data_<<" ";
			in_Order(node->right_);
		}
	}
	//�ݹ���������ʵ��
	void post_Order(Node* node)
	{
		if (node != nullptr)
		{
			post_Order(node->left_);
			post_Order(node->right_);
			cout << node->data_ << " ";
		}
	}
	//�ݹ������������
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
	//�ݹ���������ʵ��
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
	//�������Ŀ��
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
	//ͳ�Ƶĵݹ�ʵ��
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
	//�����������ĵݹ�ʵ��
	void _build(char pre[], int i, int j, char in[], int m, int n)
	{
		if (i >= j || m >= n)
		{
			return nullptr;
		}
		//������ǰ�����ĸ��ڵ�
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

	cout << "��1�������ԣ���0ֹͣ����" << endl;
	cout << "2�����������ǰ�����" << endl;
	cout << "3������������������" << endl;
	cout << "4����������ĺ������" << endl;
	cout << "5����������Ĳ������" << endl;
	cout << "6��������������" << endl;
	cout << "7����������Ŀ��" << endl;
	cout << "8�����������ͳ�ƶȽڵ�ĸ���" << endl;

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