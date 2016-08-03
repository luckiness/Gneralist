#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
//��ö���оٳ��������ÿ���ڵ���ܳ��ֵ�����
enum Type
{
	HEAD,//ͷ��������
	VALUE,//ֵ�ڵ������
	SUB//�ӱ�����
};
//��������Ľڵ�Ľṹ������
struct GeneralizedNode
{
	Type _type;//����
	GeneralizedNode* _next;//ָ��ͬ����һ���ڵ�
	//һ���ڵ�Ҫô��ֵҪô���ӱ���������
	union
	{
	char _value;
	GeneralizedNode* _sublink;//ָ���ӱ��ָ��
	};

	//�ڵ�Ĺ��캯����ʵ��
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
	//�޲εĹ��캯��
	GeneraList()
		:_head(NULL)
	{}
	//�вεĹ��캯��
	GeneraList(const char* str)
		:_head(NULL)
	{
	_head=_CreateGeneraList(str);
	}
	
	//��������
	~GeneraList()
	{
	 _Destory(_head);
	}

public:
	void Print()//��ӡ�����
	{
	_Print(_head);
	cout<<endl;
	}
	size_t Depth()//����������
	{
	return _Depth(_head);
	}
	size_t Size()//������Ĵ�С
	{
	  return _Size(_head);
	}

protected:
	
	GeneralizedNode* _CreateGeneraList(const char*& str);//���������
	void _Destory(GeneralizedNode*head);
	bool _Isvalue(const char ch);//�ж�ֵ�ڵ��Ƿ��ǺϷ�����
	size_t _Size(GeneralizedNode* head);//
	size_t _Depth(GeneralizedNode*head);//
	void _Print(GeneralizedNode* head);
protected:
  GeneralizedNode* _head;//������Ź����ͷ�ڵ�ĵ�ַ

};

//���������
 GeneralizedNode*  GeneraList::_CreateGeneraList(const char*& str)//��ֹ�˳�ѭ�����ַ��ص��տ�ʼ��λ�����¹���
{
	assert(str&&*str=='(');
	str++;//���ƹ�����൱������"("
	GeneralizedNode *head=new GeneralizedNode(HEAD);
	GeneralizedNode *cur=head;
	while(*str!='\0')
	{
		//������ֵ
		if(_Isvalue(*str))
		{
	     cur->_next=new GeneralizedNode(VALUE,*str);
		 cur=cur->_next;
		 str++;
		}
		//�������ӱ�
		else if(*str=='(')
		{
		cur->_next=new GeneralizedNode(SUB);
		cur=cur->_next;
		cur->_sublink =_CreateGeneraList(str);
		}
		//һ�������Ľ���
		else if(*str==')')
		{
		str++;
		return head;
		}
		//�ո�������ַ�����
		else
			str++;
	}
	assert(false);
	return head;
}

//�жϵ�ǰ��ֵ�Ƿ��ǹ�������Чֵ
bool GeneraList::_Isvalue(const char ch)
{
	if((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
		return true;
	else
		return false;
}


//���ٹ����
void GeneraList::_Destory(GeneralizedNode*head)
{
	GeneralizedNode* cur=head;
	while(cur!=NULL)
	{
		GeneralizedNode* del=cur;
		cur=cur->_next;
		//�����ӱ���ݹ�����
		if(del->_type ==SUB)
		{
	    _Destory(del->_sublink );
		}
		delete del;
		head=NULL;
	}
}
//������Ĵ�С
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
	     size+=_Size(cur->_sublink );//�����ӱ���еݹ�
		}
		cur=cur->_next ;
	}
	return size;
}
//����������
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
//��ӡ�����
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