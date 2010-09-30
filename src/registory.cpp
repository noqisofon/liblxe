/**
 * @file registry.cpp
 */
#include <stdafx.h>
#include <lxe/registry.hpp>


long open_registry_key( registry_t      parent_key,
                        const tstring&  subkey_name,
                        access_mask_t   security_access_mask,
                        registry_t*     subkey,
                        uint32_t        options
                        )
{
    long ret;

    ret =  RegOpenKeyEx( parent_key,
                         subkey_name.c_str(),
                         options,
                         security_access_mask,
                         subkey
                         );
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


long close_registry_key(registry_t key)
{
    long ret;

    ret =  RegCloseKey( key );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


bool get_subregistry_key(registry_t  key, std::vector<tstring>& subkey_names)
{
    const size_t   DEFAULT_LENGTH  = 256;

    _TCHAR*   name_buffer          = NULL;
    size_t    name_buffer_length   = DEFAULT_LENGTH;

    long      ret           = 0;
    int       subkey_index  = 0;

    name_buffer = new _TCHAR[name_buffer_length];

    while ( ret != ERROR_NO_MORE_ITEMS ) {
        memset( name_buffer, 0, name_buffer_length );
        ret = RegEnumKeyEx( key,
                            subkey_index,
                            name_buffer,
                            __REINTERPRET_CAST(LPDWORD, &name_buffer_length),
                            0,
                            NULL,
                            NULL,
                            NULL
                            );

        if ( ERROR_MORE_DATA == ret || ERROR_SUCCESS == ret ) {
            subkey_names.push_back( name_buffer );
        } else {

            if ( ret == ERROR_NO_MORE_ITEMS )
                break;
            else {
                delete [] name_buffer;
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
                throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */
                return false;
            }

        }
        ++ subkey_index;
        name_buffer_length = DEFAULT_LENGTH;
    }
    delete [] name_buffer;

    return true;
}


long create_registry_key( registry_t                root_key,
                          const tstring&            subkey_name,
                          uint32_t                  options,
                          access_mask_t             security_access_mask,
                          security_attr_t* const&   security_attribute,
                          registry_t*               result_key,
                          uint32_t* const           disposition
                          )
{
    long ret;

    ret = RegCreateKeyEx( root_key,
                          subkey_name.c_str(),
                          0,
                          NULL,
                          options,
                          security_access_mask,
                          security_attribute,
                          result_key,
                          __REINTERPRET_CAST(DWORD* const, disposition)
                          );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret ) {

        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
    }
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


long query_registry_key_info(registry_t self_key, registry_info_t& result_query)
{
    long ret;

    ret =  RegQueryInfoKey( self_key,
                            NULL,
                            NULL,
                            NULL,
                            &result_query.subkeyAmount,
                            &result_query.maxSubKeyLength,
                            &result_query.maxKindLength,
                            &result_query.registryEntryAmount,
                            &result_query.registryEntryNameMaxLength,
                            &result_query.registryEntryDataMaxLength,
                            &result_query.securityDescriptorSize,
                            &result_query.lastWriteTime
                            );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


tstring query_entry_value_sz(registry_t parent_key, tstring entry_name)
{
    BYTE*  buffer       = NULL;
    DWORD  buffer_size  = 0;

    long   ret;

    ret  = RegQueryValueEx( parent_key,
                            entry_name.c_str(),
                            NULL,
                            NULL,
                            buffer,
                            &buffer_size
                            );

    if ( buffer_size == 0 ) {
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

        return tstring();
    }

    buffer  = new BYTE[buffer_size];

    ret     = RegQueryValueEx( parent_key,
                               entry_name.c_str(),
                               NULL,
                               NULL,
                               buffer,
                               &buffer_size
                               );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret ) {
        delete [] buffer;

        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
    }
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    tstring result_sz( __REINTERPRET_CAST(_TCHAR *, buffer) );

    delete [] buffer;

    return result_sz;
}


uint32_t query_entry_value_dword(registry_t parent_key, tstring entry_name)
{
    reg_dword_t  result;
    size_t       result_size  = sizeof(result);

    long         ret;


    ret = RegQueryValueEx( parent_key,
                           entry_name.c_str(),
                           NULL,
                           NULL,
                           result.byte_part,
                           __REINTERPRET_CAST(LPDWORD, &result_size)
                           );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return result.word_part;
}




/**
 * 指定されたレジストリキーに所属する、指定された 1 つのレジストリエントリのデータと、データ型を設定します。
 *    @param parent_key  所属させる親キーのハンドル。
 *    @param entry_name  レジストリエントリ名。
 *    @param reserved    予約済み。
 *    @param entry_type  レジストリエントリのデータ型。
 *    @param レジストリエントリのデータ。
 */
long set_registry_entry( registry_t                  parent_key,
                         const tstring&              entry_name,
                         uint32_t                    reserved,
                         uint32_t                    entry_type,
                         const std::vector<ubyte>&   entry_value
                         )
{
    long ret;

    ret = RegSetValueEx( parent_key,
                         entry_name.c_str(),
                         reserved,
                         entry_type,
                         &entry_value.at( 0 ),
                         __STATIC_CAST( DWORD, entry_value.size() )
                         );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const tstring&         entry_value
                         )
{
    long ret;

    ret= RegSetValueEx( parent_key,
                        entry_name.c_str(),
                        0,
                        REG_SZ,
                        __REINTERPRET_CAST( const BYTE*, entry_value.c_str() ),
                        __STATIC_CAST( DWORD, entry_value.length() )
                        );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const reg_dword_t&     entry_value
                         )
{
    long ret;

    ret = RegSetValueEx( parent_key,
                         entry_name.c_str(),
                         0,
                         REG_DWORD,
                         entry_value.byte_part,
                         sizeof(entry_value.byte_part)
                         );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}
long set_registry_entry( registry_t         parent_key,
                         const tstring&     entry_name,
                         const reg_qword_t& entry_value
                         )
{
    long ret;

    ret = RegSetValueEx( parent_key,
                         entry_name.c_str(),
                         0,
                         REG_QWORD,
                         entry_value.byte_part,
                         sizeof(entry_value.byte_part)
                         );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


long enumeration_registry_entry(registry_t parent_key, uint32_t index, registry_entry_t& entry)
{
    long ret;

    ret = RegEnumValue( parent_key,
                        __STATIC_CAST(DWORD, index),
                        __REINTERPRET_CAST(LPSTR, entry.name),
                        __REINTERPRET_CAST(LPDWORD, &entry.name_length),
                        NULL,
                        __REINTERPRET_CAST(LPDWORD, &entry.data_type),
                        __REINTERPRET_CAST(LPBYTE, entry.value),
                        __REINTERPRET_CAST(LPDWORD, &entry.value_size)
                        );

    return ret;
}


long delete_registry_key(registry_t parent_key, const tstring& subkey_name)
{
    long ret = RegDeleteKey( parent_key, subkey_name.c_str() );

#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( ERROR_SUCCESS != ret )
        throw get_error_for_hr( ret, _T(_T(__FILE__)), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}
