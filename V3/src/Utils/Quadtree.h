#pragma once
#include "..\Core\GameObject.h"
#include <list>
#include <unordered_set>
#include <set>

/**
* @class NodeElement
* @brief Wrapper class for quadtree nodes
*
*
* @author Paolo Ferri
* @version 01
* @date 4/05/2019
* @bug No known bugs.
*/
template <class T>
class NodeElement
{
public:

	/**
	* @class Constructor
	* @pre The object does not exist
	* @post The object is created
	* @param T The data in the node
	* @param x The x position of the node
	* @param z The z position of the node
	* @param sx The width of the node
	* @param sz The height of the node
	*/
	NodeElement(T& telement, int x, int z, int sx, int sz) : element(telement), posX(x), posZ(z), sizeX(sx), sizeZ(sz){}

	/**
	* @class Constructor
	* @pre The object does not exist
	* @post The object is created
	* @param T The data in the node
	* @param x The x position of the node
	* @param z Thez position of the node
	*/
	NodeElement(T& telement, int x, int z) : element(telement), posX(x), posZ(z){}

	T element;
	int posX;
	int posZ;
	int sizeX;
	int sizeZ;
	int maxElementInNode;
};

/**
* @class NodeElementInfo
* @brief Wrapper class for quadtree nodes with extra info
*
*
* @author Paolo Ferri
* @version 01
* @date 4/05/2019
* @bug No known bugs.
*/
struct NodeElementInfo
{
	/**
	* @class Constructor
	* @pre The object does not exist
	* @post The object is created
	*/
	NodeElementInfo(){}

	/**
	* @class Constructor
	* @pre The object does not exist
	* @post The object is created
	* @param x The x position of the node
	* @param z The z position of the node
	* @param sx The width of the node
	* @param sz The height of the node
	*/
	NodeElementInfo(int x, int z, int sx, int sz) : posX(x), posZ(z), sizeX(sx), sizeZ(sz){}
	int posX;
	int posZ;
	int sizeX;
	int sizeZ;
};

/**
* @class QuadNode
* @brief Class defining a quadtree node
*
*
* @author Paolo Ferri
* @version 01
* @date 4/05/2019
* @bug No known bugs.
*/
template <class T>
class QuadNode
{
public:
	/**
	* @brief Constructor
	* @pre The object does not exist
	* @post The object is created
	* @param centerX The center x position of the node
	* @param centerY The center y position of the node
	* @param sizeX The width of the node
	* @param sizeY The height of the node
	*/
	QuadNode(int centerX, int centerY, int sizeX, int sizeY, int maxElementsInNode);

	/**
	* @brief Destructor, clears the elements
	* @pre The object must exist
	* @post The object is destorued
	*/
	~QuadNode() {/* Logger::LogInfo("Quadnode deleted");*/ };

	/**
	* @brief The width of the quadtree
	*/
	int width;

	/**
	* @brief The height of the quadtree
	*/
	int height;

	/**
	* @brief The center x position
	*/
	int centerX;

	/**
	* @brief The center y position
	*/
	int centerY;

	/**
	* @brief Maximum number of elements in a node
	*/
	int maxElements;

	/**
	* @brief Whether the node has been split
	*/
	bool isSplit;

	/**
	* @brief Reference to top left node
	*/
	QuadNode<T> *topLeft;


	/**
	* @brief Reference to top left node
	*/
	QuadNode<T> *bottomLeft;


	/**
	* @brief Reference to top right node
	*/
	QuadNode<T> *topRight;


	/**
	* @brief Reference to bottom right node
	*/
	QuadNode<T> *bottomRight;

	/**
	* @brief The list of elements in this node
	*/

	std::unordered_set<T> elements;


	/**
	* @brief Split the node and populates them with the current element
	*/
	void Split();

};

/**
* @class QuadTree
* @brief Class defining a quadtree 
* @author Paolo Ferri
* @version 01
* @date 4/05/2019
* @bug No known bugs.
*/
template <class T>
class QuadTree
{
public:
	/**
	* @brief Constructor
	* @pre The object does not exist
	* @post The object is created
	* @param centerX The center x position of the quadtree
	* @param centerY The center y position of the quadtree
	* @param sizeX The width of the node
	* @param sizeY The height of the node
	*/
	QuadTree(int centerX, int centerY, int sizeX, int sizeY, int maxElements = 10000);

	/**
	* @brief Destructor, clears the tree
	* @pre The object must exist
	* @post The object is destoryed
	*/
	~QuadTree();

	/**
	* @brief The quadtree root
	*/
	QuadNode<T>* root;

	/**
	* @brief Add element into the quadtree
	* @ T go	The element
	* @ posX	The element x position
	* @ posZ	The element z position
	*/
	void AddElement(T go, float posX, float posZ);

