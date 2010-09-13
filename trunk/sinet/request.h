#ifndef SINET_REQUEST_H
#define SINET_REQUEST_H

#include "api_base.h"
#include "api_refptr.h"
#include "postdata.h"

namespace sinet
{

class request:
  public base
{
public:
  static refptr<request> create_instance();

  // request method
  virtual void set_request_method(std::wstring& method) = 0;
  virtual std::wstring get_request_method() = 0;

  // request url
  virtual void set_request_url(std::wstring& method) = 0;
  virtual std::wstring get_request_url() = 0;

  // request header
  virtual void set_request_header(si_stringmap& header) = 0;
  virtual si_stringmap get_request_header() = 0;

  // request postdata
  virtual void set_postdata(refptr<postdata> postdata) = 0;
  virtual refptr<postdata> get_postdata() = 0;

  // response header
  virtual void set_response_header(si_stringmap& header) = 0;
  virtual si_stringmap get_response_header() = 0;

  // response content buffer
  virtual void set_response_buffer(si_buffer& buffer) = 0;
  virtual si_buffer get_response_buffer() = 0;

  // response content buffer size only
  virtual void set_response_size(size_t size_in) = 0;
  virtual size_t get_response_size() = 0;

  // response error code
  virtual void set_response_errcode(int errcode) = 0;
  virtual int get_response_errcode() = 0;
};

} // namespace sinet

#endif // SINET_REQUEST_H