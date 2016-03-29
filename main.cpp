/*
 * main.cpp
 *
 *  Created on: 2016年3月24日
 *      Author: smallcroco
 */
#include "Dictionary.h"
#include <iostream>

using namespace std;

int main() {

	// 词库文件路径
	string path = "common-1.txt";

	// 初始化词库
	Dictionary dictionary;
	dictionary.ReadDictionary(path);

	// 文件内容
	string fileContent = "小羊肖恩全棉短袖T恤A5（男童）（110-130） 芥末绿色";
	fileContent += "长春市长春药店铺面前方面馆（末尾逐字删除测试效果）";
	fileContent += "中国人民银行决定，自2012年6月8日起下调金融机构人民币存贷款基准利率。金融机构一年期存款基准利率下调0.25个百分点，一年期贷款基准利率下调0.25个百分点；其他各档次存贷款基准利率及个人住房公积金存贷款利率相应调整。";

	time_t begin, end;

	begin = clock();

	for (int i = 0; i < 1000000; i++) {
//	for (int i = 0; i < 1; i++) {
		// 读取文件内容
		dictionary.ReadContent((const unsigned char*)fileContent.c_str(), fileContent.length());
//		dictionary.ReadFile(filepath);
	}

	end = clock();

	cout<<"runtime: "<<double(end-begin)/CLOCKS_PER_SEC<<endl;

	cout<<dictionary.result.count<<endl;

	for (int i = 0; i<dictionary.result.count; i++) {
		cout<<dictionary.result.entry[i]->value<<dictionary.result.pos[i]<<endl;
	}

	return 0;
}


