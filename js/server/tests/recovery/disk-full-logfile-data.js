/*jshint globalstrict:false, strict:false, unused : false */
/*global fail, assertEqual */

////////////////////////////////////////////////////////////////////////////////
/// @brief tests for dump/reload
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2012 triagens GmbH, Cologne, Germany
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
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

var db = require("org/arangodb").db;
var internal = require("internal");
var jsunity = require("jsunity");
var fs = require("fs");

function runSetup () {
  'use strict';
  internal.debugClearFailAt();
  
  db._drop("UnitTestsRecovery");
  var c = db._create("UnitTestsRecovery"); 
  internal.wal.flush(true, true);
  internal.debugSetFailAt("CreateDatafile1");
  internal.debugSetFailAt("LogfileManagerGetWriteableLogfile");

  c.insert({ value: 1 });
  try {
    internal.wal.flush();
    fail();
  }
  catch (err) {
  }

  internal.wait(3);
  try {
    c.save({ _key: "crashme" }, true); // wait for sync
    fail();
  }
  catch (err) {
  }

  internal.debugSegfault("crashing server");
}

////////////////////////////////////////////////////////////////////////////////
/// @brief test suite
////////////////////////////////////////////////////////////////////////////////

function recoverySuite () {
  'use strict';
  jsunity.jsUnity.attachAssertions();

  return {
    setUp: function () {
    },
    tearDown: function () {
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test whether we can start the server
////////////////////////////////////////////////////////////////////////////////
    
    testDiskFullLogfileData : function () {
      assertEqual(1, db._collection("UnitTestsRecovery").count());
    }
        
  };
}

////////////////////////////////////////////////////////////////////////////////
/// @brief executes the test suite
////////////////////////////////////////////////////////////////////////////////

function main (argv) {
  'use strict';
  if (argv[1] === "setup") {
    runSetup();
    return 0;
  }
  else {
    jsunity.run(recoverySuite);
    return jsunity.done().status ? 0 : 1;
  }
}
