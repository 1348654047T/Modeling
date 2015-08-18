#include "vmesh.h"

VPoint3 VMesh::m_PointColor(1.0,1.0,1.0);									//��ʼ��Ĭ�ϵĵ���ʾ��ʽʱ�ĵ���ɫ
VPoint3 VMesh::m_LineColor(1.0,1.0,1.0);									//��ʼ��Ĭ�ϵ�����ʾ��ʽ������ɫ

/*********************************************************************************
  *Function:  VMesh()
  *Description�� Ĭ�Ϲ��캯��
  *Input:  ��
  *Return: �� 
               *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
VMesh::VMesh()
{
	m_iNumVerts = m_iNumFaces = 0;	//���㡢��Ƭ������0
	m_pVerts = NULL;															//���������ÿ�
	m_pVertColors = NULL;															//������ɫ�����ÿ�
	m_pFaces = NULL;															//��Ƭ�����ÿ�
	m_iShowMode = MESH_LINE;													//Ĭ�����߿�ʽ��ʾ
	m_bSelect = false;                                                          //Ĭ��Ϊ��ѡ��
}

/*********************************************************************************
  *Function:  VMesh(const VMesh& fromMesh)
  *Description�� �������캯��
  *Input:  ԭ����
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
VMesh::VMesh(const VMesh& fromMesh)
{
	CopyVerts(fromMesh);														//��������
	CopyVertColors(fromMesh);														//����������ɫ
	CopyFaces(fromMesh);														//������Ƭ
}

VMesh::~VMesh()
{
	if(m_pVerts)																//��������������
		delete[] m_pVerts;														//ɾ����������
	if (m_pVertColors)															//���������ɫ�������
		delete[] m_pVertColors;													//ɾ��������ɫ����
	if(m_pFaces)																//�����Ƭ�������
		delete[] m_pFaces;														//ɾ����Ƭ����
	
}

/*********************************************************************************
  *Function: Display(const VMatrix3& mat,bool flag) 
  *Description���������� 
  *Input:  mat-������̬����
  *Return: �� 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
void VMesh::Display(const VMatrix3& mat,bool flag)
{
	VRender* render = VRender::GetSingleton();
	int showMod = GetShowMode();
	render->SetTransform(mat);//���ñ任����
	if (flag)
	{
		render->DrawBoundBox(m_bBox);
	}
	
	//////////////////////////////////////////////////////////////////////////
		switch (showMod)														//�������ʾ��ʽ
		{
		case MESH_POINT:														//����ʾ
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			break;
		case MESH_LINE:															//����ʾ
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors,true);
			break;
		case MESH_SOLID:														//ʵ������ʾ���������Σ�Ĭ�����
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_POINT_LINE:													//���߻����ʾ
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_POINT_SOLID:													//��������ʾ
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_LINE_SOLID:													//��������ʾ
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors,true);
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_POINT_LINE_SOLID:													//����������ʾ
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors,true);
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		}
	//////////////////////////////////////////////////////////////////////////
	render->RemoveTransform(mat);
								

}
/*********************************************************************************
  *Function: InitMesh() 
  *Description�� ��ʼ������
  *Input:  ��
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/

void VMesh::InitMesh()
{
	m_iNumVerts = m_iNumFaces = 0;		//���㡢��Ƭ������0
	if(m_pVerts)																//�ɶ����������
	{
		delete[] m_pVerts;														//ɾ���ɶ�������
		m_pVerts = NULL;														//���������ÿ�
	}
	if(m_pFaces)																//����Ƭ�������
	{
		delete[] m_pFaces;														//ɾ������Ƭ����
		m_pFaces = NULL;														//��Ƭ�����ÿ�
	}
	
}

/*********************************************************************************
  *Function:  SetNumVerts(int num,bool keep //= false )
  *Description�� ���ö������,�����ö�����ɫ����
  *Input:  num-���������keep-�Ƿ񱣳�Ԫ��������
  *Return: ���óɹ�����true��ʧ�ܷ���false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::SetNumVerts(int num,bool keep /* = false */)
{
	if(num <= 0)																//������鳤��С�ڻ����0
	{
		m_iNumVerts = 0;														//���鳤����0
		if(m_pVerts)															//������������
		{
			delete[] m_pVerts;													//ɾ��������
			m_pVerts = NULL;													//�����ÿ�
		}
		if (m_pVertColors)
		{
			delete[] m_pVertColors;
			m_pVertColors = NULL;
		}
		return true;
	}

	if(num == m_iNumVerts)														//������鳤����ͬ
	{
		return true;															//�����κβ�������
	}
	int originNum = m_iNumVerts;
	m_iNumVerts = num;
	if (!keep)																	//�������Ҫ����ԭ����
	{
		if(m_pVerts)	delete[] m_pVerts;										//ɾ��������
		m_pVerts = new VPoint3[m_iNumVerts];									//��������������
		if(!m_pVerts)	{m_iNumVerts = 0; m_pVerts = NULL;return false;}		//�ڴ����ʧ��
		FreeVertColors();																//ɾ��������
		m_pVertColors = new VPoint3[m_iNumVerts];										//��������������
		if(!m_pVertColors)	{ m_pVertColors = NULL;return false;}						//�ڴ����ʧ��
		SetDefColor();                                                            //���ж�������ΪĬ����ɫ
	}
	else																		//�����Ҫ����ԭ����
	{
		int MinNum = originNum;													//��¼�¾������г��Ƚ�Сֵ
		if(MinNum > m_iNumVerts)	MinNum = m_iNumVerts;						//�¾����鳤���еĽ�Сֵ
		VPoint3 *pNewVerts = new VPoint3[m_iNumVerts];							//����������
		if(!pNewVerts)	{m_iNumVerts = originNum; return false;}				//�ڴ����ʧ��
		for (int i = 0; i < MinNum; i++)										//���ƾ���������
		{
			pNewVerts[i] = m_pVerts[i];
		}
		delete[] m_pVerts;														//ɾ��������
		m_pVerts = pNewVerts;													//����������
	}									//���½���������λ����
	return true;
}

