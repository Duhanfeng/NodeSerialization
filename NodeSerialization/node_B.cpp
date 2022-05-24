#include "node_B.h"

void NodeB::run()
{
    std::cout << "NodeB" << std::endl;
};

//BOOST_CLASS_EXPORT(NodeB)
BOOST_CLASS_EXPORT_IMPLEMENT(NodeB)