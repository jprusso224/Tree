#ifndef TREENODE_H
#define TREENODE_H

#include "tree_global.h"

#include <QSharedPointer>
#include <QVector>
#include <QDebug>

template <class T>
/**

 * @brief The TreeNode class
 *
 * Templated Tree data structure build using Qt.
 *
 * Author: John P Russo
 * Date Created: 8/3/19
 * Last Modified: 8/3/19
 *
 */
class TREESHARED_EXPORT TreeNode
{
public:
    TreeNode(const T & value)
    {
        m_value = value;
    }

    ~TreeNode()
    {
        m_children.clear();
    }

    bool hasParent() const
    {
        return m_pParent.isNull() == false;
    }

    bool hasChildren() const
    {
        return m_children.isEmpty() == false;
    }

    bool hasAdjacentSibling() const
    {
        bool hasSibling = false;

        //If this isn't true something is broken
        if(m_pParent->hasChildren())
        {
            QVector<QSharedPointer<TreeNode<T>>> potentialSiblings = m_pParent->getChildNodes();

            typename QVector<QSharedPointer<TreeNode<T>>>::iterator iter;
            for(iter = potentialSiblings.begin(); iter != potentialSiblings.end(); ++iter)
            {
                //is self
                if((iter)->data() == this)
                {
                    typename QVector<QSharedPointer<TreeNode<T>>>::iterator next = ++iter;
                    if(next != potentialSiblings.end())
                    {
                        hasSibling = true;
                    }
                    break;
                }
            }
        }

        return hasSibling;
    }


    void setParent(QSharedPointer<TreeNode<T>> parent)
    {
        m_pParent = parent;
    }

    bool addChildNode(QSharedPointer<TreeNode<T>> treeNode)
    {
        bool childAdded = false;

        if(treeNode.isNull() == false)
        {
            if(m_children.contains(treeNode) == false)
            {
                treeNode->setParent(QSharedPointer<TreeNode<T>>(this));
                m_children.append(treeNode);
                childAdded = true;
            }
            else
            {
                qDebug() << "Error: Insert failed, child already exists";
            }
        }
        else
        {
            qDebug() << "Error: Cannot add null pointer to tree.";
        }

        return childAdded;
    }

    QSharedPointer<TreeNode<T>> getParentNode()
    {
        return m_pParent;
    }

    QVector<QSharedPointer<TreeNode<T>>> getChildNodes()
    {
        return m_children;
    }

    QSharedPointer<TreeNode<T>> getAdjacentSibling()
    {
        QSharedPointer<TreeNode<T>> adjacentSibling;

        //If this isn't true something is broken
        if(m_pParent->hasChildren())
        {
            QVector<QSharedPointer<TreeNode<T>>> potentialSiblings = m_pParent->getChildNodes();

            typename QVector<QSharedPointer<TreeNode<T>>>::iterator iter;
            for(iter = potentialSiblings.begin(); iter != potentialSiblings.end(); ++iter)
            {
                //is self
                if((iter)->data() == this)
                {
                    typename QVector<QSharedPointer<TreeNode<T>>>::iterator next = ++iter;
                    if(next != potentialSiblings.end())
                    {
                        adjacentSibling = *(next);
                    }

                    break;
                }
            }
        }

        return adjacentSibling;
    }

    const T & getValue() const
    {
        return m_value;
    }

private:
    QVector<QSharedPointer<TreeNode<T>>> m_children;
    QSharedPointer<TreeNode<T>> m_pParent;
    T m_value;
};

#endif // TREENODE_H
