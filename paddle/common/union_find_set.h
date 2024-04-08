// Copyright (c) 2024 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <unordered_map>
#include <vector>

namespace common {

template <typename T>
class UnionFindSet {
 public:
  T Find(const T& x) {
    if (parent_.find(x) == parent_.end()) {
      return x;
    }
    if (parent_[x] != x) {
      parent_[x] = Find(parent_[x]);
    }
    return parent_[x];
  }

  void Union(const T& p, const T& q) {
    if (parent_.find(p) == parent_.end()) {
      parent_[p] = p;
    }
    if (parent_.find(q) == parent_.end()) {
      parent_[q] = q;
    }
    parent_[Find(q)] = Find(p);
  }

  std::vector<std::vector<T>> Clusters() {
    std::unordered_map<T, std::vector<T>> clusters_map;
    for (auto it = parent_.begin(); it != parent_.end(); it++) {
      clusters_map[Find(it->first)].emplace_back(it->first);
    }
    std::vector<std::vector<T>> clusters;
    for (auto it = clusters_map.begin(); it != clusters_map.end(); it++) {
      clusters.emplace_back(it->second);
    }
    return clusters;
  }

  bool IsConnect(const T& p, const T& q) { return Find(p) == Find(q); }

  std::unordered_map<T, T> GetMap() { return parent_; }

 private:
  std::unordered_map<T, T> parent_;
};

}  // namespace common
