/**
 * @file  ini_file.hpp
 * @brief 設定ファイル操作用モジュール。
 */
#ifndef lxe_win32api_ini_file_hpp
#define lxe_win32api_ini_file_hpp

#include <spaghetti/string_util.hpp>

#ifndef LXE_DEFINE_REGISTRY_T
typedef     HKEY            registry_t;
#   define          LXE_DEFINE_REGISTRY_T
#endif  /* ndef LXE_DEFINE_REGISTRY_T */

#ifndef LXE_DEFINE_ACCESS_MASK_T
typedef     ACCESS_MASK     access_mask_t;
#   define         LXE_DEFINE_ACCESS_MASK_T
#endif  /* ndef LXE_DEFINE_ACCESS_MASK_T */

#ifndef LXE_DEFINE_SECURITY_ATTR_T
typedef     SECURITY_ATTRIBUTES     security_attr_t;
#   define      LXE_DEFINE_SECURITY_ATTR_T
#endif  /* ndef LXE_DEFINE_SECURITY_ATTR_T */


const size_t    _TEMPORAY_BUFFER_LENGTH    =   4096;


/**
 * @def INI_VALUE_YES
 * @since 2010-09-03
 * ini ファイル用の真偽値？の 1 つで、真を表します。
 */
#define     INI_VALUE_YES           _T("yes")
/**
 * @def INI_VALUE_SHORT_YES
 * @since 2010-09-03
 * ini ファイル用の真偽値？の 1 つで、真を表します。
 * INI_VALUE_YES の短いバージョンです。
 */
#define     INI_VALUE_SHORT_YES     _T("y")
/**
 * @def INI_VALUE_NO
 * @since 2010-09-03
 * ini ファイル用の真偽値？の 1 つで偽を表します。
 */
#define     INI_VALUE_NO            _T("no")
/**
 * @def INI_VALUE_SHORT_NO
 * @since 2010-09-03
 * ini ファイル用の真偽値？の 1 つで偽を表します。
 * INI_VALUE_NO の短いバージョンです。
 */
#define     INI_VALUE_SHORT_NO      _T("n")


/**
 * @def INI_VALUE_NIL
 * @since 2010-10-04T08:56:38+0900
 * ini ファイル用の無効な値を表します。
 */
#define     INI_VALUE_NIL           _T("nil")


/**
 * *.ini ファイルから、指定されたセクション内の全てのキーと値を取得します。
 * <pre>
 * 内部で呼び出す GetPrivateProfileSection() が必要なバッファを返してくれないので、
 * 呼び出す側が確保するべきバッファを指定する必要があります。
 * </pre>
 *    @param section_name          キーと値を取得したいセクション名。
 *    @param result_map            情報が格納されるコンテナ。
 *    @param result_buffer_length  確保するバッファの長さ。
 *    @param filepath              *.ini ファイルの名前。
 *
 *    @return バッファに格納された文字列。
 */
uint32_t get_private_profile_section( const tstring&               section_name,
                                      std::map<tstring, tstring>&  result_map,
                                      size_t                       result_buffer_length,
                                      const tstring&               filepath
                                      );


/**
 * *.ini ファイルから全てのセクションの名前を取得します。
 *    @param sections             セクション名が入るベクタコンテナです。
 *    @param temp_buffer_length   テンポラリバッファのサイズ。
 *    @param filename             *.ini ファイルの名前。
 */
uint32_t get_private_profile_section_names( std::vector<tstring>& sections,
                                            size_t                temp_buffer_length,
                                            const tstring&        filename
                                            );


/**
 * 指定された *.ini ファイルの指定されたセクション内にある、指定されたキーに関連付けられている整数を取得します。
 *    @param section_name  セクション名。
 *    @param key           キー名。
 *    @param default_value キー名が見つからなかったときに返すべき値。
 *    @param filename      *.ini ファイルの名前。
 */
uint32_t get_private_profile_int( const tstring&    section_name,
                                  const tstring&    key,
                                  int               default_value,
                                  const tstring&    filename
                                  );


/**
 * 指定された *.ini ファイルの指定されたセクション内にある、指定されたキーに関連付けられている文字列を取得します。
 */
tstring get_ini_string( const tstring&    section_name,
                        const tstring&    key,
                        const tstring&    filename,
                        const tstring&    default_string    = tstring(INI_VALUE_NIL),
                        size_t            string_length     = _TEMPORAY_BUFFER_LENGTH
                        );
inline
tstring get_ini_string( const _TCHAR* const&    section_name,
                        const _TCHAR* const&    key_name,
                        const _TCHAR* const&    filename,
                        const _TCHAR* const&    default_value       = INI_VALUE_NIL,
                        size_t                  buffer_length       = _TEMPORAY_BUFFER_LENGTH
                        )
{
    return get_ini_string( tstring( section_name ),
                           tstring( key_name ),
                           tstring( filename ),
                           tstring( default_value ),
                           buffer_length
                           );
}


/**
 * 指定された *.ini ファイルの、指定されたセクション内に、指定されたキー名とそ
 * れに関連付けられた値を格納します。
 *    @param section_name  セクション名。
 *    @param key           キー名。
 *    @param value         キー名と関連する値。
 *    @param filename      *.ini ファイル名。
 *
 *    @return 成功したら真。
 */
bool write_private_profile_string( const tstring& section_name,
                                   const tstring& key,
                                   const tstring& value,
                                   const tstring& filename
                                   );
/**
 * 指定された *.ini ファイルの、指定されたセクション内に、指定されたキー名とそ
 * れに関連付けられた値を格納します。
 *    @param section_name  セクション名。
 *    @param key           キー名。
 *    @param value         キー名と関連する値。
 *    @param filename      *.ini ファイル名。
 *
 *    @return 成功したら真。
 */
