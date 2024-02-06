#include <iostream>
#include "behaviortree_cpp/bt_factory.h"

using BT::BehaviorTreeFactory;
using BT::TreeNode;

/*
There are 3 ways to create a node:
    1. Node Class (inheritance)
    2. Function Pointer
    3. Custom CLass (without inheritance)
*/

// #1st method: create our own action node
class ExecuteTask1 : public BT::SyncActionNode
{
public:
    ExecuteTask1(const std::string &name) : BT::SyncActionNode(name, {})
    {
    }

    // Note: we MUST override the virtual function tick()
    BT::NodeStatus tick() override
    {
        /*
        The method tick() is the place where the actual Action takes place!!
        It MUST always return a NodeStatus, i.e. RUNNING, SUCCESS or FAILURE.
        */
        std::cout << "Executing Task 1: " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

// #2nd method: Simple function that return a NodeStatus
BT::NodeStatus ExecuteTask2()
{
    std::cout << "Executing Task 2..." << std::endl;
    return BT::NodeStatus::SUCCESS;
}

// #3rd method: We want to wrap into an ActionNode the methods open() and close()
class RobotState
{
public:
    RobotState() : _start(true) {}

    BT::NodeStatus start()
    {
        _start = true;
        std::cout << "RobotState::start" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus stop()
    {
        std::cout << "RobotState::stop" << std::endl;
        _start = false;
        return BT::NodeStatus::SUCCESS;
    }

private:
    bool _start; // shared information
};

int main()
{
    // We use the BehaviorTreeFactory to register our custom nodes
    BehaviorTreeFactory factory;

    // The recommended way to create a Node is through inheritance
    factory.registerNodeType<ExecuteTask1>("ExecuteTask1");

    // Registering a SimpleActionNode using a function pointer.
    // You can use C++11 lambdas or std::bind
    // factory.registerSimpleCondition("ExecuteTask2", [&](TreeNode &) { return ExecuteTask2(); });
    factory.registerSimpleCondition("ExecuteTask2", std::bind(ExecuteTask2));

    // You can also create SimpleActionNodes using methods of a class
    RobotState robot;
    factory.registerSimpleAction("StartRobot", [&](TreeNode &)
                                 { return robot.start(); });
    factory.registerSimpleAction("StopRobot", [&](TreeNode &)
                                 { return robot.stop(); });

    // Trees are created at run-time.
    // Writing the tree in an XML file allowes to make
    // quick changes to teh BT structure without having
    // to recompile our code! it's awesome! :)
    auto tree = factory.createTreeFromFile("./../basic_tree.xml");

    // To "execute" a Tree you need to "tick" it.
    // The tick is propagated to the children based on the logic of the tree.
    tree.tickWhileRunning();

    return 0;
}