	/**
	* @brief Add element into the quadtree
	* @ T go	The element
	* @ posX	The element x position
	* @ posZ	The element z position
	* @ sizeX	The element width
	* @ sizeZ	The element depth/height
	*/
	void AddElement(T go, float posX, float posZ, float sizeX, float sizeZ);

	/**
	* @brief Returns the number of elements in a quadtrant (node) at world position
	* @param x	The x position in world space
	* @param x	The y position in world space
	* @return the number of elements in a quadtrant (node) at world position
	*/
	int GameObjectInQuadrant(int x, int y);

	/**
	* @brief Clear all the elements from all nodes
	*/
	void ClearNodes();

	/**
	* @brief Returns the number elements in a quadtrant (node) at world position
	* @param x	The x position in world space
	* @param x	The y position in world space
	* @return the number elements in a quadtrant (node) at world position
	*/
	std::unordered_set<T>& GameObjectsAt(int x, int y);

private:
	/**
	* @brief Recursive method to add element in the quadtree
	*/
	void AddElement(T go, float posX, float posZ, QuadNode<T>* &node);

	/**
	* @brief Recursive method to add element in the quadtree
	*/
	void AddElement(T go, float posX, float posZ, float sizeX, float sizeZ, QuadNode<T>* &node);

	/**
	* @brief Recursive method to clear elements in the quadtree
	*/
	void ClearNode(QuadNode<T>* &node);

	/**
	* @brief Recursive method to retrieve element in the quadtree
	*/
	int GameObjectInQuadrant(int x, int y, QuadNode<T>* node);

	/**
	* @brief Recursive method to add element in the quadtree
	*/
	std::unordered_set<T>& GameObjectsAt(int x, int y, QuadNode<T>* node);

	/**
	* @brief Keeps track of elements position
	*/
	std::map<T,NodeElementInfo> elementsInfo;

	/**
	* @brief Recursive method to delete nodes
	*/
	void DeleteNode(QuadNode<T>*& n);

};

template <class T>
QuadNode<T>::QuadNode(int centerX, int centerY, int sizeX, int sizeY, int maxElements) : centerX(centerX), centerY(centerY), width(sizeX), height(sizeY), maxElements(maxElements)
{
	bottomRight = nullptr;
	bottomLeft = nullptr;
	topLeft = nullptr;
	topRight = nullptr;
	isSplit = 0;	
}

template <class T>
void QuadNode<T>::Split()
{
	isSplit = 1;

	/*Logger::LogError("Split, top left", centerX - width / 4, centerY + height / 4, width / 2, height / 2);
	Logger::LogError("Split, top right", centerX + width / 4, centerY + height / 4, width / 2, height / 2);
	Logger::LogError("Split, bottom left", centerX - width / 4, centerY - height / 4, width / 2, height / 2);
	Logger::LogError("Split, bottom right", centerX + width / 4, centerY - height / 4, width / 2, height / 2);*/

	topLeft = new QuadNode<T>(centerX - width / 4, centerY + height / 4, width / 2, height / 2,maxElements);
	topRight = new QuadNode<T>(centerX + width / 4, centerY + height / 4, width / 2, height / 2, maxElements);
	bottomRight = new QuadNode<T>(centerX + width / 4, centerY - height / 4, width / 2, height / 2, maxElements);
	bottomLeft = new QuadNode<T>(centerX - width / 4, centerY - height / 4, width / 2, height / 2, maxElements);

}

template <class T>
QuadTree<T>::QuadTree(int centerX, int centerY, int sizeX, int sizeY, int maxElements)
{
	root = new QuadNode<T>(centerX, centerY, sizeX, sizeY,maxElements);
	//Logger::LogError("Quadtree created", centerX,centerY,sizeX, sizeY);

	root->Split();
}

template <class T>
QuadTree<T>::~QuadTree()
{
	DeleteNode(root);
	//Logger::LogError("Quadtree destroyed");
}

template <class T>
void QuadTree<T>::DeleteNode(QuadNode<T>*& n)
{
	if (n->isSplit)
	{
		DeleteNode(n->topLeft);
		DeleteNode(n->topRight);
		DeleteNode(n->bottomLeft);
		DeleteNode(n->bottomRight);
	}
	else
		delete n;
}

template <class T>
void QuadTree<T>::AddElement(T go, float posX, float posZ)
{
	NodeElement<T> element(go,posX,posZ);

	AddElement(element, posX, posZ, root);
}

template <class T>
void QuadTree<T>::AddElement(T go, float posX, float posZ, float sizeX, float sizeZ)
{

	AddElement(go, posX, posZ, sizeX, sizeZ, root);
}

template <class T>
int QuadTree<T>::GameObjectInQuadrant(int x, int y)
{
	return GameObjectInQuadrant(x, y, root);
}

