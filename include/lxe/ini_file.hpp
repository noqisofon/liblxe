/**
 * @file  ini_file.hpp
 * @brief �ݒ�t�@�C������p���W���[���B
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
 * ini �t�@�C���p�̐^�U�l�H�� 1 �ŁA�^��\���܂��B
 */
#define     INI_VALUE_YES           _T("yes")
/**
 * @def INI_VALUE_SHORT_YES
 * @since 2010-09-03
 * ini �t�@�C���p�̐^�U�l�H�� 1 �ŁA�^��\���܂��B
 * INI_VALUE_YES �̒Z���o�[�W�����ł��B
 */
#define     INI_VALUE_SHORT_YES     _T("y")
/**
 * @def INI_VALUE_NO
 * @since 2010-09-03
 * ini �t�@�C���p�̐^�U�l�H�� 1 �ŋU��\���܂��B
 */
#define     INI_VALUE_NO            _T("no")
/**
 * @def INI_VALUE_SHORT_NO
 * @since 2010-09-03
 * ini �t�@�C���p�̐^�U�l�H�� 1 �ŋU��\���܂��B
 * INI_VALUE_NO �̒Z���o�[�W�����ł��B
 */
#define     INI_VALUE_SHORT_NO      _T("n")


/**
 * @def INI_VALUE_NIL
 * @since 2010-10-04T08:56:38+0900
 * ini �t�@�C���p�̖����Ȓl��\���܂��B
 */
#define     INI_VALUE_NIL           _T("nil")


/**
 * *.ini �t�@�C������A�w�肳�ꂽ�Z�N�V�������̑S�ẴL�[�ƒl���擾���܂��B
 * <pre>
 * �����ŌĂяo�� GetPrivateProfileSection() ���K�v�ȃo�b�t�@��Ԃ��Ă���Ȃ��̂ŁA
 * �Ăяo�������m�ۂ���ׂ��o�b�t�@���w�肷��K�v������܂��B
 * </pre>
 *    @param section_name          �L�[�ƒl���擾�������Z�N�V�������B
 *    @param result_map            ��񂪊i�[�����R���e�i�B
 *    @param result_buffer_length  �m�ۂ���o�b�t�@�̒����B
 *    @param filepath              *.ini �t�@�C���̖��O�B
 *
 *    @return �o�b�t�@�Ɋi�[���ꂽ������B
 */
uint32_t get_private_profile_section( const tstring&               section_name,
                                      std::map<tstring, tstring>&  result_map,
                                      size_t                       result_buffer_length,
                                      const tstring&               filepath
                                      );


/**
 * *.ini �t�@�C������S�ẴZ�N�V�����̖��O���擾���܂��B
 *    @param sections             �Z�N�V������������x�N�^�R���e�i�ł��B
 *    @param temp_buffer_length   �e���|�����o�b�t�@�̃T�C�Y�B
 *    @param filename             *.ini �t�@�C���̖��O�B
 */
uint32_t get_private_profile_section_names( std::vector<tstring>& sections,
                                            size_t                temp_buffer_length,
                                            const tstring&        filename
                                            );


/**
 * �w�肳�ꂽ *.ini �t�@�C���̎w�肳�ꂽ�Z�N�V�������ɂ���A�w�肳�ꂽ�L�[�Ɋ֘A�t�����Ă��鐮�����擾���܂��B
 *    @param section_name  �Z�N�V�������B
 *    @param key           �L�[���B
 *    @param default_value �L�[����������Ȃ������Ƃ��ɕԂ��ׂ��l�B
 *    @param filename      *.ini �t�@�C���̖��O�B
 */
uint32_t get_private_profile_int( const tstring&    section_name,
                                  const tstring&    key,
                                  int               default_value,
                                  const tstring&    filename
                                  );


/**
 * �w�肳�ꂽ *.ini �t�@�C���̎w�肳�ꂽ�Z�N�V�������ɂ���A�w�肳�ꂽ�L�[�Ɋ֘A�t�����Ă��镶������擾���܂��B
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
 * �w�肳�ꂽ *.ini �t�@�C���́A�w�肳�ꂽ�Z�N�V�������ɁA�w�肳�ꂽ�L�[���Ƃ�
 * ��Ɋ֘A�t����ꂽ�l���i�[���܂��B
 *    @param section_name  �Z�N�V�������B
 *    @param key           �L�[���B
 *    @param value         �L�[���Ɗ֘A����l�B
 *    @param filename      *.ini �t�@�C�����B
 *
 *    @return ����������^�B
 */
bool write_private_profile_string( const tstring& section_name,
                                   const tstring& key,
                                   const tstring& value,
                                   const tstring& filename
                                   );
/**
 * �w�肳�ꂽ *.ini �t�@�C���́A�w�肳�ꂽ�Z�N�V�������ɁA�w�肳�ꂽ�L�[���Ƃ�
 * ��Ɋ֘A�t����ꂽ�l���i�[���܂��B
 *    @param section_name  �Z�N�V�������B
 *    @param key           �L�[���B
 *    @param value         �L�[���Ɗ֘A����l�B
 *    @param filename      *.ini �t�@�C�����B
 *
 *    @return ����������^�B
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
 * �w�肳�ꂽ *.ini �t�@�C���́A�w�肳�ꂽ�Z�N�V�������ɁA�w�肳�ꂽ�L�[���Ƃ�
 * ��Ɋ֘A�t����ꂽ�l���i�[���܂��B
 *    @param section_name  �Z�N�V�������B
 *    @param key           �L�[���B
 *    @param value         �L�[���Ɗ֘A����l�B
 *    @param filename      *.ini �t�@�C�����B
 *
 *    @return ����������^�B
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
 * *.ini �t�@�C������S�ẴZ�N�V�����̖��O���擾���܂��B
 *    @param sections             �Z�N�V������������x�N�^�R���e�i�ł��B
 *    @param temp_buffer_length   �e���|�����o�b�t�@�̃T�C�Y�B
 *    @param filename             *.ini �t�@�C���̖��O�B
 *
 *    @return �o�b�t�@�Ɋi�[�����f�[�^�̒�����Ԃ��܂��B
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
         * result_buffer �ɂ́A'\0' �ŋ�؂�ꂽ�L�[�ƒl�̃y�A�������Ă��܂��B
         * p �����ꂼ��̕�����̐擪�Ƃ��邽�߂ɁAstrlen() + 1 ���� p ��i�߂Ă����A
         * �擪�� '\0' �ɂȂ����� map �ɑ}������̂�����߂܂��B
         * do-while() �̏����� *p �ɂȂ��Ă���̂́A���̂��߂ł��B
         */
        _Char*      p                   = result_buffer;
        _String     split_allee;            //!< ��������镶����B
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
