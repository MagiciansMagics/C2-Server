#ifndef _PATHS_HPP_
#define _PATHS_HPP_
#include "../qnj_config.h"
#include "../memory/qnj_memory_pool.hpp"
#include "../payloads/send_tcp_commands.hpp"
#include "../server_2/TCP_handle_client.hpp"
#include "../shutdown/HTTP_SERVER_SHUTDOWN.hpp"
#include "../lib/paths.h"
#include "../lib/signup_save_data.h"
#include "../networking/send_html_files.hpp"
#include "../networking/send_html_client_side.hpp"
#include "../networking/utils/get_login_credentials.hpp"
#include "../networking/Parse_stuff/parse_page.hpp"
#include "../networking/Parse_stuff/parse_file_upload.hpp"
#include "../networking/Parse_stuff/replace-characters.hpp"
#include "../networking/Parse_stuff/parse_file_for_client_side.hpp"
#include "../networking/Parse_stuff/parse-signup-page.hpp"
#include "../networking/http/DIRECT_WITH_COOKIE.hpp"
#include "../networking/http/DIRECT_TO-PAGE.hpp"
#include "../networking/http/DIRECT-REMOVE-COOKIE.hpp"
#include "../save_user_signup.h"

void get_path_handler(const std::string& path, std::string& userIdCookieValue, std::string& data0x00UserIdCookieValue, int client_socket, std::string& requestHeaders);
void post_path_handler(const std::string& path, std::string& userIdCookieValue, std::string& data0x00UserIdCookieValue, int client_socket, std::string& requestHeaders);
//auto quick_return_client_data() { return returned_client_data_string(); }
int page_views;

void path_handler(const std::string& method, const std::string& path, int client_socket, std::string& userIdCookieValue, std::string& data0x00UserIdCookieValue, std::string& requestHeaders)
{
    if (method == "GET")
    {
        get_path_handler(path, userIdCookieValue, data0x00UserIdCookieValue, client_socket, requestHeaders);
    }
    else if (method == "POST")
    {
        post_path_handler(path, userIdCookieValue, data0x00UserIdCookieValue, client_socket, requestHeaders);
    }
    else
    {
        send_html_file("/home/magician/Desktop/QNJ/web-gui/405.html", "text/html", "405 Method Not Allowed", "HTTP/1.1", client_socket);
    }
}