template <class T>
std::unordered_set<T>& QuadTree<T>::GameObjectsAt(int x, int y)
{
	return GameObjectsAt(x, y, root);
}

template <class T>
std::unordered_set<T>& QuadTree<T>::GameObjectsAt(int x, int z, QuadNode<T>* node)
{
	if (node->isSplit)
	{
		if (x <= node->centerX && z >= node->centerY)
			return GameObjectsAt(x, z, node->topLeft);

		if (x <= node->centerX && z <= node->centerY)
			return GameObjectsAt(x, z, node->bottomLeft);

		if (x >= node->centerX && z >= node->centerY)
			return GameObjectsAt(x, z, node->topRight);

		if (x >= node->centerX && z <= node->centerY)
			return GameObjectsAt(x, z, node->bottomRight);
	}
	else
		return node->elements;
}

template <class T>
int QuadTree<T>::GameObjectInQuadrant(int x, int z, QuadNode<T>* node)
{
	if (node->isSplit)
	{
		if (x <= node->centerX && z >= node->centerY)
			return GameObjectInQuadrant(x, z, node->topLeft);

		if (x <= node->centerX && z <= node->centerY)
			return GameObjectInQuadrant(x, z, node->bottomLeft);

		if (x >= node->centerX && z >= node->centerY)
			return GameObjectInQuadrant(x, z, node->topRight);

		if (x >= node->centerX && z <= node->centerY)
			return GameObjectInQuadrant(x, z, node->bottomRight);
	}
	else
		return node->elements.size();
}

template <class T>
void QuadTree<T>::AddElement(T go, float posX, float posZ, QuadNode<T>* &node)
{
	if (node->isSplit)
	{
		//Logger::LogError("Added object at", posX, posZ);


		if (posX <= node->centerX && posZ >= node->centerY)
		{
			//Logger::LogError("Added top left");
			AddElement(go, posX, posZ, node->topLeft);
		}

		if (posX <= node->centerX && posZ <= node->centerY)
		{
			//Logger::LogError("Added bottom left");

			AddElement(go, posX, posZ, node->bottomLeft);
		}

		if (posX >= node->centerX && posZ >= node->centerY)
		{
			//Logger::LogError("Added top right");

			AddElement(go, posX, posZ, node->topRight);
		}

		if (posX >= node->centerX && posZ <= node->centerY)
		{
			//Logger::LogError("Added bottom right");

			AddElement(go, posX, posZ, node->bottomRight);
		}
	}
	else
	{

		node->elements.insert(go);
	}
}


template <class T>
void QuadTree<T>::AddElement(T go, float posX, float posZ, float sizeX, float sizeZ, QuadNode<T>* &node)
{
	if (node->isSplit)
	{
		//Logger::LogError("Added object at", posX, posZ);

		if (posX - sizeX / 2 <= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX - sizeX / 2 >= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX - sizeX / 2 >= node->centerX && posZ - sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX - sizeX / 2 <= node->centerX && posZ - sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);

		/**/
		if (posX + sizeX / 2 <= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX + sizeX / 2 >= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX + sizeX / 2 >= node->centerX && posZ - sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX + sizeX / 2 <= node->centerX && posZ - sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);

		/**/
		if (posX - sizeX / 2 <= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX - sizeX / 2 >= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX - sizeX / 2 >= node->centerX && posZ + sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX - sizeX / 2 <= node->centerX && posZ + sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);

		/**/
		if (posX + sizeX / 2 <= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX + sizeX / 2 >= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX + sizeX / 2 >= node->centerX && posZ + sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX + sizeX / 2 <= node->centerX && posZ + sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);



	}
	else
	{
		if (node->elements.size() >= node->maxElements - 1)
		{
			node->Split();
		//	Logger::LogWarning("Had to split it further");
			for (auto it = node->elements.begin(); it != node->elements.end(); it++)
			{
				NodeElementInfo* info = &elementsInfo[(*it)];
				AddElement((*it), info->posX, info->posZ, info->sizeX, info->sizeZ,node);
			}

			AddElement(go, posX, posZ, sizeX, sizeZ,node);

			node->elements.clear();


		}
		else
		{

			elementsInfo[go] = NodeElementInfo(posX, posZ, sizeX, sizeZ);
			node->elements.insert(go);
		}
	}
}


template <class T>
void QuadTree<T>::ClearNodes()
{
	ClearNode(root);

}

template <class T>
void QuadTree<T>::ClearNode(QuadNode<T>* &node)
{
	node->elements.clear();

	if (node->isSplit)
	{
		ClearNode(node->topLeft);
		ClearNode(node->topRight);
		ClearNode(node->bottomLeft);
		ClearNode(node->bottomRight);
	}
}

