#pragma once

#include "Command.h"

class CmdBeginDraw : public Command
{
	public:
		const char* GetName() override
		{
			return "BeginDraw";
		}
		const char* GetDescription() override
		{
			return 
				"BeginDraw(topology, applyTransform)\n"
				"\n"
				"- starts storing vertices\n"
				"- topology (point, line, triangle)\n";
			"- optional) applyTransform (true, false) - whether to apply the current matrix stack transform to the vertices";
		}
		bool Execute(const std::vector<std::string>& params) override;
};