void get_path_handler(const std::string& path, std::string& userIdCookieValue, std::string& data0x00UserIdCookieValue, int client_socket, std::string& requestHeaders)
{
    if (path == "/")
    {
        send_html_file("/home/magician/Desktop/QNJ/web-gui/index.html", "text/html", "200 OK", "HTTP/1.1", client_socket);
    }

    else if (path == "/login" || path == "/login/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            sendRedirect("/dashboard", client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/login.html", "text/html", "200 OK", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/signup" || path == "/signup/")
    {
        send_html_file("/home/magician/Desktop/QNJ/web-gui/signup.html", "text/html", "200 OK", "HTTP/1.1", client_socket);
    }

    //##### CONTROL STUFF #####//
    else if (path == "/dashboard" || path == "/dashboard/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
            client_side_data += get_username_from_database();
            client_side_data += "</span>";
            client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
            replace_char(client_side_data, "%40", "@");
            content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/dashboard.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/connections" || path == "/dashboard/connections/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
            client_side_data += get_username_from_database();
            client_side_data += "</span>";
            client_side_data += "<span id='QNJ-CONNECTIONS-DATA-SP'>";
            client_side_data += extract_client_vector_data();
            client_side_data += "</span>";
            client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
            replace_char(client_side_data, "%40", "@");
            content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/connections.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/payloads" || path == "/dashboard/settings/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
            client_side_data += get_username_from_database();
            client_side_data += "</span>";
            client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
            replace_char(client_side_data, "%40", "@");
            content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/payloads.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/data-0x00" || path == "/dashboard/data-0x00/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            if (get_cookies_from_file(data0x00UserIdCookieValue, "/root/qnj-server/data-0x00-cookies.log"))
            {
                std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
                client_side_data += get_username_from_database();
                client_side_data += "</span>";
                client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
                replace_char(client_side_data, "%40", "@");
                content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/data-0x00-logged-in.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
            }
            else
            {
                std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
                client_side_data += get_username_from_database();
                client_side_data += "</span>";
                client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
                replace_char(client_side_data, "%40", "@");
                content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/data-0x00.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
            }
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/statics" || path == "/dashboard/statics/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
            client_side_data += get_username_from_database();
            client_side_data += "</span>";
            client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
            replace_char(client_side_data, "%40", "@");
            content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/statics.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/settings" || path == "/dashboard/settings/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
            client_side_data += get_username_from_database();
            client_side_data += "</span>";
            client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
            replace_char(client_side_data, "%40", "@");
            content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/settings.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/profile" || path == "/dashboard/profile/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string client_side_data = "<span id='QNJ-USERNAME-TEXT-SP'>";
            client_side_data += get_username_from_database();
            client_side_data += "</span>";
            client_side_data += "<script src='/QNJ-Cloud/js/dashboard.js'></script>";
            replace_char(client_side_data, "%40", "@");
            content_send_file_w_client_side("/home/magician/Desktop/QNJ/web-gui/profile.html", "text/html", "200 OK", "HTTP/1.1", client_socket, client_side_data);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/favicon.ico" || path == "/favicon.ico/")
    {
        send_html_file("/home/magician/Desktop/QNJ/web-gui/favicon.ico", "image/x-icon", "200 OK", "HTTP/1.1", client_socket);
    }

    //##### API KEYS ######//
    else if (path == "/dashboard/api/QNJ-UsQ313HVXz-Sm33G-Ela3qs")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            send_html_file("/home/magician/Desktop/QNJ/database.json", "application/json", "200 OK", "HTTP/1.1", client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/api/QNJ-Jg94japEjgnammykglA316-geadgE69")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            send_html_file("/root/qnj-server/server_data.json", "application/json", "200 OK", "HTTP/1.1", client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/api/QNJ-Megj4aj3194g2-h5mantt4N-!33gc31E69")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            send_html_file("/root/qnj-server/tcp_connections_database.json", "application/json", "200 OK", "HTTP/1.1", client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/api/QNJ-yhew5h5eh34sxghmfnbfrfg-g4g34yhr4yte!t543y78" || path == "/dashboard/api/QNJ-yhew5h5eh34sxghmfnbfrfg-g4g34yhr4yte!t543y78/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            if (get_cookies_from_file(data0x00UserIdCookieValue, "/root/qnj-server/data-0x00-cookies.log"))
            {
                send_html_file("/root/qnj-server/user_client_data-0x00.json", "application/json", "200 OK", "HTTP/1.1", client_socket);
            }
            else
            {
                send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
            }
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    //##### PNG FILES #####//
    else if (path.find("/QNJ-Cloud/assets/png/") == 0 && is_png_file(path.substr(23))) 
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "image/png", "200 OK", "HTTP/1.1", client_socket);
    }
    
    //##### JAVASCRIPT FILES #####//
    else if (path.find("/QNJ-Cloud/js/") == 0 && is_js_file(path.substr(14))) 
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "text/javascript", "200 OK", "HTTP/1.1", client_socket);
    }

    //##### CSS FILES #####//
    else if (path.find("/QNJ-Cloud/styling/") == 0 && is_css_file(path.substr(19))) 
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "text/css", "200 OK", "HTTP/1.1", client_socket);
    }

    //##### SVG FILES #####//
    else if (path.find("/QNJ-Cloud/assets/svg/") == 0 && is_svg_file(path.substr(22)))
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "image/svg+xml", "200 OK", "HTTP/1.1", client_socket);
    }

    else if (path.find("/QNJ-Cloud/assets/data-0x00/") == 0 && is_data_0x00_mugshot(path.substr(28)))
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log") && get_cookies_from_file(data0x00UserIdCookieValue, "/root/qnj-server/data-0x00-cookies.log"))
        {
            std::string full_path = "/home/magician/Desktop/QNJ" + path;
            send_html_file(full_path, "text/css", "200 OK", "HTTP/1.1", client_socket);
        }
    }

    else
    {
        send_html_file("/home/magician/Desktop/QNJ/web-gui/404.html", "text/html", "404 Not Found", "HTTP/1.1", client_socket);
    }
}

