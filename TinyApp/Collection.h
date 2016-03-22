#pragma once

/// <summary>
/// �ֵ���
/// </summary>
class Trie
{
	struct TrieNode
	{
		TrieNode*	m_branch[26];//26����֧
		CHAR*		m_pzText;//��֧�����ڵ�ĵ���
	};
public:
	Trie();
	~Trie();
	BOOL Insert(LPCSTR pzValue, LPCSTR pzKey);
	BOOL Remove(LPCSTR pzValue);
private:
	TrieNode* m_pRoot;
};