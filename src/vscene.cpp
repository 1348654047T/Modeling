//#include "stdafx.h"
#include "vscene.h"
#include <gl/GL.h>
#include <gl/glu.h>
#include "vcamera.h"
VScene* VScene::m_pScence = NULL;

VScene::VScene()
{
	m_pRootNode = VNode::GetRootNode();											//�����ָ��
	m_pNodeSel = VNodeSelector::GetInstance();									//���ѡ����ָ��
}

VScene::~VScene()
{
	DeleteAllNodes();
}

//////////////////////////////////////////

VScene* VScene::GetInstance() //���س���ʵ��
{
	if(!m_pScence)																//�������ʵ����δ����
	{ m_pScence = new VScene; }													//��������ʵ��
	return m_pScence;															//���س���ʵ��ָ��
}

void VScene::DestroyInstance() //�ͷų���ʵ��
{
	if(m_pScence)
		delete m_pScence;
	m_pScence = NULL;
}


VNode* VScene::CreateNode()//����һ���µĽ��
{
	VNode* node= new VNode;													//����һ���½��
	if(node)																	//�����ɹ�
		VNode::GetRootNode()->AttachChild(node);									//Ĭ�������������������
	return node;																//���ؽ��ָ��
}


VNode* VScene::CreateNode(VMesh* pMesh)//����һ���µĳ��������������	
{
	VNode* node = new VNode;													//����һ���½��
	if(node)																	//�����ɹ�
		VNode::GetRootNode()->AttachChild(node);									//Ĭ�������������������
	node->SetMesh(pMesh);													//������ҽӵ��½����
	return node;																//���ؽ��ָ��
}


VNode* VScene::CreateNode(VNode* attachNode)									//����һ���µĳ��������������	
{
	VNode* node = new VNode;													//����һ���½��
	if(node)																	//�����ɹ�
		attachNode->AttachChild(node);
	return node;																//���ؽ��ָ��
}

VNode* VScene::CreateNode(VMesh* pMesh,VNode* attachNode)				//����һ���µĳ��������������	
{
	VNode* node = new VNode;													//����һ���½��
	if(node)																	//�����ɹ�
		attachNode->AttachChild(node);									
	node->SetMesh(pMesh);		
	return node;																//���ؽ��ָ��
}
void VScene::ReadAllNodes(VNodeVector& vNodesVec)//��ȡ�����е����н�㲢����ָ���б�
{
	int numChild = m_pRootNode->GetChildList().size();							//��ȡ�������������
	for (int i = 0; i < numChild; i++)											//���ڸ�����ÿ���ӽ��
	{
		ReadSubTree(m_pRootNode->GetChildNode(i),vNodesVec);					//��ȡÿһ������
	}
}


void VScene::ReadSubTree(VNode* pNode,VNodeVector& vNodeVec)					//��ȡһ������
{
	vNodeVec.push_back(pNode);													//��ǰ������б�
	int numChild = pNode->GetChildList().size();										//�ӽ�����
	for (int i = 0; i < numChild; i++)											//����ÿ���ӽ��
	{
		ReadSubTree(pNode->GetChildNode(i),vNodeVec);							//��ȡ����
	}
}


void VScene::DeleteNode(VNode* pNode, bool dSubTree /* = false */)
{
	pNode->DeleteThis(dSubTree);												//ɾ���ý�㣨dSubTree��־�Ƿ�ɾ����������
}


void VScene::DeleteAllNodes()                                             //ɾ�����������еĽ��
{
	for(int i=0;i<m_pRootNode->GetNumChild();i++)
	{
		m_pRootNode->GetChildNode(i)->Delete();
	}
}
int VScene::GetNumSel()
{
	return m_pNodeSel->GetNumSelNodes();										//����ѡ�����б��н��ĸ���
}


VNode* VScene::GetSelNode(int i)
{
	return m_pNodeSel->GetSelNode(i);											//ѡ�����е�i�����
}


void VScene::SelectNode(VNode* pNode, bool bClearSel /* = true */)//ѡ��ý�㣬����־�Ƿ������ǰ�Ľ��ָ��	
{
	m_pNodeSel->AppendSelNode(pNode, bClearSel);								//ѡ��ý��
}
void VScene::DeleteSelNodes()  //ɾ�����б�ѡ��Ľ��
{
	VNodeVector vNodeList;
	m_pNodeSel->GetSelNodeTab(vNodeList);										//��ȡ���ѡ���������н��ָ��
	m_pNodeSel->Clear();														//��ս��ѡ����
	int numSel = vNodeList.size();												//ԭѡ�����б�ѡ����ĸ���
	for (int i = 0; i < numSel; i++)											//����ÿ����ѡ��Ľ��
	{
		vNodeList[i]->DeleteThis();												//ɾ���ý��
	}
}

