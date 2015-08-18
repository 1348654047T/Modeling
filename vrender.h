/**********************************************************************
DESCRIPTION: �����˻���ͼԪ�Ļ��ƽӿ� 

CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************/
#ifndef _VRENDER_H_
#define _VRENDER_H_
///////////////////////////////////////////////
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include "vmatrix.h"
#include "vboundbox.h"
#include "vface.h"
//////////////////////////////////////////////////////////////////////////
class VRender
{
public:
	VRender(){};
	~VRender(){};
	static VRender* GetSingleton();
	static void DestroySingleton();	
public:
	//����任
	void SetTransform(const VMatrix3& matrix);
	void RemoveTransform(const VMatrix3& matrix);
public:
	//����ͼԪ���ƽӿ�	
	//���Ƶ㼯 
	void DrawPoints(int numVerts,VPoint3* pVerts,VPoint3* pColor );
	//�����߶�
	void DrawLine(VPoint3& p0,VPoint3& p1,VPoint3& pColor);
	//���������߶μ�
	void DrawLines(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor,bool bClosed = TRUE);
	//����һ�������
	void DrawPolygon(int numVerts,VPoint3* pVerts,VPoint3* pColor);
	//����������
	void DrawTriangle(VPoint3* pVerts,VPoint3* pColor );
	//�������������δ�
	void DrawTriStrip(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor);
	//���ƶ��������
	void DrawTriangles(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor);	
	//���ư�Χ��
	void DrawBoundBox(VBoundBox& box); 
	//��������߻�
	//void DrawBorder(vector<VPoint3>& vpt,VPoint3 color);

	//ʹ�������
	void RenderCamera(VVector3& camPos,VVector3& camView,VVector3& camDir);
private:
	static VRender* m_pRender;//����
};





///////////////////////////////////////////////
#endif