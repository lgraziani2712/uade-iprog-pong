#include "configs.hpp"

std::string getAssetsPath(const std::string& relativePath) {
  namespace fs = std::filesystem;

  // where the binary runs from
  auto base = fs::current_path();

  return (base / "src" / "assets" / relativePath).generic_string();
}
