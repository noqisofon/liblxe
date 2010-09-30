/**
 * @file  registry.hpp
 * @brief レジストリ操作用モジュール。
 */
#ifndef lxe_win32api_registry_hpp
#define lxe_win32api_registry_hpp

#include <lxe/win32api.hpp>

/**
 * 
 * @see query_registry_key_info
 */
struct registry_info_t {
    LPTSTR            kindName;                    //!< キーのクラス名。
    DWORD             kindLength;                  //!< キーのクラス名の長さ。
    DWORD             reserved;                    //!< 予約済み。
    DWORD             subkeyAmount;                //!< サブキーの数。
    DWORD             maxSubKeyLength;             //!< サブキー名の最長の長さ。
    DWORD             maxKindLength;               //!< クラス名の最長の長さ。
    DWORD             registryEntryAmount;         //!< レジストリエントリの数。
    DWORD             registryEntryNameMaxLength;  //!< レジストリエントリ名の最長の長さ。
    DWORD             registryEntryDataMaxLength;  //!< レジストリエントリのデータの最長の長さ。
    DWORD             securityDescriptorSize;      //!< セキュリティ記述子の長さ。
    FILETIME          lastWriteTime;               //!< 最終書き込み時刻。
};


/**
 * @see enumeration_registry_entry
 */
struct registry_entry_t {
    _TCHAR*   name;
    size_t    name_length;
    uint32_t  data_type;
    ubyte*    value;
    size_t    value_size;
};


union reg_dword_t {
    uint32_t    word_part;
    ubyte       byte_part[_AMOUNTS(uint32_t)];
#ifdef LXE_USE_UNION_CPP_EXTENSION
    reg_dword_t(uint32_t value = 0) : word_part(value) {
    }
    reg_dword_t(const reg_dword_t& other) : word_part(other.word_part) {
    }


    reg_dword_t& operator = (uint32_t value) {
        word_part   = value;

        return *this;
    }
    reg_dword_t& operator = (const reg_dword_t& other) {
        word_part   = other.word_part;

        return *this;
    }
#endif  /* def LXE_USE_UNION_CPP_EXTENSION */
};


union reg_qword_t {
    uint64_t    word_part;
    ubyte       byte_part[_AMOUNTS(uint64_t)];
#ifdef LXE_USE_UNION_CPP_EXTENSION
    reg_qword_t(uint64_t value = 0) : word_part(value) {
    }
    reg_qword_t(const reg_qword_t& other) : word_part(other.word_part) {
    }


    reg_qword_t& operator = (uint64_t value) {
        word_part   = value;

        return *this;
    }
    reg_qword_t& operator = (const reg_qword_t& other) {
        word_part   = other.word_part;

        return *this;
    }
#endif  /* def LXE_USE_UNION_CPP_EXTENSION */
};


/**
 * 指定されたレジストリキーを開きます。
 *    @param  key                   開いている親キーのハンドル。
 *    @param  subkey_name           開くべきサブキーの名前。
 *    @param  security_access_mask  セキュリティアクセスマスク。
 *    @param  options               予約済み。
 *
 *    @return 成功すると ERROR_SUCCESS。
 */
long open_registry_key( registry_t      parent_key,
                        const tstring&  subkey_name,
                        access_mask_t   security_access_mask,
                        registry_t*     subkey,
                        uint32_t        options             = 0
                      );


/**
 * 指定されたレジストリキーハンドルを閉じます。
 *    @param key 閉じたいレジストリキーハンドル。
 * 
 *    @return 成功すると ERROR_SUCCESS。
 */
long close_registry_key(registry_t key);


/**
 * 指定された 1 つのレジストリーキーのサブキーを列挙します。
 *    @param  key   列挙したいキーのハンドル。
 *    @subkey_names レジストリキーのサブキー名。
 */
bool get_subregistry_key(registry_t key, std::vector<tstring>& subkey_names);


/**
 * 指定されたレジストリキーを作成します。
 *     @param root_key              開きたいキーのルートハンドル。
 *     @param subkey_name           サブキーの名前。
 *     @param options               特別なオプション。
 *     @param security_access_mask  希望のセキュリティアクセス権。
 *     @param security_attribute    継承可否設定。
 *     @param result_key            取得するキーのハンドル。
 *     @param disposition           既存かどうかを示す値が格納される変数。
 * 
 *    @return 成功すると ERROR_SUCCESS。
 */
