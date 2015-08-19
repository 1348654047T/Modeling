
#include "vnodeselector.h"
VNodeSelector* VNodeSelector::m_pNodeSelector=NULL;
VNodeSelector::~VNodeSelector()
{

	m_pNodeSelector->Clear();
}
VNodeSelector* VNodeSelector::GetInstance()  //��ȡʵ��
{
  if(m_pNodeSelector==NULL)
	  m_pNodeSelector=new VNodeSelector;
  return m_pNodeSelector;

}
void VNodeSelector::DestoryInstance()//����ʵ��
{

	if(m_pNodeSelector)
		delete m_pNodeSelector;
}
void VNodeSelector::Clear()//��ս��ѡ����
{
	int num=m_vSelList.size();
	for(int i=0;i<num;i++)
	{
		m_vSelList[i]->UnSelect();
	}
	m_vSelList.clear();
}
int VNodeSelector::IndexOf(VNode* pNode)  //���ؽ���ڽ��ѡ�����е�����
{
	int numNodes = GetNumSelNodes();											//ѡ�����н��ĸ���
	for (int i = 0; i < numNodes; i++)											//����ѡ�����е�ÿ�����
	{
		if(m_vSelList[i] == pNode)												//�����������ָ����ͬ
			return i;															//��������
	}
	return -1;																	//�����ڸ�ָ�뷵��-1
}


VNode* VNodeSelector::GetSelNode(int i) //��ȡ��i�����ָ��
{
	if (i >= 0 && i < m_vSelList.size())
	{
		return m_vSelList[i];
	}
	return NULL;
}

void VNodeSelector::GetSelNodeTab(VNodeVector& vNodeList) //ȡ�ý���б������еĽ��ָ��
{
	vNodeList.clear();															//����ý��ָ������
	int numSel = m_vSelList.size();												//���ѡ�����н��ָ��ĸ���
	for (int i = 0; i < numSel; i++)											//����ѡ���������н��ָ��
	{
		vNodeList.push_back(m_vSelList[i]);										//���ý�������ָ������
	}
}


void VNodeSelector::AppendSelNode(VNode* pNode, bool bClearSel /* = true */)//���һ�����ָ��
{
	if(bClearSel)																//�����Ҫ������ѡ������ԭ�еĽ��ָ��
	{
		Clear();																//������ѡ����������
		m_vSelList.push_back(pNode);											//����ý��ָ��
		pNode->SetSelect();														//������ѡ��״̬
	}
	else
	{
		if(IndexOf(pNode) == -1)												//������ѡ������û�д˽��ָ��
		{
			m_vSelList.push_back(pNode);										//�򽫽��ָ������б���
			pNode->SetSelect();													//������ѡ��״̬
		}
	}
}

void VNodeSelector::AppendSelNodeTab(VNodeVector& vSelList, bool bClearSel /* = true */)//ָ������б��е����н�����ѡ����
{
	int i, numSel = vSelList.size();											//Ҫ������ĸ���
	if(bClearSel)																//�����Ҫ������ѡ����������
	{
		Clear();																//����������ѡ����������
		for (i = 0; i < numSel; i++)
		{
			vSelList[i]->SetSelect();											//���ý���ѡ��״̬
			m_vSelList.push_back(vSelList[i]);									//���ý����������ѡ����
		}
	}
	else
	{
		int index = 0;
		for (i = 0; i < numSel; i++)
		{
			index = IndexOf(vSelList[i]);										//���ȼ��ý���Ƿ��Ѵ����ڽ��ѡ������
			if(index != -1)														//����ý�㲻�����ڽ��ѡ����
			{
				vSelList[i]->SetSelect();										//���ý���ѡ��״̬
				m_vSelList.push_back(vSelList[i]);								//���ý����������ѡ����
			}
		}
	}
}

bool VNodeSelector::DeleteSelNode(VNode* pNode)//ɾ��ָ���Ľ��ָ��
{
	int index = IndexOf(pNode);													//�ý����ѡ�����е�����
	if(index != -1)																//���ѡ�����д��ڸý��
	{
		m_vSelList[index]->UnSelect();											//��ȡ���ý���ѡ��״̬
		m_vSelList.erase(m_vSelList.begin() + index);							//Ȼ���ѡ�������Ƴ��ý��ָ��
		return true;															//��ѡ�������Ƴ����ɹ�
	}
	return false;																//ѡ�����в����ڸý��
}

