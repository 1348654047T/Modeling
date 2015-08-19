

/**********************************************************************
DESCRIPTION: ����������Ƭ 

CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************/
#ifndef _VFACE_H_
#define _VFACE_H_
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////

class VFace{																		// ��Ķ���
public:
	VFace(){ //Ĭ�Ϲ��캯��
		vert[0] = vert[1] = vert[2] = 0;
	}				
	VFace(const VFace& fromFace)													//�������캯��
	{
		vert[0] = fromFace.vert[0];													//�����涥������
		vert[1] = fromFace.vert[1];
		vert[2] = fromFace.vert[2];
	}
	~VFace(){}																		//��������

public:
	int vert[3];
	int index_normals[3];

public:

	//������Ϣ������
	inline int GetVert(int i){return vert[i];}										//������Ƭ��i����������
	inline int GetNormal(int i){return index_normals[i];}							//������Ƭ��i�����߶�������
	inline int* GetAllVerts(){return vert;}											//������Ƭ���ж�������ָ��
	int GetVertIndex(int v0)														//���ض��������ڸ���Ƭ�µ��±�
	{
		for (int i = 0; i < 3; i++)													//����ÿ����Ƭ����
		{
			if(vert[i] == v0)	return i;											//������ڣ����ظ��±�����
		}
		return -1;																	//�����ڷ���-1
	}
	inline void SetVert(int index,int VertIndex){vert[index] = VertIndex;}			//������Ƭ����
	inline void SetVerts(int v0, int v1, int v2){vert[0] = v0; vert[1] = v1; vert[2] = v2;}	//����������Ƭ���ж���
	inline void SetVerts(int pVerts[3]){vert[0] = pVerts[0]; vert[1] = pVerts[1]; vert[2] = pVerts[2];}//������Ƭ���ж���

	VFace& operator =(const VFace& fromFace)
	{
		vert[0] = fromFace.vert[0];													//�����涥������
		vert[1] = fromFace.vert[1];
		vert[2] = fromFace.vert[2];
		
		index_normals[0] = fromFace.index_normals[0];
		index_normals[1] = fromFace.index_normals[1];
		index_normals[2] = fromFace.index_normals[2];
		return (*this);																//���ظ�ֵ�����Ƭ
	}



};
//////////////////////////////////////////////////////////////////////////
#endif