inline bool write_private_profile_string( const _TCHAR* const& section_name,
                                          const _TCHAR* const& key,
                                          const _TCHAR* const& value,
                                          const _TCHAR* const& filename
                                          )
{
    return write_private_profile_string( tstring( section_name ),
                                         tstring( key ),
                                         tstring( value ),
                                         tstring( filename )
                                         );
}
/**
 * 指定された *.ini ファイルの、指定されたセクション内に、指定されたキー名とそ
 * れに関連付けられた値を格納します。
 *    @param section_name  セクション名。
 *    @param key           キー名。
 *    @param value         キー名と関連する値。
 *    @param filename      *.ini ファイル名。
 *
 *    @return 成功したら真。
 */
inline bool write_inifile_pair( tstring section_name,
                                tstring key,
                                tstring value,
                                tstring filename
                                )
{
    return write_private_profile_string( section_name,
                                         key,
                                         value,
                                         filename
                                         );
}
inline bool write_inifile_pair( tstring                             section_name,
                                const std::pair<tstring, tstring>&  kav,
                                tstring                             filename
                                )
{
    return write_private_profile_string( section_name,
                                         kav.first,
                                         kav.second,
                                         filename
                                         );
}


/**
 * *.ini ファイルから全てのセクションの名前を取得します。
 *    @param sections             セクション名が入るベクタコンテナです。
 *    @param temp_buffer_length   テンポラリバッファのサイズ。
 *    @param filename             *.ini ファイルの名前。
 *
 *    @return バッファに格納したデータの長さを返します。
 */
template <class _Container> inline
uint32_t get_ini_section_names( _Container&                               sections,
                                const typename _Container::value_type&    filename,
                                typename _Container::size_type            temp_buffer_length    = _TEMPORAY_BUFFER_LENGTH
                                )
{
    typedef      typename _Container::size_type        size_type;
    typedef      typename _Container::value_type       _String;
    typedef      typename _String::value_type          _Char;

    if ( temp_buffer_length == 0 )
        return _TEMPORAY_BUFFER_LENGTH;

    _Char*      return_buffer   = new _Char[temp_buffer_length];
    uint32_t    ret             = 0;

    ret = GetPrivateProfileSectionNames( return_buffer,
                                         __STATIC_CAST(DWORD, temp_buffer_length),
                                         filename.c_str()
                                         );
    if ( ret > 0 ) {
        _Char*  p       = return_buffer;

        do {
            _String     element     = p;

            sections.push_back( element );
            p += element.length() + 1;
        } while ( *p );
    }
    delete [] return_buffer;

    return ret;
}


template <class _Container> inline
uint32_t
fetch_ini_section_entries( const typename _Container::mapped_type&    section_name,
                           _Container&                                result_map,
                           const typename _Container::mapped_type&    filepath,
                           typename _Container::size_type             result_buffer_length   = _TEMPORAY_BUFFER_LENGTH
                           )
{
    typedef     typename _Container::size_type                      size_type;
    typedef     typename _Container::mapped_type                    _String;
    typedef     typename _String::value_type                        _Char;

    typedef     typename _Container::allocator_type::value_type     _Pair;

    uint32_t    ret;
    _Char*      result_buffer;

    if ( result_buffer_length == 0 )
        return _TEMPORAY_BUFFER_LENGTH;

    result_buffer   = new _Char[result_buffer_length];

    ret = GetPrivateProfileSection( section_name.c_str(),
                                    __REINTERPRET_CAST(LPSTR, result_buffer),
                                    __STATIC_CAST(DWORD, result_buffer_length),
                                    filepath.c_str()
                                    );
    if ( ret > 0 ) {
        /**
         * result_buffer には、'\0' で区切られたキーと値のペアが入っています。
         * p をそれぞれの文字列の先頭とするために、strlen() + 1 だけ p を進めていき、
         * 先頭が '\0' になったら map に挿入するのを取りやめます。
         * do-while() の条件が *p になっているのは、そのためです。
         */
        _Char*      p                   = result_buffer;
        _String     split_allee;            //!< 分割される文字列。
        size_type   eq_separator_pos    = 0;
        do {
            split_allee         = p;
            eq_separator_pos    = split_allee.find( _T('=') );

            result_map.insert( _Pair( split_allee.substr( 0, eq_separator_pos ),
                                      split_allee.substr( eq_separator_pos + 1 )
                                      )
                               );

            p   += split_allee.length() + 1;
        } while ( *p );
    }

    delete [] result_buffer;

    return ret;
}


template <class _String> inline
bool write_ini_string( const _String& section_name,
                       const _String& key_name,
                       const _String& append_value,
                       const _String& filename
                       )
{
    return WritePrivateProfileString( section_name.c_str(),
                                      key_name.c_str(),
                                      append_value.c_str(),
                                      filename.c_str()
                                      ) != 0;
}
inline
bool write_ini_string( const char* const& section_name,
                       const char* const& key_name,
                       const char* const& append_value,
                       const char* const& filename
                       )
{
    return WritePrivateProfileStringA( section_name,
                                       key_name,
                                       append_value,
                                       filename
                                       ) != 0;
}
inline
bool write_ini_string( const wchar_t* const& section_name,
                       const wchar_t* const& key_name,
                       const wchar_t* const& append_value,
                       const wchar_t* const& filename
                       )
{
    return WritePrivateProfileStringW( section_name,
                                       key_name,
                                       append_value,
                                       filename
                                       ) != 0;
}


#endif  /* lxe_win32api_ini_file_hpp */
