#ifndef __PATHS_H_
#define __PATHS_H_

#include <string>

bool is_css_file(const std::string& filename) 
{
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".css";
}

bool is_js_file(const std::string& filename) 
{
    return filename.size() >= 3 && filename.substr(filename.size() - 3) == ".js";
}

bool is_png_file(const std::string& filename) 
{
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".png";
}

bool is_svg_file(const std::string& filename)
{
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".svg";
}

bool is_data_0x00_mugshot(const std::string& filename)
{
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".jpg";
}

#endif