/*********************************************************************************
  *Function: CopyVerts(const VMesh& fromMesh) 
  *Description�� ��Դ�����п�������
  *Input: fromeMesh-Դ����
  *Return: �����ɹ�����true�����󷵻�false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::CopyVerts(const VMesh& fromMesh)
{
	if(m_pVerts)																//���ԭ�����������
	{
		if(m_iNumVerts != fromMesh.m_iNumVerts)									//�����ǰ���鳤�Ⱥ͸���Դ���鳤�Ȳ���ͬ
		{
			this->m_iNumVerts = fromMesh.m_iNumVerts;							//����Դ������Ŀ
			delete[] m_pVerts;													//ɾ��������
			m_pVerts = NULL;
			if(m_iNumVerts != 0)
			{
				m_pVerts = new VPoint3[m_iNumVerts];							//����������			
				if(!m_pVerts) return false;										//�ڴ����ʧ��
				memcpy(m_pVerts,fromMesh.m_pVerts,m_iNumVerts*sizeof(m_pVerts[0]));	//�ڴ濽��
			}
		}
		else
		{
			memcpy(m_pVerts,fromMesh.m_pVerts,m_iNumVerts*sizeof(m_pVerts[0]));	//�����鳤����ͬ���������ݼ���
		}
	}
	else																		//�����鲻����
	{
		if(fromMesh.m_iNumVerts > 0)											//���Դ�����������
		{
			this->m_iNumVerts = fromMesh.m_iNumVerts;							//����Դ���񶥵���Ŀ
			m_pVerts = new VPoint3[m_iNumVerts];								//����������
			if(!m_pVerts)	return false;										//�ڴ����ʧ��			
			memcpy(m_pVerts,fromMesh.m_pVerts,m_iNumVerts*sizeof(m_pVerts[0]));	//�ڴ濽��
		}
	}
	return true;
}

/*********************************************************************************
  *Function: FreeVerts() 
  *Description�� �ͷŶ�������
  *Input:  ��
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::FreeVerts()
{
	if(m_pVerts)																//������ڶ�������
		delete[] m_pVerts;														//�ͷŶ�������
	m_pVerts = NULL;															//��������ָ���ÿ�
	m_iNumVerts = 0;															//���������0
}




/*********************************************************************************
  *Function: CopyVertColors(const VMesh& fromMesh) 
  *Description�� ��Դ�����п���������ɫ����
  *Input: fromeMesh-Դ����
  *Return: �����ɹ�����true�����󷵻�false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::CopyVertColors(const VMesh& fromMesh)
{
	if(m_pVertColors)																//���ԭ������ɫ�������
	{
		if(m_iNumVerts != fromMesh.m_iNumVerts)									//�����ǰ���鳤�Ⱥ͸���Դ���鳤�Ȳ���ͬ
		{
			delete[] m_pVertColors;												//ɾ��������
			m_pVertColors = NULL;
			if(m_iNumVerts != 0)												//Դ������Ƭ�������
			{
				m_pVertColors = new VPoint3[m_iNumVerts];							//����������	
				if(!m_pVertColors) return false;									//�ڴ����ʧ��
				memcpy(m_pVertColors,fromMesh.m_pVertColors,
					m_iNumVerts*sizeof(m_pVertColors[0]));							//�ڴ濽��
			}
		}
		else																	//�����鳤����ͬ���������ڴ����ݼ���
		{
			memcpy(m_pVertColors,fromMesh.m_pVertColors,
				m_iNumVerts*sizeof(m_pVertColors[0]));								//�����ڴ�����
		}
	}
	else																		//�������񶥵���ɫ���鲻����
	{
		if(fromMesh.m_iNumVerts > 0)											//��Դ���񶥵���ɫ�������
		{
			m_pVertColors = new VPoint3[m_iNumVerts];								//����������
			if(!m_pVertColors)	return false;									//�ڴ����ʧ��
			memcpy(m_pVertColors,fromMesh.m_pVertColors,
				m_iNumVerts*sizeof(m_pVertColors[0]));							//�ڴ濽��
		}
	}
	return true;
}
/*********************************************************************************
  *Function:SetDefColor()  
  *Description�� ���ö���Ĭ����ɫ
  *Input:  ��
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::SetDefColor()
{
	if(m_pVertColors)																//������ڶ�����ɫ����
	{
		for (int i=0;i<m_iNumVerts;i++)
			SetVertColor(i,m_PointColor);										//�������ö�����ɫΪĬ����ɫ
	}
}
/*********************************************************************************
  *Function: SetAllToColor(float x,float y,float z) 
  *Description�� ���ö��ж���Ϊ����ɫ
  *Input:  RGB
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::SetAllToColor(float x,float y,float z)
{
	if(m_pVertColors)																//������ڶ�����ɫ����
	{
		VPoint3 color(x,y,z);
		for (int i=0;i<m_iNumVerts;i++)
			SetVertColor(i,color);											//�������ö�����ɫΪĬ����ɫ
	}
}
/*********************************************************************************
  *Function: FreeVertColors() 
  *Description���ͷŶ�����ɫ���� 
  *Input:  ��
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::FreeVertColors()
{
	if(m_pVertColors)																//������ڶ�����ɫ����
		delete[] m_pVertColors;													//�ͷŶ�����ɫ����
	m_pVertColors = NULL;															//������ɫ����ָ���ÿ�
}

/*********************************************************************************
  *Function: SetNumFaces(int num,bool keep / = false /) 
  *Description��������Ƭ������� 
  *Input:  num-��Ƭ������keep-�Ƿ񱣳�ԭʼ����
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::SetNumFaces(int num,bool keep /* = false */)
{
	if(num <= 0)																//������鳤��С�ڻ����0
	{
		m_iNumFaces = 0;														//���鳤����0
		if(m_pFaces)															//������������
		{
			delete[] m_pFaces;													//ɾ��������
			m_pFaces = NULL;													//�����ÿ�
		}
		return true;
	}

	if(num == m_iNumFaces)	return true;										//������鳤����ͬ������Ҫ����

	int originNum = m_iNumFaces;
	m_iNumFaces = num;
	if (!keep)																	//�������Ҫ����ԭ����
	{
		if(m_pFaces)	delete[] m_pFaces;										//ɾ��������
		m_pFaces = new VFace[m_iNumFaces];										//��������������
		if(!m_pFaces)	{m_iNumFaces = 0; m_pFaces = NULL;return false;}		//�ڴ����ʧ��
	}
	else																		//�����Ҫ����ԭ����
	{
		int MinNum = originNum;													//��¼�¾������г��Ƚ�Сֵ
		if(MinNum > m_iNumFaces)	MinNum = m_iNumFaces;						//�¾����鳤���еĽ�Сֵ
		VFace *pNewFaces = new VFace[m_iNumFaces];								//����������
		if(!pNewFaces)	{m_iNumFaces = originNum; return false;}				//�ڴ����ʧ��
		for (int i = 0; i < MinNum; i++)										//����������������
		{
			pNewFaces[i] = m_pFaces[i];
		}
		delete[] m_pFaces;														//ɾ���ɵ���Ƭ����
		m_pFaces = pNewFaces;													//�����µ���Ƭ����
	}
	return true;
}

