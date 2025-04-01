#include "Error.h"
#include<iostream>
#include <string>
//#include <climits> 
using namespace std;

// 通用异常类的实现部分
Error::Error(const string mes)
// 操作结果：由mes构构通用异常对象
{
    message = mes;				// 复制异常信息
}

string Error::Show()const
// 操作结果：显示异常信息
{
    return message ;			// 显示异常信息	
}