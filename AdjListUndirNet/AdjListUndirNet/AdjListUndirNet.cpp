
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <stdexcept>
#include "AdjListUndirNet.h"


// ��������
template <class ElemType, class WeightType>
AdjListUndirNet<ElemType, WeightType>::~AdjListUndirNet() {
    Clear();
    delete[] vexTable;
    delete[] tag;
}

// ���ͼ
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::Clear() {
    for (int i = 0; i < vexNum; ++i) {
        AdjListNetworkArc<WeightType>* p = vexTable[i].firstarc;
        while (p != nullptr) {
            AdjListNetworkArc<WeightType>* temp = p->nextarc;
            delete p;
            p = temp;
        }
        vexTable[i].firstarc = NULL;
    }
    vexNum = 0;
    arcNum = 0;
}

// �ж�ͼ�Ƿ�Ϊ��
template <class ElemType, class WeightType>
bool AdjListUndirNet<ElemType, WeightType>::IsEmpty() {
    return vexNum == 0;
}

// ��ֵ���������
template <class ElemType, class WeightType>
AdjListUndirNet<ElemType, WeightType>& AdjListUndirNet<ElemType, WeightType>::operator=(
    const AdjListUndirNet<ElemType, WeightType>& copy) {
    if (this != &copy) {
        Clear();
        vexMaxNum = copy.vexMaxNum;
        infinity = copy.infinity;
        delete[] vexTable;
        delete[] tag;
        vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
        tag = new Status[vexMaxNum];
        vexNum = copy.vexNum;
        arcNum = copy.arcNum;
        // ���ƶ�������
        for (int i = 0; i < vexNum; ++i) {
            vexTable[i].data = copy.vexTable[i].data;
            tag[i] = copy.tag[i];
            // ���Ʊ���Ϣ
            AdjListNetworkArc<WeightType>* p = copy.vexTable[i].firstarc;
            AdjListNetworkArc<WeightType>* q = NULL;
            while (p != NULL) {
                AdjListNetworkArc<WeightType>* newArc = new AdjListNetworkArc<WeightType>(
                    p->adjvex, p->weight);
                if (vexTable[i].firstarc == NULL) {
                    vexTable[i].firstarc = newArc;
                }
                else {
                    q->nextarc = newArc;
                }
                q = newArc;
                p = p->nextarc;
            }
        }
    }
    return *this;
}

// ��ӡͼ����Ϣ
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::Display() const {
    cout << "���������ڽӱ��ʾ:" << endl;
    cout << "������: " << vexNum << ", ����: " << arcNum << endl;
    for (int i = 0; i < vexNum; ++i) {
        cout << vexTable[i].data << " -> ";
        AdjListNetworkArc<WeightType>* p = vexTable[i].firstarc;
        while (p != NULL) {
            cout << "(" << vexTable[p->adjvex].data << ", " << p->weight << ") ";
            p = p->nextarc;
        }
        cout << endl;
    }
}

// ��ȡ��ǰ������
template <class ElemType, class WeightType>
int AdjListUndirNet<ElemType, WeightType>::GetVexNum() const {
    return vexNum;
}

// ��ȡ��ǰ����
template <class ElemType, class WeightType>
int AdjListUndirNet<ElemType, WeightType>::GetArcNum() const {
    return arcNum;
}

// ���붥��
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::InsertVex(const ElemType& e) {
    if (vexNum >= vexMaxNum) {
        throw Error("ͼ�Ķ��������ܳ���������������");
    }
    vexTable[vexNum].data = e;
    vexTable[vexNum].firstarc = NULL;
    tag[vexNum] = UNVISITED;
    vexNum++;
}

