/**
 * @file  eventlog.hpp
 * @brief �C�x���g���O�p���W���[���B
 */
#ifndef win32api_eventlog_hpp
#define win32api_eventlog_hpp

#include <windows.h>
#include <spaghetti/string_util.hpp>

#ifndef LXELIB_DEFINE_SECURITY_ID_T
typedef     SID         security_id_t;
#   define      LXELIB_DEFINE_SECURITY_ID_T
#endif  /* ndef LXELIB_DEFINE_SECURITY_ID_T */


/**
 * ���O�ɏ������ރC�x���g�̎�ނł��B
 */
#if defined(__cplusplus) && __cplusplus > 199711L
// C++0x: �����^�t���̗񋓌^�B
enum class EventLogType : uint16_t {
    ERROR         = EVENTLOG_ERROR_TYPE,         //!< �G���[�C�x���g
    WARNING       = EVENTLOG_WARNING_TYPE,       //!< �x���C�x���g
    INFORMATION   = EVENTLOG_INFORMATION_TYPE,   //!< ���C�x���g
    AUDIT_SUCCESS = EVENTLOG_AUDIT_SUCCESS,      //!< �����̊č��C�x���g
    AUDIT_FAILURE = EVENTLOG_AUDIT_FAILURE       //!< ���s�̊č��C�x���g
};
#else
enum EventLogType {
    EventLogType_ERROR         = EVENTLOG_ERROR_TYPE,         //!< �G���[�C�x���g
    EventLogType_WARNING       = EVENTLOG_WARNING_TYPE,       //!< �x���C�x���g
    EventLogType_INFORMATION   = EVENTLOG_INFORMATION_TYPE,   //!< ���C�x���g
    EventLogType_AUDIT_SUCCESS = EVENTLOG_AUDIT_SUCCESS,      //!< �����̊č��C�x���g
    EventLogType_AUDIT_FAILURE = EVENTLOG_AUDIT_FAILURE       //!< ���s�̊č��C�x���g
};
#endif  /* defined(__cplusplus) && __cplusplus >= 199711L */


/**
 * �C�x���g���O�̓o�^�ς݃n���h����Ԃ��܂��B
 *    @param source_name      �C�x���g�\�[�X�̖��O�B
 *
 *    @return �C�x���g���O�̓o�^�ς݃n���h���B
 */
handle_t register_event_source(const tstring& source_name);
/**
 * �C�x���g���O�̓o�^�ς݃n���h����Ԃ��܂��B
 *    @param unc_server_name  �T�[�o�[�� UNC(Universal Naming Convention)���B
 *    @param source_name      �C�x���g�\�[�X�̖��O�B
 *
 *    @return �C�x���g���O�̓o�^�ς݃n���h���B
 */
handle_t register_event_source( const tstring& unc_server_name,
                                const tstring& source_name
                              );


/**
 * �w�肵���C�x���g���O�̍Ō�ɃG���g�����������݂܂��B
 */
bool report_event( handle_t                 eventlog_handle,
                   EventLogType             event_type,
                   uint16_t                 event_category,
                   uint32_t                 event_id,
                   security_id_t* const&    user_sid        = NULL
                 );
/**
 *
 */
bool report_event( handle_t                     eventlog_handle,
                   EventLogType                 event_type,
                   uint16_t                     event_category,
                   uint32_t                     event_id,
                   security_id_t* const&        user_sid,
                   const std::vector<tstring>&  messages
                 );
/**
 *
 */
bool report_event( handle_t                     eventlog_handle,
                   EventLogType                 event_type,
                   uint16_t                     event_category,
                   uint32_t                     event_id,
                   security_id_t* const&        user_sid,
                   const std::vector<tstring>&  messages,
                   const std::vector<ubyte>&    raw_data
                 );


/**
 * �w�肵���C�x���g���O�n���h������܂��B
 *    @param eventlog_handle �������C�x���g���O�n���h���B
 */
bool deregister_event_source(handle_t eventlog_handle);


#endif  /* win32api_eventlog_hpp */
