#include "resultOutput.h"

std::string qv::ResultOutputPacket::getDoubleString(double value)
{
	if (isAmplifyFloat)
	{
		return std::to_string((int)std::round(value * amplifyRate));
	}
	else
	{
		char buff[512] = { 0 };
		if (floatLength < 1)
		{
			sprintf(buff, "%d", (int)std::round(value));
		}
		else if (floatLength == 1)
		{
			sprintf(buff, "%.1f", value);
		}
		else if (floatLength == 2)
		{
			sprintf(buff, "%.2f", value);
		}
		else
		{
			sprintf(buff, "%.3f", value);
		}

		return std::string(buff);
	}

	return std::string();
}

std::string qv::ResultOutputPacket::getVariantString(Variant* var)
{
	if (var == nullptr)
	{
		return "";
	}

	std::string varString;

    Variant::VariantType type = var->type();
	switch (type)
	{
	case qv::Variant::VariantType::Int:
	{
        const std::vector<int>& value = var->getIntArray();
		for (int i = 0; i < (int)value.size(); i++)
		{
			varString += std::to_string(value[i]);
			if (i != (int)value.size() - 1)
			{
				varString += vectorSeparateChar;
			}
		}
		break;
	}
	case qv::Variant::VariantType::Double:
	{
        const std::vector<double>& value = var->getDoubleArray();
        for (int i = 0; i < (int)value.size(); i++)
		{
			varString += getDoubleString(value[i]);
			if (i != (int)value.size() - 1)
			{
				varString += vectorSeparateChar;
			}
		}
		break;
	}	
	case qv::Variant::VariantType::String:
	{
        const std::vector<std::string>& value = var->getStringArray();
        for (int i = 0; i < (int)value.size(); i++)
		{
			varString += value[i];
			if (i != (int)value.size() - 1)
			{
				varString += vectorSeparateChar;
			}
		}
		break;
	}
	case qv::Variant::VariantType::Point:
	{
        const std::vector<qv::Point2D>& value = var->getPointArray();
        for (int i = 0; i < (int)value.size(); i++)
		{
			varString += getDoubleString(value[i].x) + vectorSeparateChar + getDoubleString(value[i].y);
			if (i != (int)value.size() - 1)
			{
				varString += vectorSeparateChar;
			}
		}
		break;
	}
	case qv::Variant::VariantType::Pose:
	{
        const std::vector<qv::Pose2D>& value = var->getPoseArray();
        for (int i = 0; i < (int)value.size(); i++)
		{
			varString += getDoubleString(value[i].point.x) + vectorSeparateChar + getDoubleString(value[i].point.y) + vectorSeparateChar + getDoubleString(value[i].theta);
			if (i != (int)value.size() - 1)
			{
				varString += vectorSeparateChar;
			}
		}
		break;
	}
	case qv::Variant::VariantType::Line:
		break;
	case qv::Variant::VariantType::Circle:
		break;
	case qv::Variant::VariantType::Rect:
		break;
	default:
		break;
	}

	return varString;
}

std::string qv::ResultOutputPacket::getValueString(NodeConnection& connection, const OutputSelection& selection)
{
	Variant* var = connection.getCurrentNodeVariant(selection.guid, selection.paramName);
	
	return getVariantString(var);
}

std::string qv::ResultOutputPacket::getOutputString(NodeConnection& connection)
{
	std::string output = startChar;
	 
	for (int i = 0; i < (int)selections.size(); i++)
	{
		output += getValueString(connection, selections[i]);

		if (i != (int)selections.size() - 1)
		{
			output += separateChar;
		}
	}

	output += endChar;

	return output;
}