// �����
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w) {
    if (v1 < 0 || v1 >= vexNum) {
        throw Error("v1���Ϸ�!");
    }
    if (v2 < 0 || v2 >= vexNum) {
        throw out_of_range("v2���Ϸ�!");
    }
    if (v1 == v2) {
        throw invalid_argument("v1���ܵ���v2��");
    }
    // �����Ƿ��Ѵ���
    AdjListNetworkArc<WeightType>* p = vexTable[v1].firstarc;
    while (p != NULL) {
        if (p->adjvex == v2) {
            throw Error("���Ѵ��ڣ�");
        }
        p = p->nextarc;
    }
    vexTable[v1].firstarc = new AdjListNetworkArc<WeightType>(v2, w, vexTable[v1].firstarc);
    vexTable[v2].firstarc = new AdjListNetworkArc<WeightType>(v1, w, vexTable[v2].firstarc);
    arcNum++;
}

// ɾ������
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::DeleteVex(const ElemType& d) {
    int index = -1;
    for (int i = 0; i < vexNum; ++i) {
        if (vexTable[i].data == d) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        throw Error("�Ҳ������㣡");
    }
    AdjListNetworkArc<WeightType>* p = vexTable[index].firstarc;
    while (p != NULL) {
        int adjVex = p->adjvex;
        AdjListNetworkArc<WeightType>* q = vexTable[adjVex].firstarc;
        AdjListNetworkArc<WeightType>* pre = NULL;
        while (q != NULL) {
            if (q->adjvex == index) {
                if (pre == NULL) {
                    vexTable[adjVex].firstarc = q->nextarc;
                }
                else {
                    pre->nextarc = q->nextarc;
                }
                delete q;
                arcNum--;
                break;
            }
            pre = q;
            q = q->nextarc;
        }
        AdjListNetworkArc<WeightType>* temp = p;
        p = p->nextarc;
        delete temp;
    }
    vexTable[index].firstarc = NULL;
    //�ƶ������������ȱ
    for (int i = index; i < vexNum - 1; ++i) {
        vexTable[i] = vexTable[i + 1];
        // �����ڽӱ���ָ���ƶ�����ı�
        p = vexTable[i].firstarc;
        while (p != NULL) {
            if (p->adjvex == i + 1) {
                p->adjvex = i;
            }
            p = p->nextarc;
        }
    }
    vexNum--;
    //�����ڽӱ��д���index�Ķ�������
    for (int i = 0; i < vexNum; ++i) {
        p = vexTable[i].firstarc;
        while (p != NULL) {
            if (p->adjvex > index) {
                p->adjvex--;
            }
            p = p->nextarc;
        }
    }
}

// ɾ����
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::DeleteArc(int v1, int v2) {
    if (v1 < 0 || v1 >= vexNum) {
        throw Error("v1���Ϸ�!");
    }
    if (v2 < 0 || v2 >= vexNum) {
        throw out_of_range("v2���Ϸ�!");
    }
    bool found = false;
    AdjListNetworkArc<WeightType>* p = vexTable[v1].firstarc;// ɾ��v1��v2�ı�
    AdjListNetworkArc<WeightType>* pre = NULL;
    while (p != NULL) {
        if (p->adjvex == v2) {
            if (pre == NULL) {
                vexTable[v1].firstarc = p->nextarc;
            }
            else {
                pre->nextarc = p->nextarc;
            }
            delete p;
            found = true;
            break;
        }
        pre = p;
        p = p->nextarc;
    }
    p = vexTable[v2].firstarc;// ɾ��v2��v1�ı�
    pre = NULL;
    while (p != NULL) {
        if (p->adjvex == v1) {
            if (pre == NULL) {
                vexTable[v2].firstarc = p->nextarc;
            }
            else {
                pre->nextarc = p->nextarc;
            }
            delete p;
            break;
        }
        pre = p;
        p = p->nextarc;
    }

    if (found) {
        arcNum--;
    }
}

// ��ȡ����v�ĵ�һ���ڽӵ����
template <class ElemType, class WeightType>
int AdjListUndirNet<ElemType, WeightType>::FirstAdjVex(int v) const {
    if (v < 0 || v >= vexNum) {
        throw Error("v���Ϸ���");
    }
    if (vexTable[v].firstarc == NULL) {
        return -1;
    }
    return vexTable[v].firstarc->adjvex;
}

