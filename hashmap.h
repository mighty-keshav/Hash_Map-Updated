/*
 * hashmap.h
 *
 *  Created on: Nov 5, 2018
 *      Author: murthk5
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

//============================================================================
// Name        : hashmap_new.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : RP_HashMap.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <cstddef>

using namespace std;

#define MAX_SPACE 30

#define start_key_all 1000

#define offset_key_all 50

#define start_val_int 45
#define start_val_string "keshav_"

#define start_val_age 2
#define start_val_marks 25
#define offset_val_float 2.6

#define offset_val_int_string 2

int index,endIndex;

enum STATUS{SUCCESS,MEM_ALLOC_FAIL,DUP_KEY};

template<class T, class U>
struct Hash
				{
					T key;
					U val;
					struct Hash<T,U> *left, *right;
				};


template<class T, class U>
class MyHashmap
			{

				//friend class ForwardIter<T, U>;
				public:int i=0;

				struct Hash<T,U> *hashArray[MAX_SPACE];

				//Hash<T, U> *freeptr;

				uint32_t m_count=0;

				uint32_t *m_collVector = new uint32_t[MAX_SPACE];
				uint32_t m_collis=0;



				//--------------------------Constructor;
				public:	MyHashmap<T, U>();


			//-------------------------------- A utility function to do inorder traversal of BST
			void inorder(struct Hash<T, U>*);
			//-------------------------------- A utility function to insert a new node with given key in BST
			void insertTree(struct Hash<T, U>*, T, U);
			//--------------------------------to find for an element in the hashMap;
			void find(T, struct Hash<T,U>**, struct Hash<T,U>*);

			//---------------------------------Func to find the value of a given Key;
			U get(const T&);
			//-----------------Func to find the greatest of two child in deletion of the root node;
			Hash<T, U>* FindMax(Hash<T,U>*);
			//-----------------Func to delete a node from BST;
			Hash<T,U>* DeleteNodeInBST(Hash<T,U> *root,T keyTemp);
		//------------------------------Func to insert the key value pair into the Hashmap;
		STATUS insert(const T& x, U& y,uint32_t);
		//---------------------Func to check and insert the key value pair ;
		STATUS findAndInsert(const T&, U&);
		//----------------------Func to remove an entry from the hashmap;
		bool remove(const T&);

		// Statstical Functions
	uint32_t size();

	uint32_t getTotalNumberOfCollision();

	uint32_t getNumberOfCollisionPerSlot(uint32_t);

	uint32_t* printCollisionStatistics();

	class ForwardIter
	{
	public:
		friend class MyHashmap<T,U>;
		Hash<T, U> *endNode=new Hash<T,U>;

		Hash<T,U> *temp;
		Hash<T, U> *move;

		MyHashmap<T,U> *o;

		ForwardIter(Hash<T, U>* ptr,int i,MyHashmap<T,U>& owner);

		ForwardIter(MyHashmap<T,U>& owner,int ie);



		Hash<T, U>* findParent(Hash<T,U>* temp);

		Hash<T,U>* init();

		ForwardIter& operator ++ ();


		bool operator != (const ForwardIter& rhs);

		bool operator == (const ForwardIter& rhs);

		T& operator*();

	};

				friend class ForwardIter;

				//--------------------------->begin() and end() of iterators;
				ForwardIter begin();
				ForwardIter end();

	//---------------Destructor;
	~MyHashmap();

};





#endif /* HASHMAP_H_ */