/*********************************************************************************
  *Function:  CopyFaces(const VMesh& fromMesh)
  *Description�� ��Դ���񿽱���Ƭ����
  *Input:  fromMesh-Դ����
  *Return: ���ݿ����ɹ�����true��ʧ�ܷ���false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::CopyFaces(const VMesh& fromMesh)
{
	if(m_pFaces)																//���ԭ��Ƭ�������
	{
		if(m_iNumFaces != fromMesh.m_iNumFaces)									//�����ǰ���鳤�Ⱥ͸���Դ���鳤�Ȳ���ͬ
		{
			this->m_iNumFaces = fromMesh.m_iNumFaces;							//����Դ������Ƭ��Ŀ
			delete[] m_pFaces;													//ɾ��������
			m_pFaces = NULL;
			if(m_iNumFaces != 0)												//Դ������Ƭ�������
			{
				m_pFaces = new VFace[m_iNumFaces];								//����������	
				if(!m_pFaces) return false;										//�ڴ����ʧ��
				memcpy(m_pFaces,fromMesh.m_pFaces,m_iNumFaces*sizeof(m_pFaces[0]));	//�ڴ濽��
			}
		}
		else																	//�����鳤����ͬ���������ڴ����ݼ���
		{
			memcpy(m_pFaces,fromMesh.m_pFaces,m_iNumFaces*sizeof(m_pFaces[0]));	//�����ڴ�����
		}
	}
	else																		//����������Ƭ���鲻����
	{
		if(fromMesh.m_iNumFaces > 0)											//��Դ������Ƭ�������
		{
			this->m_iNumFaces = fromMesh.m_iNumFaces;							//����Դ������Ƭ��Ŀ
			m_pFaces = new VFace[m_iNumFaces];									//����������
			if(!m_pFaces)	return false;										//�ڴ����ʧ��
			memcpy(m_pFaces,fromMesh.m_pFaces,m_iNumFaces*sizeof(m_pFaces[0]));	//�ڴ濽��
		}
	}
	return true;
}

/*********************************************************************************
  *Function:  FreeFaces()
  *Description�� �ͷ���Ƭ����
  *Input:  ��
  *Return: �� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::FreeFaces()
{
	if(m_pFaces)																//���������Ƭ����
		delete[] m_pFaces;														//�ͷ���Ƭ����
	m_pFaces = NULL;															//��Ƭ����ָ���ÿ�
	m_iNumFaces = 0;															//��Ƭ������0
}



/*********************************************************************************
  *Function:  operator=(const VMesh& fromMesh)
  *Description�� ���ز�����operator =
  *Input:  fromMesh-Դ����
  *Return: ����������� 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
VMesh& VMesh::operator=(const VMesh& fromMesh)
{
	CopyVerts(fromMesh);														//��������
	CopyFaces(fromMesh);														//������Ƭ
	CopyVertColors(fromMesh);
	return (*this);
}



void VMesh::PrintMesh(char* cFileName)
{
	FILE* fp = fopen(cFileName,"wt");
	fprintf(fp,"Verts:\n");
	for (int i = 0; i < m_iNumVerts; i++)
	{
		fprintf(fp,"%d-(%f,%f,%f)\n",i,m_pVerts[i].x,m_pVerts[i].y,m_pVerts[i].z);
	}
	fprintf(fp,"Faces:\n");
	for (int i = 0; i < m_iNumFaces; i++)
	{
		fprintf(fp,"%d-(%d,%d,%d)\n",i,m_pFaces[i].vert[0],m_pFaces[i].vert[1],m_pFaces[i].vert[2]);
	}
	fclose(fp);
}
//////////////////////////////////////////////////////////////////////////
//��Χ����ط���
/*********************************************************************************
  *Function: ComputeBoundBox() 
  *Description�� �����Χ��
  *Input:  ��
  *Return: �� 
              *CREATED BY:  [8/7/2015 niewenchao]
**********************************************************************************/
void VMesh::ComputeBoundBox()
{
	if(m_iNumVerts <= 0)
	{
		m_bBox.InitBoundBox();
		return;
	}
	m_bBox.m_Pmin = m_pVerts[0];
	m_bBox.m_Pmax = m_pVerts[0];
	for (int i = 1; i < m_iNumVerts; i++)										//�������ж��㣬������Χ��
	{
		if(m_bBox.m_Pmin.x > m_pVerts[i].x)								//�ҳ���С��x����ֵ
			m_bBox.m_Pmin.x = m_pVerts[i].x;
		if(m_bBox.m_Pmin.y > m_pVerts[i].y)								//�ҳ���С��y����ֵ
			m_bBox.m_Pmin.y = m_pVerts[i].y;
		if(m_bBox.m_Pmin.z > m_pVerts[i].z)								//�ҳ���С��z����ֵ
			m_bBox.m_Pmin.z = m_pVerts[i].z;
		if(m_bBox.m_Pmax.x < m_pVerts[i].x)								//�ҳ�����x����ֵ
			m_bBox.m_Pmax.x = m_pVerts[i].x;
		if(m_bBox.m_Pmax.y < m_pVerts[i].y)								//�ҳ�����y����ֵ
			m_bBox.m_Pmax.y = m_pVerts[i].y;
		if(m_bBox.m_Pmax.z < m_pVerts[i].z)								//�ҳ�����z����ֵ
			m_bBox.m_Pmax.z = m_pVerts[i].z;
	}
}