void VScene::ClearScence()                                                  //��ճ���
{
	m_pNodeSel->Clear();													//���ѡ����
	DeleteAllNodes();														//ɾ�����г������
	VNode::DestroyRootNode();
	VScene::DestroyInstance();
}


void VScene::Render()                                             //��Ⱦ��������
{
	//��Ⱦ�������������������
	// 	int numChild = m_pRootNode->GetChildList().size();									//�����ĺ��ӽ�����������������㲢�������κ����壬����Ҫ��Ⱦ��
	// 	for (int i = 0; i < numChild; i++)											//���ڸ�����ÿ���ӽ��
	// 	{
	// 		VNode* node = m_pRootNode->GetChildNode(i);
	// 		RenderNode(m_pRootNode->GetChildNode(i),t);								//��Ⱦ������
	// 	}
	VNodeVector nodeVec;
	ReadAllNodes(nodeVec);
	for (int i=0;i<nodeVec.size();i++)
	{
		VNode* node = nodeVec.at(i);
		RenderNode(node);									
	}
}

//////////////////////////////////////////
//������	RenderNode(DNode* pNode)	//
//���ܣ�	��Ⱦָ����㼰�亢�ӽ��	//
//CREATED BY:  [8/9/2015 niewenchao]
//////////////////////////////////////////
void VScene::RenderNode(VNode* pNode)
{
	if(!pNode) return;
	bool exsited = false;
	if (GetNodeSelector()->IndexOf(pNode) >= 0)
		exsited = TRUE;
	pNode->Display(exsited);
}

/*********************************************************************************
  *Function: GetViewPortPt(DPoint3& p0)	 
  *Description����opengl��������ת��Ϊ��Ļ���꣨�ӿ����꣩ 
  *Input:  p0-opengl��������
  *Return: ��Ļ���� 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetViewPortPt(VPoint3& p0)
{
	VPoint3 p1;

	GLint    viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetIntegerv(GL_VIEWPORT, viewport);											//�ӿھ���
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);									//ģ�ͱ任����
	glGetDoublev(GL_PROJECTION_MATRIX, projection);									//ͶӰ����
	GLdouble px, py, pz;
	gluProject(p0.x, p0.y, p0.z, modelview, projection, viewport, &px, &py, &pz);	//ͶӰ
	py = viewport[3] - py;															//У��������
	p1.SetXYZ(px, py, pz);															//ͶӰ��ĵ�
	/**/
	return p1;																		//����ͶӰ��ĵ�����
}

