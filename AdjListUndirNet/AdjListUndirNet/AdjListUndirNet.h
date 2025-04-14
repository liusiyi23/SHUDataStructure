#pragma once
//构造函数、拷贝构造、析构函数
//清空、判空、打印、获取顶点数量
//重载函数、插入顶点、插入边、删除顶点、删除边
//统计顶点的度、求图的连通分量数目
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
	Error() :message("发生错误"){}
	Error(string message) {
		this->message = message;
	}
	void show()const {
		cout << message << endl;
	}
};

//边
template <class WeightType>
struct AdjListNetworkArc { 
    int adjvex;          // 邻接点索引
    WeightType weight;   // 边权重
    AdjListNetworkArc<WeightType>* nextarc; // 下一条边指针

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
	int vexNum;         //当前顶点数
	int vexMaxNum;      //最大顶点容量
	int arcNum;         //当前边数
	AdjListNetWorkVex<ElemType,WeightType>* vexTable; //顶点表
	mutable Status* tag;                             //顶点标记数组
	WeightType infinity;
public:
	template <class ElemType, class WeightType>
	friend WeightType findMaxEdgeInPath(int u, int v, const AdjListUndirNet<ElemType, WeightType>& mst);

	AdjListUndirNet(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	AdjListUndirNet(int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	~AdjListUndirNet();

	void Clear();      //清空图
	bool IsEmpty();    //判断图是否为空
	AdjListUndirNet& operator=(const AdjListUndirNet<ElemType,WeightType>& copy);//赋值运算符重载
	void Display() const;  //打印图的信息

	int GetVexNum() const; //获取当前顶点的数量
	int GetArcNum() const; //获取当前边的数量
	void InsertVex(const ElemType& e);             //插入顶点
	void InsertArc(int v1, int v2, WeightType w);  //插入边
	void DeleteVex(const ElemType& d);             //删除顶点
	void DeleteArc(const int v1, int v2);          //删除边
	int FirstAdjVex(int v) const;                  //求顶点v的第一个邻接点的序号
	int NextAdjVex(int v1, int v2) const;          //求顶点v1的下一个邻接点序号
	void SetWeight(int v1, int v2, WeightType w);  //添加边的权重
	WeightType GetWeight(int v1, int v2) const; // 获取边的权重
	int GetDegree(int v) const;                    // 统计顶点的度
	int GetConnectedComponents() const;            // 求图的连通分量数目
	bool IsConnected(int u, int v) const;          // 判断连通性
	void BreakCycleMST(AdjListUndirNet<ElemType, WeightType>& mst);   // 破圈法生成最小生成树
	bool hasUniqueMinTree()const; 	// 判断是否存在唯一最小生成树
};
//构造空图
template<class ElemType, class WeightType>
AdjListUndirNet<ElemType, WeightType>::AdjListUndirNet(int vertexMaxNum, WeightType infinit) {
	if (vertexMaxNum < 0)
		throw Error("允许的顶点的最大数目不能为负！");
	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	infinity = infinit;
	tag = new Status[vertexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
}

//构造函数
template<class ElemType, class WeightType>
AdjListUndirNet<ElemType, WeightType>::AdjListUndirNet(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infinit) {
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负！");
	if (vertexMaxNum < vertexNum)
		throw Error("顶点数目不能大于允许的顶点最大数目！");
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

