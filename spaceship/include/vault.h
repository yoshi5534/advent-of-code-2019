#pragma once

#include <map.h>

#include <iosfwd>
#include <map>
#include <variant>

namespace AdventOfCode {

struct Entrance{};
struct Wall{};
struct Open{};
struct Key{char key;};
struct Door{char door;};

using VaultField = std::variant<Entrance, Wall, Open, Key, Door>;

using VaultMap = std::map<MapPosition, VaultField>;

class Vault {
public:
  Vault(std::istream &map);

  int collectKeys();

private:
  VaultMap vault_;
};
} // namespace AdventOfCode