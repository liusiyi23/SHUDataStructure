#pragma once
#include <iostream>
using namespace std;
enum Status {
    SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
    NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};

// 通用异常类                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
//#define MAX_ERROR_MESSAGE_LEN 100
class Error
{
private:
    // 数据成员
    string message;// 异常信息

public:
    //  方法声明
    Error(const string mes = "一般性异常!");	// 构造函数 
    ~Error(void) {};					// 析构函数	
    string Show() const;					// 显示异常信息
};
