/**
 * @file winio.cpp
 */
#include <stdafx.h>
#include <spaghetti/bitset.hpp>

#include <lxe/winio.hpp>
using namespace std;

#define     VOLUME_SEPARATOR                        _T(':')
#define     WINDOWS_DIRECTORY_SEPARATOR             _T('\\')
#define     UNIX_DIRECTORY_SEPARATOR                _T('/')

#define     S_WINDOWS_DIRECTORY_SEPARATOR           _T("\\")
#define     S_UNIX_DIRECTORY_SEPARATOR              _T("/")

#define     S_WILD_CARD                             _T("*")

#define     S_HL_CURRENT_DIRECTORY                  _T(".")
#define     S_CURRENT_DIRECTORY                     _T(".\\")
#define     S_HL_PARENT_DIRECTORY                   _T("..")
#define     S_PARENT_DIRECTORY                      _T("..\\")

#define     S_VOLUME_AND_DIRECTORY_SEPARATOR        _T(":\\")


/**
 * ファイル名と省略形式のパスから省略されていないパスに変換して返します。
 *    @param  filename  省略形式のファイル名。
 *    @param  dir       省略形式のパス。
 *    @param  data      検索データ用の構造体。
 *
 *    @return 省略されていないパス。
 */
inline tstring _M_get_long_filename_closure(const tstring& filename, const tstring& dir, WIN32_FIND_DATA& data);


/**
 * 指定されたファイルパスに所属するファイルを削除します。
 *    @param parent_path 削除するファイルの場所。
 *    @param filename  削除するファイル名。
 *    @param data      関数内で使用する WIN32_FIND_DATA 構造体のインスタンス。
 *
 *    @return 成功したら真。
 */
inline bool _M_delete_directory_closure(const tstring& parent_path, const tstring& filename, WIN32_FIND_DATA& data);


tstring get_temp_path()
{
    tstring     temp_path;
#ifndef LXE_USE_DEFAULT_TEMPORARY_DIRECTORY
    uint32_t    ret;
    _TCHAR*     buffer          = NULL;
    size_t      buffer_length   = 0;

    ret             = GetTempPath( __STATIC_CAST(DWORD, buffer_length), buffer );
    buffer_length   = ret;
    {
        buffer      = new _TCHAR[buffer_length];
        ret         = GetTempPath( __STATIC_CAST(DWORD, buffer_length), buffer );
        temp_path   = buffer;

        delete [] buffer;
    }
#else
    temp_path   = LXE_DEFAULT_TEMPORARY_DIRECTORY;
#endif  /* ndef LXE_USE_DEFAULT_TEMPORARY_DIRECTORY */
    return temp_path;
}


tstring get_temp_longpath()
{
    return get_long_path( get_temp_path() );
}


tstring get_long_path(const tstring& path)
{
    typedef     tstring::size_type      size_type;
    /*
     * ドライブレターとコロンだけを抜き出します。
     */
    tstring     longpath    = path.substr( 0, 2 );

    tstring     short_path;

    size_type   lpos        = path.find_first_of( WINDOWS_DIRECTORY_SEPARATOR, 3 );
    size_type   fpos        = 3;

    WIN32_FIND_DATA     data;
    while ( lpos != tstring::npos ) {
        short_path      = path.substr( fpos, lpos - fpos );
        longpath        = _M_get_long_filename_closure( short_path, longpath, data );
        fpos            = lpos + 1;
        lpos            = path.find_first_of( WINDOWS_DIRECTORY_SEPARATOR, fpos );
    }
    short_path  = path.substr( fpos );
    longpath    = _M_get_long_filename_closure( short_path, longpath, data );

    return longpath;
}


tstring get_temp_filename(const tstring& path, const tstring& prefix, uint32_t unique_seed)
{
    tstring     temp_filename;

    _TCHAR      temp_buffer[MAX_PATH * 2];
    if ( !GetTempFileName( path.c_str(), prefix.c_str(), unique_seed, temp_buffer ) )
        return temp_filename;

    temp_filename   = temp_buffer;

    return temp_filename;
}
tstring get_temp_filename(const tstring& path, uint32_t unique_seed)
{
    tstring     temp_filename;

    _TCHAR      temp_buffer[MAX_PATH * 2];
    if ( !GetTempFileName( path.c_str(), NULL, unique_seed, temp_buffer ) )
        return temp_filename;

    temp_filename   = temp_buffer;

    return temp_filename;
}


