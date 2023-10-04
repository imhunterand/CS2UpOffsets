#pragma once

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#if !_HAS_CXX17
#error "The Os-ImGui are available only with C++17 or later."
#endif

#include <iostream>
#include <exception>

/****************************************************
* Copyright (C)	: Imhunterand
* @file			: OS-ImGui_Exception.hpp
* @author		: Imhunterand
* @email		: imhunterand@cyberservices.com
* @version		: 2.0
* @date			: 2023/10/05	00:18
****************************************************/

namespace OSImGui
{
	class OSException : public std::exception
	{
	public:
		OSException():Error_("[OS-Exception] Unkown Error") {}
		OSException(std::string Error):Error_("[OS-Exception] " + Error){}
		char const* what() const throw()
		{
			return Error_.c_str();
		}
	private:
		std::string Error_ = "";
	};
}