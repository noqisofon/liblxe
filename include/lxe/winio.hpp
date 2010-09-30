/**
 * @file winio.hpp
 * 
 */
#ifndef lxe_win32api_winio_hpp
#define lxe_win32api_winio_hpp

#include <vector>
#include <lxe/win32api.hpp>


/**
 * %TMP% ���ȗ��`���ŕԂ��܂��B
 */
tstring get_temp_path();


/**
 * %TMP% ��Ԃ��܂��B
 */
tstring get_temp_longpath();


/**
 * �w�肳�ꂽ�p�X�A�v���t�B�b�N�X�A��������ꎞ�t�@�C������Ԃ��܂��B
 *     @param base_path    �ꎞ�t�@�C�������f�B���N�g���p�X�B
 *     @param prefix       �ꎞ�t�@�C���̃v���t�B�b�N�X�B
 *     @param unique_seed  �����_���Ȗ��O�𐶐�����ׂ̗����l�B
 *
 *     @return �ꎞ�t�@�C�����B
 */
tstring get_temp_filename(const tstring& base_path, const tstring& prefix, uint32_t unique_seed);
inline tstring get_temp_filename(const _TCHAR* base_path, const _TCHAR* prefix, uint32_t unique_seed) {
    return get_temp_filename( tstring( base_path ), tstring( prefix ), unique_seed );
}
/**
 * �w�肳�ꂽ�p�X�A�v���t�B�b�N�X�A��������ꎞ�t�@�C������Ԃ��܂��B
 *     @param base_path    �ꎞ�t�@�C�������f�B���N�g���p�X�B
 *     @param unique_seed  �����_���Ȗ��O�𐶐�����ׂ̗����l�B
 *
 *     @return �ꎞ�t�@�C�����B
 */
tstring get_temp_filename(const tstring& base_path, uint32_t unique_seed);
inline tstring get_temp_filename(const _TCHAR* base_path, uint32_t unique_seed) {
    return get_temp_filename( tstring( base_path ), unique_seed );
}


/**
 * �ȗ��`���̃p�X���ȗ�����Ă��Ȃ��p�X�ɕϊ����ĕԂ��܂��B
 *     @param short_path �ȗ��`���̃p�X�B
 *
 *     @return �ȗ�����Ă��Ȃ��p�X�B
 */
tstring get_long_path(const tstring& short_path);
inline tstring get_long_path(const _TCHAR* short_path) {
    return get_long_path( tstring( short_path ) );
}


/**
 * �w�肳�ꂽ�t�@�C���A�܂��̓f�B���N�g���̑������擾���܂��B
 *     @param  filepath   �������擾�������t�@�C���A�܂��̓f�B���N�g���B
 *
 *     @return �t�@�C���A�܂��̓f�B���N�g���̑����B
 */
uint32_t get_file_attributes(const tstring& filepath);
inline uint32_t get_file_attributes(const _TCHAR* const& filepath) {
    return get_file_attributes( tstring( filepath ) );
}


/**
 * �t�@�C���A�܂��̓f�B���N�g�����쐬���邩�J���A����ɃA�N�Z�X����ׂɗ��p�ł���n���h����Ԃ��܂��B
 *    @param  filepath              �쐬�A�܂��͊J���ΏƂ̃t�@�C���B
 *    @param  desire_access         �A�N�Z�X���[�h�B
 *    @param  share_mode            ���L���[�h�B
 *    @param  security_attributes   �Z�L�����e�B�L�q�q�ւ̃|�C���^�B
 *    @param  creation_disposition  �쐬���@�B
 *    @param  flags_and_attributes  �t�@�C�������B
 *    @param  template_file         �e���v���[�g�t�@�C���̃n���h���B
 *
 *    @return �w�肵���t�@�C���ɑ΂���n���h���B
 */
handle_t create_file( const tstring&            filepath,
                      uint32_t                  desire_access,
                      uint32_t                  share_mode              = FILE_SHARE_READ,
                      security_attr_t* const&   security_attributes     = NULL,
                      uint32_t                  creation_disposition    = OPEN_ALWAYS,
                      uint32_t                  flags_and_attributes    = 0,
                      handle_t                  template_file           = NULL
                    );
/**
 * �t�@�C���A�܂��̓f�B���N�g�����쐬���邩�J���A����ɃA�N�Z�X����ׂɗ��p�ł���n���h����Ԃ��܂��B
 *    @param  filepath              �쐬�A�܂��͊J���ΏƂ̃t�@�C���B
 *    @param  desire_access         �A�N�Z�X���[�h�B
 *    @param  share_mode            ���L���[�h�B
 *    @param  security_attributes   �Z�L�����e�B�L�q�q�ւ̃|�C���^�B
 *    @param  creation_disposition  �쐬���@�B
 *    @param  flags_and_attributes  �t�@�C�������B
 *    @param  template_file         �e���v���[�g�t�@�C���̃n���h���B
 *
 *    @return �w�肵���t�@�C���ɑ΂���n���h���B
 */
inline handle_t create_file( const _TCHAR* const&       filepath,
                             uint32_t                   desire_access,
                             uint32_t                   share_mode              = FILE_SHARE_READ,
                             security_attr_t* const&    security_attributes     = NULL,
                             uint32_t                   creation_disposition    = OPEN_ALWAYS,
                             uint32_t                   flags_and_attributes    = 0,
                             handle_t                   template_file           = NULL
                           )
{
    return create_file( tstring( filepath ),
                        desire_access,
                        share_mode,
                        security_attributes,
                        creation_disposition,
                        flags_and_attributes,
                        template_file
                      );
}