void post_path_handler(const std::string& path, std::string& userIdCookieValue, std::string& data0x00UserIdCookieValue, int client_socket, std::string& requestHeaders)
{
    if (path == "/")
    {
    
    }

    else if (path == "/logout_user" || path == "/logout_user/")
    {
        sendRedirect_W_Remove_Cookie("/", "session_id", "none", client_socket);
    }

    else if (path == "/login_user" || path == "/login/")
    {
        std::string get_login_username = parsePostData(requestHeaders, "QNJ-username-login=");
        std::string get_login_password = parsePostData(requestHeaders, "QNJ-password-login=");
        if (get_username(get_login_username, "/root/qnj-server/general_username.log") && get_password(get_login_password, "/root/qnj-server/general_password.log"))
        {
            sendRedirectWithCookie("/dashboard", "session_id", exract_full_cookie(), client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/login-failed.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
            std::cout << "EMAILA: " << get_login_username << "\n";
            std::cout << "PASSWD: " << get_login_password << "\n";
        }
    }

    else if (path == "/signup_user" || path == "/signup_user")
    {
        std::string password, email;
        signup_parsePostData(requestHeaders, password, email);

        last_execute_save_data_singup(email, password);
        sendRedirect("/login", client_socket);
    }

    else if (path == "/dashboard/api/QNJ-0x00-NULL-SERVER" || path == "/dashboard/api/QNJ-0x00-NULL-SERVER/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            shutdown_both_server(client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/404.html", "text/html", "404 Not Found", "HTTP/1.1", client_socket);
        }
    }

    //##### PAYLOAD SEND ######//
    else if (path == "/dashboard/api/send_payload_data" || path == "/dashboard/api/send_payload_data/")
    {
        std::string cmd_value = parsePostData(requestHeaders, "QNJ-PAYLOAD-CMD=");
        std::string QNJ_client_id = parsePostData(requestHeaders, "QNJ-PAYLOAD-CMD-CLIENT-ID="); 
        std::thread send_tcp_clients_command_data([&]() { send_tcp_commands_to_client(cmd_value, QNJ_client_id); });
        send_tcp_clients_command_data.join();
        sendRedirect("/dashboard/payloads", client_socket);
    }

    //##### PAYLOAD GENERATION FILE #####//
    else if (path == "/dashboard/api/QNJ-GENERATE-0x00-EXPLOIT" || path == "/dashboard/api/QNJ-GENERATE-0x00-EXPLOIT")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string hack_type_val = parsePostData(requestHeaders, "QNJ-EXPLOIT-TYPE=");
            std::string format_type_val = parsePostData(requestHeaders, "QNJ-FORMAT-TYPE=");
            std::string os_type_val = parsePostData(requestHeaders, "QNJ-OS-TYPE=");
            std::string ARC_type_val = parsePostData(requestHeaders, "QNJ-ARCHITECTURE-TYPE=");
            sendRedirect("/dashboard/payloads", client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    else if (path == "/dashboard/api/QNJ-GENERATE-NEW-CMD-PAYLOAD" || path == "/dashboard/api/QNJ-GENERATE-NEW-CMD-PAYLOAD")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string generated_cmd_name = parsePostData(requestHeaders, "QNJ-MAKE-CMD-PAYLOAD=");
            std::string generated_path_name = parsePostData(requestHeaders, "QNJ-NEW-PAYLOAD-FILE-PATH=");
            std::cout << generated_cmd_name << "\n";
            std::cout << generated_path_name << "\n";
            sendRedirect("/dashboard/payloads", client_socket);
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    //##### DATA 0X00 LOGIN ######//

    else if (path == "/dashboard/api/QNJ-Data-0x00-login" || path == "/dashboard/api/QNJ-Data-0x00-login/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            std::string get_login_username = parsePostData(requestHeaders, "QNJ-data-0x00-login-username=");
            std::string get_login_password = parsePostData(requestHeaders, "QNJ-data-0x00-login-password=");
            if (get_username(get_login_username, "/root/qnj-server/data-0x00-usernames.log") && get_password(get_login_password, "/root/qnj-server/data-0x00-passwords.log"))
            {
                sendRedirectWithCookie("/dashboard/data-0x00", "session_data_0x00", "1234", client_socket);
            }
            else
            {
                sendRedirect("/dashboard/data-0x00", client_socket);
            }
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    //###### DATA 0x00 LOGOUT #####//
    else if (path == "/dashboard/api/QNJ-data-0x00-logout" || path == "/dashboard/api/QNJ-data-0x00-logout/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            if (get_cookies_from_file(data0x00UserIdCookieValue, "/root/qnj-server/data-0x00-cookies.log"))
            {
                sendRedirect_W_Remove_Cookie("/dashboard/data-0x00", "session_data_0x00", "none", client_socket);
            }
            else
            {
                send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
            }
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    //##### DATA 0X00 ADD #####//
    else if (path == "/dashboard/api/QNJ-data-0x00-newclient" || path == "/dashboard/api/64fjqg4ms-a6g4isng5ef-d9grrs4-d99/")
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log"))
        {
            if (get_cookies_from_file(data0x00UserIdCookieValue, "/root/qnj-server/data-0x00-cookies.log"))
            {
                
                std::string first_name = parsePostData(requestHeaders, "QNJ-data-0x00-first-name=");
                std::string last_name = parsePostData(requestHeaders, "QNJ-data-0x00-last-name=");
                std::string age = parsePostData(requestHeaders, "QNJ-data-0x00-age-name=");
                std::string gender = parsePostData(requestHeaders, "QNJ-data-0x00-gender-name=");
                std::string email = parsePostData(requestHeaders, "QNJ-data-0x00-email-name=");
                std::string phonenumber = parsePostData(requestHeaders, "QNJ-data-0x00-phonenumber-name=");
                std::string country = parsePostData(requestHeaders, "QNJ-data-0x00-country-name=");
                std::string city = parsePostData(requestHeaders, "QNJ-data-0x00-city-name=");
                std::string material_status = parsePostData(requestHeaders, "QNJ-data-0x00-martialstat-name=");
                std::string children_amount = parsePostData(requestHeaders, "QNJ-data-0x00-children-name=");
                std::string user_mugshot_pic = parsePostData(requestHeaders, "QNJ-data-0x00-userpic-name=");

                std::cout << requestHeaders << "\n";

                requestHeaders.clear();

                            
                sendRedirect("/dashboard/data-0x00", client_socket);
            }
            else
            {
                send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
            }
        }
        else
        {
            send_html_file("/home/magician/Desktop/QNJ/web-gui/401.html", "text/html", "401 Unauthorized", "HTTP/1.1", client_socket);
        }
    }

    //##### PNG FILES #####//
    else if (path.find("/QNJ-Cloud/assets/png/") == 0 && is_png_file(path.substr(23))) 
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "image/png", "200 OK", "HTTP/1.1", client_socket);
    }
    
    //##### JAVASCRIPT FILES #####//
    else if (path.find("/QNJ-Cloud/js/") == 0 && is_js_file(path.substr(14))) 
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "text/javascript", "200 OK", "HTTP/1.1", client_socket);
    }

    //##### CSS FILES #####//
    else if (path.find("/QNJ-Cloud/styling/") == 0 && is_css_file(path.substr(19))) 
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "text/css", "200 OK", "HTTP/1.1", client_socket);
    }

    //##### SVG FILES #####//
    else if (path.find("/QNJ-Cloud/styling/") == 0 && is_svg_file(path.substr(19)))
    {
        std::string full_path = "/home/magician/Desktop/QNJ" + path;
        send_html_file(full_path, "text/css", "200 OK", "HTTP/1.1", client_socket);
    }

    else if (path.find("/QNJ-Cloud/data-0x00/") == 0 && is_data_0x00_mugshot(path.substr(27)) || path.find("/QNJ-Cloud/data-0x00/") == 0 && is_data_0x00_mugshot(path.substr(27)))
    {
        if (get_cookies_from_file(userIdCookieValue, "/root/qnj-server/general_cookie.log") && get_cookies_from_file(data0x00UserIdCookieValue, "/root/qnj-server/data-0x00-cookies.log"))
        {
            std::string full_path = "/home/magician/Desktop/QNJ" + path;
            send_html_file(full_path, "text/css", "200 OK", "HTTP/1.1", client_socket);
        }
    }

    else
    {
        send_html_file("/home/magician/Desktop/QNJ/web-gui/404.html", "text/html", "404 Not Found", "HTTP/1.1", client_socket);
    }
}
#endif
/*


*/