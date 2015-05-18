
// =================================================================================================
// This file is part of the CLTune project, which loosely follows the Google C++ styleguide and uses
// a tab-size of two spaces and a max-width of 100 characters per line.
//
// Author: cedric.nugteren@surfsara.nl (Cedric Nugteren)
//
// This file implements the OpenCL Memory class, a container for both host and device data. The
// device data is based on the OpenCL C++ API and the cl::Buffer class, while the host data is based
// on the std::vector class. The Memory class is templated to support different types.
//
// -------------------------------------------------------------------------------------------------
//
// Copyright 2014 SURFsara
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//  http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// =================================================================================================

#ifndef CLTUNE_MEMORY_H_
#define CLTUNE_MEMORY_H_

#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <complex>

#include "cltune/opencl.h"

namespace cltune {
// =================================================================================================

// Shorthands for complex data-types
using float2 = std::complex<float>; // cl_float2;
using double2 = std::complex<double>; // cl_double2;

// =================================================================================================

// Enumeration of currently supported data-types by this class
enum class MemType { kInt, kFloat, kDouble, kFloat2, kDouble2 };

// See comment at top of file for a description of the class
template <typename T>
class Memory {
 public:

  // Static variable to get the memory type based on a template argument
  const static MemType type;

  // Initializes the host and device data (with zeroes or based on a source-vector)
  explicit Memory(const size_t size, cl::CommandQueue queue, const cl::Context &context,
                  const cl_mem_flags flags);
  explicit Memory(const size_t size, cl::CommandQueue queue, const cl::Context &context,
                  const cl_mem_flags flags, const std::vector<T> &source);

  // Accessors to the host/device data
  std::vector<T> host() const { return host_; }
  std::shared_ptr<cl::Buffer> device() const { return device_; }

  // Downloads the device data onto the host
  void UploadToDevice();
  void DownloadFromDevice();

 private:

  // The data (both host and device)
  const size_t size_;
  std::vector<T> host_;
  std::shared_ptr<cl::Buffer> device_;

  // Pointer to the OpenCL command queue
  cl::CommandQueue queue_;
};


// =================================================================================================
} // namespace cltune

// CLTUNE_MEMORY_H_
#endif