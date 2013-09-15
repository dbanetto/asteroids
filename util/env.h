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



//SDL Byte orders

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

#endif
