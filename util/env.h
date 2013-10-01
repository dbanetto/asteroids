#ifndef H_ENV
#define H_ENV

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV64
#else
#define ENV32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64
#else
#define ENV32
#endif
#endif


//Settings location
#define SETTINGS_LOCATION "settings.ini"

#endif
