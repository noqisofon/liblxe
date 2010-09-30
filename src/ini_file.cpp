/**
 * @file ini_file.cpp
 */
#include <stdafx.h>

#include <lxe/ini_file.hpp>
using namespace std;


uint32_t get_private_profile_section( const tstring&            section_name,
                                      map<tstring, tstring>&    result_map,
                                      size_t                    result_buffer_length,
                                      const tstring&            filepath
                                      )
{
    if ( result_buffer_length == 0 )
        return _TEMPORAY_BUFFER_LENGTH;

    _TCHAR*     result_buffer   = new _TCHAR[result_buffer_length];
    uint32_t    ret             = 0;

    ret = GetPrivateProfileSection( section_name.c_str(),
                                    __REINTERPRET_CAST(LPSTR, result_buffer),
                                    __STATIC_CAST(DWORD, result_buffer_length),
                                    filepath.c_str()
                                    );
    if ( ret > 0 ) {
        /**
         * result_buffer �ɂ́A'\0' �ŋ�؂�ꂽ�L�[�ƒl�̃y�A�������Ă��܂��B
         * p �����ꂼ��̕�����̐擪�Ƃ��邽�߂ɁAstrlen() + 1 ���� p ��i�߂Ă����A
         * ������ '\0' �� 2 �A���ő����Ƃ���� map �ɑ}������̂�����߂܂��B
         * do-while() �̏����� *p �ɂȂ��Ă���̂́A���̂��߂ł��B
         */
        _TCHAR*  p           = result_buffer;
        tstring  splitee;               //!< ��������镶����B
        tstring  separator( _T("=") );  //!< ��؂蕶����B
        do {
            splitee     = p;
            vector<tstring>    v;
            split_all( splitee, v, separator );

            result_map.insert( pair<tstring, tstring>( v[0], v[1] ) );

            p += splitee.length() + 1;
        } while ( *p );
    }

    delete [] result_buffer;

    return ret;

}


uint32_t get_private_profile_section_names( vector<tstring>&    sections,
                                            size_t              temp_buffer_length,
                                            const tstring&      filename
                                            )
{
    if ( temp_buffer_length == 0 )
        return _TEMPORAY_BUFFER_LENGTH;

    _TCHAR*     return_buffer   = new _TCHAR[temp_buffer_length];
    uint32_t    ret             = 0;

    ret = GetPrivateProfileSectionNames( return_buffer,
                                         __STATIC_CAST(DWORD, temp_buffer_length),
                                         filename.c_str()
                                         );
    if ( ret > 0 ) {
        _TCHAR*     p = return_buffer;

        do {
            sections.push_back( tstring( p ) );
            p += _tcslen( p ) + 1;
        } while ( *p );
    }

    delete [] return_buffer;

    return ret;
}


uint32_t get_private_profile_int( const tstring&    section_name,
                                  const tstring&    key,
                                  int               default_value,
                                  const tstring&    filename
                                  )
{
    uint32_t ret;

    ret = GetPrivateProfileInt( section_name.c_str(),
                                key.c_str(),
                                default_value,
                                filename.c_str()
                                );

    return ret;
}


tstring get_ini_string( const tstring&    section_name,
                        const tstring&    key,
                        const tstring&    filename,
                        const tstring&    default_value,
                        size_t            string_length
                        )
{
    if ( string_length == 0 )
        return default_value;

    tstring     result;
    _TCHAR*     temp_buffer  = new _TCHAR[string_length];
    uint32_t    ret;

    ret = GetPrivateProfileString( section_name.c_str(),
                                   key.c_str(),
                                   default_value.c_str(),
                                   temp_buffer,
                                   __STATIC_CAST(DWORD, string_length),
                                   filename.c_str()
                                   );
    if ( ret ) {
        result = temp_buffer;
    }
    delete [] temp_buffer;

    return result;
}


bool write_private_profile_string( const tstring&   section_name,
                                   const tstring&   key,
                                   const tstring&   value,
                                   const tstring&   filename
                                   )
{
    return WritePrivateProfileString( section_name.c_str(),
                                      key.c_str(),
                                      value.c_str(),
                                      filename.c_str()
                                      ) != 0;
}
