////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Achim Brandt
////////////////////////////////////////////////////////////////////////////////

#include "GeneralResponse.h"

#include "Basics/StringUtils.h"

using namespace arangodb;
using namespace arangodb::basics;

std::string GeneralResponse::responseString(ResponseCode code) {
  switch (code) {
    //  Informational 1xx
    case ResponseCode::CONTINUE:
      return "100 Continue";
    case ResponseCode::SWITCHING_PROTOCOLS:
      return "101 Switching Protocols";
    case ResponseCode::PROCESSING:
      return "102 Processing";

    //  Success 2xx
    case ResponseCode::OK:
      return "200 OK";
    case ResponseCode::CREATED:
      return "201 Created";
    case ResponseCode::ACCEPTED:
      return "202 Accepted";
    case ResponseCode::PARTIAL:
      return "203 Non-Authoritative Information";
    case ResponseCode::NO_CONTENT:
      return "204 No Content";
    case ResponseCode::RESET_CONTENT:
      return "205 Reset Content";
    case ResponseCode::PARTIAL_CONTENT:
      return "206 Partial Content";

    //  Redirection 3xx
    case ResponseCode::MOVED_PERMANENTLY:
      return "301 Moved Permanently";
    case ResponseCode::FOUND:
      return "302 Found";
    case ResponseCode::SEE_OTHER:
      return "303 See Other";
    case ResponseCode::NOT_MODIFIED:
      return "304 Not Modified";
    case ResponseCode::TEMPORARY_REDIRECT:
      return "307 Temporary Redirect";
    case ResponseCode::PERMANENT_REDIRECT:
      return "308 Permanent Redirect";

    //  Client Error 4xx
    case ResponseCode::BAD:
      return "400 Bad Request";
    case ResponseCode::UNAUTHORIZED:
      return "401 Unauthorized";
    case ResponseCode::PAYMENT_REQUIRED:
      return "402 Payment Required";
    case ResponseCode::FORBIDDEN:
      return "403 Forbidden";
    case ResponseCode::NOT_FOUND:
      return "404 Not Found";
    case ResponseCode::METHOD_NOT_ALLOWED:
      return "405 Method Not Allowed";
    case ResponseCode::NOT_ACCEPTABLE:
      return "406 Not Acceptable";
    case ResponseCode::REQUEST_TIMEOUT:
      return "408 Request Timeout";
    case ResponseCode::CONFLICT:
      return "409 Conflict";
    case ResponseCode::GONE:
      return "410 Gone";
    case ResponseCode::LENGTH_REQUIRED:
      return "411 Length Required";
    case ResponseCode::PRECONDITION_FAILED:
      return "412 Precondition Failed";
    case ResponseCode::REQUEST_ENTITY_TOO_LARGE:
      return "413 Payload Too Large";
    case ResponseCode::REQUEST_URI_TOO_LONG:
      return "414 Request-URI Too Long";
    case ResponseCode::UNSUPPORTED_MEDIA_TYPE:
      return "415 Unsupported Media Type";
    case ResponseCode::REQUESTED_RANGE_NOT_SATISFIABLE:
      return "416 Requested Range Not Satisfiable";
    case ResponseCode::EXPECTATION_FAILED:
      return "417 Expectation Failed";
    case ResponseCode::I_AM_A_TEAPOT:
      return "418 I'm a teapot";
    case ResponseCode::UNPROCESSABLE_ENTITY:
      return "422 Unprocessable Entity";
    case ResponseCode::LOCKED:
      return "423 Locked";
    case ResponseCode::PRECONDITION_REQUIRED:
      return "428 Precondition Required";
    case ResponseCode::TOO_MANY_REQUESTS:
      return "429 Too Many Requests";
    case ResponseCode::REQUEST_HEADER_FIELDS_TOO_LARGE:
      return "431 Request Header Fields Too Large";
    case ResponseCode::UNAVAILABLE_FOR_LEGAL_REASONS:
      return "451 Unavailable For Legal Reasons";

    //  Server Error 5xx
    case ResponseCode::SERVER_ERROR:
      return "500 Internal Server Error";
    case ResponseCode::NOT_IMPLEMENTED:
      return "501 Not Implemented";
    case ResponseCode::BAD_GATEWAY:
      return "502 Bad Gateway";
    case ResponseCode::SERVICE_UNAVAILABLE:
      return "503 Service Unavailable";
    case ResponseCode::HTTP_VERSION_NOT_SUPPORTED:
      return "505 HTTP Version Not Supported";
    case ResponseCode::BANDWIDTH_LIMIT_EXCEEDED:
      return "509 Bandwidth Limit Exceeded";
    case ResponseCode::NOT_EXTENDED:
      return "510 Not Extended";

    // default
    default: {
      // print generic group responses, based on error code group
      int group = ((int)code) / 100;
      switch (group) {
        case 1:
          return StringUtils::itoa((int)code) + " Informational";
        case 2:
          return StringUtils::itoa((int)code) + " Success";
        case 3:
          return StringUtils::itoa((int)code) + " Redirection";
        case 4:
          return StringUtils::itoa((int)code) + " Client error";
        case 5:
          return StringUtils::itoa((int)code) + " Server error";
        default:
          break;
      }
    }
  }

  return StringUtils::itoa((int)code) + " Unknown";
}

