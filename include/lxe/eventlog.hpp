/**
 * @file  eventlog.hpp
 * @brief イベントログ用モジュール。
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
 * ログに書き込むイベントの種類です。
 */
#if defined(__cplusplus) && __cplusplus > 199711L
// C++0x: 強い型付けの列挙型。
enum class EventLogType : uint16_t {
    ERROR         = EVENTLOG_ERROR_TYPE,         //!< エラーイベント
    WARNING       = EVENTLOG_WARNING_TYPE,       //!< 警告イベント
    INFORMATION   = EVENTLOG_INFORMATION_TYPE,   //!< 情報イベント
    AUDIT_SUCCESS = EVENTLOG_AUDIT_SUCCESS,      //!< 成功の監査イベント
    AUDIT_FAILURE = EVENTLOG_AUDIT_FAILURE       //!< 失敗の監査イベント
};
#else
enum EventLogType {
    EventLogType_ERROR         = EVENTLOG_ERROR_TYPE,         //!< エラーイベント
    EventLogType_WARNING       = EVENTLOG_WARNING_TYPE,       //!< 警告イベント
    EventLogType_INFORMATION   = EVENTLOG_INFORMATION_TYPE,   //!< 情報イベント
    EventLogType_AUDIT_SUCCESS = EVENTLOG_AUDIT_SUCCESS,      //!< 成功の監査イベント
    EventLogType_AUDIT_FAILURE = EVENTLOG_AUDIT_FAILURE       //!< 失敗の監査イベント
};
#endif  /* defined(__cplusplus) && __cplusplus >= 199711L */


/**
 * イベントログの登録済みハンドルを返します。
 *    @param source_name      イベントソースの名前。
 *
 *    @return イベントログの登録済みハンドル。
 */
handle_t register_event_source(const tstring& source_name);
/**
 * イベントログの登録済みハンドルを返します。
 *    @param unc_server_name  サーバーの UNC(Universal Naming Convention)名。
 *    @param source_name      イベントソースの名前。
 *
 *    @return イベントログの登録済みハンドル。
 */
handle_t register_event_source( const tstring& unc_server_name,
                                const tstring& source_name
                              );


/**
 * 指定したイベントログの最後にエントリを書き込みます。
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
 * 指定したイベントログハンドルを閉じます。
 *    @param eventlog_handle 閉じたいイベントログハンドル。
 */
bool deregister_event_source(handle_t eventlog_handle);


#endif  /* win32api_eventlog_hpp */
