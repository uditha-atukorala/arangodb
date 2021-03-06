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

#ifndef ARANGOD_HTTP_SERVER_HTTP_COMM_TASK_H
#define ARANGOD_HTTP_SERVER_HTTP_COMM_TASK_H 1

#include "Scheduler/SocketTask.h"

#include "Basics/Mutex.h"
#include "Basics/StringBuffer.h"
#include "Basics/WorkItem.h"

#include <deque>

namespace arangodb {
class HttpRequest;
class HttpResponse;

namespace rest {
class HttpCommTask;
class HttpServer;

////////////////////////////////////////////////////////////////////////////////
/// @brief http communication
////////////////////////////////////////////////////////////////////////////////

class HttpCommTask : public SocketTask, public RequestStatisticsAgent {
  HttpCommTask(HttpCommTask const&) = delete;
  HttpCommTask const& operator=(HttpCommTask const&) = delete;

 public:
  static size_t const MaximalHeaderSize;
  static size_t const MaximalBodySize;
  static size_t const MaximalPipelineSize;
  static size_t const RunCompactEvery;

 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief constructs a new task
  //////////////////////////////////////////////////////////////////////////////

  HttpCommTask(HttpServer*, TRI_socket_t, ConnectionInfo&&,
               double keepAliveTimeout);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief destructs a task
  //////////////////////////////////////////////////////////////////////////////

 protected:
  ~HttpCommTask();

 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief return whether or not the task desires to start a dispatcher thread
  //////////////////////////////////////////////////////////////////////////////
  
  bool startThread() const { return _startThread; }

  //////////////////////////////////////////////////////////////////////////////
  /// @brief handles response
  //////////////////////////////////////////////////////////////////////////////

  void handleResponse(HttpResponse*);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief reads data from the socket
  //////////////////////////////////////////////////////////////////////////////

  bool processRead();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief sends more chunked data
  //////////////////////////////////////////////////////////////////////////////

  void sendChunk(basics::StringBuffer*);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief chunking is finished
  //////////////////////////////////////////////////////////////////////////////

  void finishedChunked();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief task set up complete
  //////////////////////////////////////////////////////////////////////////////

  void setupDone();

 private:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief reads data from the socket
  //////////////////////////////////////////////////////////////////////////////

  void addResponse(HttpResponse*);

  //////////////////////////////////////////////////////////////////////////////
  /// check the content-length header of a request and fail it is broken
  //////////////////////////////////////////////////////////////////////////////

  bool checkContentLength(bool expectContentLength);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief fills the write buffer
  //////////////////////////////////////////////////////////////////////////////

  void fillWriteBuffer();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief handles CORS options
  //////////////////////////////////////////////////////////////////////////////

  void processCorsOptions();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief processes a request
  //////////////////////////////////////////////////////////////////////////////

  void processRequest();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief clears the request object
  //////////////////////////////////////////////////////////////////////////////

  void clearRequest();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief resets the internal state
  ///
  /// this method can be called to clean up when the request handling aborts
  /// prematurely
  //////////////////////////////////////////////////////////////////////////////

  void resetState(bool close);

 protected:
  bool setup(Scheduler* scheduler, EventLoop loop) override;
  void cleanup() override;
  bool handleEvent(EventToken token, EventType events) override;
  void signalTask(TaskData*) override;

 protected:
  bool handleRead() override;

  void completedWriteBuffer() override;

  void handleTimeout() override;

 protected:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief connection info
  //////////////////////////////////////////////////////////////////////////////

  ConnectionInfo _connectionInfo;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief the underlying server
  //////////////////////////////////////////////////////////////////////////////

  HttpServer* const _server;

 private:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief write buffers
  //////////////////////////////////////////////////////////////////////////////

  std::deque<basics::StringBuffer*> _writeBuffers;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief statistics buffers
  //////////////////////////////////////////////////////////////////////////////

  std::deque<TRI_request_statistics_t*> _writeBuffersStats;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief current read position
  //////////////////////////////////////////////////////////////////////////////

  size_t _readPosition;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief start of the body position
  //////////////////////////////////////////////////////////////////////////////

  size_t _bodyPosition;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief body length
  //////////////////////////////////////////////////////////////////////////////

  size_t _bodyLength;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief true if request is complete but not handled
  //////////////////////////////////////////////////////////////////////////////

  bool _requestPending;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief true if a close has been requested by the client
  //////////////////////////////////////////////////////////////////////////////

  bool _closeRequested;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief true if reading the request body
  //////////////////////////////////////////////////////////////////////////////

  bool _readRequestBody;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief whether or not to allow credentialed requests
  ///
  /// this is only used for CORS
  //////////////////////////////////////////////////////////////////////////////

  bool _denyCredentials;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief whether the client accepts deflate algorithm
  //////////////////////////////////////////////////////////////////////////////

  bool _acceptDeflate;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief new request started
  //////////////////////////////////////////////////////////////////////////////

  bool _newRequest;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief true if within a chunked response
  //////////////////////////////////////////////////////////////////////////////

  bool _isChunked;
  
  //////////////////////////////////////////////////////////////////////////////
  /// @brief start a separate thread if the task is added to the dispatcher?
  //////////////////////////////////////////////////////////////////////////////

  bool _startThread;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief the request with possible incomplete body
  //////////////////////////////////////////////////////////////////////////////

  HttpRequest* _request;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief http version number used
  //////////////////////////////////////////////////////////////////////////////

  GeneralRequest::ProtocolVersion _httpVersion;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief type of request (GET, POST, ...)
  //////////////////////////////////////////////////////////////////////////////

  GeneralRequest::RequestType _requestType;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief value of requested URL
  //////////////////////////////////////////////////////////////////////////////

  std::string _fullUrl;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief value of the HTTP origin header the client sent (if any).
  ///
  /// this is only used for CORS
  //////////////////////////////////////////////////////////////////////////////

  std::string _origin;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief start position of current request
  //////////////////////////////////////////////////////////////////////////////

  size_t _startPosition;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief number of requests since last compactification
  //////////////////////////////////////////////////////////////////////////////

  size_t _sinceCompactification;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief original body length
  //////////////////////////////////////////////////////////////////////////////

  size_t _originalBodyLength;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief task ready
  //////////////////////////////////////////////////////////////////////////////

  std::atomic<bool> _setupDone;
};
}
}

#endif
