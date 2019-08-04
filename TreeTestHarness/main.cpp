#include <QCoreApplication>
#include <QDebug>
#include <QSharedPointer>

#include "TreeIterator.h"
#include "TreeNode.h"

int getIntFromPointer(int value)
{
    QSharedPointer<int> result = QSharedPointer<int>::create(value);

    return *(result.data());
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "TESTING POINT LOGIC";
    //int test = getIntFromPointer(127);
    qDebug() << getIntFromPointer(127);

    QSharedPointer<TreeNode<int>> rootNode = QSharedPointer<TreeNode<int>>::create(TreeNode<int>(9));

    QSharedPointer<TreeNode<int>> child1 = QSharedPointer<TreeNode<int>>::create(TreeNode<int>(1));
    QSharedPointer<TreeNode<int>> child2 = QSharedPointer<TreeNode<int>>::create(TreeNode<int>(2));
    QSharedPointer<TreeNode<int>> child3 = QSharedPointer<TreeNode<int>>::create(TreeNode<int>(3));

    rootNode->addChildNode(child1);
    rootNode->addChildNode(child2);
    rootNode->addChildNode(child3);

    QSharedPointer<TreeNode<int>> grandChild1 = QSharedPointer<TreeNode<int>>::create(TreeNode<int>(4));
    QSharedPointer<TreeNode<int>> grandChild2 = QSharedPointer<TreeNode<int>>::create(TreeNode<int>(5));
    QSharedPointer<TreeNode<int>> grandChild3 = QSharedPointer<TreeNode<int>>::create(TreeNode<int>(6));

    child1->addChildNode(grandChild1);
    child2->addChildNode(grandChild2);
    child2->addChildNode(grandChild2);

    TreeIterator<int> testIter = TreeIterator<int>(rootNode);

    int count = 0;
    for(testIter.begin(); testIter.current() != testIter.end(); ++testIter)
    {
        qDebug() << testIter.current()->getValue() << " loop count: " << count;
        count++;
    }



    return a.exec();
}
