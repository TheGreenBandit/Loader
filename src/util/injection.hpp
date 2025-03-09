#pragma once
#include "../common.hpp"
#include "../gui/gui.hpp"
//#include "../../includes/BlackBone/src/BlackBone/Process/RPC/RemoteFunction.hpp"
//#include "../../includes/BlackBone/src/BlackBone/Process/Process.h"

namespace fs = std::filesystem;

namespace loader
{
	inline class injection
	{
	public:
		/*blackbone::Process process;
		blackbone::ModuleDataPtr module_data;
		blackbone::ThreadPtr thread;*/

		//util
		intptr_t get_root_domain();
		intptr_t get_domain();
		intptr_t thread_attatch(intptr_t domain);
		void security_set_mode(int mode);
		intptr_t image_open_from_data_full(const std::vector<char>& image);
		intptr_t assembly_load_from_full(intptr_t raw_image);
		intptr_t assembly_get_image(intptr_t assembly);
		intptr_t get_class_from_name(intptr_t image, const char* name_space, const char* class_name);
		intptr_t get_method_from_name(intptr_t class_id, const char* method_name);
		intptr_t runtime_invoke_method(intptr_t method_id);
		int thread_detach(intptr_t domain);
		NTSTATUS unlink_assembly(intptr_t domain);
	public:
		void auto_inject();
		void inject();
		void mono_inject(etab tab);
		void inject_dll(etab tab, std::string_view npath = "", std::string_view nwindow = "");
	} g_inject;
}