#include "Error.h"
#include "AdjMatrixDirNet.h"


template <class ElemType>
AdjMatrixDirNet<ElemType>::AdjMatrixDirNet(ElemType es[], int vertexNum, int vertexMaxNum) {
    if (vertexMaxNum < 0) {
        throw Error("允许的顶点最大数目不能为负!");
    }
    if (vertexMaxNum < vertexNum) {
        throw Error("顶点数目不能大于允许的顶点最大数目!");
    }

    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;

    vertexes = new ElemType[vexMaxNum];
    tag = new Status[vexMaxNum];
    arcs = new int* [vexMaxNum];
    for (int i = 0; i < vexMaxNum; ++i) {
        arcs[i] = new int[vexMaxNum];
        for (int j = 0; j < vexMaxNum; ++j) {
            arcs[i][j] = INF;//默认赋值最大
        }
    }

    for (int i = 0; i < vexNum; ++i) {
        vertexes[i] = es[i];
        tag[i] = UNVISITED;
    }
}

template <class ElemType>
AdjMatrixDirNet<ElemType>::AdjMatrixDirNet(int vertexMaxNum) {
    if (vertexMaxNum < 0) {
        throw Error("允许的顶点最大数目不能为负!");
    }
    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;

    vertexes = new ElemType[vexMaxNum];
    tag = new Status[vexMaxNum];
    arcs = new int* [vexMaxNum];
    for (int i = 0; i < vexMaxNum; ++i) {
        arcs[i] = new int[vexMaxNum];
        for (int j = 0; j < vexMaxNum; ++j) {
            arcs[i][j] = INF;
        }
    }
}


template <class ElemType>
AdjMatrixDirNet<ElemType>::AdjMatrixDirNet(const AdjMatrixDirNet& g) {
    vexNum = g.vexNum;
    vexMaxNum = g.vexMaxNum;
    arcNum = g.arcNum;

    vertexes = new ElemType[vexMaxNum];
    tag = new Status[vexMaxNum];
    arcs = new int* [vexMaxNum];
    for (int i = 0; i < vexMaxNum; ++i) {
        arcs[i] = new int[vexMaxNum];
        for (int j = 0; j < vexMaxNum; ++j) {
            arcs[i][j] = g.arcs[i][j];
        }
    }

    for (int i = 0; i < vexNum; ++i) {
        vertexes[i] = g.vertexes[i];
        tag[i] = g.tag[i];
    }
}

template <class ElemType>
AdjMatrixDirNet<ElemType>::~AdjMatrixDirNet() {
    delete[] vertexes;
    delete[] tag;
    for (int i = 0; i < vexMaxNum; ++i) {
        delete[] arcs[i];
    }
    delete[] arcs;
}

template<class ElemType>
inline void AdjMatrixDirNet<ElemType>::Clear()
{
    vexNum = 0;
    arcNum = 0;
}

template<class ElemType>
inline bool AdjMatrixDirNet<ElemType>::IsEmpty()
{
    return vexNum == 0;
}
template <class ElemType>
AdjMatrixDirNet<ElemType>& AdjMatrixDirNet<ElemType>::operator=(const AdjMatrixDirNet& g) {
    if (this != &g) {
        delete[] vertexes;
        delete[] tag;
        for (int i = 0; i < vexMaxNum; ++i) {
            delete[] arcs[i];
        }
        delete[] arcs;

        vexNum = g.vexNum;
        vexMaxNum = g.vexMaxNum;
        arcNum = g.arcNum;

        vertexes = new ElemType[vexMaxNum];
        tag = new Status[vexMaxNum];
        arcs = new int* [vexMaxNum];
        for (int i = 0; i < vexMaxNum; ++i) {
            arcs[i] = new int[vexMaxNum];
            for (int j = 0; j < vexMaxNum; ++j) {
                arcs[i][j] = g.arcs[i][j];
            }
        }

        for (int i = 0; i < vexNum; ++i) {
            vertexes[i] = g.vertexes[i];
            tag[i] = g.tag[i];
        }
    }
    return *this;
}

template <class ElemType>
int AdjMatrixDirNet<ElemType>::GetOrder(const ElemType& d) const {
    for (int i = 0; i < vexNum; ++i) {
        if (vertexes[i] == d) {
            return i;
        }
    }
    return -1;
}

template <class ElemType>
Status AdjMatrixDirNet<ElemType>::GetElem(int v, ElemType& d) const {
    if (v < 0 || v >= vexNum) {
        return NOT_PRESENT;
    }
    d = vertexes[v];
    return ENTRY_FOUND;
}

