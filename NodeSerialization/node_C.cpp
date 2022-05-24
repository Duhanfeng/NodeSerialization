#include "node_C.h"

void NodeC::run()
{
    std::cout << "NodeC" << std::endl;
};
//BOOST_CLASS_EXPORT(NodeC)
BOOST_CLASS_EXPORT_IMPLEMENT(NodeC)