uint32_t get_file_attributes(const tstring& filepath)
{
    return GetFileAttributes( filepath.c_str() );
}


handle_t create_file( const tstring&            filepath,
                      uint32_t                  desire_access,
                      uint32_t                  share_mode,
                      security_attr_t* const&   security_attributes,
                      uint32_t                  creation_disposition,
                      uint32_t                  flags_and_attributes,
                      handle_t                  template_file
                      )
{
    handle_t  ret;
#ifdef LIBLXE_USE_SEH
    __try {
#else
    {
#endif  /* def LIBLXE_USE_SEH */
        ret = CreateFile( filepath.c_str(),
                          desire_access,
                          share_mode,
                          security_attributes,
                          creation_disposition,
                          flags_and_attributes,
                          template_file
                          );
#ifdef LIBLXE_USE_SEH
    } __except ( seh_filter( GetExceptionInfomation() ) ) {
    }
#else
    }
#endif  /* def LIBLXE_USE_SEH */

#ifdef LIBLXE_USE_THROW_DOMAIN_ERROR
    if ( handle_is_invalid( ret ) )
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* def LIBLXE_USE_THROW_DOMAIN_ERROR */

    return ret;
}


bool create_directory( const tstring&           pathname,
                       security_attr_t* const&  security_attributes
                       )
{
    bool    ret;
#ifdef LIBLXE_USE_SEH
    __try {
#else
    {
#endif  /* def LIBLXE_USE_SEH */
        ret = CreateDirectory( pathname.c_str(), security_attributes ) != 0;
#ifdef LIBLXE_USE_SEH
    } __except ( seh_filter( GetExceptionInfomation() ) ) {
    }
#else
    }
#endif  /* def LIBLXE_USE_SEH */

#ifdef LIBLXE_USE_THROW_DOMAIN_ERROR
    if ( handle_is_invalid( ret ) )
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* def LIBLXE_USE_THROW_DOMAIN_ERROR */

    return ret;
}


bool create_recursive_directory(const tstring& path)
{
    typedef     tstring::size_type                  size_type;
    typedef     std::vector<tstring>::iterator      iterator;

    tstring     created_path    = expand_path( path );
    tstring     current_path    = get_current_directory();
    tstring     base_path       = current_path;
    int         location        = 0;

    if ( created_path.length() == 0 )
        return false;

    if ( ( location = __STATIC_CAST(int, created_path.find( current_path, 0 )) ) == tstring::npos ) {
        while ( ( location = __STATIC_CAST(int, base_path.rfind( WINDOWS_DIRECTORY_SEPARATOR )) ) != tstring::npos  ) {
            base_path   = base_path.substr( 0, location );

            if ( ( location = __STATIC_CAST(int, created_path.find( base_path )) ) == 0 )
                break;
        }
    }

    if ( location == tstring::npos )
        base_path   = created_path.substr( 0, 2 );

    int         first_pos   = __STATIC_CAST(int, base_path.length() + 1);
    int         last_pos    = __STATIC_CAST(int, created_path.length() - first_pos);
    tstring     tmp_path    = created_path.substr( first_pos, last_pos );

    std::vector<tstring>    tmps;
    split_all( tmp_path, tmps, S_WINDOWS_DIRECTORY_SEPARATOR );

    tstringstream   dirpath_builder;
    iterator        sentinel        = tmps.end();
    int             create_count    = 0;

    dirpath_builder << base_path;
    for ( iterator it = tmps.begin(); it != sentinel; ++ it ) {
        dirpath_builder << WINDOWS_DIRECTORY_SEPARATOR << *it;

        tstring     makedir_path    = dirpath_builder.str();
        if ( !is_exists( makedir_path ) ) {
            if ( create_directory( makedir_path ) )
                ++ create_count;
        }
    }

    return create_count > 0;
}


bool is_exists(const tstring& find_path)
{
    typedef     tstring::size_type      size_type;

    uint32_t    ret                 = 0;

    tstring     parent_path;
    size_type   last_separator_pos  = find_path.find_last_of( WINDOWS_DIRECTORY_SEPARATOR );
    /*
     * "\" が無かった場合、parent_path に空文字列が入り、存在しないファイルとして
     * 判定されてしまうので parent_path には "." をいれておきます。
     */
    if ( last_separator_pos == tstring::npos )
        parent_path   = S_HL_CURRENT_DIRECTORY;
    else
        parent_path   = find_path.substr( 0, last_separator_pos );

    tstring     file_name   =   find_path.substr( last_separator_pos + 1,
                                                  find_path.length() - last_separator_pos
                                                  );

    ret = SearchPath( parent_path.c_str(),
                      file_name.c_str(),
                      NULL,
                      0,
                      NULL,
                      NULL
                      );

    return ret != 0;
}