GeneralResponse::ResponseCode GeneralResponse::responseCode(
    std::string const& str) {
  int number = ::atoi(str.c_str());

  switch (number) {
    case 100:
      return ResponseCode::CONTINUE;
    case 101:
      return ResponseCode::SWITCHING_PROTOCOLS;
    case 102:
      return ResponseCode::PROCESSING;

    case 200:
      return ResponseCode::OK;
    case 201:
      return ResponseCode::CREATED;
    case 202:
      return ResponseCode::ACCEPTED;
    case 203:
      return ResponseCode::PARTIAL;
    case 204:
      return ResponseCode::NO_CONTENT;
    case 205:
      return ResponseCode::RESET_CONTENT;
    case 206:
      return ResponseCode::PARTIAL_CONTENT;

    case 301:
      return ResponseCode::MOVED_PERMANENTLY;
    case 302:
      return ResponseCode::FOUND;
    case 303:
      return ResponseCode::SEE_OTHER;
    case 304:
      return ResponseCode::NOT_MODIFIED;
    case 307:
      return ResponseCode::TEMPORARY_REDIRECT;
    case 308:
      return ResponseCode::PERMANENT_REDIRECT;

    case 400:
      return ResponseCode::BAD;
    case 401:
      return ResponseCode::UNAUTHORIZED;
    case 402:
      return ResponseCode::PAYMENT_REQUIRED;
    case 403:
      return ResponseCode::FORBIDDEN;
    case 404:
      return ResponseCode::NOT_FOUND;
    case 405:
      return ResponseCode::METHOD_NOT_ALLOWED;
    case 406:
      return ResponseCode::NOT_ACCEPTABLE;
    case 408:
      return ResponseCode::REQUEST_TIMEOUT;
    case 409:
      return ResponseCode::CONFLICT;
    case 410:
      return ResponseCode::GONE;
    case 411:
      return ResponseCode::LENGTH_REQUIRED;
    case 412:
      return ResponseCode::PRECONDITION_FAILED;
    case 413:
      return ResponseCode::REQUEST_ENTITY_TOO_LARGE;
    case 414:
      return ResponseCode::REQUEST_URI_TOO_LONG;
    case 415:
      return ResponseCode::UNSUPPORTED_MEDIA_TYPE;
    case 416:
      return ResponseCode::REQUESTED_RANGE_NOT_SATISFIABLE;
    case 417:
      return ResponseCode::EXPECTATION_FAILED;
    case 418:
      return ResponseCode::I_AM_A_TEAPOT;
    case 422:
      return ResponseCode::UNPROCESSABLE_ENTITY;
    case 423:
      return ResponseCode::LOCKED;
    case 428:
      return ResponseCode::PRECONDITION_REQUIRED;
    case 429:
      return ResponseCode::TOO_MANY_REQUESTS;
    case 431:
      return ResponseCode::REQUEST_HEADER_FIELDS_TOO_LARGE;
    case 451:
      return ResponseCode::UNAVAILABLE_FOR_LEGAL_REASONS;

    case 500:
      return ResponseCode::SERVER_ERROR;
    case 501:
      return ResponseCode::NOT_IMPLEMENTED;
    case 502:
      return ResponseCode::BAD_GATEWAY;
    case 503:
      return ResponseCode::SERVICE_UNAVAILABLE;
    case 505:
      return ResponseCode::HTTP_VERSION_NOT_SUPPORTED;
    case 509:
      return ResponseCode::BANDWIDTH_LIMIT_EXCEEDED;
    case 510:
      return ResponseCode::NOT_EXTENDED;

    default:
      return ResponseCode::NOT_IMPLEMENTED;
  }
}

