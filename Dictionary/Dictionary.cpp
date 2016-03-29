/*
 * Dictionary.cpp
 *
 *  Created on: 2016年3月24日
 *      Author: smallcroco
 */

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

Dictionary::Dictionary() {
	// TODO Auto-generated constructor stub
	wordList = NULL;

	result.count = 0;

	trie = new Trie();
}

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
}

/*
 * @Function Name: ReadDictionary
 * @Parameter [in] string path: 词库文件路径
 * @Description: 读取词库文件
 * ＠Return Value: 读取成功返回true, 失败返回false
 */
bool Dictionary::ReadDictionary(string path) {

	// 打开文件
	ifstream file(path.c_str());
	if (file.is_open()) {

		// 循环读取文件每一行
		while (!file.eof()) {
			string line;
			getline(file, line);

			// 创建关键词对象
			ST_node* word = new ST_node;
			word->value = line;
			word->length = line.length();

			// 创建词库链表结点
			ST_listNode* listNode = new ST_listNode;
			listNode->word = word;
			listNode->next = wordList;

			wordList = listNode;
		}
		file.close();

		return InitDictionary(wordList);
	} else {
		cout<<"打开词库文件失败"<<endl;
		return false;
	}
}

bool Dictionary::InitDictionary(ST_listNode* list) {

	// 判断词库不为空
	if (list == NULL) {
		return false;
	}

	// 读取词库中的每一个词语
	while (list != NULL) {
		int i = 0;
		trie->insertRoot(list->word->value[i]);
		for(i = 1; (i < list->word->length && list->word->value[i] != '\r' && list->word->value[i] != 0); i++) {
			trie->insertNode(list->word->value[i]);
		}
		list->word->length = i;
		trie->setWordEnd(list->word);

		ST_listNode* p = list;
		list = list->next;

		p->next = NULL;
		p->word = NULL;
		delete p;
		p = NULL;

	}

	return true;
}

void Dictionary::ReadFile(string path) {
	ifstream file(path.c_str());
	if (!file.is_open()) {

		file.close();
	} else {
		cout<<"文件打开失败"<<endl;
	}
}

void Dictionary::ReadContent(const unsigned char* content, long length) {
	result.count = 0;
	for (int i = 0; i < length; ) {

//		// 如果字节是在过滤字节中则进行过滤
//		if (content[i] in others) {
//			continue;
//		}

		// 存在以该字节开头的词语
		ST_trieNode* word = trie->findRoot(content[i]);
		if (word != NULL) {

//			// 判断是不是单字节关键词结尾
//			if (word->value != NULL) {
//				// 加入结果集
//				result.entry[result.count] = word->value;
//				result.pos[result.count] = i;
//				result.count += 1;
//			}

			// 继续匹配下一个字节
			for (int j = i + 1; j < length; j++) {

				word = trie->findNode(content[j]);
				if (word == NULL) { // 关键词查找失败

					break;
				} else {

					if (word->value != NULL) { // 关键词查找成功, 继续往下查找

						result.entry[result.count] = word->value;
						result.pos[result.count] = i;
						result.count += 1;

					} // 查找到一个关键词语

				} // 当前字节匹配成功
			}

		} // 一个字节查找完成

		if (content[i] >223 && content[i] < 240 ) {
			i += 3;
		} else if (content[i] < 128)  {
			i += 1;
		} else if (content[i] >191 && content[i] < 224) {
			i += 2;
		} else if (content[i] > 251) {
			i += 6;
		} else if (content[i] > 247) {
			i += 5;
		}else {
			i += 4;
		}

	}
}

