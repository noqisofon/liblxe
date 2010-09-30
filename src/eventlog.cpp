/**
 * @file eventlog.cpp
 */
#include <stdafx.h>

#include <lxe/handle.hpp>

#include <lxe/eventlog.hpp>

using namespace std;


handle_t register_event_source(const tstring& source_name)
{
    return RegisterEventSource( NULL, source_name.c_str() );
}
handle_t register_event_source( const tstring& unc_server_name,
                                const tstring& source_name
                                )
{
    return RegisterEventSource( unc_server_name.c_str(), source_name.c_str() );
}


bool report_event( handle_t         eventlog_handle,
                   EventLogType     event_type,
                   uint16_t         event_category,
                   uint32_t         event_id,
                   SID* const&      user_sid
                   )
{
    bool ret;

    if ( handle_is_invalid( eventlog_handle ) || eventlog_handle == NULL )
        return false;

    ret = ReportEvent( eventlog_handle,
                       __STATIC_CAST(WORD, event_type),
                       event_category,
                       event_id,
                       user_sid,
                       0,
                       0,
                       NULL,
                       NULL
                       ) != 0;
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( !ret )
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}
bool report_event( handle_t                 eventlog_handle,
                   EventLogType             event_type,
                   uint16_t                 event_category,
                   uint32_t                 event_id,
                   SID* const&              user_sid,
                   const vector<tstring>&   messages
                   )
{
    vector<const _TCHAR*>           sv;
    bool                            ret     = false;
    vector<tstring>::size_type      i       = 0;
    vector<tstring>::size_type      stop    = messages.size();

    if ( handle_is_invalid( eventlog_handle ) || eventlog_handle == NULL )
        return false;

    /*
     * ReportEvent() の lpStrings 引数は LPCTSTR* なので、
     * ラッパ関数の中で C スタイル文字列のベクターを作成しなければならない。
     */
    for ( i = 0; i < stop; ++ i )
        sv.push_back( messages[i].c_str() );
    /*
     * &v.at( 0 ) で、ベクタコンテナ内の配列の先頭ポインタを得ることができます。
     */
    ret = ReportEvent( eventlog_handle,
                       __STATIC_CAST(WORD, event_type),
                       event_category,
                       event_id,
                       user_sid,
                       __STATIC_CAST( WORD, sv.size() ),
                       0,
                       &sv.at( 0 ),
                       NULL
                       ) != 0;
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( !ret )
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}
bool report_event( handle_t                 eventlog_handle,
                   EventLogType             event_type,
                   uint16_t                 event_category,
                   uint32_t                 event_id,
                   SID* const&              user_sid,
                   const vector<tstring>&   messages,
                   const vector<ubyte>&     raw_data
                   )
{
    vector<const _TCHAR*>       sv;
    bool                        ret     = false;
    vector<tstring>::size_type  i       = 0;
    vector<tstring>::size_type  stop    = messages.size();
#ifdef LXE_USE_ASSERT
    assert( stop == 0 );
#endif  /* def LXE_USE_ASSERT */

    if ( handle_is_invalid( eventlog_handle ) || eventlog_handle == NULL )
        return false;
    /*
     * ReportEvent() の lpStrings 引数は LPCTSTR* なので、
     * ラッパ関数の中で C スタイル文字列のベクターを作成しなければならない。
     */
    for ( i = 0; i < stop; ++ i )
        sv.push_back( messages[i].c_str() );
    /*
     * 本当はキャストしてまたキャストするのは具合が悪いのだが、
     * const security と兼ね合いでオーバーヘッド？をとることにした。
     */
    ret = ReportEvent( eventlog_handle,
                       __STATIC_CAST(WORD, event_type),
                       event_category,
                       event_id,
                       user_sid,
                       __STATIC_CAST( WORD, sv.size() ),
                       __STATIC_CAST( DWORD, raw_data.size() ),
                       &sv.at( 0 ),
                       __REINTERPRET_CAST( LPVOID, __CONST_CAST( ubyte *, &raw_data.at( 0 ) ) )
                       ) != 0;
#if defined(LXE_USE_THROW_DOMAIN_ERROR)
    if ( !ret )
        throw get_last_error( _T(__FILE__), __FUNCTION__, __LINE__ );
#endif  /* defined(LXE_USE_THROW_DOMAIN_ERROR) */

    return ret;
}


bool deregister_event_source(handle_t eventlog_handle)
{
    if ( handle_is_invalid( eventlog_handle ) || eventlog_handle == NULL )
        return false;

    return DeregisterEventSource( eventlog_handle ) != 0;
}