/*********************************************************************************
  *Function: GetGLPortPt(VPoint3& p0) 
  *Description������Ļ����ת��Ϊopengl�������� 
  *Input:  p0-��Ļ����
  *Return: opengl�������� 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetGLPortPt(VPoint3& p0)
{
	VPoint3 p1;

	GLint    viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetIntegerv(GL_VIEWPORT, viewport);											//�ӿھ���
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);									//ģ�ͱ任����
	glGetDoublev(GL_PROJECTION_MATRIX, projection);									//ͶӰ����
	GLdouble px, py, pz;
	p0.y= viewport[3] - p0.y;	                                                    //У��������
	gluUnProject(p0.x, p0.y, p0.z, modelview, projection, viewport, &px, &py, &pz);	//��ͶӰ	
	p1.SetXYZ(px, py, pz);															//��ͶӰ��ĵ�

	return p1;																		//���ط�ͶӰ��ĵ�����
}



/*********************************************************************************
  *Function: GetTransPt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt)  
  *Description����ȡ�ƶ�������ƶ����� 
  *Input:  p_start,p_end��Ļ������ƶ��������㣬centerPt��ģ�͵���Ļ��������
  *Return: opengl����������ƶ����� 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetTransPt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt)	//���ƽ������
{
	VPoint3 transEnd(float(p_end.x),float(p_end.y),centerPt.z);//��Ļ��ƽ�ƺ�����Ϊ�����
	transEnd = GetGLPortPt(transEnd);
	VPoint3 transStart(float(p_start.x),float(p_start.y),centerPt.z);
	transStart = GetGLPortPt(transStart);	

	VPoint3 transMove; 
	transMove.SetXYZ((transEnd.x-transStart.x),(transEnd.y-transStart.y),(transEnd.z-transStart.z));//���ƽ������

	return transMove;
}
/*********************************************************************************
  *Function: GetRotatePt(VPoint3 startPt,VPoint3 endPt,VPoint3 CenterPt) 
  *Description����ȡ�ƶ�������ƶ����� 
  *Input:  p_start,p_end��Ļ������ƶ��������㣬centerPt��ģ�͵���Ļ��������
  *Return: opengl�����������ת���� 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetRotatePt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt)
{
	VPoint3 transREnd(-float(p_end.y),float(p_end.x),centerPt.z);
	transREnd = GetGLPortPt(transREnd);
	VPoint3 transRStart(-float(p_start.y),float(p_start.x),centerPt.z);
	transRStart = GetGLPortPt(transRStart);
	VPoint3 transRotate;
	transRotate.SetXYZ(5*(transRStart.x-transREnd.x),(transRStart.y-transREnd.y),(transRStart.z-transREnd.z));

	return transRotate;
}
//��ȡ��������
VPoint3 VScene::GetScalePt(VPoint3 p_start,VPoint3 p_end)
{
	float k=1+6.0f*(p_end.y-p_start.y)/512.0;//����������ת����
	VPoint3 transScale(k,k,k);

	return transScale;
}
/*********************************************************************************
  *Function: Hit(int x, int y) 
  *Description�� ͨ����Χ�еıȽϴӳ�����ʰȡģ�ͣ�ʰȡ����ģ�ͱ��浽vnodeselector
  *Input:  x,y�����Ļ����
  *Return: �� 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
void VScene::Hit(int x, int y)
{
	m_pNodeSel->Clear();														//���ѡ����
	VNodeVector vNodeList;														//����һ�����ָ������
	ReadAllNodes(vNodeList);													//��ȡ���������н��ָ��
	int i, j, numNodes = vNodeList.size();										//�����н��ĸ���
	VBoundBox* pBB;																//��Χ��ָ��
	VMatrix3 mat;																//������
	VPoint3 p[9];
	VPoint3 world;
	for (i = 0; i < numNodes; i++)												//����ÿ�����
	{
		VNode* node = vNodeList[i];
		if(vNodeList[i]->GetDisplayFlag() == false)	continue;					//�����������״̬����
		pBB = &(vNodeList[i]->GetMesh()->GetBoundBox());									//���ؽ������İ�Χ��
		mat = vNodeList[i]->GetNodeTM();										//���ؽ��ľ���
		if(pBB)																	//�����Χ�д���
		{
			p[0] = pBB->m_Pmin;													//8���ǵ�
			p[1] = pBB->m_Pmax;
			p[2].SetXYZ(p[0].x, p[1].y, p[0].z);
			p[3].SetXYZ(p[0].x, p[1].y, p[1].z);
			p[4].SetXYZ(p[0].x, p[0].y, p[1].z);
			p[5].SetXYZ(p[1].x, p[0].y, p[0].z);
			p[6].SetXYZ(p[1].x, p[1].y, p[0].z);
			p[7].SetXYZ(p[1].x, p[0].y, p[1].z);
			for (j = 0; j < 8; j++)												//����ÿ���ǵ�
			{
				p[j] = mat.TransPoint(p[j]);									//�������ת����ĵ�
				p[j] = GetViewPortPt(p[j]);										//ת��Ϊ�ӿ�����
			}
			p[8].SetXYZ(p[0]);
			for (j = 1; j < 8; j++)												//����ת�����ÿ���ǵ㣬��¼����ߵ����͵�
			{
				if(p[j].x < p[0].x)	p[0].x = p[j].x;
				if(p[j].x > p[8].x)	p[8].x = p[j].x;
				if(p[j].y < p[0].y) p[0].y = p[j].y;
				if(p[j].y > p[8].y) p[8].y = p[j].y;
			}
			
			
			/*VPoint3 temp;
			temp = GetGLPortPt(VPoint3(x,y,0));*/
			
			//if((temp.x > p[0].x) && (temp.x < p[8].x) && (temp.y > p[0].y) && (temp.y < p[8].y))	//�����ǰ�������Χ�й�������
			if((x > p[0].x) && (x < p[8].x) && (y > p[0].y) && (y < p[8].y))
			{
				this->SelectNode(vNodeList[i]);									//ѡ���ģ��
				vNodeList.clear();												//����б�
				return;															//����
			}
		}  
	}
	vNodeList.clear();															//����б�
}