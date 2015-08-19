
#ifndef _VNODE_H_
#define _VNODE_H_
/**********************************************************************
DESCRIPTION:�����ؼ��ṹ��VNode��һ��������ṹ����������������������̬����Ϣ  

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
#include "vcontrol.h"
#include "vmesh.h"

class VNode;
typedef vector<VNode*> VNodeVector;//�����vnode�͵�vector����ӽڵ�
typedef VNode VCamNode;
class VNode
{
public:
	VNode();
	~VNode();
public:
	//NODE Naming
	char * GetName();//��ýڵ�����
	void SetNodeName(char *s);//���ýڵ�����Ϊs

	//���ӽڵ���ز���
	VNode* GetParentNode(){return m_parentnode;} //���ظ��ڵ� 
	static VNode* GetRootNode();
	static void DestroyRootNode();
	VMatrix3 GetParentTM();//��ø��ڵ�ľ���
	VNodeVector& GetChildList();	//��ú��ӽڵ������� 
	VNode* GetChildNode(int i);//��ȡ�ӽڵ�
	void AttachChild(VNode* node);//�����ӽڵ�
	void Detach();//���ýڵ����丸�ڵ����
	int GetChildIndex(VNode* pchild);//����ӽڵ������
	void RemoveChild(VNode* pchild);//�Ƴ��ӽڵ�
	void GetSubTree(VNode* node,VNodeVector& nodevector);//���node�ڵ���������洢��nodevector��
	int GetNumChild(){return m_vChildList.size();}

	void Delete();//ɾ���ڵ�
	void DeleteThis(bool subtree=false);//ɾ���ڵ㣬���subtreeΪtree��������һ��ɾ��������ֻɾ���ýڵ�
	int IsRootNode();//�ж��Ƿ��Ǹ��ڵ�
	//������
	void SetTMController(VControl* m3cont){m_matCtrler = m3cont;}//���ÿ�����
	VControl* GetTMController(){
		if (!m_matCtrler)
			m_matCtrler = new VControl;
		return m_matCtrler;
	}//��ȡ������

	//Transformation Matrices
	VMatrix3 GetNodeTM();//��ýڵ����
	void SetNodeTM(VMatrix3& tm);//���ýڵ����
	void SetNodeTM(VMatrix3* tm);//���ýڵ����ָ��

	//����tmAxis�ƶ��ڵ���߼�����
	void Move(VVector3& move);//�ƶ�
	void Rotate(VAxisAngle& val);//��ת
	void Scale(VVector3& scale);//����
	//Display
	void Display(bool flag); //�Ƿ�ѡ�� ѡ����Ⱦ��Χ��
	//object��ط���
	VMesh* GetMesh();											//���ع�������ָ��
	VMesh* SetMesh(VMesh* mesh);								//���ù�������,����ԭ����Objectָ��
public:
	//Node Selection
	void SetSelect() { m_select = true;}//����ѡ��
	bool GetSelect() { return m_select;}//����ѡ��״̬
	void UnSelect(){ m_select=false;}//����ѡ��״̬

	//��ʾ����
	void Hide();//����
	int IsHidden();//�Ƿ�����
	void SetDisplayFlag(bool show){m_displayFlag = show;}
	int GetDisplayFlag(){return m_displayFlag;}
private:
	static VNode* m_rootnode;  //���ڵ�
	VNode* m_parentnode; //���ڵ�
	VNodeVector m_vChildList;//�洢�ӽڵ��vector
	VControl* m_matCtrler;//������
	VMesh* m_pMesh;//�ڵ��¹ҵ�����
	bool m_select;//ѡ������
	bool m_displayFlag; //��ʾ����

private:
	char m_NodeName[256];//��Žڵ�����

};
#endif




