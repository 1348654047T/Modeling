/**********************************************************************
DESCRIPTION: ��������ṹ 

CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************/
#ifndef _VMESH_H_
#define _VMESH_H_
#include "vpoint.h"
#include "vmatrix.h"
#include "vface.h"
#include "glut.h"
#include "vrender.h"
//////////////////////////////////////////////////////////////////////////
//mesh��ʾ��ʽ
#define MESH_NONE				0x0000
#define MESH_SOLID				0x0001
#define MESH_POINT				0x0002
#define MESH_POINT_SOLID		0x0003
#define MESH_LINE				0x0004
#define MESH_LINE_SOLID			0x0005
#define MESH_POINT_LINE			0x0006
#define MESH_POINT_LINE_SOLID	0x0007
																								
class VMesh
{
public:
	VMesh();																					//Ĭ�Ϲ��캯��
	VMesh(const VMesh& fromMesh);																//�������캯��
	~VMesh();																					//��������

private:
	static VPoint3 m_PointColor;															//mesh�ڵ���ʾ״̬�µ���ɫ
	static VPoint3 m_LineColor;																//mesh������ʾ״̬�µ���ɫ
	int m_iShowMode;																			//��ʾ��ʽ
	bool m_bSelect;																				//�Ƿ�ѡ��
public:
	int m_iNumVerts;																			//������Ŀ
	int m_iNumFaces;																			//��Ƭ��Ŀ
	VPoint3 *m_pVerts;																			//��������
	VPoint3 *m_pVertColors;																		//������ɫ����
	VFace *m_pFaces;																			//��Ƭ����
public:
	VBoundBox m_bBox;//��Χ��
	
public:
	static VPoint3& GetPointColor() { return m_PointColor; }										//������ʾ��ɫ
	static void SetPointColor(VPoint3& newColor) { m_PointColor = newColor; }					//������ʾ��ɫ
	static VPoint3& GetLineColor() { return m_LineColor; }										//������ʾ��ɫ
	static void SetLineColor(VPoint3& newColor) { m_LineColor = newColor; }						//������ʾ��ɫ
	int GetShowMode(){ return m_iShowMode; }                                             //������ʾ��ʽ
	void SetShowMode(int showMode){ m_iShowMode = showMode;}

public:

	//����Ļ���
	void Display(const VMatrix3& mat,bool flag);											//����Ļ���

	//��ʼ��
	void InitMesh();																			//��ʼ������
	
	//������ط���
	inline int GetNumVerts(){ return m_iNumVerts; }												//���ض�������Ŀ
	bool SetNumVerts(int num,bool keep = false);												//���ö�����Ŀ
	bool CopyVerts(const VMesh& fromMesh);														//��Դ���񿽱���������
	inline VPoint3& GetVert(int index){ return m_pVerts[index]; }								//����ָ�������Ķ���
	inline VPoint3* GetVertPtr(int index){ return &(m_pVerts[index]); }							//��ָ����ʽ����ָ�������Ķ���
	inline void SetVert(int index, const VPoint3& xyz){ m_pVerts[index].SetXYZ(xyz); }			//����ָ���������������
	inline void SetVert(int index,float x,float y,float z){ m_pVerts[index].SetXYZ(x,y,z); }	//��ָֻ���������������
	void FreeVerts();																			//�ͷŶ�������
	

	//������ɫ��ط���
	bool SetNumVertColors(int num);																//������ɫ������Ŀ
	bool CopyVertColors(const VMesh& fromMesh);													//��Դ���񿽱���������
	inline VPoint3& GetVertCol(int index){ return m_pVertColors[index]; }							//����ָ�������Ķ���
	inline VPoint3* GetVertColPtr(int index){ return &(m_pVertColors[index]); }					//��ָ����ʽ����ָ�������Ķ���
	inline void SetVertColor(int index, const VPoint3& xyz){ m_pVertColors[index].SetXYZ(xyz); }		//����ָ���������������
	inline void SetVertColor(int index,float x,float y,float z){ m_pVertColors[index].SetXYZ(x,y,z); }	//��ָֻ���������������
	inline void SetDefColor();																	//
	void SetAllToColor(float x,float y,float z);
	void FreeVertColors();																		//�ͷŶ�������

	//��Ƭ��ط���
	inline int GetNumFaces(){ return m_iNumFaces; }												//������Ƭ��Ŀ
	bool SetNumFaces(int num,bool keep = false);												//������Ƭ��Ŀ
	bool CopyFaces(const VMesh& fromMesh);														//��Դ���񿽱���Ƭ
	VFace& GetFace(int fIndex){ return m_pFaces[fIndex]; }										//����ָ����������Ƭ
	VFace* GetFacePtr(int fIndex) { return &(m_pFaces[fIndex]); }								//����ָ����Ƭ��ָ��
	void SetFace(int fIndex, int v0, int v1, int v2){ m_pFaces[fIndex].SetVerts(v0,v1,v2); }	//����ָ����Ƭ�Ķ�������
	void SetFace(int fIndex, int f_v[3]){ m_pFaces[fIndex].SetVerts(f_v); }						//����ָ����Ƭ�Ķ�������
	void SetFace(int fIndex, VFace& f1){ m_pFaces[fIndex] = f1; }								//����ָ��������Ƭ
	void SetFace_Normal_Verts(int fIndex, int x, int y, int z, int nx, int ny, int nz)
	{
		SetFace(fIndex,x, y,z);	
		m_pFaces[fIndex].index_normals[0] = nx;
		m_pFaces[fIndex].index_normals[1] = ny;
		m_pFaces[fIndex].index_normals[2] = nz;
	}
	void FreeFaces();																			//�ͷ���Ƭ����
	
	//����������
	//!!�ȴ���֤��δ��֤
	VMesh& operator=(const VMesh& fromMesh);													//���ص��ڷ���

	//TestPrint
	void PrintMesh(char* cFileName);

	//��Χ����ط���
	inline VBoundBox& GetBoundBox(){ return m_bBox; }											//���ذ�Χ��
	void ComputeBoundBox();																		//�����Χ��

	//ѡ��״̬
	inline bool GetSelect(){ return m_bSelect; }												//���ص�ǰѡ��״̬
	inline void SetSelect(bool bSelect = true){ m_bSelect = bSelect; }							//���õ�ǰѡ��״̬
	inline void UnSelect(){ m_bSelect = false; }												//���õ�ǰѡ��״̬Ϊ��ѡ��
	
};
//////////////////////////////////////////////////////////////////////////
#endif