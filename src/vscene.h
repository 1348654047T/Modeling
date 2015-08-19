#ifndef _VSCENE_H_
#define _VSCENE_H_

/**********************************************************************
DESCRIPTION:�����ඨ�� ����VNode�ڵ�  

CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************/

#include "vnode.h"
#include "vnodeselector.h"
#include <fstream>


class VScene
{
private:
	VScene();														//˽���Խ�ֹ�����ⴴ��ʵ��
public:
	~VScene();

private:
	static VScene* m_pScence;										//����ʵ��ָ��(Ψһ)
	VNode* m_pRootNode;												//���������
	VNodeSelector* m_pNodeSel;										//���ѡ����ָ��
	
public:
	static VScene* GetInstance();									//��ȡ����Ψһ��ʵ��
	static void DestroyInstance();									//�ͷų���ʵ��
	
	//�����ط���
	VNode* CreateNode();											//����һ���½��
	VNode* CreateNode(VMesh* pMesh);							//Ϊ���崴��һ�����
	VNode* CreateNode(VNode* attachNode);							//����һ���½��ҵ�attachNode��
	VNode* CreateNode(VMesh* pMesh,VNode* attachNode);			//Ϊ���崴��һ�����ҵ�attachNode��
	void ReadAllNodes(VNodeVector& vNodesVec);						//��ȡ���������н�㲢��ָ������б�
	void ReadSubTree(VNode* pNode,VNodeVector& vNodeVec);			//��ȡһ�����������н��
	void DeleteNode(VNode* pNode, bool dSubTree = false);			//ɾ��ָ�����
	void DeleteAllNodes();											//ɾ�����н��
	void ClearScence();												//��ճ���

	//ѡ��ڵ���ط���
	int GetNumSel();												//���ص�ǰѡ�����б��н��ĸ���
	VNode* GetSelNode(int i);										//���ص�ǰѡ��ĵ�i�����
	void SelectNode(VNode* pNode, bool bClearSel = true);			//ѡ��ǰ���
	void DeleteSelNodes();											//ɾ��ѡ�����
	////�������ط���
	//void RenderCamera(VNode* camNode);								//����ָ�������
	//VCamNode* GetCurCamera();										//��õ�ǰ����ʹ�õ�������ڵ�ָ��
	//void JudgeScene();									//�����ӵ�


	//������������Ϣ��ط���
	int GetNumVerts();												//�õ����������е����嶥������
	int GetNumFaces();												//�õ������������������Ƭ����
	void GetNumVerts(VNode* pNode, int& numVerts);					//�õ���pNodeΪ������������������
	void GetNumFaces(VNode* pNode, int& numFaces);					//�õ���pNodeΪ������������Ƭ����
	void GetNumVertsFaces(int& numVerts, int& numFaces);			//�õ���������������Ķ������Ƭ����
	void GetNumVertsFaces(VNode* pNode, int& numVerts, int& numFaces);//�õ���pNodeΪ����������������Ƭ����

	//��Ⱦ����
	void Render();							//��Ⱦ����
	void RenderNode(VNode* pNode);			//��Ⱦָ����㼰�亢�ӽ��

	//�������
	void Hit(int x, int y);											//�������
public:
	inline VNode* GetRootNode(){ return m_pRootNode; }				//���س��������
	inline VNodeSelector* GetNodeSelector(){ return m_pNodeSel; }	//���ؽ��ѡ����ָ��
	static VPoint3 GetViewPortPt(VPoint3& p0);								//����GL�����ӿ��е�λ��
	static VPoint3 GetGLPortPt(VPoint3& p0);									//�����ӿ��еĵ���GLλ��
	static VPoint3 GetTransPt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt);//ͨ������ƶ��������� ���������ĵ�õ������ƶ�ƽ������
	static VPoint3 GetRotatePt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt);//ͨ������ƶ��������� ���������ĵ�õ�������ת����
	static VPoint3 GetScalePt(VPoint3 p_start,VPoint3 p_end);//ͨ������ƶ���������õ�������������
};




#endif