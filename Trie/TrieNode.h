/*
 * TrieNode.h
 *
 *  Created on: 2016年3月24日
 *      Author: smallcroco
 */

#ifndef TRIE_TRIENODE_H_
#define TRIE_TRIENODE_H_

#include <string>
#include <vector>

#define RESULT_MAX_COUNT 65535

using namespace std;

// 关键词
struct ST_node {
	string value;
	int length;
};

// 词库链表
struct ST_listNode {
	ST_node* word;
	ST_listNode* next;
};

// Trie树的结点
struct ST_trieNode {
	ST_node* value;
    ST_trieNode** arrary1; // 数组表1
    ST_trieNode** arrary2; // 数组表2
    ST_trieNode** arrary3; // 数组表3
};

// 结果记录
struct ST_result {
	int count; //
//	vector<pair<ST_node*, long> > words;
	ST_node* entry[RESULT_MAX_COUNT];
	int pos[RESULT_MAX_COUNT];
};

union character {
	struct Bit {
		unsigned char byte7:1;
		unsigned char byte6:1;
		unsigned char byte5:1;
		unsigned char byte4:1;
		unsigned char byte3:1;
		unsigned char byte2:1;
		unsigned char byte1:1;
		unsigned char byte0:1;
	}byBit;
	char byChar;
};

#endif /* TRIE_TRIENODE_H_ */
