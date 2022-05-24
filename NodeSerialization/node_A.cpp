#include "node_A.h"
#include <boost/serialization/export.hpp>

//BOOST_CLASS_EXPORT_IMPLEMENT(Node)
BOOST_CLASS_EXPORT_IMPLEMENT(NodeA)


void NodeA::run()
{
    std::cout << "NodeA" << std::endl;
};