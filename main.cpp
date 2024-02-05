#include <iostream>
#include "behaviortree_cpp/bt_factory.h"
// file that contains the custom nodes definitions
#include "my_nodes.h"
using namespace MyNodes;

using BT::BehaviorTreeFactory;
using BT::TreeNode;

/*
There are 3 ways to create a node:
    1. Node Class (inheritance)
    2. Function Pointer
    3. Custom CLass (without inheritance)
*/

int main()
{
    // We use the BehaviorTreeFactory to register our custom nodes
    BehaviorTreeFactory factory;

    // The recommended way to create a Node is through inheritance
    factory.registerNodeType<ApproachObject>("ApproachObject");

    // Registering a SimpleActionNode using a function pointer.
    // You can use C++11 lambdas or std::bind
    factory.registerSimpleCondition("CheckBattery", [&](TreeNode &)
                                    { return CheckBattery(); });
    factory.registerSimpleCondition("Backup", std::bind(Backup));

    // You can also create SimpleActionNodes using methods of a class
    TaskInterface task;
    factory.registerSimpleAction("StartTask", [&](TreeNode &)
                                 { return task.start(); });
    factory.registerSimpleAction("CloseTask", [&](TreeNode &)
                                 { return task.close(); });

    // Trees are created at run-time
    auto tree = factory.createTreeFromFile("./../decorator_tree.xml");

    // To "execute" a Tree you need to "tick" it.
    // The tick is propagated to the children based on the logic of the tree.
    tree.tickWhileRunning();

    return 0;
}
