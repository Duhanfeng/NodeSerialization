#include "ifit.h"
#include "ccore/fit.h"
#if ENABLE_HCORE

#endif

cv::Ptr<IFit> IFit::create(bool useHCore)
{
#if ENABLE_HCORE
    if (useHCore)
    {
        return cv::Ptr<IFit>();
    }
#endif

    return cv::Ptr<IFit>(new Fit());
}