GeneralResponse::ResponseCode GeneralResponse::responseCode(int code) {
  TRI_ASSERT(code != TRI_ERROR_NO_ERROR);

  switch (code) {
    case TRI_ERROR_BAD_PARAMETER:
    case TRI_ERROR_ARANGO_DATABASE_NAME_INVALID:
    case TRI_ERROR_ARANGO_DOCUMENT_KEY_BAD:
    case TRI_ERROR_ARANGO_DOCUMENT_KEY_UNEXPECTED:
    case TRI_ERROR_ARANGO_DOCUMENT_KEY_MISSING:
    case TRI_ERROR_ARANGO_DOCUMENT_TYPE_INVALID:
    case TRI_ERROR_ARANGO_DOCUMENT_HANDLE_BAD:
    case TRI_ERROR_CLUSTER_MUST_NOT_CHANGE_SHARDING_ATTRIBUTES:
    case TRI_ERROR_CLUSTER_MUST_NOT_SPECIFY_KEY:
    case TRI_ERROR_TYPE_ERROR:
    case TRI_ERROR_QUERY_NUMBER_OUT_OF_RANGE:
    case TRI_ERROR_QUERY_VARIABLE_NAME_INVALID:
    case TRI_ERROR_QUERY_VARIABLE_REDECLARED:
    case TRI_ERROR_QUERY_VARIABLE_NAME_UNKNOWN:
    case TRI_ERROR_QUERY_TOO_MANY_COLLECTIONS:
    case TRI_ERROR_QUERY_FUNCTION_NAME_UNKNOWN:
    case TRI_ERROR_QUERY_FUNCTION_ARGUMENT_NUMBER_MISMATCH:
    case TRI_ERROR_QUERY_FUNCTION_ARGUMENT_TYPE_MISMATCH:
    case TRI_ERROR_QUERY_INVALID_REGEX:
    case TRI_ERROR_QUERY_BIND_PARAMETERS_INVALID:
    case TRI_ERROR_QUERY_BIND_PARAMETER_MISSING:
    case TRI_ERROR_QUERY_BIND_PARAMETER_UNDECLARED:
    case TRI_ERROR_QUERY_BIND_PARAMETER_TYPE:
    case TRI_ERROR_QUERY_INVALID_LOGICAL_VALUE:
    case TRI_ERROR_QUERY_INVALID_ARITHMETIC_VALUE:
    case TRI_ERROR_QUERY_DIVISION_BY_ZERO:
    case TRI_ERROR_QUERY_ARRAY_EXPECTED:
    case TRI_ERROR_QUERY_FAIL_CALLED:
    case TRI_ERROR_QUERY_INVALID_DATE_VALUE:
    case TRI_ERROR_QUERY_MULTI_MODIFY:
    case TRI_ERROR_QUERY_COMPILE_TIME_OPTIONS:
    case TRI_ERROR_QUERY_EXCEPTION_OPTIONS:
    case TRI_ERROR_QUERY_COLLECTION_USED_IN_EXPRESSION:
    case TRI_ERROR_QUERY_DISALLOWED_DYNAMIC_CALL:
    case TRI_ERROR_QUERY_ACCESS_AFTER_MODIFICATION:
    case TRI_ERROR_QUERY_FUNCTION_INVALID_NAME:
    case TRI_ERROR_QUERY_FUNCTION_INVALID_CODE:
    case TRI_ERROR_REPLICATION_INVALID_APPLIER_CONFIGURATION:
    case TRI_ERROR_REPLICATION_RUNNING:
    case TRI_ERROR_REPLICATION_NO_START_TICK:
    case TRI_ERROR_ARANGO_USE_SYSTEM_DATABASE:
    case TRI_ERROR_ARANGO_INVALID_KEY_GENERATOR:
    case TRI_ERROR_ARANGO_INVALID_EDGE_ATTRIBUTE:
    case TRI_ERROR_ARANGO_INDEX_DOCUMENT_ATTRIBUTE_MISSING:
    case TRI_ERROR_ARANGO_INDEX_CREATION_FAILED:
    case TRI_ERROR_ARANGO_COLLECTION_TYPE_MISMATCH:
    case TRI_ERROR_ARANGO_COLLECTION_TYPE_INVALID:
    case TRI_ERROR_ARANGO_VALIDATION_FAILED:
    case TRI_ERROR_ARANGO_ATTRIBUTE_PARSER_FAILED:
    case TRI_ERROR_ARANGO_CROSS_COLLECTION_REQUEST:
    case TRI_ERROR_ARANGO_INDEX_HANDLE_BAD:
    case TRI_ERROR_ARANGO_CAP_CONSTRAINT_ALREADY_DEFINED:
    case TRI_ERROR_ARANGO_DOCUMENT_TOO_LARGE:
    case TRI_ERROR_QUERY_PARSE:
    case TRI_ERROR_QUERY_EMPTY:
    case TRI_ERROR_TRANSACTION_NESTED:
    case TRI_ERROR_TRANSACTION_UNREGISTERED_COLLECTION:
    case TRI_ERROR_TRANSACTION_DISALLOWED_OPERATION:
    case TRI_ERROR_USER_INVALID_NAME:
    case TRI_ERROR_USER_INVALID_PASSWORD:
    case TRI_ERROR_TASK_INVALID_ID:
    case TRI_ERROR_GRAPH_INVALID_GRAPH:
    case TRI_ERROR_GRAPH_COULD_NOT_CREATE_GRAPH:
    case TRI_ERROR_GRAPH_INVALID_VERTEX:
    case TRI_ERROR_GRAPH_COULD_NOT_CREATE_VERTEX:
    case TRI_ERROR_GRAPH_COULD_NOT_CHANGE_VERTEX:
    case TRI_ERROR_GRAPH_INVALID_EDGE:
    case TRI_ERROR_GRAPH_COULD_NOT_CREATE_EDGE:
    case TRI_ERROR_GRAPH_COULD_NOT_CHANGE_EDGE:
    case TRI_ERROR_GRAPH_COLLECTION_MULTI_USE:
    case TRI_ERROR_GRAPH_COLLECTION_USE_IN_MULTI_GRAPHS:
    case TRI_ERROR_GRAPH_CREATE_MISSING_NAME:
    case TRI_ERROR_GRAPH_CREATE_MALFORMED_EDGE_DEFINITION:
    case TRI_ERROR_GRAPH_WRONG_COLLECTION_TYPE_VERTEX:
    case TRI_ERROR_GRAPH_NOT_IN_ORPHAN_COLLECTION:
    case TRI_ERROR_GRAPH_COLLECTION_USED_IN_EDGE_DEF:
    case TRI_ERROR_GRAPH_EDGE_COLLECTION_NOT_USED:
    case TRI_ERROR_GRAPH_NOT_AN_ARANGO_COLLECTION:
    case TRI_ERROR_GRAPH_INVALID_EXAMPLE_ARRAY_OBJECT_STRING:
    case TRI_ERROR_GRAPH_INVALID_EXAMPLE_ARRAY_OBJECT:
    case TRI_ERROR_GRAPH_INVALID_NUMBER_OF_ARGUMENTS:
    case TRI_ERROR_GRAPH_INVALID_PARAMETER:
    case TRI_ERROR_GRAPH_INVALID_ID:
    case TRI_ERROR_GRAPH_COLLECTION_USED_IN_ORPHANS:
    case TRI_ERROR_GRAPH_EDGE_COL_DOES_NOT_EXIST:
      return ResponseCode::BAD;

    case TRI_ERROR_ARANGO_READ_ONLY:
      return ResponseCode::FORBIDDEN;

    case TRI_ERROR_ARANGO_DATABASE_NOT_FOUND:
    case TRI_ERROR_ARANGO_COLLECTION_NOT_FOUND:
    case TRI_ERROR_ARANGO_COLLECTION_NOT_LOADED:
    case TRI_ERROR_ARANGO_DOCUMENT_NOT_FOUND:
    case TRI_ERROR_ARANGO_ENDPOINT_NOT_FOUND:
    case TRI_ERROR_ARANGO_INDEX_NOT_FOUND:
    case TRI_ERROR_CURSOR_NOT_FOUND:
    case TRI_ERROR_QUERY_FUNCTION_NOT_FOUND:
    case TRI_ERROR_QUERY_GEO_INDEX_MISSING:
    case TRI_ERROR_QUERY_FULLTEXT_INDEX_MISSING:
    case TRI_ERROR_QUERY_NOT_FOUND:
    case TRI_ERROR_USER_NOT_FOUND:
    case TRI_ERROR_TASK_NOT_FOUND:
    case TRI_ERROR_GRAPH_NOT_FOUND:
    case TRI_ERROR_GRAPH_VERTEX_COL_DOES_NOT_EXIST:
    case TRI_ERROR_GRAPH_NO_GRAPH_COLLECTION:
    case TRI_ERROR_QUEUE_UNKNOWN:
      return ResponseCode::NOT_FOUND;

    case TRI_ERROR_REQUEST_CANCELED:
    case TRI_ERROR_QUERY_KILLED:
    case TRI_ERROR_TRANSACTION_ABORTED:
      return ResponseCode::GONE;

    case TRI_ERROR_ARANGO_CONFLICT:
    case TRI_ERROR_ARANGO_UNIQUE_CONSTRAINT_VIOLATED:
    case TRI_ERROR_CURSOR_BUSY:
    case TRI_ERROR_USER_DUPLICATE:
    case TRI_ERROR_TASK_DUPLICATE_ID:
    case TRI_ERROR_GRAPH_DUPLICATE:
    case TRI_ERROR_QUEUE_ALREADY_EXISTS:
      return ResponseCode::CONFLICT;

    case TRI_ERROR_DEADLOCK:
    case TRI_ERROR_ARANGO_OUT_OF_KEYS:
    case TRI_ERROR_CLUSTER_SHARD_GONE:
    case TRI_ERROR_CLUSTER_TIMEOUT:
    case TRI_ERROR_OUT_OF_MEMORY:
    case TRI_ERROR_INTERNAL:
      return ResponseCode::SERVER_ERROR;

    case TRI_ERROR_CLUSTER_BACKEND_UNAVAILABLE:
      return ResponseCode::SERVICE_UNAVAILABLE;

    case TRI_ERROR_CLUSTER_UNSUPPORTED:
      return ResponseCode::NOT_IMPLEMENTED;

    default:
      return ResponseCode::SERVER_ERROR;
  }
}

