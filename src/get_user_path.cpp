#include <iostream>

#ifdef __linux__

#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#elif defined _WIN32

#define NOMINMAX
#include <UserEnv.h>

#endif

std::string get_userpath()
{
#ifdef __linux__

    const char* home_dir;

    if ((home_dir = getenv("HOME")) == NULL)
        home_dir = getpwuid(getuid())->pw_dir;

#elif defined _WIN32
    HANDLE token_handle = nullptr; 
    OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token_handle);
    
    char home_dir[50];

    LPSTR profile_dir = home_dir;
    DWORD size = 50;

    GetUserProfileDirectoryA(token_handle, profile_dir, &size);
#endif

    return home_dir;
}
