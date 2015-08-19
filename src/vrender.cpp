#include "vrender.h"
VRender* VRender::m_pRender = NULL;
//////////////////////////////////////////////////////////////////////////
//��ȡ����
VRender* VRender::GetSingleton()
{
	if (!m_pRender)	
	{m_pRender = new VRender;}
	return m_pRender;
}
//�ݻٵ���
void VRender::DestroySingleton()
{
	if (m_pRender)

	{
		delete m_pRender;
		m_pRender = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//	��Ⱦ����任
void VRender::SetTransform(const VMatrix3& matrix)
{
	glPushMatrix();
	float fMatrix[16];
	matrix.GetTransPoseMat(fMatrix);//openglʶ��ľ���Ϊ16��Ԫ�ص�����
	glMultMatrixf(fMatrix);
}
//�ָ��任֮ǰ�ľ���״̬
void VRender::RemoveTransform(const VMatrix3& matrix)
{
	glPopMatrix();
}
//////////////////////////////////////////////////////////////////////////
//����ͼԪ���ƽӿ�
/*********************************************************************************
  *Function:  DrawPoints(int num,VPoint3* pVerts,VPoint3* pColor)
  *Description�� ���ƶ�������
  *Input: num�����������pVerts���������飻pColor��������ɫ
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawPoints(int num,VPoint3* pVerts,VPoint3* pColor)
{      
	if(num <= 0 || !pVerts)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);//��ѯϵͳ״̬�ĵ�ǰֵ����������ɫ������ʹģ����ͼ�����
	//���ö�������
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,sizeof(VPoint3),pVerts);	
	if(pColor)
	{
		//������ɫ����
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3,GL_FLOAT,sizeof(VPoint3),pColor);		
	}
	glDrawArrays(GL_POINTS,0,num);
	if(pColor) glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor4fv(fCurColor);//�ָ�ϵͳ��״̬
}
/*********************************************************************************
  *Function: DrawLine(VPoint3& p0,VPoint3& p1,VPoint3& pColor) 
  *Description�������߶�P0P1 
  *Input:  p0������0��p1������1��pColor���߶���ɫ
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawLine(VPoint3& p0,VPoint3& p1,VPoint3& pColor)
{
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glColor4f(pColor.x,pColor.y,pColor.z,1.0f);
	glBegin(GL_LINES);		
	glVertex3f(p0.x,p0.y,p0.z);
	glVertex3f(p1.x,p1.y,p1.z);
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function:DrawLines(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor,bool bClosed )  
  *Description������������˻��Ʊպ��߶λ������߶� 
  *Input:  numFaces������;pVerts:��������;pColor��������ɫ;  bClosed���Ƿ�Ϊ�պ��߶Σ�pFaces:������
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawLines(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor,bool bClosed /* = TRUE */)
{
	if(numFaces <= 0)
		return;
	float fCurColor[4];
	int LineMode = 0;
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	if(bClosed)
		LineMode = GL_LINE_LOOP;
	else
		LineMode = GL_LINE_STRIP;
	for (int i = 0;i<numFaces;i++)
	{
		glBegin(LineMode);
		for (int j = 0;j<3;j++)
		{
			int indexVert = pFaces[i].GetVert(j);
			if(pColor)
				glColor4f(pColor[indexVert].x,pColor[indexVert].y,pColor[indexVert].z,1.0f);
			//glColor4f(0.6,0.6,0.6,1.0);
			glVertex3f(pVerts[indexVert].x,pVerts[indexVert].y,pVerts[indexVert].z);
		}
		glEnd();
	}
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function: DrawPolygon(int numVerts,VPoint3* pVerts,VPoint3* pColor) 
  *Description�����ƶ���� 
  *Input:  numVerts�����������pVerts���������飻pColor��������ɫ;
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawPolygon(int numVerts,VPoint3* pVerts,VPoint3* pColor)
{
	if(numVerts <= 0)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glBegin(GL_POLYGON);
	for (int i = 0;i<numVerts;i++)
	{
		if (pColor)
			glColor4f(pColor[i].x,pColor[i].y,pColor[i].z,1.0f);
		glVertex3f(pVerts[i].x,pVerts[i].y,pVerts[i].z);
	}
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function:  DrawTriangle(VPoint3* pVerts,VPoint3* pColor)
  *Description������������ 
  *Input:  pVerts���������飻pColor��������ɫ
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawTriangle(VPoint3* pVerts,VPoint3* pColor)
{	
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glBegin(GL_TRIANGLES);
	for(int i = 0;i<3;i++)
	{
		if(pColor)
			glColor4f(pColor[i].x,pColor[i].y,pColor[i].z,1);
		glVertex3f(pVerts[i].x,pVerts[i].y,pVerts[i].z);
	}		
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function: DrawTriStrip(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor) 
  *Description�� ���������δ�
  *Input:  numFaces��������pFaces:�����飻pVerts���������飻 pColor��������ɫ;
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawTriStrip(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor)
{
	if(numFaces <= 0)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0;i<numFaces;i++)
	{
		for (int j = 0;j<3;j++)
		{
			int index = pFaces[i].GetVert(j);
			if (pColor)
				glColor4f(pColor[index].x, pColor[index].y, pColor[index].z, 1.0f);
			glVertex3f(pVerts[index].x, pVerts[index].y, pVerts[index].z);
		}		

	}
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function:DrawTriangles(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor)  
  *Description������numFaces�������� 
  *Input:  numFaces��������pFaces:�����飻pVerts���������飻 pColor��������ɫ
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawTriangles(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor)
{
	if(numFaces <= 0)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);		
	glBegin(GL_TRIANGLES);
	for (int i = 0;i<numFaces;i++)
	{	
		for (int j = 0;j<3;j++)
		{
			int vindex = pFaces[i].GetVert(j);
			if (pColor)
				glColor4f(pColor[vindex].x,pColor[vindex].y,pColor[vindex].z,1.0f);
			glVertex3f(pVerts[vindex].x,pVerts[vindex].y,pVerts[vindex].z);
		}		
	}
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function: DrawBoundBox(VBoundBox& box) 
  *Description�����ư�Χ�� 
  *Input:  box ��Χ��
  *Return: �� 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawBoundBox(VBoundBox& box)
{
	VPoint3 pDefC, pLC, pHC;
	pDefC = box.GetColor();
	pLC = box.Min();
	pHC = box.Max();
	float fCurColor[4];															//��¼��ǰ��ɫ
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);										//��ȡ��ǰ��ɫ
	glColor3f(pDefC.x, pDefC.y, pDefC.z);									//���õ�ǰ������ɫ
	//�����干��12����
	glBegin(GL_LINE_LOOP);
	//���Ʊ�����
	glVertex3f(pLC.x, pLC.y, pLC.z);
	glVertex3f(pLC.x, pLC.y, pHC.z);
	glVertex3f(pLC.x, pHC.y, pHC.z);
	glVertex3f(pLC.x, pHC.y, pLC.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	//����������
	glVertex3f(pHC.x, pLC.y, pLC.z);
	glVertex3f(pHC.x, pHC.y, pLC.z);
	glVertex3f(pHC.x, pHC.y, pHC.z);
	glVertex3f(pHC.x, pLC.y, pHC.z);
	glEnd();
	glBegin(GL_LINES);
	//����ʣ���������
	glVertex3f(pLC.x, pLC.y, pLC.z);
	glVertex3f(pHC.x, pLC.y, pLC.z);										//1-th Edge
	glVertex3f(pLC.x, pLC.y, pHC.z);
	glVertex3f(pHC.x, pLC.y, pHC.z);										//2-th Edge
	glVertex3f(pLC.x, pHC.y, pLC.z);
	glVertex3f(pHC.x, pHC.y, pLC.z);										//3-th Edge
	glVertex3f(pLC.x, pHC.y, pHC.z);
	glVertex3f(pHC.x, pHC.y, pHC.z);										//4-th Edge
	glEnd();
	glColor4fv(fCurColor);											//�ָ���һ�λ��Ƶ���ɫ
}