GeneralResponse::GeneralResponse(ResponseCode responseCode,
                                 uint32_t compatibility)
    : _responseCode(responseCode), _apiCompatibility(compatibility) {}

std::string const& GeneralResponse::header(std::string const& key) const {
  static std::string const EMPTY_STR = "";

  std::string k = StringUtils::tolower(key);
  auto it = _headers.find(k);

  if (it == _headers.end()) {
    return EMPTY_STR;
  }

  return it->second;
}

std::string const& GeneralResponse::header(std::string const& key,
                                           bool& found) const {
  static std::string const EMPTY_STR = "";

  std::string k = StringUtils::tolower(key);
  auto it = _headers.find(k);

  if (it == _headers.end()) {
    found = false;
    return EMPTY_STR;
  }

  found = true;
  return it->second;
}

void GeneralResponse::setHeader(std::string const& key,
                                std::string const& value) {
  std::string k = StringUtils::tolower(key);

  _headers[key] = value;
}

void GeneralResponse::setHeaderNC(std::string const& key,
                                  std::string const& value) {
  std::string k = StringUtils::tolower(key);

  _headers[key] = value;
}

#if 0

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the content length
////////////////////////////////////////////////////////////////////////////////

size_t HttpResponse::contentLength() {
  if (_isHeadResponse) {
    return _bodySize;
  }

  Dictionary<char const*>::KeyValue const* kv =
      _headers.lookup(TRI_CHAR_LENGTH_PAIR("content-length"));

  if (kv == nullptr) {
    return 0;
  }

  return StringUtils::uint32(kv->_value);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief returns a header field
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief returns a header field
////////////////////////////////////////////////////////////////////////////////

std::string HttpResponse::header(char const* key, size_t keyLength) const {
  Dictionary<char const*>::KeyValue const* kv = _headers.lookup(key, keyLength);

  if (kv == nullptr) {
    return "";
  }
  return kv->_value;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief returns a header field
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief returns a header field
////////////////////////////////////////////////////////////////////////////////

std::string HttpResponse::header(char const* key, size_t keyLength,
                                 bool& found) const {
  Dictionary<char const*>::KeyValue const* kv = _headers.lookup(key, keyLength);

  if (kv == nullptr) {
    found = false;
    return "";
  }
  found = true;
  return kv->_value;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief returns all header fields
////////////////////////////////////////////////////////////////////////////////

std::map<std::string, std::string> HttpResponse::headers() const {
  basics::Dictionary<char const*>::KeyValue const* begin;
  basics::Dictionary<char const*>::KeyValue const* end;

  std::map<std::string, std::string> result;

  for (_headers.range(begin, end); begin < end; ++begin) {
    char const* key = begin->_key;

    if (key == nullptr) {
      continue;
    }

    result[key] = begin->_value;
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets a header field
////////////////////////////////////////////////////////////////////////////////

void HttpResponse::setHeader(char const* key, size_t keyLength,
                             std::string const& value) {
  if (value.empty()) {
    _headers.erase(key);
  } else {
    char const* v = StringUtils::duplicate(value);

    if (v != nullptr) {
      _headers.insert(key, keyLength, v);
      checkHeader(key, v);

      _freeables.emplace_back(v);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets a header field
////////////////////////////////////////////////////////////////////////////////

void HttpResponse::setHeader(char const* key, size_t keyLength,
                             char const* value) {
  if (*value == '\0') {
    _headers.erase(key);
  } else {
    _headers.insert(key, keyLength, value);
    checkHeader(key, value);
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets a header field
////////////////////////////////////////////////////////////////////////////////

void HttpResponse::setHeader(std::string const& key, std::string const& value) {
  std::string lk = StringUtils::tolower(key);

  if (value.empty()) {
    _headers.erase(lk.c_str());
  } else {
    StringUtils::trimInPlace(lk);

    char const* k = StringUtils::duplicate(lk);
    char const* v = StringUtils::duplicate(value);

    _headers.insert(k, lk.size(), v);
    checkHeader(k, v);

    _freeables.push_back(k);
    _freeables.push_back(v);
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets many header fields
////////////////////////////////////////////////////////////////////////////////

void HttpResponse::setHeaders(std::string const& headers, bool includeLine0) {
  // make a copy we can change, this buffer will be deleted in the destructor
  char* headerBuffer = new char[headers.size() + 1];
  memcpy(headerBuffer, headers.c_str(), headers.size() + 1);

  _freeables.push_back(headerBuffer);

  // check for '\n' (we check for '\r' later)
  int lineNum = includeLine0 ? 0 : 1;

  char* start = headerBuffer;
  char* end = headerBuffer + headers.size();
  char* end1 = start;

  for (; end1 < end && *end1 != '\n'; ++end1) {
  }

  while (start < end) {
    char* end2 = end1;

    if (start < end2 && end2[-1] == '\r') {
      --end2;
    }

    // the current line is [start, end2)
    if (start < end2) {
      // now split line at the first spaces
      char* end3 = start;

      for (; end3 < end2 && *end3 != ' ' && *end3 != ':'; ++end3) {
        *end3 = ::tolower(*end3);
      }

      // the current token is [start, end3) and all in lower case
      if (lineNum == 0) {
        // the start should be HTTP/1.1 followed by blanks followed by the
        // result code
        if (start + 8 <= end3 && memcmp(start, "http/1.1", 8) == 0) {
          char* start2 = end3;

          for (; start2 < end2 && (*start2 == ' ' || *start2 == ':');
               ++start2) {
          }

          if (start2 < end2) {
            *end2 = '\0';

            _code = static_cast<HttpResponseCode>(::atoi(start2));
          } else {
            _code = NOT_IMPLEMENTED;
          }
        } else {
          _code = NOT_IMPLEMENTED;
        }
      }

      // normal header field, key is [start, end3) and the value is [start2,
      // end4)
      else {
        for (; end3 < end2 && *end3 != ':'; ++end3) {
          *end3 = ::tolower(*end3);
        }

        *end3 = '\0';

        if (end3 < end2) {
          char* start2 = end3 + 1;

          for (; start2 < end2 && *start2 == ' '; ++start2) {
          }

          char* end4 = end2;

          for (; start2 < end4 && *(end4 - 1) == ' '; --end4) {
          }

          *end4 = '\0';

          _headers.insert(start, end3 - start, start2);
        } else {
          _headers.insert(start, end3 - start, end3);
        }
      }
    }

    start = end1 + 1;

    for (end1 = start; end1 < end && *end1 != '\n'; ++end1) {
    }

    lineNum++;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief add a cookie
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief swaps data
////////////////////////////////////////////////////////////////////////////////

HttpResponse* HttpResponse::swap() {
  HttpResponse* response = new HttpResponse(_code, _apiCompatibility);

  response->_headers.swap(&_headers);
  response->_body.swap(&_body);
  response->_freeables.swap(_freeables);

  bool isHeadResponse = response->_isHeadResponse;
  response->_isHeadResponse = _isHeadResponse;
  _isHeadResponse = isHeadResponse;

  size_t bodySize = response->_bodySize;
  response->_bodySize = _bodySize;
  _bodySize = bodySize;

  return response;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief writes the header
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the size of the body
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the body
////////////////////////////////////////////////////////////////////////////////

StringBuffer& HttpResponse::body() { return _body; }

////////////////////////////////////////////////////////////////////////////////
/// @brief indicates a head response
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief deflates the response body
///
/// the body must already be set. deflate is then run on the existing body
////////////////////////////////////////////////////////////////////////////////

int HttpResponse::deflate(size_t bufferSize) {
  int res = _body.deflate(bufferSize);

  if (res != TRI_ERROR_NO_ERROR) {
    return res;
  }

  setHeader(TRI_CHAR_LENGTH_PAIR("content-encoding"), "deflate");
  return TRI_ERROR_NO_ERROR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief checks for special headers
////////////////////////////////////////////////////////////////////////////////

void HttpResponse::checkHeader(char const* key, char const* value) {
  if (key[0] == 't' && strcmp(key, "transfer-encoding") == 0) {
    if (TRI_CaseEqualString(value, "chunked")) {
      _isChunked = true;
    } else {
      _isChunked = false;
    }
  }
}

#endif
