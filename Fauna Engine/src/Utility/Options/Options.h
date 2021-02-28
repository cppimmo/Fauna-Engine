#pragma once

#include <string>

namespace Fuana 
{
	// use auto
	class Options
	{
		class Resolution 
		{
		public:
			Resolution();
			Resolution(const uint32_t width, const uint32_t height);
		public:
			uint32_t width;
			uint32_t height;
		};
		struct GfxConfig
		{
			
		};
	public:
		static bool LoadOptions(const std::string& config_file, Options& option_cfg);
		
		// obtain reference to each member
		Resolution& GetRes();
	private:
		Resolution screen_res;
	}
	
}
