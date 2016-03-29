/*
 * Trie.cpp
 *
 *  Created on: 2016年3月24日
 *      Author: smallcroco
 */

#include "Trie.h"
#include <iostream>

using namespace std;

/*
 * @Function Name: Trie
 * @Description: 为Trie开一个256的根数组，每一个数组元素用来存放关键词的开头字节，
 * 		初始化这个256数组为空
 */
Trie::Trie() {
	for (int i = 0; i < 256; i++) {
		root[i] = NULL;
	}

	word_end = NULL;
}

/*
 * @Fucntion Name: ~Trie
 * @Description: 释放trie树
 */
Trie::~Trie() {
	word_end = NULL;
	for (int i=0; i<256; i++) {
		if (root[i] != NULL) {
			freeTrieNode(root[i]);
			root[i] = NULL;
		}
	}
}

/*
 * @Function Name: freeTrieNode
 * @Parameter [in] ST_trieNode* node: trie的结点
 * @Description: 释放trie树的结点
 */
void Trie::freeTrieNode(ST_trieNode* node) {
	if (node == NULL) {
		return ;
	}

	if (node->arrary1 != NULL) {
		for(int i = 0; i < 128; i++) {
			if (node->arrary1[i] != NULL) {
				freeTrieNode(node->arrary1[i]);
			}
		}
		delete[] node->arrary1;
		node->arrary1 = NULL;
	}

	if (node->arrary2 != NULL) {
		for(int i = 0; i < 64; i++) {
			if (node->arrary2[i] != NULL) {
				freeTrieNode(node->arrary2[i]);
			}
		}
		delete[] node->arrary2;
		node->arrary2 = NULL;
	}

	if (node->arrary3 != NULL) {
		for(int i = 0; i < 64; i++) {
			if (node->arrary3[i] != NULL) {
				freeTrieNode(node->arrary3[i]);
			}
		}
		delete[] node->arrary3;
		node->arrary3 = NULL;
	}

	if (node->value != NULL) {
		delete node->value;
		node->value = NULL;
	}

	delete node;
}

/*
 * @Function Name: insertRoot
 * @Parameter [in] unsigned char c: 要插入到根数组的字节
 * ＠Description: 将每一个关键词语的开头字节插入到trie树的根数组中去
 * @Return Value: 如果数组中已经存在该值则返回false，相返则返回true
 */
bool Trie::insertRoot(unsigned char c) {

	if (root[c] == NULL) { // root数组中没有些元素

		// 新建结点
		ST_trieNode* node = new ST_trieNode;
		node->value = NULL;
		node->arrary1 = NULL;
		node->arrary2 = NULL;
		node->arrary3 = NULL;

		root[c] = node;
		word_end = node;

		return true;
	} else { // root数组中已经存在此元素
		word_end = root[c];

		return false;
	}
}

/*
 * @Function Name: insertNode
 * @Parameter [in] unsigned char c: 要插入的字节
 * @Description: 将关键词语头字节以后的其它字节插入到trie中，根据UTF8的编码分三种情况：
 * 		1：如果是英文字符，则插入0～127数组中
 * 		2：如果是汉字的头一个字节，则插入到192～255字节中去
 * 		3：如果是汉字的除头字节外的其它字节，则插入到128~191字节中去
 * @Return Value: 如果此字节值已经存在，则返回false，相反则返回true
 */
bool Trie::insertNode(unsigned char c) {
	// 如果是0~127
	if (c < 128) {
		// 查看数组是否存，不存在则分配
		if (word_end->arrary1 == NULL) {
			word_end->arrary1 = new ST_trieNode*[128];
			for (int i = 0; i < 128; i++) {
				word_end->arrary1[i] = NULL;
			}
		}

		// 查看数组相应下标是否存在此值
		if (word_end->arrary1[c] == NULL) {
			ST_trieNode* node = new ST_trieNode;
			node->value = NULL;
			node->arrary1 = NULL;
			node->arrary2 = NULL;
			node->arrary3 = NULL;

			word_end->arrary1[c] = node;
			word_end = node;

			return true;
		} else {
			word_end = word_end->arrary1[c];

			return false;
		}

	} else if (c <192) {
		// 查看数组是否存，不存在则分配
		if (word_end->arrary2 == NULL) {
			word_end->arrary2 = new ST_trieNode*[64];
			for(int i = 0; i < 64; i++) {
				word_end->arrary2[i] = NULL;
			}
		}

		// 查看数组相应下标是否存在此值
		if (word_end->arrary2[(c-128)] == NULL) {
			ST_trieNode* node = new ST_trieNode;
			node->value = NULL;
			node->arrary1 = NULL;
			node->arrary2 = NULL;
			node->arrary3 = NULL;

			word_end->arrary2[(c-128)] = node;
			word_end = node;

			return true;
		} else 	{
			word_end = word_end->arrary2[(c-128)];

			return false;
		}
	} else {
		// 查看数组是否存，不存在则分配
		if (word_end->arrary3 == NULL) {
			word_end->arrary3 = new ST_trieNode*[64];
			for (int i = 0; i < 64; i++) {
				word_end->arrary3[i] = NULL;
			}
		}

		// 查看数组相应下标是否存在此值
		if (word_end->arrary3[c-192] == NULL) {
			ST_trieNode* node = new ST_trieNode;
			node->value = NULL;
			node->arrary1 = NULL;
			node->arrary2 = NULL;
			node->arrary3 = NULL;

			word_end->arrary3[(c-192)] = node;
			word_end = node;

			return true;
		} else {
			word_end = word_end->arrary3[(c-192)];

			return false;
		}
	}
}

/*
 * @Function Name: setWordEnd
 * @Parameter [in] ST_node* word: 关键词语对象
 * @Description: 设置一个关键词语的结尾标志
 */
void Trie::setWordEnd(ST_node* word) {
	word_end->value = word;
	word_end = NULL;
}

/*
 * @Function Name: findRoot
 * @Parameter [in] unsigned char c: 要查找根字节
 * @Description: 查找trie树的根结点
 */
ST_trieNode* Trie::findRoot(unsigned char c) {
	word_end = root[c];

	return word_end;
}

/*
 * @Function Name: findNode
 * @Parameter [in] unsigned char c: 要查找的字节
 * @Description: 根据上一个trie的节点(word_end)查找其子结点是否存在相应字节
 * @Return Value: 返回查找到的当前trie结点
 */
ST_trieNode* Trie::findNode(unsigned char c) {
	if (c > 191) {
		if (word_end->arrary3 != NULL) {
			word_end = word_end->arrary3[(c-192)];
		} else {
			word_end =  NULL;
		}
	} else if (c > 127) {
		if (word_end->arrary2 != NULL) {
			word_end = word_end->arrary2[(c-128)];
		} else {
			word_end =  NULL;
		}
	} else {
		if (word_end->arrary1 != NULL) {
			word_end = word_end->arrary1[c];
		} else {
			word_end =  NULL;
		}
	}

	return word_end;
}
