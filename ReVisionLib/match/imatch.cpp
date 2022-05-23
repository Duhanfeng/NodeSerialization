#include "imatch.h"

#if ENABLE_HCORE
#include "hcore/matchInterface.h"
#endif


namespace rv
{
    cv::Ptr<MatchInterface> MatchInterface::create(bool useHCore)
    {
#if ENABLE_HCORE
        if (useHCore)
        {
            return cv::Ptr<MatchInterface>(new HMatchInterface());
        }
#endif

        return cv::Ptr<MatchInterface>();
    }

}