// ��ȡ����v1�����v2����һ���ڽӵ����
template <class ElemType, class WeightType>
int AdjListUndirNet<ElemType, WeightType>::NextAdjVex(int v1, int v2) const {
    if (v1 < 0 || v1 >= vexNum) {
        throw Error("v1���Ϸ�!");
    }
    if (v2 < 0 || v2 >= vexNum) {
        throw out_of_range("v2���Ϸ�!");
    }
    AdjListNetworkArc<WeightType>* p = vexTable[v1].firstarc;
    while (p != NULL) {
        if (p->adjvex == v2 && p->nextarc != NULL) {
            return p->nextarc->adjvex;
        }
        p = p->nextarc;
    }
    return -1;

}

// ��ӱߵ�Ȩ��
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w) {
    if (v1 < 0 || v1 >= vexNum) {
        throw Error("v1���Ϸ�!");
    }
    if (v2 < 0 || v2 >= vexNum) {
        throw out_of_range("v2���Ϸ�!");
    }
    bool found = false;
    AdjListNetworkArc<WeightType>* p = vexTable[v1].firstarc;// ����v1��v2�ı�Ȩ��
    while (p != NULL) {
        if (p->adjvex == v2) {
            p->weight = w;
            found = true;
            break;
        }
        p = p->nextarc;
    }
    p = vexTable[v2].firstarc;// ����v2��v1�ı�Ȩ��
    while (p != NULL) {
        if (p->adjvex == v1) {
            p->weight = w;
            break;
        }
        p = p->nextarc;
    }
}
template <class ElemType, class WeightType>
WeightType AdjListUndirNet<ElemType, WeightType>::GetWeight(int v1, int v2) const {
    if (v1 < 0 || v1 >= vexNum || v2 < 0 || v2 >= vexNum) {
        throw out_of_range("��������Խ��");
    }
    AdjListNetworkArc<WeightType>* p = vexTable[v1].firstarc;
    while (p != NULL) {
        if (p->adjvex == v2) {
            return p->weight;
        }
        p = p->nextarc;
    }
    throw out_of_range("�߲�����");
}


// ͳ�ƶ���Ķ�
template <class ElemType, class WeightType>
int AdjListUndirNet<ElemType, WeightType>::GetDegree(int v) const {
    if (v < 0 || v >= vexNum) {
        throw out_of_range("v���Ϸ���");
    }
    int degree = 0;
    AdjListNetworkArc<WeightType>* p = vexTable[v].firstarc;
    while (p != NULL) {
        degree++;
        p = p->nextarc;
    }
    return degree;
}

// ��ͼ����ͨ������Ŀ��DFS��
template <class ElemType, class WeightType>
int AdjListUndirNet<ElemType, WeightType>::GetConnectedComponents() const {
    if (vexNum == 0) return 0;
    int count = 0;
    bool* visited = new bool[vexNum];
    for (int i = 0; i < vexNum; ++i) {
        visited[i] = false;
    }
    auto dfs = [&](int v, auto&& dfs) -> void { // ����DFS����
        visited[v] = true;
        AdjListNetworkArc<WeightType>* p = vexTable[v].firstarc;
        while (p != NULL) {
            if (!visited[p->adjvex]) {
                dfs(p->adjvex, dfs);
            }
            p = p->nextarc;
        }
        };
    for (int i = 0; i < vexNum; ++i) {// ��ÿ��δ���ʵĶ������DFS
        if (!visited[i]) {
            dfs(i, dfs);
            count++;
        }
    }
    delete[] visited;
    return count;
}




