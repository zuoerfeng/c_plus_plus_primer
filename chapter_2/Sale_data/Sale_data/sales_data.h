/***************************************************/
//Description:c++ primer chapter2
//Author: Zuo Lu 		Version: 1.0	Date:2017/12/06
/***************************************************/

//#ifdef VARIABLE_NAME
//    code1
//#else
//    code2
//#endif


#ifndef SALES_DATA_H  //当这个SALES_DATA_H没有被定义的时候
#define SALES_DATA_H  //定义这个SALES_DATA_H文件
#include <string>


struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
