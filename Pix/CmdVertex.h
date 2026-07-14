#pragma once

#include "Command.h"

class CmdVertex : public Command
{
	public:
		const char* GetName() override
		{
			return "Vertex";
		}
		const char* GetDescription() override
		{
			return 
				"Vertex(x, y)\n" //2D
				"Vertex(x, y, z)\n" //3D
				"- r, g, b\n"; //Color
			    "\n"
				"- adds  vertex to the primitives manager before render";
		}

		bool Execute(const std::vector<std::string>& params) override;
};
