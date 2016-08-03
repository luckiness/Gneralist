#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
//用枚举列举出广义表中每个节点可能出现的类型
enum Type
{
	HEAD,//头结点的类型
	VALUE,//值节点的类型
	SUB//子表类型
};
//定义广义表的节点的结构体类型
struct GeneralizedNode
{
	Type _type;//类型
	GeneralizedNode* _next;//指向同层下一个节点
	//一个节点要么是值要么是子表，故用联合
	union
	{
	char _value;
	GeneralizedNode* _sublink;//指向子表的指针
	};

	//节点的构造函数的实现
	GeneralizedNode(Type type=HEAD,char value=0)
		:_type(type)
		,_next(NULL)
	{
		if(_type==VALUE)
		{
			_value=value;
		}
		else if(_type==SUB)
		{
			_sublink=NULL;
		}
	}
};

class GeneraList
{
public:
	//无参的构造函数
	GeneraList()
		:_head(NULL)
	{}
	//有参的构造函数
	GeneraList(const char* str)
		:_head(NULL)
	{
	_head=_CreateGeneraList(str);
	}
	
	//析构函数
	~GeneraList()
	{
	 _Destory(_head);
	}

public:
	void Print()//打印广义表
	{
	_Print(_head);
	cout<<endl;
	}
	size_t Depth()//求广义表的深度
	{
	return _Depth(_head);
	}
	size_t Size()//求广义表的大小
	{
	  return _Size(_head);
	}

protected:
	
	GeneralizedNode* _CreateGeneraList(const char*& str);//创建广义表
	void _Destory(GeneralizedNode*head);
	bool _Isvalue(const char ch);//判断值节点是否是合法类型
	size_t _Size(GeneralizedNode* head);//
	size_t _Depth(GeneralizedNode*head);//
	void _Print(GeneralizedNode* head);
protected:
  GeneralizedNode* _head;//用来存放广义表头节点的地址

};

//创建广义表
 GeneralizedNode*  GeneraList::_CreateGeneraList(const char*& str)//防止退出循环后又返回到刚开始的位置重新构建
{
	assert(str&&*str=='(');
	str++;//后移广义表，相当于跳过"("
	GeneralizedNode *head=new GeneralizedNode(HEAD);
	GeneralizedNode *cur=head;
	while(*str!='\0')
	{
		//若遇到值
		if(_Isvalue(*str))
		{
	     cur->_next=new GeneralizedNode(VALUE,*str);
		 cur=cur->_next;
		 str++;
		}
		//若遇到子表
		else if(*str=='(')
		{
		cur->_next=new GeneralizedNode(SUB);
		cur=cur->_next;
		cur->_sublink =_CreateGeneraList(str);
		}
		//一个广义表的结束
		else if(*str==')')
		{
		str++;
		return head;
		}
		//空格等其他字符跳过
		else
			str++;
	}
	assert(false);
	return head;
}

//判断当前的值是否是广义表的有效值
bool GeneraList::_Isvalue(const char ch)
{
	if((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
		return true;
	else
		return false;
}


//销毁广义表
void GeneraList::_Destory(GeneralizedNode*head)
{
	GeneralizedNode* cur=head;
	while(cur!=NULL)
	{
		GeneralizedNode* del=cur;
		cur=cur->_next;
		//遇到子表则递归销毁
		if(del->_type ==SUB)
		{
	    _Destory(del->_sublink );
		}
		delete del;
		head=NULL;
	}
}
//求广义表的大小
size_t GeneraList::_Size(GeneralizedNode* head)
{
	GeneralizedNode* cur=head;
	size_t size=0;
	while(cur!=NULL)
	{
		if(cur->_type ==VALUE)
		{
		++size;
		}
		else if(cur->_type ==SUB)
		{
	     size+=_Size(cur->_sublink );//遇到子表进行递归
		}
		cur=cur->_next ;
	}
	return size;
}
//求广义表的深度
size_t GeneraList::_Depth(GeneralizedNode*head)
{
	size_t depth=1;
	GeneralizedNode* cur=head;
	while(cur!=NULL)
	{
	if(cur->_type ==SUB)
	{
		 size_t sublinkdepth= _Depth(cur->_sublink );
		 if(depth<sublinkdepth+1)
		 {
		 depth=sublinkdepth+1;
		 }
	 }
	cur=cur->_next;
   }
	return depth;
}
//打印广义表
void GeneraList::_Print(GeneralizedNode* head)
{
	GeneralizedNode* cur=head;
	while(cur!=NULL)
	{

		if(cur->_type ==HEAD)
		{
		cout<<"(";
		}

		else if(cur->_type ==VALUE)
		{
			 cout<<cur->_value;
			 if(cur->_next !=NULL)
			 {
			 cout<<",";
			 }
		}

		else if(cur->_type ==SUB)
		{
			cout<<"(";
			_Print(cur->_sublink );
			if(cur->_next!=NULL )
			{
			cout<<",";
			}
		}
		cur=cur->_next ;
	}
	cout<<")";
}
void test()
{
	GeneraList g1=("(A,B,(C,(G)),D)");
	g1.Print ();
	cout<<"g1 Depth is:"<<g1.Depth ()<<endl;
	cout<<"g1 Size is:"<<g1.Size ()<<endl;
}

int main()
{
	test();
	getchar();
	return 0;
}