/**
 * �w�肳�ꂽ���O�̃f�B���N�g�����쐬���܂��B
 *    @param pathname             �쐬����f�B���N�g�����B
 *    @param security_attributes  �Z�L�����e�B�L�q�q�ւ̃|�C���^�B
 *
 *    @return ����������^�B
 */
bool create_directory( const tstring&           pathname,
                       security_attr_t* const&  security_attributes = NULL
                     );
inline bool create_directory( const _TCHAR*             pathname,
                              security_attr_t* const&   security_attributes = NULL
                            ) {
    return create_directory( tstring( pathname ),
                             security_attributes
                           );
}


bool create_recursive_directory(const tstring& path);
inline bool create_recursive_directory(const _TCHAR* path) {

    return create_recursive_directory( tstring( path ) );
}


/**
 * �w�肳�ꂽ�t�@�C�����������܂��B
 */
tstring search_path(const tstring& find_path, const tstring& filename, tstring& filepath);
inline tstring search_path(const _TCHAR* find_path, const _TCHAR* filename, _TCHAR* filepath) {
    return search_path( tstring( find_path ), tstring( filename ), tstring( filepath ) );
}
/**
 * �w�肳�ꂽ�t�@�C�����������܂��B
 */
tstring search_path(const tstring& find_path, const tstring& filename);
inline tstring search_path(const _TCHAR*& find_path, const _TCHAR*& filename) {
    return search_path( tstring( find_path ), tstring( filename ) );
}
/**
 * �w�肳�ꂽ�t�@�C�����������܂��B
 */
inline tstring search_path(const tstring& find_path) {
    tstring::size_type   last_separator_pos = find_path.find_last_of( _T('\\') );

    if ( last_separator_pos == tstring::npos )
        return find_path;

    return search_path( find_path.substr( 0, last_separator_pos ),
                        find_path.substr( last_separator_pos + 1 )
                      );
}
inline tstring search_path(const _TCHAR* find_path) {
    return search_path( tstring( find_path ) );
}


/**
 * �w�肳�ꂽ�p�X�����݂�����^��Ԃ��܂��B
 *     @param find_path �w�肵���p�X�B
 * 
 *     @return �p�X�����݂�����^�B
 */
bool is_exists(const tstring& find_path);
inline bool is_exists(const _TCHAR* find_path) {
    return is_exists( tstring( find_path ) );
}


/**
 * ���݂̃v���Z�X�̃J�����g�f�B���N�g���̃p�X��Ԃ��܂��B
 *     @return ���݂̃v���Z�X�̃J�����g�f�B���N�g���̃p�X�B
 */
tstring get_current_directory();


/**
 * �w�肳�ꂽ�t�@�C�����폜���܂��B
 *    @param original_path  �폜�������t�@�C�����B
 * 
 *    @return ����������^�B
 */
bool delete_file(const tstring& original_filepath);
inline bool delete_file(const _TCHAR* original_filepath) {
    return delete_file( tstring( original_filepath ) );
}


/**
 * �w�肳�ꂽ��̃f�B���N�g�����폜���܂��B
 *    @param original_path  �폜�������f�B���N�g�����B
 * 
 *    @return ����������^�B
 */
bool delete_directory(const tstring& original_path);
inline bool delete_directory(const _TCHAR* original_path) {
    return delete_directory( tstring( original_path ) );
}


/**
 * �w�肳�ꂽ�f�B���N�g���ȉ���S�č폜���܂��B
 *    @param original_path  �폜�������f�B���N�g�����B
 * 
 *    @return ����������^�B
 */
bool delete_directory_forse(const tstring& original_path);
/**
 * �w�肳�ꂽ�f�B���N�g���ȉ���S�č폜���܂��B
 *    @param original_path  �폜�������f�B���N�g�����B
 *
 *    @return ����������^�B
 */
inline bool delete_directory_forse(const _TCHAR* original_path) {
    return delete_directory_forse( tstring( original_path ) );
}


/**
 * �w�肳�ꂽ�p�X����w�肳�ꂽ�p�^�[���ɓ��Ă͂܂�t�@�C�������擾���܂��B
 *    @param original_path  �w�肵���p�X�B
 *    @param pattern        �擾�������t�@�C�����̃p�^�[���B
 *    @param discoveries    ���������t�@�C�������i�[���Ă����R���e�i�B
 * 
 *    @return ����������^�B
 */
bool find_directory(const tstring& original_path, const tstring& pattern, std::vector<tstring>& discoveries);
/**
 * �w�肳�ꂽ�p�X����w�肳�ꂽ�p�^�[���ɓ��Ă͂܂�t�@�C�������擾���܂��B
 *    @param original_path  �w�肵���p�X�B
 *    @param pattern        �擾�������t�@�C�����̃p�^�[���B
 *    @param discoveries         ���������t�@�C�������i�[���Ă����R���e�i�B
 * 
 *    @return ����������^�B
 */
inline bool find_directory(const _TCHAR* original_path, const _TCHAR* pattern, std::vector<tstring>& discoveries) {
    return find_directory( tstring( original_path ), tstring( pattern ), discoveries );
}


/**
 * 
 */
tstring get_fullpath(const tstring& original_path);
inline tstring get_fullpath(const _TCHAR* original_path) {
    return get_fullpath( tstring( original_path ) );
}


tstring convert_platform_path(const tstring& original_path);
inline tstring convert_platform_path(const _TCHAR* original_path) {
    return convert_platform_path( tstring( original_path ) );
}


tstring get_root_path(const tstring& local_path);
inline tstring get_root_path(const _TCHAR* local_path) {
    return get_root_path( tstring( local_path ) );
}


tstring expand_path(const tstring& local_path);
inline tstring expand_path(const _TCHAR* local_path) {
    return expand_path( tstring( local_path ) );
}


#endif  /* lxe_win32api_winio_hpp */
