/**
 * @file  registry.hpp
 * @brief ���W�X�g������p���W���[���B
 */
#ifndef lxe_win32api_registry_hpp
#define lxe_win32api_registry_hpp

#include <lxe/win32api.hpp>

/**
 * 
 * @see query_registry_key_info
 */
struct registry_info_t {
    LPTSTR            kindName;                    //!< �L�[�̃N���X���B
    DWORD             kindLength;                  //!< �L�[�̃N���X���̒����B
    DWORD             reserved;                    //!< �\��ς݁B
    DWORD             subkeyAmount;                //!< �T�u�L�[�̐��B
    DWORD             maxSubKeyLength;             //!< �T�u�L�[���̍Œ��̒����B
    DWORD             maxKindLength;               //!< �N���X���̍Œ��̒����B
    DWORD             registryEntryAmount;         //!< ���W�X�g���G���g���̐��B
    DWORD             registryEntryNameMaxLength;  //!< ���W�X�g���G���g�����̍Œ��̒����B
    DWORD             registryEntryDataMaxLength;  //!< ���W�X�g���G���g���̃f�[�^�̍Œ��̒����B
    DWORD             securityDescriptorSize;      //!< �Z�L�����e�B�L�q�q�̒����B
    FILETIME          lastWriteTime;               //!< �ŏI�������ݎ����B
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
 * �w�肳�ꂽ���W�X�g���L�[���J���܂��B
 *    @param  key                   �J���Ă���e�L�[�̃n���h���B
 *    @param  subkey_name           �J���ׂ��T�u�L�[�̖��O�B
 *    @param  security_access_mask  �Z�L�����e�B�A�N�Z�X�}�X�N�B
 *    @param  options               �\��ς݁B
 *
 *    @return ��������� ERROR_SUCCESS�B
 */
long open_registry_key( registry_t      parent_key,
                        const tstring&  subkey_name,
                        access_mask_t   security_access_mask,
                        registry_t*     subkey,
                        uint32_t        options             = 0
                      );


/**
 * �w�肳�ꂽ���W�X�g���L�[�n���h������܂��B
 *    @param key ���������W�X�g���L�[�n���h���B
 * 
 *    @return ��������� ERROR_SUCCESS�B
 */
long close_registry_key(registry_t key);


/**
 * �w�肳�ꂽ 1 �̃��W�X�g���[�L�[�̃T�u�L�[��񋓂��܂��B
 *    @param  key   �񋓂������L�[�̃n���h���B
 *    @subkey_names ���W�X�g���L�[�̃T�u�L�[���B
 */
bool get_subregistry_key(registry_t key, std::vector<tstring>& subkey_names);


/**
 * �w�肳�ꂽ���W�X�g���L�[���쐬���܂��B
 *     @param root_key              �J�������L�[�̃��[�g�n���h���B
 *     @param subkey_name           �T�u�L�[�̖��O�B
 *     @param options               ���ʂȃI�v�V�����B
 *     @param security_access_mask  ��]�̃Z�L�����e�B�A�N�Z�X���B
 *     @param security_attribute    �p���ېݒ�B
 *     @param result_key            �擾����L�[�̃n���h���B
 *     @param disposition           �������ǂ����������l���i�[�����ϐ��B
 * 
 *    @return ��������� ERROR_SUCCESS�B
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
 * �w�肳�ꂽ���W�X�g���L�[�̏����擾���܂��B
 *     @param self_key      �����擾���������W�X�g���L�[�̃n���h���B
 *     @param result_query  �����i�[����\���́B
 */
long query_registry_key_info(registry_t self_key, registry_info_t& result_query);


/**
 * �w�肳�ꂽ���W�X�g���L�[�ɏ������Ă���A�w�肳�ꂽ���W�X�g���G���g��(uint32)�̒l��Ԃ��܂��B
 *    @param parent_key  �擾���������W�X�g���G���g�����������Ă��郌�W�X�g���L�[�B
 *    @param entry_name  �l���擾���������W�X�g���G���g�����B
 *
 *    @return ���W�X�g���G���g���̒l�B
 */
uint32_t query_entry_value_dword(registry_t parent_key, tstring entry_name);


/**
 * �w�肳�ꂽ���W�X�g���L�[�ɏ������Ă���A�w�肳�ꂽ���W�X�g���G���g��(������)�̒l��Ԃ��܂��B
 *    @param parent_key  �擾���������W�X�g���G���g�����������Ă��郌�W�X�g���L�[�B
 *    @param entry_name  �l���擾���������W�X�g���G���g�����B
 *
 *    @return ���W�X�g���G���g���̒l�B
 */
tstring query_entry_value_sz(registry_t parent_key, tstring entry_name);


/**
 * �w�肳�ꂽ���W�X�g���L�[�ɏ�������A�w�肳�ꂽ 1 �̃��W�X�g���G���g���̒l�ƁA���̃f�[�^�^��ݒ肵�܂��B
 *    @param parent_key   ����������e�L�[�̃n���h���B
 *    @param entry_name   ���W�X�g���G���g�����B
 *    @param reserved     �\��ς݁B
 *    @param entry_type   ���W�X�g���G���g���̃f�[�^�^�B
 *    @param entry_value  ���W�X�g���G���g���̒l�B
 *
 *    @return ����������AERROR_SUCCESS�B
 */
long set_registry_entry( registry_t                  parent_key,
                         const tstring&              entry_name,
                         uint32_t                    reserved,
                         uint32_t                    entry_type,
                         const std::vector<ubyte>&   entry_value
                       );
/**
 * �w�肳�ꂽ���W�X�g���L�[�ɏ�������A�w�肳�ꂽ 1 �̃��W�X�g���G���g���̒l��ݒ肵�܂��B
 *    @param parent_key   ����������e�L�[�̃n���h���B
 *    @param entry_name   ���W�X�g���G���g�����B
 *    @param entry_value  ���W�X�g���G���g���̒l�B
 *
 *    @return ����������AERROR_SUCCESS�B
 */
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const tstring&         entry_value
                       );
/**
 * �w�肳�ꂽ���W�X�g���L�[�ɏ�������A�w�肳�ꂽ 1 �̃��W�X�g���G���g���̒l��ݒ肵�܂��B
 *    @param parent_key   ����������e�L�[�̃n���h���B
 *    @param entry_name   ���W�X�g���G���g�����B
 *    @param entry_value  ���W�X�g���G���g���̒l�B
 *
 *    @return ����������AERROR_SUCCESS�B
 */
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const reg_dword_t&     entry_value
                       );
/**
 * �w�肳�ꂽ���W�X�g���L�[�ɏ�������A�w�肳�ꂽ 1 �̃��W�X�g���G���g���̒l��ݒ肵�܂��B
 *    @param parent_key   ����������e�L�[�̃n���h���B
 *    @param entry_name   ���W�X�g���G���g�����B
 *    @param entry_value  ���W�X�g���G���g���̒l�B
 *
 *    @return ����������AERROR_SUCCESS�B
 */
long set_registry_entry( registry_t             parent_key,
                         const tstring&         entry_name,
                         const reg_qword_t&     entry_value
                       );


/**
 * �w�肳�ꂽ���W�X�g���L�[�� index �Ԗڂ̃��W�X�g���G���g���̓��e�� entry �ɃR�s�[���܂��B
 *    @param  parent_key  �w�肵�����W�X�g���L�[�B
 *    @param  index       �R�s�[���������W�X�g���G���g���̃C���f�b�N�X�B
 *    @param  entry       �R�s�[��� registry_entry_t �\���́B
 *
 *    @return �����Ȃ� ERROR_SUCCESS�B
 */
long enumeration_registry_entry(registry_t parent_key, uint32_t index, registry_entry_t& entry);


/**
 * �w�肳�ꂽ���W�X�g���L�[�̃T�u�L�[���폜���܂��B
 *    @param parent_key  �폜����T�u�L�[���������郌�W�X�g���L�[�B
 *    @param subkey_name �폜����T�u�L�[�̖��O�B
 *
 *    @return ���������� ERROR_SUCCESS�B
 */
long delete_registry_key(registry_t parent_key, const tstring& subkey_name);
/**
 * �w�肳�ꂽ���W�X�g���L�[�̃T�u�L�[���폜���܂��B
 *    @param parent_key  �폜����T�u�L�[���������郌�W�X�g���L�[�B
 *    @param subkey_name �폜����T�u�L�[�̖��O�B
 *
 *    @return ���������� ERROR_SUCCESS�B
 */
inline long delete_registry_key(registry_t parent_key, const _TCHAR* const& subkey_name) {
    return delete_registry_key( parent_key, tstring( subkey_name ) );
}


#endif  /* lxe_win32api_registry_hpp */