// �����������ж���ͨ��
template <class ElemType, class WeightType>
bool AdjListUndirNet<ElemType, WeightType>::IsConnected(int u, int v) const {
    if (u < 0 || u >= vexNum || v < 0 || v >= vexNum) {
        return false;
    }
    if (u == v) {
        return true;
    }
    bool* visited = new bool[vexNum]();
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        AdjListNetworkArc<WeightType>* p = vexTable[current].firstarc;
        while (p != NULL) {
            int adj = p->adjvex;
            if (adj == v) {
                delete[] visited;
                return true;
            }
            if (!visited[adj]) {
                visited[adj] = true;
                q.push(adj);
            }
            p = p->nextarc;
        }
    }
    delete[] visited;
    return false;
}

// ��Ȧ��������С������
template <class ElemType, class WeightType>
void AdjListUndirNet<ElemType, WeightType>::BreakCycleMST(AdjListUndirNet<ElemType, WeightType>& mst) {
    if (GetConnectedComponents() != 1) {
        throw Error("ͼ����ͨ���޷�������С��������");
    }
    
    mst = *this;

    while (mst.GetArcNum() > mst.GetVexNum() - 1) {
        WeightType maxWeight = mst.infinity;
        int u_max = -1, v_max = -1;

        // ���ҵ�ǰ����
        for (int i = 0; i < mst.vexNum; ++i) {
            AdjListNetworkArc<WeightType>* p = mst.vexTable[i].firstarc;
            while (p != NULL) {
                if (i < p->adjvex && p->weight > maxWeight) {
                    maxWeight = p->weight;
                    u_max = i;
                    v_max = p->adjvex;
                }
                p = p->nextarc;
            }
        }

        if (u_max == -1) break;

        // ɾ���߲������ͨ��
        mst.DeleteArc(u_max, v_max);
        if (!mst.IsConnected(u_max, v_max)) {
            mst.InsertArc(u_max, v_max, maxWeight);
        }
    }
}


// �����������ҵ���������u��v·���ϵ�����Ȩ
template <class ElemType, class WeightType>
WeightType findMaxEdgeInPath(int u, int v, const AdjListUndirNet<ElemType, WeightType>& mst) {
    int n = mst.GetVexNum();
    vector<WeightType> maxWeight(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(u);
    maxWeight[u] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        AdjListNetworkArc<WeightType>* p = mst.vexTable[current].firstarc;
        while (p != NULL) {
            int adj = p->adjvex;
            if (parent[adj] == -1 && adj != u) {
                parent[adj] = current;
                maxWeight[adj] = max(maxWeight[current], p->weight);
                if (adj == v) {
                    return maxWeight[v];
                }
                q.push(adj);
            }
            p = p->nextarc;
        }
    }
    throw Error("����������ͨ");
}

// �ж��Ƿ����Ψһ��С������
template <class ElemType, class WeightType>
bool AdjListUndirNet<ElemType, WeightType>::hasUniqueMinTree() const {
    if (GetConnectedComponents() != 1) return false;

    // ����MST
    AdjListUndirNet<ElemType, WeightType> temp = *this;
    AdjListUndirNet<ElemType, WeightType> mst;
    temp.BreakCycleMST(mst);

    // �ռ�MST�ı�
    set<pair<int, int>> treeEdges;
    for (int i = 0; i < mst.vexNum; ++i) {
        AdjListNetworkArc<WeightType>* p = mst.vexTable[i].firstarc;
        while (p) {
            if (i < p->adjvex) {
                treeEdges.insert({ i, p->adjvex });
            }
            p = p->nextarc;
        }
    }

    // ��������
    for (int i = 0; i < vexNum; ++i) {
        AdjListNetworkArc<WeightType>* p = vexTable[i].firstarc;
        while (p) {
            int j = p->adjvex;
            if (i < j && !treeEdges.count({ i, j })) {
                WeightType maxInPath = findMaxEdgeInPath(i, j, mst);
                if (p->weight == maxInPath) {
                    return false;
                }
            }
            p = p->nextarc;
        }
    }
    return true;
}
template class AdjListUndirNet<string, int>;