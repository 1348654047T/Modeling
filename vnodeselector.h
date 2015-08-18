
/**********************************************************************
DESCRIPTION: �ڵ�ѡ���� ����ѡ�е�ģ�� 

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
#ifndef _VNODESELECTOR_H_
#define _VNODESELECTOR_H_
#include "vnode.h"
class VNodeSelector
{
private:
	VNodeSelector(){};//���캯��
	~VNodeSelector();
private:
	static VNodeSelector* m_pNodeSelector;//���ѡ����ָ��
	VNodeVector m_vSelList;//��ѡ��Ľ���б�
public:
	static VNodeSelector* GetInstance();//��ȡ���ѡ�������Ψһʵ��
	static void DestoryInstance();//����ʵ��
	void Clear();//���ѡ����������
	int GetNumSelNodes(){return m_vSelList.size();}//���ر�ѡ��Ľ�����Ŀ
	VNode* GetSelNode(int i);//���ص�i�����ָ��
	void GetSelNodeTab(VNodeVector& vNodeList);//ȡ�ý���б������еĽ��ָ��
	int IndexOf(VNode* pNode);											//�鿴ָ������Ƿ��Ѿ���ѡ������
	void AppendSelNode(VNode* pNode, bool bClearSel = true);			//��ָ��������ѡ����
	void AppendSelNodeTab(VNodeVector& vSelList, bool bClearSel);		//��ָ�������е����н�����ѡ����
	bool DeleteSelNode(VNode* pNode);									//ȡ���ý���ѡ��״̬������ѡ�������Ƴ�

};
#endif