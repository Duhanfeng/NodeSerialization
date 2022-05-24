#include "iimgproc.h"
#include "ccore/imgproc.h"

namespace rv
{
    cv::Ptr<IImageProc> rv::IImageProc::create(bool useHCore)
    {
#if ENABLE_HCORE
        if (useHCore)
        {
            return cv::Ptr<IImageProc>(new ImageProc());
        }
#endif

        return cv::Ptr<IImageProc>(new ImageProc());
    }
}
