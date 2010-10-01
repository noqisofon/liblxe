/**
 * @file  error_handler.hpp
 * @brief エラーハンドラモジュール。
 */
#ifndef win32api_error_hpp
#define win32api_error_hpp

#include <stdexcept>
#include <spaghetti/string_util.hpp>


/**
 * 
 */
inline tstring get_error_message(uint32_t error_code);


/**
 *
 */
class win32_error : public std::domain_error
{
 public:
    /**
     * 
     */
    explicit win32_error(uint32_t error_code)
         : std::domain_error( get_error_message( error_code ) ),
           category_(0x00002400L),
           detail_code_(0),
           error_code_(error_code),
           filename_(),
           function_name_(),
           line_(0)
    {
    }
    /**
     * 
     */
    win32_error( uint32_t          error_code,
                 const tstring&    filename,
                 const tstring&    function_name,
                 int               line
               )
         : std::domain_error( get_error_message( error_code ) ),
           category_(0x00002400L),
           detail_code_(0),
           error_code_(error_code),
           filename_(filename),
           function_name_(function_name + _T("()")),
           line_(line)
    {
    }
    /**
     * 
     */
    win32_error( uint32_t           error_code,
                 uint32_t           category_code,
                 uint32_t           detail_code,
                 const tstring&     filename,
                 const tstring&     function_name,
                 int                line
               )
         : std::domain_error( get_error_message( error_code ) ),
           category_(category_code),
           detail_code_(detail_code),
           filename_(filename),
           function_name_(function_name + _T("()")),
           line_(line)
    {
    }


    /**
     * 
     */
    virtual ~win32_error() {
    }

 public:
    /**
     * 
     */
    uint32_t category() const { return category_; }


    /**
     * 
     */
    uint32_t detail() const { return detail_code_; }


    /**
     * 
     */
    uint32_t mean() const { return error_code_; }


    /**
     * 
     */
    const tstring& filename() const { return filename_; }


    /**
     * 
     */
    const tstring& function_name() const { return function_name_; }


    /**
     * 
     */
    int line() const { return line_; }


    /**
     * 
     */
    tstring inspect() const {
        tstringstream   ss;

        ss << filename() << _T(": ") << function_name() << _T(" in ") << line() << _T(": ") << what();

        return ss.str();
    }

 private:
    uint32_t    category_;
    uint32_t    detail_code_;
    uint32_t    error_code_;
    tstring     filename_;
    tstring     function_name_;
    int         line_;
};


inline tstring get_error_message(uint32_t error_code) {
    void*   message_buffer  = NULL;

    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM     |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL,
                   __STATIC_CAST(DWORD, error_code),
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 既定の言語
                   __REINTERPRET_CAST(LPTSTR, &message_buffer),
                   0,
                   NULL
                 );

    tstring result = trim( tstring( __REINTERPRET_CAST(LPTSTR, message_buffer) ) );

    // バッファを解放する。
    LocalFree( message_buffer );

    return result;
}


inline win32_error get_error_for_hr(uint32_t error_code, tstring filename, tstring function_name, int line) {
    return win32_error( error_code,
                        filename,
                        function_name,
                        line
                      );
}


/**
 * 最後に起こったエラーを取得します。
 */
inline win32_error get_last_error(tstring filename, tstring function_name, int line) {
    return win32_error( GetLastError(),
                        filename,
                        function_name,
                        line
                      );
}


inline std::ostream& operator << (std::ostream& out, const win32_error& error) {
    out << error.inspect();

    return out;
}


//void eventlog_translator(unsigned int code, EXCEPTION_POINTERS* ep);


void throw_exception_translator(unsigned int code, EXCEPTION_POINTERS* ep);


#endif  /* win32api_error_hpp */
