#include "matchInterface.h"
#include "genericShapeModel.h"
#include "nccModel.h"

namespace rv
{
    cv::Ptr<IShapeModel> rv::HMatchInterface::createShapeModel()
    {
        return cv::Ptr<IShapeModel>(new GenericShapeModel());
    }

    cv::Ptr<INccModel> HMatchInterface::createNccModel()
    {
        return cv::Ptr<INccModel>(new HNccModel());
    }

    cv::Ptr<IColorModel> HMatchInterface::createColorModel()
    {
        return cv::Ptr<IColorModel>();
    }

    bool HMatchInterface::find(InputReMat image, InputRegion region, const IModel& model, std::vector<MatchResult>& results) const
    {

        return model.find(image, region, results);
    }

    bool HMatchInterface::find(InputReMat image, InputRegion region, const std::vector<IModel>& models, std::vector<MatchResult>& results)
    {
        if (models.size() == 0)
        {
            return false;
        }

        const GenericShapeModel* shapeModelPtr = dynamic_cast<const GenericShapeModel*>(&models[0]);
        const HNccModel* nccModelPtr = dynamic_cast<const HNccModel*>(&models[0]);

        if (shapeModelPtr != nullptr)
        {
            std::vector<const GenericShapeModel*> shapeModels;
            for (size_t i = 0; i < models.size(); i++)
            {
                shapeModels.push_back(dynamic_cast<const GenericShapeModel*>(&models[i]));
            }

            return GenericShapeModel::find(image, region, shapeModels, results);
        }
        else if (nccModelPtr != nullptr)
        {
            std::vector<const HNccModel*> nccModels;
            for (size_t i = 0; i < models.size(); i++)
            {
                nccModels.push_back(dynamic_cast<const HNccModel*>(&models[i]));
            }

            return HNccModel::find(image, region, nccModels, results);
        }
        
        return false;
    }



}

