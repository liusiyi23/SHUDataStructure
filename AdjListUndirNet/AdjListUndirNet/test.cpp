#include <iostream>
#include "AdjListUndirNet.h" 

using namespace std;


int main() {
    try {
        // 创建一个图，最多10个顶点，边权无穷大设为9999
        AdjListUndirNet<string, int> graph(10, 9999);

        // 插入顶点
        graph.InsertVex("A");
        graph.InsertVex("B");
        graph.InsertVex("C");
        graph.InsertVex("D");

        // 插入边
        graph.InsertArc(0, 1, 5);  // A-B
        graph.InsertArc(0, 2, 3);  // A-C
        graph.InsertArc(1, 2, 2);  // B-C
        graph.InsertArc(2, 3, 4);  // C-D

        // 打印图
        graph.Display();

        // 删除一条边
        cout << "\n删除边 B-C 后:" << endl;
        graph.DeleteArc(1, 2);
        graph.Display();

        // 统计连通分量
        cout << "\n连通分量数量: " << graph.GetConnectedComponents() << endl;

        // 判断连通性
        cout << "A 与 D 连通吗？" << (graph.IsConnected(0, 3) ? "是" : "否") << endl;

        // 删除一个顶点
        cout << "\n删除顶点 C 后:" << endl;
        graph.DeleteVex("C");
        graph.Display();

        // 测试最小生成树
        AdjListUndirNet<string, int> mst;
        graph.InsertVex("C");
        graph.InsertArc(1, 2, 2);  // B-C (重新插入)
        graph.InsertArc(2, 3, 4);  // C-D
        graph.BreakCycleMST(mst);

        cout << "\n最小生成树:" << endl;
        mst.Display();

        // 是否唯一最小生成树
        cout << "是否存在唯一的最小生成树: " << (graph.hasUniqueMinTree() ? "是" : "否") << endl;

    }
    catch (Error& e) {
        e.show();
    }

    return 0;
}
