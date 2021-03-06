#include "doctest.h"

#include <sstream>
#include <vault.h>

using namespace AdventOfCode;

TEST_CASE("Collect all keys in small example") {
  std::stringstream map;
  map << "#########\n"
         "#b.A.@.a#\n"
         "#########\n";

  Vault vault{map};
  auto steps = vault.collectKeys();
  int expected = 8;
  REQUIRE(expected == steps);
}

TEST_CASE("Collect all keys in larger example") {
  std::stringstream map;
  map << "########################\n"
         "#f.D.E.e.C.b.A.@.a.B.c.#\n"
         "######################.#\n"
         "#d.....................#\n"
         "########################\n";

  Vault vault{map};
  auto steps = vault.collectKeys();
  int expected = 86;
  REQUIRE(expected == steps);
}

TEST_CASE("Collect all keys in example 3") {
  std::stringstream map;
  map << "########################\n"
         "#...............b.C.D.f#\n"
         "#.######################\n"
         "#.....@.a.B.c.d.A.e.F.g#\n"
         "########################\n";

  Vault vault{map};
  auto steps = vault.collectKeys();
  int expected = 132;
  REQUIRE(expected == steps);
}

TEST_CASE("Collect all keys in example 4") {
  std::stringstream map;
  map << "#################\n"
         "#i.G..c...e..H.p#\n"
         "########.########\n"
         "#j.A..b...f..D.o#\n"
         "########@########\n"
         "#k.E..a...g..B.n#\n"
         "########.########\n"
         "#l.F..d...h..C.m#\n"
         "#################\n";

  Vault vault{map};
  auto steps = vault.collectKeys();
  int expected = 136;
  REQUIRE(expected == steps);
}

TEST_CASE("Collect all keys in example 5") {
  std::stringstream map;
  map << "########################\n"
         "#@..............ac.GI.b#\n"
         "###d#e#f################\n"
         "###A#B#C################\n"
         "###g#h#i################\n"
         "########################\n";

  Vault vault{map};
  auto steps = vault.collectKeys();
  int expected = 81;
  REQUIRE(expected == steps);
}

TEST_CASE("Collect by multiple robots 1") {
  std::stringstream map;
  map << "#######\n"
         "#a.#Cd#\n"
         "##...##\n"
         "##.@.##\n"
         "##...##\n"
         "#cB#Ab#\n"
         "#######\n";

  Vault vault{map};
  vault.deployRobots();
  auto steps = vault.collectKeys();
  int expected = 8;
  REQUIRE(expected == steps);
}

TEST_CASE("Collect by multiple robots 2") {
  std::stringstream map;

  map << "###############\n"
         "#d.ABC.#.....a#\n"
         "######@#@######\n"
         "###############\n"
         "######@#@######\n"
         "#b.....#.....c#\n"
         "###############\n";

  Vault vault{map};
  auto steps = vault.collectKeys();
  int expected = 24;
  REQUIRE(expected == steps);
}

TEST_CASE("Collect by multiple robots 4") {
  std::stringstream map;

  map << "#############\n"
         "#g#f.D#..h#l#\n"
         "#F###e#E###.#\n"
         "#dCba@#@BcIJ#\n"
         "#############\n"
         "#nK.L@#@G...#\n"
         "#M###N#H###.#\n"
         "#o#m..#i#jk.#\n"
         "#############\n";

  Vault vault{map};
  auto steps = vault.collectKeys();
  int expected = 72;
  REQUIRE(expected == steps);
}