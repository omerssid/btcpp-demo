namespace MyNodes
{
    // #1st method: create our own action node
    // custom sync action node without ports
    class ApproachObject : public BT::SyncActionNode
    {
    public:
        ApproachObject(const std::string &name) : BT::SyncActionNode(name, {})
        {
        }

        // Note: we MUST override the virtual function tick()
        BT::NodeStatus tick() override
        {
            /*
            The method tick() is the place where the actual Action takes place!!
            It MUST always return a NodeStatus, i.e. RUNNING, SUCCESS or FAILURE.
            */
            std::cout << "ApproachObject: " << this->name() << std::endl;
            if (this->name() == "approach_object_failure")
                return BT::NodeStatus::FAILURE;
            return BT::NodeStatus::SUCCESS;
        }
    };

    // #2nd method: Simple function that return a NodeStatus
    BT::NodeStatus CheckBattery()
    {
        std::cout << "[ Battery: OK ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus Backup()
    {
        std::cout << "[ApproachObject: Failed] Backing up..." << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    // #3rd method: We want to wrap into an ActionNode the methods open() and close()
    class TaskInterface
    {
    public:
        TaskInterface() : _start(true) {}

        BT::NodeStatus start()
        {
            _start = true;
            std::cout << "TaskInterface::start" << std::endl;
            return BT::NodeStatus::SUCCESS;
        }

        BT::NodeStatus close()
        {
            std::cout << "TaskInterface::close" << std::endl;
            _start = false;
            return BT::NodeStatus::SUCCESS;
        }

    private:
        bool _start; // shared information
    };
}