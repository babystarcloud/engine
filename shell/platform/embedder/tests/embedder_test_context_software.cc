// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/shell/platform/embedder/tests/embedder_test_context_software.h"

#include "flutter/fml/make_copyable.h"
#include "flutter/fml/paths.h"
#include "flutter/runtime/dart_vm.h"
#include "flutter/shell/platform/embedder/tests/embedder_assertions.h"
#include "flutter/shell/platform/embedder/tests/embedder_test_compositor_software.h"
#include "flutter/testing/testing.h"
#include "third_party/dart/runtime/bin/elf_loader.h"
#include "third_party/skia/include/core/SkSurface.h"

namespace flutter {
namespace testing {

EmbedderTestContextSoftware::EmbedderTestContextSoftware(
    std::string assets_path)
    : EmbedderTestContext(assets_path) {}

EmbedderTestContextSoftware::~EmbedderTestContextSoftware() = default;

bool EmbedderTestContextSoftware::Present(sk_sp<SkImage> image) {
  software_surface_present_count_++;

  FireRootSurfacePresentCallbackIfPresent([image] { return image; });

  return true;
}

size_t EmbedderTestContextSoftware::GetSurfacePresentCount() const {
  return software_surface_present_count_;
}

void EmbedderTestContextSoftware::SetupSurface(SkISize surface_size) {
  surface_size_ = surface_size;
}

void EmbedderTestContextSoftware::SetupCompositor() {
  FML_CHECK(!compositor_) << "Already setup a compositor in this context.";
  compositor_ = std::make_unique<EmbedderTestCompositorSoftware>(surface_size_);
}

}  // namespace testing
}  // namespace flutter
