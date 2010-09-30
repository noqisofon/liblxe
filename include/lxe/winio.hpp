/**
 * @file winio.hpp
 * 
 */
#ifndef lxe_win32api_winio_hpp
#define lxe_win32api_winio_hpp

#include <vector>
#include <lxe/win32api.hpp>


/**
 * %TMP% を省略形式で返します。
 */
tstring get_temp_path();


/**
 * %TMP% を返します。
 */
tstring get_temp_longpath();


/**
 * 指定されたパス、プレフィックス、整数から一時ファイル名を返します。
 *     @param base_path    一時ファイルを作るディレクトリパス。
 *     @param prefix       一時ファイルのプレフィックス。
 *     @param unique_seed  ランダムな名前を生成する為の乱数値。
 *
 *     @return 一時ファイル名。
 */
tstring get_temp_filename(const tstring& base_path, const tstring& prefix, uint32_t unique_seed);
inline tstring get_temp_filename(const _TCHAR* base_path, const _TCHAR* prefix, uint32_t unique_seed) {
    return get_temp_filename( tstring( base_path ), tstring( prefix ), unique_seed );
}
/**
 * 指定されたパス、プレフィックス、整数から一時ファイル名を返します。
 *     @param base_path    一時ファイルを作るディレクトリパス。
 *     @param unique_seed  ランダムな名前を生成する為の乱数値。
 *
 *     @return 一時ファイル名。
 */
tstring get_temp_filename(const tstring& base_path, uint32_t unique_seed);
inline tstring get_temp_filename(const _TCHAR* base_path, uint32_t unique_seed) {
    return get_temp_filename( tstring( base_path ), unique_seed );
}


/**
 * 省略形式のパスを省略されていないパスに変換して返します。
 *     @param short_path 省略形式のパス。
 *
 *     @return 省略されていないパス。
 */
tstring get_long_path(const tstring& short_path);
inline tstring get_long_path(const _TCHAR* short_path) {
    return get_long_path( tstring( short_path ) );
}


/**
 * 指定されたファイル、またはディレクトリの属性を取得します。
 *     @param  filepath   属性を取得したいファイル、またはディレクトリ。
 *
 *     @return ファイル、またはディレクトリの属性。
 */
uint32_t get_file_attributes(const tstring& filepath);
inline uint32_t get_file_attributes(const _TCHAR* const& filepath) {
    return get_file_attributes( tstring( filepath ) );
}


/**
 * ファイル、またはディレクトリを作成するか開き、それにアクセスする為に利用できるハンドルを返します。
 *    @param  filepath              作成、または開く対照のファイル。
 *    @param  desire_access         アクセスモード。
 *    @param  share_mode            共有モード。
 *    @param  security_attributes   セキュリティ記述子へのポインタ。
 *    @param  creation_disposition  作成方法。
 *    @param  flags_and_attributes  ファイル属性。
 *    @param  template_file         テンプレートファイルのハンドル。
 *
 *    @return 指定したファイルに対するハンドル。
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
 * ファイル、またはディレクトリを作成するか開き、それにアクセスする為に利用できるハンドルを返します。
 *    @param  filepath              作成、または開く対照のファイル。
 *    @param  desire_access         アクセスモード。
 *    @param  share_mode            共有モード。
 *    @param  security_attributes   セキュリティ記述子へのポインタ。
 *    @param  creation_disposition  作成方法。
 *    @param  flags_and_attributes  ファイル属性。
 *    @param  template_file         テンプレートファイルのハンドル。
 *
 *    @return 指定したファイルに対するハンドル。
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
 * 指定された名前のディレクトリを作成します。
 *    @param pathname             作成するディレクトリ名。
 *    @param security_attributes  セキュリティ記述子へのポインタ。
 *
 *    @return 成功したら真。
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
 * 指定されたファイルを検索します。
 */
tstring search_path(const tstring& find_path, const tstring& filename, tstring& filepath);
inline tstring search_path(const _TCHAR* find_path, const _TCHAR* filename, _TCHAR* filepath) {
    return search_path( tstring( find_path ), tstring( filename ), tstring( filepath ) );
}
/**
 * 指定されたファイルを検索します。
 */
tstring search_path(const tstring& find_path, const tstring& filename);
inline tstring search_path(const _TCHAR*& find_path, const _TCHAR*& filename) {
    return search_path( tstring( find_path ), tstring( filename ) );
}
/**
 * 指定されたファイルを検索します。
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
 * 指定されたパスが存在したら真を返します。
 *     @param find_path 指定したパス。
 * 
 *     @return パスが存在したら真。
 */
bool is_exists(const tstring& find_path);
inline bool is_exists(const _TCHAR* find_path) {
    return is_exists( tstring( find_path ) );
}


/**
 * 現在のプロセスのカレントディレクトリのパスを返します。
 *     @return 現在のプロセスのカレントディレクトリのパス。
 */
tstring get_current_directory();


/**
 * 指定されたファイルを削除します。
 *    @param original_path  削除したいファイル名。
 * 
 *    @return 成功したら真。
 */
bool delete_file(const tstring& original_filepath);
inline bool delete_file(const _TCHAR* original_filepath) {
    return delete_file( tstring( original_filepath ) );
}


/**
 * 指定された空のディレクトリを削除します。
 *    @param original_path  削除したいディレクトリ名。
 * 
 *    @return 成功したら真。
 */
bool delete_directory(const tstring& original_path);
inline bool delete_directory(const _TCHAR* original_path) {
    return delete_directory( tstring( original_path ) );
}


/**
 * 指定されたディレクトリ以下を全て削除します。
 *    @param original_path  削除したいディレクトリ名。
 * 
 *    @return 成功したら真。
 */
bool delete_directory_forse(const tstring& original_path);
/**
 * 指定されたディレクトリ以下を全て削除します。
 *    @param original_path  削除したいディレクトリ名。
 *
 *    @return 成功したら真。
 */
inline bool delete_directory_forse(const _TCHAR* original_path) {
    return delete_directory_forse( tstring( original_path ) );
}


/**
 * 指定されたパスから指定されたパターンに当てはまるファイル名を取得します。
 *    @param original_path  指定したパス。
 *    @param pattern        取得したいファイル名のパターン。
 *    @param discoveries    見つかったファイル名を格納しておくコンテナ。
 * 
 *    @return 成功したら真。
 */
bool find_directory(const tstring& original_path, const tstring& pattern, std::vector<tstring>& discoveries);
/**
 * 指定されたパスから指定されたパターンに当てはまるファイル名を取得します。
 *    @param original_path  指定したパス。
 *    @param pattern        取得したいファイル名のパターン。
 *    @param discoveries         見つかったファイル名を格納しておくコンテナ。
 * 
 *    @return 成功したら真。
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
