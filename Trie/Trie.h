/*
 * Trie.h
 *
 *  Created on: 2016年3月24日
 *      Author: smallcroco
 */

#ifndef TRIE_TRIE_H_
#define TRIE_TRIE_H_

#include "TrieNode.h"

class Trie {
public:
	Trie();
	~Trie();

	// 构建trie树
	bool insertRoot(unsigned char c);
	bool insertNode(unsigned char c);
	void setWordEnd(ST_node* word);

	// 查找trie树根结点
	ST_trieNode* findRoot(unsigned char c);
	ST_trieNode* findNode(unsigned char c);

private:
	void freeTrieNode(ST_trieNode* node);

private:
	ST_trieNode* root[256];	// Trie树的根数组
	ST_trieNode* word_end; // 关键词的结尾标志
};

#endif /* TRIE_TRIE_H_ */