long create_registry_key( registry_t                root_key,
                          const tstring&            subkey_name,
                          uint32_t                  options,
                          access_mask_t             security_access_mask,
                          security_attr_t* const&   security_attribute,
                          registry_t*               result_key,
                          uint32_t* const           disposition
                        );


/**
 * 指定されたレジストリキーの情報を取得します。
 *     @param self_key      情報を取得したいレジストリキーのハンドル。
 *     @param result_query  情報を格納する構造体。
 */
long query_registry_key_info(registry_t self_key, registry_info_t& result_query);


/**
 * 指定されたレジストリキーに所属している、指定されたレジストリエントリ(uint32)の値を返します。
 *    @param parent_key  取得したいレジストリエントリが所属しているレジストリキー。
 *    @param entry_name  値を取得したいレジストリエントリ名。
 *
 *    @return レジストリエントリの値。
 */
uint32_t query_entry_value_dword(registry_t parent_key, tstring entry_name);


/**
 * 指定されたレジストリキーに所属している、指定されたレジストリエントリ(文字列)の値を返します。
 *    @param parent_key  取得したいレジストリエントリが所属しているレジストリキー。
 *    @param entry_name  値を取得したいレジストリエントリ名。
 *
 *    @return レジストリエントリの値。
 */
tstring query_entry_value_sz(registry_t parent_key, tstring entry_name);


/**
 * 指定されたレジストリキーに所属する、指定された 1 つのレジストリエントリの値と、そのデータ型を設定します。
 *    @param parent_key   所属させる親キーのハンドル。
 *    @param entry_name   レジストリエントリ名。
 *    @param reserved     予約済み。
 *    @param entry_type   レジストリエントリのデータ型。
 *    @param entry_value  レジストリエントリの値。
 *
 *    @return 成功したら、ERROR_SUCCESS。
 */
long set_registry_entry( registry_t                  parent_key,
                         const tstring&              entry_name,
                         uint32_t                    reserved,
                         uint32_t                    entry_type,
                         const std::vector<ubyte>&   entry_value
                       );
/**
 * 指定されたレジストリキーに所属する、指定された 1 つのレジストリエントリの値を設定します。
 *    @param parent_key   所属させる親キーのハンドル。
 *    @param entry_name   レジストリエントリ名。
 *    @param entry_value  レジストリエントリの値。
 *
 *    @return 成功したら、ERROR_SUCCESS。
 */
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const tstring&         entry_value
                       );
/**
 * 指定されたレジストリキーに所属する、指定された 1 つのレジストリエントリの値を設定します。
 *    @param parent_key   所属させる親キーのハンドル。
 *    @param entry_name   レジストリエントリ名。
 *    @param entry_value  レジストリエントリの値。
 *
 *    @return 成功したら、ERROR_SUCCESS。
 */
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const reg_dword_t&     entry_value
                       );
/**
 * 指定されたレジストリキーに所属する、指定された 1 つのレジストリエントリの値を設定します。
 *    @param parent_key   所属させる親キーのハンドル。
 *    @param entry_name   レジストリエントリ名。
 *    @param entry_value  レジストリエントリの値。
 *
 *    @return 成功したら、ERROR_SUCCESS。
 */
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const reg_qword_t&     entry_value
                       );


/**
 * 指定されたレジストリキーの index 番目のレジストリエントリの内容を entry にコピーします。
 *    @param  parent_key  指定したレジストリキー。
 *    @param  index       コピーしたいレジストリエントリのインデックス。
 *    @param  entry       コピー先の registry_entry_t 構造体。
 *
 *    @return 成功なら ERROR_SUCCESS。
 */
long enumeration_registry_entry(registry_t parent_key, uint32_t index, registry_entry_t& entry);


/**
 * 指定されたレジストリキーのサブキーを削除します。
 *    @param parent_key  削除するサブキーが所属するレジストリキー。
 *    @param subkey_name 削除するサブキーの名前。
 *
 *    @return 成功したら ERROR_SUCCESS。
 */
long delete_registry_key(registry_t parent_key, const tstring& subkey_name);
/**
 * 指定されたレジストリキーのサブキーを削除します。
 *    @param parent_key  削除するサブキーが所属するレジストリキー。
 *    @param subkey_name 削除するサブキーの名前。
 *
 *    @return 成功したら ERROR_SUCCESS。
 */
inline long delete_registry_key(registry_t parent_key, const _TCHAR* const& subkey_name) {
    return delete_registry_key( parent_key, tstring( subkey_name ) );
}


#endif  /* lxe_win32api_registry_hpp */
