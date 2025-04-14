#include <iostream>
#include "AdjListUndirNet.h" 

using namespace std;


int main() {
    try {
        // ����һ��ͼ�����10�����㣬��Ȩ�������Ϊ9999
        AdjListUndirNet<string, int> graph(10, 9999);

        // ���붥��
        graph.InsertVex("A");
        graph.InsertVex("B");
        graph.InsertVex("C");
        graph.InsertVex("D");

        // �����
        graph.InsertArc(0, 1, 5);  // A-B
        graph.InsertArc(0, 2, 3);  // A-C
        graph.InsertArc(1, 2, 2);  // B-C
        graph.InsertArc(2, 3, 4);  // C-D

        // ��ӡͼ
        graph.Display();

        // ɾ��һ����
        cout << "\nɾ���� B-C ��:" << endl;
        graph.DeleteArc(1, 2);
        graph.Display();

        // ͳ����ͨ����
        cout << "\n��ͨ��������: " << graph.GetConnectedComponents() << endl;

        // �ж���ͨ��
        cout << "A �� D ��ͨ��" << (graph.IsConnected(0, 3) ? "��" : "��") << endl;

        // ɾ��һ������
        cout << "\nɾ������ C ��:" << endl;
        graph.DeleteVex("C");
        graph.Display();

        // ������С������
        AdjListUndirNet<string, int> mst;
        graph.InsertVex("C");
        graph.InsertArc(1, 2, 2);  // B-C (���²���)
        graph.InsertArc(2, 3, 4);  // C-D
        graph.BreakCycleMST(mst);

        cout << "\n��С������:" << endl;
        mst.Display();

        // �Ƿ�Ψһ��С������
        cout << "�Ƿ����Ψһ����С������: " << (graph.hasUniqueMinTree() ? "��" : "��") << endl;

    }
    catch (Error& e) {
        e.show();
    }

    return 0;
}
