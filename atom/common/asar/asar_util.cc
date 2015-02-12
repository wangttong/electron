// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/common/asar/asar_util.h"

#include <map>

#include "atom/common/asar/archive.h"
#include "base/files/file_path.h"
#include "base/lazy_instance.h"
#include "base/stl_util.h"

namespace asar {

typedef std::map<base::FilePath, std::shared_ptr<Archive>> ArchiveMap;

namespace {

static base::LazyInstance<ArchiveMap> g_archive_map = LAZY_INSTANCE_INITIALIZER;

}  // namespace

std::shared_ptr<Archive> GetOrCreateAsarArchive(const base::FilePath& path) {
  ArchiveMap& archive_map = *g_archive_map.Pointer();
  if (!ContainsKey(archive_map, path)) {
    std::shared_ptr<Archive> archive(new Archive(path));
    if (!archive->Init())
      return nullptr;
    archive_map[path] = archive;
  }
  return archive_map[path];
}

}  // namespace asar
