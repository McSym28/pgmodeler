#ifndef DLLAPI_H
#define DLLAPI_H

#if defined(LIBUTILS_EXPORT) // inside DLL
#   if defined _MSC_VER
#       define LIBUTILS_API   __declspec(dllexport)
#   else
#       define LIBUTILS_API
#   endif
#else // outside DLL
#   if defined _MSC_VER
#       define LIBUTILS_API   __declspec(dllimport)
#   else
#       define LIBUTILS_API
#   endif
#endif  // LIBUTILS_EXPORT

#if defined(LIBPARSERS_EXPORT) // inside DLL
#   if defined _MSC_VER
#       define LIBPARSERS_API   __declspec(dllexport)
#   else
#       define LIBPARSERS_API
#   endif
#else // outside DLL
#   if defined _MSC_VER
#       define LIBPARSERS_API   __declspec(dllimport)
#   else
#       define LIBPARSERS_API
#   endif
#endif  // LIBPARSERS_EXPORT

#if defined(LIBPGMODELER_EXPORT) // inside DLL
#   if defined _MSC_VER
#       define LIBPGMODELER_API   __declspec(dllexport)
#   else
#       define LIBPGMODELER_API
#   endif
#else // outside DLL
#   if defined _MSC_VER
#       define LIBPGMODELER_API   __declspec(dllimport)
#   else
#       define LIBPGMODELER_API
#   endif
#endif  // LIBPGMODELER_EXPORT

#if defined(LIBPGCONNECTOR_EXPORT) // inside DLL
#   if defined _MSC_VER
#       define LIBPGCONNECTOR_API   __declspec(dllexport)
#   else
#       define LIBPGCONNECTOR_API
#   endif
#else // outside DLL
#   if defined _MSC_VER
#       define LIBPGCONNECTOR_API   __declspec(dllimport)
#   else
#       define LIBPGCONNECTOR_API
#   endif
#endif  // LIBPGCONNECTOR_EXPORT

#if defined(LIBOBJRENDERER_EXPORT) // inside DLL
#   if defined _MSC_VER
#       define LIBOBJRENDERER_API   __declspec(dllexport)
#   else
#       define LIBOBJRENDERER_API
#   endif
#else // outside DLL
#   if defined _MSC_VER
#       define LIBOBJRENDERER_API   __declspec(dllimport)
#   else
#       define LIBOBJRENDERER_API
#   endif
#endif  // LIBOBJRENDERER_EXPORT

#if defined(LIBPGMODELERUI_EXPORT) // inside DLL
#   if defined _MSC_VER
#       define LIBPGMODELERUI_API   __declspec(dllexport)
#   else
#       define LIBPGMODELERUI_API
#   endif
#else // outside DLL
#   if defined _MSC_VER
#       define LIBPGMODELERUI_API   __declspec(dllimport)
#   else
#       define LIBPGMODELERUI_API
#   endif
#endif  // LIBPGMODELERUI_EXPORT

#endif // DLLAPI_H
