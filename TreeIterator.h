#ifndef TREE_H
#define TREE_H

#include "tree_global.h"

#include "TreeNode.h"

#include <QSharedPointer>

/**
 * @brief The TreeIterator class
 *
 * Templated class for iterating over a tree of TreeNode<T>'s
 *
 * Example Usage:
 *
 * TreeIterator iter;
 * for(iter.begin(); iter.current() != iter.end(); ++iter)
 * {
 *      //Perform operations with iter->current() here.
 * }
 *
 * Author: John P Russo
 * Date Created: 8/3/19
 * Last Modified: 8/3/19
 *
 */
template <class T>
class TREESHARED_EXPORT TreeIterator
{
public:
    TreeIterator(QSharedPointer<TreeNode<T>> rootTreeNode)
    {
        m_pRootNode = rootTreeNode;
        m_pCurrentNode = rootTreeNode;
    }

    ~TreeIterator(){}

    QSharedPointer<TreeNode<T>> begin()
    {
        return m_pRootNode;
    }
    QSharedPointer<TreeNode<T>> current()
    {
        return m_pCurrentNode;
    }
    QSharedPointer<TreeNode<T>> end()
    {
        return m_pEndNode;
    }

    /**
     * @brief operator ++
     * @return next TreeNode in the iteration.
     *
     * Parses top-to-bottom and left-to-right
     * Uses the following order:
     *
     *     1
     *    | \
     *   2  5
     *  | \  \
     * 3  4  6
     *
     */
    QSharedPointer<TreeNode<T>>& operator++()
    {
        //First we check to see if this node has any childrem
        //If so, we move down into the next level of the tree.
        if(m_pCurrentNode->hasChildren())
        {
            m_pCurrentNode = m_pCurrentNode->getChildNodes().first();
        }

        //If this node has no children, we then check to see if
        //this node has any siblings. If so, we move horizontally in the tree.
        else if(m_pCurrentNode->hasAdjacentSibling())
        {
            m_pCurrentNode = m_pCurrentNode->getAdjacentSibling();
        }

        //If this node has no children nor siblings, we move up the tree
        //and check the parent (if we have one.)
        else if(m_pCurrentNode->hasParent())
        {
            //If the parent has a sibling. We move horizontally to
            //the parents next sibling.
            if(m_pCurrentNode->getParentNode()->hasAdjacentSibling())
            {
                m_pCurrentNode = m_pCurrentNode->getParentNode()->getAdjacentSibling();
            }
            //If the parent is on orphan, we've reached the end of the tree.
            else
            {
                m_pCurrentNode = m_pEndNode;
            }
        }

        //If for any reason a node returns null, end the iteration.
        if(m_pCurrentNode.isNull())
        {
            m_pCurrentNode = m_pEndNode;
        }

        //IF we make it back to the root node, stop.
        //This allows a TreeIterator to only iterate
        //on subsets of a tree.
        if(m_pCurrentNode == m_pRootNode)
        {
            m_pCurrentNode = m_pEndNode;
        }

        return m_pCurrentNode;
    }

private:
    QSharedPointer<TreeNode<T>> m_pRootNode;
    QSharedPointer<TreeNode<T>> m_pCurrentNode;
    QSharedPointer<TreeNode<T>> m_pEndNode;
};

#endif // TREE_H