tstring search_path(const tstring& find_path, const tstring& filename, tstring& ret_filepart)
{
    _TCHAR*     temp_buffer         = NULL;
    size_t      temp_buffer_length  = 0;

    tstring     result;

    uint32_t    ret         = 0;

    ret = SearchPath( find_path.c_str(),
                      filename.c_str(),
                      NULL,
                      __STATIC_CAST(DWORD, temp_buffer_length),
                      temp_buffer,
                      NULL
                      );

    if ( ret > 0 ) {
        temp_buffer_length = __STATIC_CAST(size_t, ret * 1.5);
        ret                     = 0;
        temp_buffer             = new _TCHAR[temp_buffer_length];

        _TCHAR*     file_part   = NULL;

        ret = SearchPath( find_path.c_str(),
                          filename.c_str(),
                          NULL,
                          __STATIC_CAST(DWORD, temp_buffer_length),
                          temp_buffer,
                          &file_part
                          );
        if ( ret > 0 ) {
            // tstring に文字列を渡す。
            result          = temp_buffer;
            ret_filepart    = file_part;
            // もう必要ないので開放する。
            delete [] temp_buffer;
        } else {
            /*
             * メモリを割り当ててしまったので、delete[] しておく。
             */
            delete [] temp_buffer;
#if defined(LIBLXE_USE_THROW_DOMAIN_ERROR)
            throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LIBLXE_USE_THROW_DOMAIN_ERROR) */
        }
    }
#if defined(LIBLXE_USE_THROW_DOMAIN_ERROR)
    else {
        /*
         * この時点では、動的にメモリを割り当てていないので delete[] しなくても
         * 済む。
         */
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
    }
#endif  /* defined(LIBLXE_USE_THROW_DOMAIN_ERROR) */
    return result;
}
tstring search_path(const tstring& find_path, const tstring& filename)
{
    _TCHAR*     temp_buffer         = NULL;
    size_t      temp_buffer_length  = 0;

    tstring     result;

    uint32_t    ret         = SearchPath( find_path.c_str(),
                                          filename.c_str(),
                                          NULL,
                                          __STATIC_CAST(DWORD, temp_buffer_length),
                                          temp_buffer,
                                          NULL
                                          );

    if ( ret > 0 ) {
        temp_buffer_length = __STATIC_CAST(size_t, ret * 1.5);
        ret             = 0;
        temp_buffer        = new _TCHAR[temp_buffer_length];

        _TCHAR* file_part  = NULL;

        ret = SearchPath( find_path.c_str(),
                          filename.c_str(),
                          NULL,
                          __STATIC_CAST(DWORD, temp_buffer_length),
                          temp_buffer,
                          &file_part
                          );
        if ( ret > 0 ) {
            // tstring に文字列を渡す。
            result          = temp_buffer;
            // もう必要ないので開放する。
            delete [] temp_buffer;
        } else {
            /*
             * メモリを割り当ててしまったので、delete[] しておく。
             */
            delete [] temp_buffer;
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
            throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */
        }

    }
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    else {
        /*
         * この時点では、動的にメモリを割り当てていないので delete[] しなくても
         * 済む。
         */
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
    }
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */
    return result;
}


tstring get_current_directory()
{
    _TCHAR*     fullpath_buffer         = NULL;
    size_t      fullpath_buffer_size    = 0;

    uint32_t    ret;

    tstring     result;

    ret = GetCurrentDirectory( __STATIC_CAST(DWORD, fullpath_buffer_size), fullpath_buffer );
    if ( ret > 0 ) {
        fullpath_buffer_size     = ret;
        fullpath_buffer          = new _TCHAR[fullpath_buffer_size];

        ret             = GetCurrentDirectory( __STATIC_CAST(DWORD, fullpath_buffer_size), fullpath_buffer );

        result          = fullpath_buffer;

        delete [] fullpath_buffer;
    }
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    else
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */
    return result;
}


