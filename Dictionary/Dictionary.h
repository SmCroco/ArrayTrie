/*
 * Dictionary.h
 *
 *  Created on: 2016年3月24日
 *      Author: smallcroco
 */

#ifndef DICTIONARY_DICTIONARY_H_
#define DICTIONARY_DICTIONARY_H_

#include "Trie.h"
#include <string>

using namespace std;

class Dictionary {
public:
	Dictionary();
	~Dictionary();

	bool ReadDictionary(string path);
	bool InitDictionary(ST_listNode* list);

	void ReadFile(string path);
	void ReadContent(const unsigned char* content, long length);

private:
	ST_listNode* wordList; // 词库
	Trie* trie; // trie树

public:
 	ST_result result; // 结果集
};

#endif /* DICTIONARY_DICTIONARY_H_ */
