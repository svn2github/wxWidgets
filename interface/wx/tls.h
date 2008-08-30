/////////////////////////////////////////////////////////////////////////////
// Name:        wx/tls.h
// Purpose:     wxTLS_TYPE()
// Author:      Vadim Zeitlin
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    Macro to be used for thread-specific variables declarations.

    This macro can be used to define thread-specific variables of the specified
    @a type. Such variables must be global or static and must be POD, i.e.
    not have any constructors or destructor (even implicitly generated by the
    compiler due to use of base classes or members which are not POD in a
    struct).

    Example of use:
    @code
    struct PerThreadData
    {
        ... data which will be different for every thread ...
    };

    static wxTLS_TYPE(PerThreadData) s_threadDataVar;
    #define s_threadData (wxTLS_VALUE(s_threadDataVar))

    ... use s_threadData as a variable of type PerThreadData ...
    @endcode

    Notice that the use of the ugly wxTLS_VALUE() macro is unfortunately
    required if you need to support platforms without native compiler support
    for thread-specific variables. If you compile your code only on platforms
    which do have such support (recent versions of GNU C++ compiler, Microsoft
    Visual C++ and Sun C++ compiler are known to have it), you can avoid it and
    use the variable directly.
 */
#define wxTLS_TYPE(type) compiler-dependent-implementation

/**
    Macro to access thread-specific variables.

    This macro is used to hide the difference in implementation of
    thread-specific variables under different platforms: they can be of type T
    used in wxTLS_TYPE() if they are directly supported by the compiler or of
    type emulating @c T @c *, i.e. a pointer to this type otherwise. This macro
    always returns an expression of type @c T itself.

    As shown in wxTLS_TYPE() example, you may want to @c \#define a symbol
    wrapping a thread-specific variable with this macro. And, as also explained
    in wxTLS_TYPE() documentation, you may avoid using it entirely if you
    target only recent compilers.

    @see wxTLS_PTR()
 */
#define wxTLS_VALUE(var)

/**
    Macro to return address of a thread-specific variables.

    This macro is similar to wxTLS_VALUE() except that it always returns a
    pointer to the type of thread-specific variable.

    Notice that this is not a constant expression even if the macro is defined
    simply as @c &amp;var -- the value returned is still different for every
    thread.
 */
#define wxTLS_PTR(var)
