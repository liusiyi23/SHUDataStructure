#include <iostream>
#include "AdjMatrixDirNet.h"
#include "Error.h"

using namespace std;

int main() {
    try {
        // 1. 测试构造函数
        cout << "===== 1. 测试构造函数 =====" << endl;
        string cities[] = { "北京", "上海", "广州", "深圳" };
        AdjMatrixDirNet<string> net(cities, 4, 10);
        net.Display();
        cout << endl;


        // 2. 测试插入边
        cout << "===== 2. 测试插入边 =====" << endl;
        net.InsertArc(0, 1, 300);   // 北京 -> 上海 300km
        net.InsertArc(0, 2, 1200);  // 北京 -> 广州 1200km
        net.InsertArc(1, 2, 800);   // 上海 -> 广州 800km
        net.InsertArc(2, 3, 100);   // 广州 -> 深圳 100km
        net.InsertArc(3, 1, 500);   // 深圳 -> 上海 500km
        net.Display();
        cout << endl;

        // 3. 测试度计算
        cout << "===== 3. 测试度计算 =====" << endl;
        for (int i = 0; i < 4; i++) {
            cout << cities[i] << " - 出度: " << net.CountOutDegree(i)
                << ", 入度: " << net.CountInDegree(i) << endl;
        }
        cout << endl;

        // 4. 测试顶点操作
        cout << "===== 4. 测试顶点操作 =====" << endl;
        string city;
        for (int i = 0; i < 4; i++) {
            if (net.GetElem(i, city)) {  // 修正：补全右括号
                cout << "顶点" << i << ": " << city << endl;
            }
        }
        cout << "广州的索引: " << net.GetOrder("广州") << endl;

        // 插入新顶点 (修正：补全代码块)
        string newCity = "成都";
        net.InsertVertex(newCity);
        cout << "插入新顶点: " << newCity << endl;
        net.InsertArc(4, 0, 500);  // 成都 -> 北京 500km
        net.Display();
        cout << endl;

        // 5. 测试删除操作
        cout << "===== 5. 测试删除操作 =====" << endl;
        cout << "删除上海->广州的边" << endl;
        net.RemoveArc(1, 2);
        net.Display();

        cout << "删除深圳顶点" << endl;
        net.RemoveVertex(3);
        net.Display();
        cout << endl;

        // 6. 测试中心性计算
        cout << "===== 6. 测试中心性计算 =====" << endl;
        for (int i = 0; i < net.GetVexNum(); i++) {
            string cityName;
            net.GetElem(i, cityName);
            cout << cityName << " - 出度中心性: " << net.CertralityOutVex(i)
                << ", 入度中心性: " << net.CertralityInVex(i) << endl;
        }
        cout << endl;

        // 7. 测试两跳邻居
        cout << "===== 7. 测试两跳邻居 =====" << endl;
        for (int i = 0; i < net.GetVexNum(); i++) {
            string cityName;
            net.GetElem(i, cityName);
            cout << cityName << " 的两跳邻居数量: " << net.TwoHopNgh(i) << endl;
        }
        cout << endl;

        // 8. 测试拷贝构造函数和赋值运算符
        cout << "===== 8. 测试拷贝和赋值 =====" << endl;
        AdjMatrixDirNet<string> netCopy(net);
        cout << "拷贝构造的网络:" << endl;
        netCopy.Display();

        AdjMatrixDirNet<string> netAssign;
        netAssign = net;
        cout << "赋值后的网络:" << endl;
        netAssign.Display();
        cout << endl;

        // 9. 测试清空网络
        cout << "===== 9. 测试清空网络 =====" << endl;
        net.Clear();
        cout << "清空后网络是否为空? " << (net.IsEmpty() ? "是" : "否") << endl;
        net.Display();

        //10.测试健壮性
        cout << "====10.健壮性测试====" << endl;
        cout << "统计第1个点的入度" << endl;
        net.CountInDegree(1);
       

    }
    catch (Error& s) {
        cerr << s.Show() << endl;
    }

    return 0;
    
}