bool delete_file(const tstring& original_filepath)
{
    bool ret;

    ret = DeleteFile( original_filepath.c_str() ) != 0;
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( !ret )
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


bool delete_directory(const tstring& original_path)
{
    bool ret;

    ret = RemoveDirectory( original_path.c_str() ) != 0;
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( !ret )
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


bool delete_directory_forse(const tstring& original_path)
{
    typedef     tstring::size_type      size_type;

    WIN32_FIND_DATA     data;

    size_type           last_separator_pos  = original_path.find_last_of( WINDOWS_DIRECTORY_SEPARATOR );
    tstring             parent_path           = original_path.substr( 0, last_separator_pos );
    tstring             file_name           = original_path.substr( last_separator_pos + 1,
                                                                    original_path.length() - last_separator_pos
                                                                    );

    tstring             current_path        = search_path( parent_path, file_name );
    tstring             path                = path_combine( current_path, S_WILD_CARD );

    HANDLE              finder              = FindFirstFile( path.c_str(), &data );

    if ( handle_is_invalid( finder ) )
        return false;

    do {
        tstring     filename( data.cFileName );

        if ( filename != S_HL_CURRENT_DIRECTORY && filename != S_HL_PARENT_DIRECTORY ) {
            filename = path_combine( current_path, filename );

            if ( bitset_is_include( data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) ) {

                if ( !_M_delete_directory_closure( current_path, tstring( data.cFileName ), data ) )
                    return false;

                delete_directory( filename );
            } else
                delete_file( filename );
        }

    } while ( FindNextFile( finder, &data ) );
    FindClose( finder );

    delete_directory( current_path );

    return true;
}


bool find_directory(const tstring& original_path, const tstring& pattern, vector<tstring>& discoverys)
{
    typedef     tstring::size_type      size_type;

    WIN32_FIND_DATA     data;
    HANDLE              finder;

    tstring             current_path  = search_path( original_path );
    tstring             find_pattern  = path_combine( current_path, pattern );

    finder      =   FindFirstFile( find_pattern.c_str(), &data );
    if ( handle_is_invalid( finder ) )
        return false;

    do {
        discoverys.push_back( path_combine( current_path, data.cFileName ) );
    } while ( FindNextFile( finder, &data ) );
    FindClose( finder );

    return true;
}


tstring get_fullpath(const tstring& original_path)
{
    _TCHAR*     buffer          = NULL;
    size_t      buffer_length   = 0;

    tstring     result;

    DWORD       ret  = GetFullPathName( original_path.c_str(),
                                        __STATIC_CAST(DWORD, buffer_length),
                                        buffer,
                                        NULL
                                        );
    if ( ret > 0 ) {
        buffer_length   = ret;
        buffer          = new _TCHAR[buffer_length];

        ret  = GetFullPathName( original_path.c_str(),
                                __STATIC_CAST(DWORD, buffer_length),
                                buffer,
                                NULL
                                );
        if ( ret > 0 )
            result  = buffer;

        delete [] buffer;
    }
    return result;
}


tstring convert_platform_path(const tstring& original_path) {
    return replace_all( original_path,
                        S_UNIX_DIRECTORY_SEPARATOR,
                        S_WINDOWS_DIRECTORY_SEPARATOR
                        );
}


tstring get_root_path(const tstring& local_path)
{
    typedef     tstring::size_type      size_type;

    tstring     path        = convert_platform_path( local_path );
    size_type   colon_pos   = path.find_first_of( VOLUME_SEPARATOR );

    if ( colon_pos != tstring::npos )
        return path.substr( 0, colon_pos + 1 ) + WINDOWS_DIRECTORY_SEPARATOR;
    else
        return S_WINDOWS_DIRECTORY_SEPARATOR;
}


tstring expand_path(const tstring& local_path)
{
    tstringstream   fullpath_builder;
    tstring         path            = replace_all( local_path,
                                                   S_WINDOWS_DIRECTORY_SEPARATOR,
                                                   S_UNIX_DIRECTORY_SEPARATOR
                                                   );

    if ( path.find_first_of( S_UNIX_DIRECTORY_SEPARATOR ) == 0 ) {
        fullpath_builder << get_root_path( path );
        fullpath_builder << replace_all( path.substr( path.find( S_WINDOWS_DIRECTORY_SEPARATOR ) + 1 ),
                                         S_UNIX_DIRECTORY_SEPARATOR,
                                         S_WINDOWS_DIRECTORY_SEPARATOR
                                         );
    } else
        fullpath_builder << get_fullpath( local_path );

    return fullpath_builder.str();
}


inline tstring _M_get_long_filename_closure(const tstring& filename, const tstring& dir, WIN32_FIND_DATA& data)
{
    tstring     find_path( path_combine( dir, filename ) );
    tstring     longname( dir );

    handle_t    finder   = FindFirstFile( find_path.c_str(), &data );

    if ( !handle_is_invalid( finder ) )
        longname = path_combine( dir, data.cFileName );

    FindClose( finder );

    return longname;
}


inline bool _M_delete_directory_closure( const tstring&     parent_path,
                                         const tstring&     directory_name,
                                         WIN32_FIND_DATA&   data
                                         )
{
    tstring     current_path    = search_path( parent_path, directory_name );
    tstring     find_path       = path_combine( current_path, S_WILD_CARD );

    HANDLE      finder          = FindFirstFile( find_path.c_str(), &data );
    if ( handle_is_invalid( finder ) )
        return false;

    do {
        tstring     tmp_entryname( data.cFileName );

        if ( tmp_entryname != S_HL_CURRENT_DIRECTORY && tmp_entryname != S_HL_PARENT_DIRECTORY ) {

            tmp_entryname = path_combine( current_path, tmp_entryname );
            if ( bitset_is_include( data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) ) {
                if ( !_M_delete_directory_closure( current_path, tstring( data.cFileName ), data ) )
                    return false;

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
                if ( !delete_directory( tmp_entryname ) )
                    throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#else
                delete_directory( tmp_entryname );
#endif  /* !defined(LXE_USE_THROW_DOMAIN_ERROR) */
            } else {
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
                if ( !delete_file( tmp_entryname ) )
                    throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#else
                delete_file( tmp_entryname );
#endif  /* !defined(LXE_USE_THROW_DOMAIN_ERROR) */
            }

        }

    } while ( FindNextFile( finder, &data ) );
    FindClose( finder );

    return true;
}


tstring path_combine(const tstring& path1, const tstring& path2)
{
    tstring     temp_basepath   = replace_all( path1,
                                               S_UNIX_DIRECTORY_SEPARATOR,
                                               S_WINDOWS_DIRECTORY_SEPARATOR
                                               );
    tstring     temp_localpath  = replace_all( path2,
                                               S_UNIX_DIRECTORY_SEPARATOR,
                                               S_WINDOWS_DIRECTORY_SEPARATOR
                                               );

    if ( temp_basepath.compare( S_HL_CURRENT_DIRECTORY ) == 0
         || temp_basepath.compare( S_CURRENT_DIRECTORY ) == 0
         ) {
        /*
         * ベースパスはカレントディレクトリを表しているので、カレントディレクトリに変えておきます。
         */
        temp_basepath   = get_current_directory();
    } else if ( temp_basepath.find( S_HL_PARENT_DIRECTORY ) == 0
                || temp_basepath.find( S_PARENT_DIRECTORY ) == 0
                ) {
        /*
         * ベースパスはパレントディレクトリを表しているので、カレントディレクトリの親ディレクトリパスにしておきます。
         */
        temp_basepath   = get_fullpath( temp_basepath );
    } else if ( temp_basepath.find( WINDOWS_DIRECTORY_SEPARATOR ) == 0 ) {
        /*
         * ベースパスはルートパスなので、ルートパスをくっつけます。
         */
        temp_basepath   = get_fullpath( temp_basepath );
    } else if ( temp_basepath.find_last_of( S_VOLUME_AND_DIRECTORY_SEPARATOR ) == 0 ) {
        /* 
         * ルートパスらしいのでディレクトリセパレータを除いておきます。
         */
        temp_basepath   = temp_basepath.substr( 0, temp_basepath.find( WINDOWS_DIRECTORY_SEPARATOR ) );
    }

    if ( temp_localpath == S_HL_CURRENT_DIRECTORY ) {
        /* 
         * ローカルパスが `.' なら、カレントディレクトリを指すことにしているので空文字列を入れておく。
         */
        temp_localpath   = tstring();
    }

    size_t  last_slash  = temp_localpath.find_last_of( WINDOWS_DIRECTORY_SEPARATOR );
    if ( last_slash != tstring::npos )
        temp_localpath  = temp_localpath.substr( 0, last_slash );

    return temp_basepath + WINDOWS_DIRECTORY_SEPARATOR + temp_localpath;
}
