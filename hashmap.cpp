/*
 * hashmap.cpp
 *
 *  Created on: Nov 5, 2018
 *      Author: murthk5
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstddef>
#include <chrono>
#include "hashmap.h"

#include "Jenkins.cpp"

template<class T, class U>
MyHashmap<T, U>::MyHashmap()
				{


					for(i=0;i<MAX_SPACE;i++)
					{
						hashArray[i] = NULL;
					}
					for(i=0;i<MAX_SPACE;i++)
						{
						m_collVector[i]=0;
						}
				}

template<class T, class U>
void MyHashmap<T, U>::inorder(struct Hash<T, U> *root)
			{
				if(root == NULL)
					return;
			    if (root != NULL)
			    {
			        inorder(root->left);
			        cout<<root->key<<", ";
			        inorder(root->right);
			    }
			}

template<class T, class U>
void MyHashmap<T, U>::insertTree(struct Hash<T, U>* node, T keyTemp, U valTemp)
			{

				if (keyTemp < node->key)
				{
						if(node->left != NULL)
						{
							insertTree(node->left, keyTemp, valTemp);
						}
						else
						{
							struct Hash<T, U> *temp = new Hash<T, U>;
							temp->key=keyTemp;
							temp->val=valTemp;
							node->left=temp;
							(node->left)->left=NULL;
							(node->left)->right=NULL;
							return;
						}
				}
				if(keyTemp > node->key)
				{
					if(node->right != NULL)
					{
						insertTree(node->right, keyTemp,valTemp);
					}
					else
					{
						struct Hash<T,U> *temp = new Hash<T, U>;
						temp->key=keyTemp;
						temp->val=valTemp;
						node->right=temp;
						(node->right)->left=NULL;
						(node->right)->right=NULL;
						return;
					}
				}
			}



template<class T, class U>
void MyHashmap<T, U>:: find(T keyTemp, struct Hash<T,U> **loc, struct Hash<T,U> *node)
			{
			    Hash<T,U> *ptr;

			    if (node == NULL)
			    {
			        *loc = NULL;

			        return;
			    }
			    if (keyTemp == node->key)
			    {

			        *loc = node;

			        return;
			    }
			    if (keyTemp < node->key)
			        ptr = node->left;
			    else
			        ptr = node->right;

			    while (ptr != NULL)
			    {
			        if (keyTemp == ptr->key)
			        {
			            *loc = ptr;

			            return;
			        }

			        if (keyTemp < ptr->key)
			            ptr = ptr->left;
				else
				    ptr = ptr->right;
			    }
			    *loc = NULL;

			}



template<class T, class U>
U MyHashmap<T, U>:: get(const T& x)
	{
		T keyTemp=x;
		U retVal;
		 Hash<T,U> *location1=NULL;
		for(int i=0;i<MAX_SPACE;i++)
		{
			find(keyTemp, &location1, hashArray[i]);
			if (location1 != NULL)
			{
				retVal = location1->val;
				return retVal;
			}
		}
		cout<<"Key not found, Select another Key. Error: \n";
	}


template<class T, class U>
Hash<T, U>* MyHashmap<T, U>:: FindMax(Hash<T,U>* root)
			{
			    while(root->right != NULL)
			    {
			        root = root->right;
			    }
			    return root;
			}




template<class T, class U>
Hash<T, U>* MyHashmap<T, U>:: DeleteNodeInBST(Hash<T,U> *root,T keyTemp)
			{
			   if(keyTemp<root->key)
			   {
				   root->left = DeleteNodeInBST(root->left, keyTemp);
			   }
			    else if (keyTemp> root->key)
			    {
			    	root->right = DeleteNodeInBST(root->right, keyTemp);

			    }
			    else
			    {
			    	if(root->right == NULL && root->left == NULL)
			    	{
			    		delete root;
			    		root=NULL;
			    	}
			    	else if(root->right == NULL)
			    	{

			    		Hash<T,U>* temp = root;
			    		root = root->left;

			    		delete temp;
			    	}
			    	else if(root->left == NULL)
			    	{
			    		Hash<T,U>* temp = root;
			    		root= root->right;
			    		delete temp;
			    	}

			    	else
			    	{

			    		Hash<T,U>* temp = FindMax(root->left);
			    		root->key = temp->key;
			    		root->val = temp->val;

			    		root->left = DeleteNodeInBST(root->left, temp->key);
			    	}
			    }
			    return root;
			}



template<class T, class U>
STATUS MyHashmap<T, U>:: insert(const T& x, U& y,uint32_t mode)
						{
					uint32_t initVal=3;
					T keyTemp=x;
					U valTemp=y;
					cout<<"key is "<<keyTemp;
					if(hashArray[mode] == NULL)
					{
						hashArray[mode]=new Hash<T,U>;
						if(!hashArray[mode])
						{
							cout<<"Memory allocation failed";
							return MEM_ALLOC_FAIL;
						}
						m_count+=1;
						hashArray[mode]->key=x;
						hashArray[mode]->val=y;
						hashArray[mode]->left = NULL;
						hashArray[mode]->right = NULL;
						return SUCCESS;
					}
					else
					{
						m_count+=1;
						m_collis+=1;
						m_collVector[mode]+=1;

						insertTree(hashArray[mode], keyTemp, valTemp);
						return SUCCESS;
					}
				}



template<class T, class U>
STATUS MyHashmap<T, U>:: findAndInsert(const T& x, U& y)
				{
					T keyTemp=x;
					U valTemp=y;
					STATUS status;
					Hash<T,U> *location1=NULL;
					uint32_t arr1[]={uint32_t(keyTemp)};
					uint32_t initVal=33;
					uint32_t size1=(sizeof(arr1)/sizeof(uint32_t));
					uint32_t index_check = JenkinsHash(arr1, size1, initVal);
					uint32_t mode1=index_check % MAX_SPACE;
					if(hashArray[mode1] == NULL)
					{
						status = insert(keyTemp, valTemp,mode1);
					}
					else
					{
							find(keyTemp, &location1, hashArray[mode1]);
							if (location1 != NULL)
							{
								cout<<"I'm in collsion\n";
								return DUP_KEY;
							}
							 status = insert(keyTemp, valTemp,mode1);
					}

					return status;
				}




template<class T, class U>
bool MyHashmap<T, U>:: remove(const T& x)
{
					int i;
					T keyDel=x;
					Hash<T,U> *location1=NULL;
					const uint32_t arr1[]={uint32_t(keyDel)};
					uint32_t initVal=33;
					uint32_t size1=(sizeof(arr1)/sizeof(uint32_t));
					uint32_t index_check = JenkinsHash(arr1, size1, initVal);		//compute hash using jenkinns;
					uint32_t mode1=index_check % MAX_SPACE;
					find(keyDel, &location1, hashArray[mode1]);
					if (location1 != NULL)
							{
								m_count-=1;
								hashArray[mode1] = DeleteNodeInBST(hashArray[mode1], keyDel);
								return true;
							}
					else
						return false;
}




template<class T, class U>
uint32_t MyHashmap<T, U>:: size()
				{
						return m_count;
				}

template<class T, class U>
uint32_t MyHashmap<T, U>:: getTotalNumberOfCollision()
				{
						return m_collis;
				}

template<class T, class U>
uint32_t MyHashmap<T, U>:: getNumberOfCollisionPerSlot(uint32_t slotNumber)
				{
					return m_collVector[slotNumber];
				}


template<class T, class U>
uint32_t* MyHashmap<T, U>:: printCollisionStatistics()
				{
					return m_collVector;
				}


template<class T, class U>
MyHashmap<T,U>::ForwardIter::ForwardIter(Hash<T, U>* ptr,int i,MyHashmap<T,U>& owner)
{
	o=&owner;
	move=ptr;
	temp=move;
	while(temp->left != NULL)
		temp=temp->left;
	index=i;

}
template<class T, class U>
MyHashmap<T,U>::ForwardIter::ForwardIter(MyHashmap<T,U>& owner,int ie)
{
	endIndex=ie;
	o=&owner;

	endIndex=ie;
	endNode->val=o->hashArray[ie]->val;
	endNode->key=o->hashArray[ie]->key;
	endNode->left=o->hashArray[ie]->left;
	endNode->right=o->hashArray[ie]->right;
	while(endNode->right!= NULL)
		endNode=endNode->right;

}
template<class T, class U>
Hash<T, U>* MyHashmap<T,U>::ForwardIter::findParent(Hash<T,U>* temp)
{
	Hash<T, U>* parent=NULL;
	Hash<T, U>* node=move;
						int val = temp->key;
						while (node != NULL)
						{
							if (val < node->key)
							{
								parent = node;
								node = node->left;
							}
							else if (val > node->key)
							{
								parent=node;
								node = node->right;
							}
							else
								break;
						}
						return parent;
					}

template<class T, class U>
Hash<T, U>* MyHashmap<T,U>::ForwardIter:: init()
					{
						for(int i=index+1;i<=endIndex;i++)
						{
							if(o->hashArray[i] != NULL)
							{
								index=i;
								return o->hashArray[i];
							}
						}
					}



template<class T, class U>
typename MyHashmap<T, U>::ForwardIter& MyHashmap<T,U>::ForwardIter:: operator ++ ()
					{

						Hash<T,U> *p;

						if(temp->right != NULL)
						{
							temp=temp->right;
							while(temp->left != NULL)
								temp=temp->left;
						}
						else
						{
							p=findParent(temp);

							while (p != NULL && temp == p->right)
							{
								temp = p;
								p = findParent(p);
							}
							       temp = p;

							       if(temp==NULL)
							       {
							    	   move=init();
							    	   temp=move;
							    	   while(temp->left != NULL)
							    		   temp=temp->left;
							       }

						}

						return *this;
				}

template<class T, class U>
bool MyHashmap<T,U>::ForwardIter:: operator != (const ForwardIter& rhs)
					{

						return (temp->key != rhs.endNode->key);
					}

template<class T, class U>
T& MyHashmap<T,U>::ForwardIter:: operator*()
						{
								return temp->key;
						}

template<class T, class U>
bool MyHashmap<T,U>::ForwardIter:: operator == (const ForwardIter& rhs)
		{
					return (temp->key == rhs.endNode->key);
		}


template<class T, class U>
typename MyHashmap<T, U>::ForwardIter MyHashmap<T, U>:: begin()
{

	for(int i=0;i<MAX_SPACE;i++)
	{
		if(hashArray[i] != NULL)
		{

			MyHashmap<T,U>::ForwardIter itr(hashArray[i],i,*this);
			return itr;
		}
	}

}


template<class T, class U>
typename MyHashmap<T, U>::ForwardIter MyHashmap<T, U>:: end()
{
	for(int j=MAX_SPACE-1;j>0;j--)
	{
		if(hashArray[j]!=NULL)
		{

			MyHashmap<T,U>::ForwardIter itr2(*this,j);
			return itr2;
		}
	}
}


















template<class T, class U>
MyHashmap<T, U>::~MyHashmap()
					{
						for(int i=0;i<MAX_SPACE;i++)
						{
							if(hashArray[i]!=NULL)
								delete hashArray[i];

						}
						delete[] m_collVector;
						cout<<"Destructor called\n";
					}