template <class ElemType>
void AdjMatrixDirNet<ElemType>::Display() const {
    cout << "顶点数: " << vexNum << ", 边数: " << arcNum << endl;
    cout << "顶点列表: ";
    for (int i = 0; i < vexNum; ++i) {
        cout << vertexes[i] << " ";
    }
    cout << "\n邻接矩阵:" << endl;

    cout << "   ";
    for (int j = 0; j < vexNum; ++j) {
        cout << vertexes[j] << "  ";
    }
    cout << " 出度" << endl;

    for (int i = 0; i < vexNum; ++i) {
        cout << vertexes[i] << " ";
        for (int j = 0; j < vexNum; ++j) {
            if (arcs[i][j] == INF) {
                cout << "∞  ";
            }
            else {
                cout << arcs[i][j] << "  ";
            }
        }
        cout << " " << CountOutDegree(i);
        cout << endl;
    }

    cout << "入度";
    for (int j = 0; j < vexNum; ++j) {
        cout << "  " << CountInDegree(j);
    }
    cout << endl;
}

template <class ElemType>
int AdjMatrixDirNet<ElemType>::GetVexNum() const {
    return vexNum;
}

template <class ElemType>
int AdjMatrixDirNet<ElemType>::CountOutDegree(int v) const {
    if (v < 0 || v >= vexNum) {
        throw Error("顶点索引越界!");
    }
    int count = 0;
    for (int j = 0; j < vexNum; ++j) {
        if (arcs[v][j] != INF) {
            count++;
        }
    }
    return count;
}

template <class ElemType>
int AdjMatrixDirNet<ElemType>::CountInDegree(int v) const {
    if (v < 0 || v >= vexNum) {
        throw Error("顶点索引越界!");
    }
    int count = 0;
    for (int i = 0; i < vexNum; ++i) {
        if (arcs[i][v] != INF) {
            count++;
        }
    }
    return count;
}

//删除顶点
template <class ElemType>
void AdjMatrixDirNet<ElemType>::RemoveVertex(int v) {
    if (v < 0 || v >= vexNum) {
        throw Error("顶点索引越界!");
    }

    vexNum--;
    for (int j = v; j < vexNum; j++) {
        vertexes[j] = vertexes[j + 1];
        tag[j] = tag[j + 1];
    }

    arcNum -= (CountOutDegree(v) + CountInDegree(v));
    for (int i = 0; i < v; i++) {
        for (int j = v; j < vexNum; j++) {
            arcs[i][j] = arcs[i][j + 1];
        }
    }
    for (int i = 0; i < v; i++) {
        for (int j = v; j < vexNum; j++) {
            arcs[j][i] = arcs[j + 1][i];
        }
    }
    for (int i = v; i <= vexNum; i++) {
        for (int j = v; j <= vexNum; j++) {
            arcs[i][j] = arcs[i + 1][j + 1];
        }
    }
}

//删除弧
template<class ElemType>
void AdjMatrixDirNet<ElemType>::RemoveArc(int v1, int v2)
{
    if (v1<0 || v1>= vexNum) {
        throw Error("v1顶点索引越界");
    }
    if (v2<0 || v2>= vexNum) {
        throw Error("v2顶点索引越界");
    }
    if (arcs[v1][v2] != INF) arcNum--;
    else arcs[v1][v2] = INF;
}

//插入弧
template<class ElemType>
void AdjMatrixDirNet<ElemType>::InsertArc(int v1, int v2, int weight)
{
    if (v1<0 || v1>= vexNum) {
        throw Error("v1顶点索引越界");
    }
    if (v2<0 || v2>= vexNum) {
            throw Error("v2顶点索引越界");
    }
    if (arcs[v1][v2] == INF) arcNum++;
    arcs[v1][v2] = weight;
}

//插入顶点
template<class ElemType>
void AdjMatrixDirNet<ElemType>::InsertVertex(ElemType& v)
{
    if (vexNum == vexMaxNum) {
        throw Error("超出最大顶点限制");
    }
    vertexes[vexNum] = v;
    tag[vexNum] = UNVISITED;
    vexNum++;
}

template<class ElemType>
int AdjMatrixDirNet<ElemType>::CertralityOutVex(int v)
{
    if (v < 0 || v >= vexNum) {
        throw Error("顶点索引越界!");
    }
    int ans = 0;
    for (int i = 0; i < vexNum; i++) {
        if (arcs[v][i] != INF)
        ans += arcs[v][i];
    }
    return ans;
}

template<class ElemType>
int AdjMatrixDirNet<ElemType>::CertralityInVex(int v)
{
    if (v < 0 || v >= vexNum) {
        throw Error("顶点索引越界!");
    }
    int ans = 0;
    for (int i = 0; i < vexNum; i++) {
        if (arcs[i][v] != INF)
        ans += arcs[i][v];
    }
    return ans;
}

template<class ElemType>
int AdjMatrixDirNet<ElemType>::TwoHopNgh(int v)
{
    if (v < 0 || v >= vexNum) {
        throw Error("顶点索引越界!");
    }
    int ans = 0;
    for (int i = 0; i < vexNum; i++) {
        if (arcs[v][i] != INF) {
            for (int j = 0; j < vexNum; j++) {
                    if (arcs[i][j] != INF && tag[j]==UNVISITED) {
                    ans++;
                    tag[j] = VISITED;
                }
            }
        }
    }
    return ans;
}
// 显式实例化模板
template class AdjMatrixDirNet<std::string>;