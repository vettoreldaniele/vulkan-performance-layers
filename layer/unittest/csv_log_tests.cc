// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdio>
#include <iostream>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "layer/support/csv_logging.h"

using ::testing::ElementsAre;

namespace performancelayers {
namespace {
// This is a simple test and only calls the methods to make sure the
// logger doesn't crash.
TEST(CSVLogger, MethodCheck) {
  StringOutput out = {};
  CSVLogger logger("pipeline,duration", &out);
  VectorInt64Attr hashes("hashes", {2, 3});
  Duration dur = Duration::FromNanoseconds(1);
  CreateGraphicsPipelinesEvent pipeline_event("create_graphics_pipeline",
                                              hashes, dur, LogLevel::kHigh);
  logger.StartLog();
  logger.AddEvent(&pipeline_event);
  logger.Flush();
  logger.EndLog();
  // Checks double `EndLog` calls.
  logger.EndLog();
  std::string_view event_str = "\"[0x2,0x3]\",1";
  EXPECT_THAT(out.GetLog(), ElementsAre("pipeline,duration", event_str));
}

}  // namespace
}  // namespace performancelayers
