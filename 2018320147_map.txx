/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 5. 9
  *
  */

// destructor
#include<string>
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap()
{
	// ToDo
	for (unsigned int i = 0; i<capacity; i++) {
		HashMapElemType* a = ht[i];
		while (a != NULL) {
			HashMapElemType* now = a;
			a = a->link;
			delete now;
		}
		ht[i] = NULL;
		delete[] ht[i];
	}
	delete[] ht;
	mapsize = 0;
}

template <class HashMapElemType>
HashMapElemType*
HashMap<HashMapElemType>::find(const KeyType k)
{
	// ToDo
	int valu = hashfunction(k);
	HashMapElemType* now = ht[valu];
	while (now != NULL) {
		if (now->key == k) {
			return now;
		}
		now = now->link;
	}
	return NULL;
}

template <class HashMapElemType>
void
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v)
{
	// ToDo
	int valu = hashfunction(k);
	HashMapElemType* now = ht[valu];
	if (now == NULL) {
		now = new HashMapElemType;
		now->key = k;
		now->val = v;
		now->link = NULL;
		ht[valu] = now;
		mapsize++;
		return;
	}
	while (true) {
		if (now->key == k) {
			now->val = v;
			return;
		}
		if (now->link != NULL) now = now->link;
		else {
			HashMapElemType* bb = new HashMapElemType;
			bb->key = k;
			bb->val = v;
			now->link = bb;
			mapsize++;
			return;
		}
	}
}

template <class HashMapElemType>
bool
HashMap<HashMapElemType>::remove(const KeyType k)
{
	// ToDo
	int valu = hashfunction(k);
	HashMapElemType* now = ht[valu];
	if (now == NULL) return false;
	else if (now->key == k) { ht[valu] = now->link; delete now; mapsize--; return true; }
	HashMapElemType* a = now->link;
	while (a != NULL) {
		if (a->key == k) {
			now->link = a->link;
			delete a;
			mapsize--;
			return true;
		}
		now = now->link;
		a = now->link;
	}
	return false;
}

template <class HashMapElemType>
unsigned int
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
	// ToDo	
	unsigned int hash_val = 0;
	int cnt = 0;
	for (char c : k) {
		cnt++;
		if (cnt % 2 == 1) hash_val += c;
		else hash_val += ((unsigned int)c) << 8;
	}
	hash_val = hash_val%divisor;
	return hash_val;
}

template <class HashMapElemType>
void
HashMap<HashMapElemType>::print()
{
	// ToDo
	if (mapsize == 0) return;
	HashMapElemType* res = new HashMapElemType[mapsize];
	
	int ind = 0;
	for (unsigned int i = 0; i < capacity; i++) {
		if (ht[i] != NULL) {
			HashMapElemType* a = ht[i];
			while (a != NULL) {
				res[ind].key = a->key;
				res[ind].val = a->val;
				ind++;
				a = a->link;
			}
		}
	}

	
	for (int k = 0; k < mapsize-1; k++) {
		for (int u = k+1; u < mapsize; u++) {
			if (res[k].val < res[u].val) {
				HashMapElemType b = res[u];
				res[u] = res[k];
				res[k] = b;
			}
		}
	}
	for (unsigned int j = 0; j < mapsize; j++) {
		std::cout << res[j].key << ':' << res[j].val << '\n';
	}
	delete[]res;
	return;
}