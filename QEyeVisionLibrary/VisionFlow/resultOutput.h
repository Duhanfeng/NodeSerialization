#pragma once

#include <iostream>
#include <vector>

#include "nodeConnection.h"

namespace qv
{
	struct OutputSelection
	{
		std::string guid = "";
		std::string paramName = "";
		std::string cmdName = "";		//额外标识符

        OutputSelection() {};
        OutputSelection(const std::string& _guid, const std::string& _paramName)
            :guid(_guid), paramName(_paramName) {};
        OutputSelection(const std::string& _guid, const std::string& _paramName, const std::string& _cmdName)
            :guid(_guid), paramName(_paramName), cmdName(_cmdName) {};

	};

	class ResultOutputPacket
	{
	public:
		std::string startChar = "";
		std::string endChar = "";
		std::string separateChar = " ";
		std::vector<OutputSelection> selections;
		std::string vectorSeparateChar = ",";

		bool isAmplifyFloat = false;		//启用浮点数放大
		int amplifyRate = 100;				//放大倍数
		int floatLength = 2;				//保留小数点位数(不启用放大功能时使用)

	public:
		std::string getValueString(NodeConnection& connection, const OutputSelection& selection);
		std::string getOutputString(NodeConnection& connection);

	private:
		std::string getDoubleString(double value);
		std::string getVariantString(Variant* var);
	};

}
