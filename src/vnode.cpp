#include "vnode.h"

VNode* VNode::m_rootnode = new VNode;								//��ʼ�����������
VNode::VNode()//���캯��
{
	strcpy(m_NodeName,"VNode");
	m_parentnode=NULL;											//��ʼ�����Ϊ�������
	m_displayFlag=true; //true���ýڵ�Ϊ�ɼ�
	m_vChildList.clear();
	m_pMesh=NULL;
	m_matCtrler = new VControl;
}

VNode::~VNode()//��������
{
	m_vChildList.clear();
	if (m_matCtrler)
		delete m_matCtrler;
	if (m_pMesh)
		delete m_pMesh;
}


char* VNode::GetName()  //��ýڵ�����
{
	return m_NodeName;
}
void VNode::SetNodeName(char *s)  //���ýڵ�����
{

	strcpy(m_NodeName,s);
}
int VNode::IsRootNode()//�ж��Ƿ��Ǹ��ڵ�
{
	return(this==m_rootnode);

}

VMatrix3 VNode::GetNodeTM()  //��ýڵ����
{
	if(this==m_rootnode) return VMatrix3();
	VMatrix3 mat;
	mat = m_matCtrler->GetTM();
	return m_parentnode->GetNodeTM()*mat;

}

// VMatrix3 VNode::GetNodeTMPtr(VTimeValue t)  //��ýڵ����
// {
// 	return m_matCtrler->GetTM(t);
// }

void VNode::SetNodeTM(VMatrix3& tm)
{
	if(this == m_rootnode)														//����ý�㼴Ϊ�����								
	{
			m_matCtrler->SetTM(VMatrix3());
	}
	else m_matCtrler->SetTM(tm);
}

void VNode::SetNodeTM(VMatrix3* tm)
{
	if(this == m_rootnode)														//����ý�㼴Ϊ�����								
	{
		m_matCtrler->SetTM(VMatrix3());
	}
	else m_matCtrler->SetTM(tm);

	
}

void VNode::Move(VVector3& move)//�ƶ�
{

	if(this!=m_rootnode)
		m_matCtrler->Move(-move);




}
void VNode::Rotate(VAxisAngle& val)//��ת
{
	if(this!=m_rootnode)
		m_matCtrler->Rotate(val);

	

}
void VNode::Scale(VVector3& scale)//����
{
	if(this!=m_rootnode)
		m_matCtrler->Scale(scale);

	
}


VMatrix3 VNode::GetParentTM()//��ø��ڵ�ľ���
{

	if(this==m_rootnode)
		return this->GetNodeTM();
	else return m_parentnode->GetNodeTM();
}
VNode* VNode::GetChildNode(int i)//��õ�i���ӽڵ�
{
	if(m_vChildList.size()<0||i<0)
		return NULL;
	return m_vChildList[i];

}
VNode* VNode::GetRootNode()
{
	if (m_rootnode == NULL)
	{
		m_rootnode = new VNode;
	}
	return m_rootnode;
}

void VNode::DestroyRootNode()
{
	if (m_rootnode)
		delete m_rootnode;
	m_rootnode = NULL;
}

VNodeVector& VNode::GetChildList()	//��ú��ӽڵ������� 
{
	return m_vChildList;
}

void VNode::Delete()//ɾ���ڵ�
{
	VNodeVector nodelist;
	GetSubTree(this,nodelist);
	int num=nodelist.size();
	for(int i=0;i<num;i++)
	{
		delete nodelist[i]; //ֱ��ɾ���ڵ㣿����
	}
	nodelist.clear();
	m_vChildList.clear();
}
void VNode::DeleteThis(bool subtree)  //ɾ���ڵ㣨������
{

	if(this==m_rootnode) //����Ǹ��ڵ㣬����ɾ��
		return ;
	this->Detach();//�����븸�ӹ�ϵ
	if(subtree)  //ɾ����������
	{

		Delete();
		

	}
	else
	{
		int i,numchild=m_vChildList.size();
		for(i=0;i<numchild;i++)
		{
			m_parentnode->AttachChild(m_vChildList[i]);

		}
		delete this;
		


	}

}
void VNode::GetSubTree(VNode* node,VNodeVector& nodevector) //��ȡnode�ڵ��������������nodevector��

{  
	nodevector.push_back(node);
	int num=node->m_vChildList.size();
	for(int i=0;i<num;i++)
	{
		GetSubTree(node->GetChildNode(i),nodevector);
	}
}
int VNode::GetChildIndex(VNode* pchild)//�����ӽڵ�pchild���ӽڵ������е�����
{
	int numChild=m_vChildList.size();
	for(int i=0;i<numChild;i++)
	{
		if(m_vChildList[i]==pchild)
			return i;

	}
	return -1;

}
void VNode::RemoveChild(VNode* pchild) //��pchild�ĸ��ӹ�ϵȥ��
{

	int index=GetChildIndex(pchild);
	if(index==-1)
		return;
	m_vChildList.erase(m_vChildList.begin()+index);//���ӽڵ��б����Ƴ�
	pchild->m_parentnode=NULL;//�ÿո��ڵ�
}

void VNode::Detach()//���븸�ӹ�ϵ
{
	if(m_parentnode)
		RemoveChild(this);
	
}

void VNode::AttachChild(VNode* node)//����ӽڵ�,nodeΪҪ��ӵ��ӽڵ�
{
	node->Detach(); 
	m_vChildList.push_back(node);//node��ӵ��ӽڵ��б�
	node->m_parentnode=this; //����node�ĸ��ڵ�
	

}

void VNode::Display(bool flag)
{
	return m_pMesh->Display(GetNodeTM(),flag);
}

VMesh* VNode::GetMesh()
{
	return m_pMesh;													//���ؽ�����������ָ��
}

VMesh* VNode::SetMesh(VMesh* mesh)
{
	VMesh* tempMesh = m_pMesh;
	m_pMesh = mesh;												
	return tempMesh;
}



