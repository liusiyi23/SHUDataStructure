#pragma once
#include "Error.h"
#include <iostream>
#include <cstring>
#include <climits> 
const int INF = INT_MAX;
using namespace std;


template <class ElemType>
class AdjMatrixDirNet {
protected:
    int vexNum;//顶点数目
    int vexMaxNum; //最大顶点数目
    int arcNum;//边数
    int** arcs;//邻接矩阵
    ElemType* vertexes;//顶点数组
    mutable Status* tag;//顶点状态

public:
    AdjMatrixDirNet(ElemType es[], int vertexNum, int vertexMaxNum = 100);//已知顶点数组的构造函数
    AdjMatrixDirNet(int vertexMaxNum = 100); //默认构造函数
    AdjMatrixDirNet(const AdjMatrixDirNet& g); //拷贝构造函数
    ~AdjMatrixDirNet(); //析构函数

    void Clear(); //清空图
    bool IsEmpty(); //判空
    AdjMatrixDirNet& operator=(const AdjMatrixDirNet& g); //赋值运算符重载
    int GetOrder(const ElemType& d) const; //获取顶点d的索引
    Status GetElem(int v, ElemType& d) const; //获取顶点d的元素值
    void Display() const; //打印图的信息
    int GetVexNum() const; //获取当前顶点数量

    int CountOutDegree(int v) const;//统计顶点v的出度
    int CountInDegree(int v) const;//统计顶点v的入度   

    void RemoveVertex(int v);//删除顶点v
    void RemoveArc(int v1, int v2);//删除弧
    void InsertArc(int v1, int v2, int weight);//插入弧
    void InsertVertex(ElemType& v);//添加顶点

    int CertralityOutVex(int v);//加权出度中心性
    int CertralityInVex(int v);//加权入度中心性
    int TwoHopNgh(int v);//2-hop的邻居数量
};
