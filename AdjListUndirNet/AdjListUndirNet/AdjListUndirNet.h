#pragma once
//���캯�����������졢��������
//��ա��пա���ӡ����ȡ��������
//���غ��������붥�㡢����ߡ�ɾ�����㡢ɾ����
//ͳ�ƶ���Ķȡ���ͼ����ͨ������Ŀ
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <cassert>

using namespace std;

const int DEFAULT_SIZE = 100;
const int DEFAULT_INFINITY = INT_MAX;

enum Status {
	UNVISITED,VISITED
};

class Error {
private:
	string message;
public:
	Error() :message("��������"){}
	Error(string message) {
		this->message = message;
	}
	void show()const {
		cout << message << endl;
	}
};

//��
template <class WeightType>
struct AdjListNetworkArc { 
    int adjvex;          // �ڽӵ�����
    WeightType weight;   // ��Ȩ��
    AdjListNetworkArc<WeightType>* nextarc; // ��һ����ָ��

    AdjListNetworkArc(int v, WeightType w, AdjListNetworkArc<WeightType>* next = NULL)
        : adjvex(v), weight(w), nextarc(next) {}
};

template <class ElemType, class WeightType>
struct AdjListNetWorkVex {
    ElemType data;
    AdjListNetworkArc<WeightType>* firstarc;
    Status tag;

    AdjListNetWorkVex() : firstarc(NULL), tag(UNVISITED) {}
    AdjListNetWorkVex(ElemType val, AdjListNetworkArc<WeightType>* adj = NULL)
        : data(val), firstarc(adj), tag(UNVISITED) {}
};

template <class ElemType, class WeightType> class AdjListUndirNet {
protected:
	int vexNum;         //��ǰ������
	int vexMaxNum;      //��󶥵�����
	int arcNum;         //��ǰ����
	AdjListNetWorkVex<ElemType,WeightType>* vexTable; //�����
	mutable Status* tag;                             //����������
	WeightType infinity;
public:
	template <class ElemType, class WeightType>
	friend WeightType findMaxEdgeInPath(int u, int v, const AdjListUndirNet<ElemType, WeightType>& mst);

	AdjListUndirNet(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	AdjListUndirNet(int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	~AdjListUndirNet();

	void Clear();      //���ͼ
	bool IsEmpty();    //�ж�ͼ�Ƿ�Ϊ��
	AdjListUndirNet& operator=(const AdjListUndirNet<ElemType,WeightType>& copy);//��ֵ���������
	void Display() const;  //��ӡͼ����Ϣ

	int GetVexNum() const; //��ȡ��ǰ���������
	int GetArcNum() const; //��ȡ��ǰ�ߵ�����
	void InsertVex(const ElemType& e);             //���붥��
	void InsertArc(int v1, int v2, WeightType w);  //�����
	void DeleteVex(const ElemType& d);             //ɾ������
	void DeleteArc(const int v1, int v2);          //ɾ����
	int FirstAdjVex(int v) const;                  //�󶥵�v�ĵ�һ���ڽӵ�����
	int NextAdjVex(int v1, int v2) const;          //�󶥵�v1����һ���ڽӵ����
	void SetWeight(int v1, int v2, WeightType w);  //��ӱߵ�Ȩ��
	WeightType GetWeight(int v1, int v2) const; // ��ȡ�ߵ�Ȩ��
	int GetDegree(int v) const;                    // ͳ�ƶ���Ķ�
	int GetConnectedComponents() const;            // ��ͼ����ͨ������Ŀ
	bool IsConnected(int u, int v) const;          // �ж���ͨ��
	void BreakCycleMST(AdjListUndirNet<ElemType, WeightType>& mst);   // ��Ȧ��������С������
	bool hasUniqueMinTree()const; 	// �ж��Ƿ����Ψһ��С������
};
//�����ͼ
template<class ElemType, class WeightType>
AdjListUndirNet<ElemType, WeightType>::AdjListUndirNet(int vertexMaxNum, WeightType infinit) {
	if (vertexMaxNum < 0)
		throw Error("����Ķ���������Ŀ����Ϊ����");
	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	infinity = infinit;
	tag = new Status[vertexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
}

//���캯��
template<class ElemType, class WeightType>
AdjListUndirNet<ElemType, WeightType>::AdjListUndirNet(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infinit) {
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ����");
	if (vertexMaxNum < vertexNum)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ��");
	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	infinity = infinit;
	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
	assert(vexNum <= vexMaxNum);
	for (int v = 0; v < vexNum; v++) {
		tag[v] = UNVISITED;
		vexTable[v].data = es[v];
		vexTable[v].firstarc = NULL;
	}
}

