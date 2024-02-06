#include <iostream>
#include "behaviortree_cpp/bt_factory.h"
#include "my_nodes.h"

using BT::BehaviorTreeFactory;
using BT::TreeNode;

using namespace MyNodes;

int main()
{
    BehaviorTreeFactory factory;

    factory.registerNodeType<ApproachObject>("ApproachObject");

    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));
    factory.registerSimpleCondition("Backup", std::bind(Backup));

    TaskInterface task;
    factory.registerSimpleAction("StartTask", [&](TreeNode &)
                                 { return task.start(); });
    factory.registerSimpleAction("CloseTask", [&](TreeNode &)
                                 { return task.close(); });

    auto tree = factory.createTreeFromFile("./../nodes_tree.xml");

    tree.tickWhileRunning();

    return 0;
}
