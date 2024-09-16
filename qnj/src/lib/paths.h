#ifndef __PATHS_H_
#define __PATHS_H_

#include <string>
int page_views = 0;

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

bool is_ss_user_file(const std::string& filename)
{
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".png";
}

int page_views_amount(const std::string& path)
{
    std::string paths[] = {"/", "/login", "/signup", "/dashboard", "/dashboard/payloads", "/dashboard/connections", "/dashboard/data-0x00", "/dashboard/statics", "/dashboard/settings", "/dashboard/profile"};
    for (const auto p : paths)
    {
        if (path == p)
        {
            page_views += 1;
        }
    }

    return page_views;
}

#endif