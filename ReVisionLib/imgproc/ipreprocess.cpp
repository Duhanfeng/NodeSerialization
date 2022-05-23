#include "ipreprocess.h"
#include "ccore/preprocess.h"

namespace rv
{
    cv::Ptr<IPreprocess> rv::IPreprocess::create(bool useHCore)
    {
#if ENABLE_HCORE
        if (useHCore)
        {
            return cv::Ptr<IPreprocess>(new Preprocess());
        }
#endif

        return cv::Ptr<IPreprocess>(new Preprocess());
    }
}
