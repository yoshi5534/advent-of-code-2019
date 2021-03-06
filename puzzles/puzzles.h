#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <amplifier.h>
#include <arcade.h>
#include <ascii.h>
#include <asteroids.h>
#include <computer.h>
#include <droid.h>
#include <fft.h>
#include <fuel.h>
#include <maze.h>
#include <motion.h>
#include <orbit.h>
#include <password.h>
#include <robot.h>
#include <spaceimage.h>
#include <springdroid.h>
#include <tractorbeam.h>
#include <vault.h>
#include <wires.h>

using namespace AdventOfCode;

void getInput(std::ifstream &input, int puzzleId) {
  std::stringstream inputFilePath;
  inputFilePath << "./../../input/" << puzzleId << ".txt";
  input.open(inputFilePath.str());

  if (!input.is_open())
    throw new std::runtime_error("Input file not found");
}

void solve1() {
  std::ifstream input;
  getInput(input, 1);

  std::int64_t fuel = 0;
  std::string line{};
  while (std::getline(input, line))
    fuel += fuel_for_module(std::stol(line));

  std::cout << "Required fuel: " << fuel << std::endl;
}

void solve2() {
  std::ifstream input;
  getInput(input, 2);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  {
    int noun = 12;
    int verb = 2;

    program[1] = noun;
    program[2] = verb;

    Computer computer(program);
    computer.calculate();
    std::cout << "Result of puzzle 2a: " << computer.accessMemory()[0]
              << std::endl;
  }
  {
    int expected = 19690720;
    for (int noun = 0; noun < 100; ++noun) {
      for (int verb = 0; verb < 100; ++verb) {
        program[1] = noun;
        program[2] = verb;

        Computer computer(program);
        computer.calculate();
        auto result = computer.accessMemory()[0];
        if (result == expected) {
          int answer = 100 * noun + verb;
          std::cout << "Result of puzzle 2b: " << answer << std::endl;
          return;
        }
      }
    }
  }
}

void solve3() {
  std::ifstream input;
  getInput(input, 3);

  std::string path_1{};
  std::getline(input, path_1);

  std::string path_2{};
  std::getline(input, path_2);

  WirePath wire_1 = fromString(path_1);
  WirePath wire_2 = fromString(path_2);
  Intersections locations = intersects(wire_1, wire_2);

  int shortestDistance = distances(locations)[0];
  std::cout << "Shortest distance to crossing: " << shortestDistance
            << std::endl;

  int steps = minimalSignalDelay(wire_1, wire_2, locations);
  std::cout << "Minimal signal delay steps: " << steps << std::endl;
}

void solve4() {
  std::ifstream input;
  getInput(input, 4);

  std::string lower_limit{};
  std::getline(input, lower_limit, '-');

  std::string upper_limit{};
  std::getline(input, upper_limit, '-');

  int validPasswords = 0;
  for (int password = std::stol(lower_limit);
       password <= std::stol(upper_limit); ++password)
    if (isValidPassword(password))
      validPasswords++;

  std::cout << "Number of valid passwords: " << validPasswords << std::endl;
}

void solve5() {
  std::ifstream input;
  getInput(input, 5);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  {
    Computer computer(program);
    computer.writeInput({1});
    computer.calculate();

    auto output = computer.readOutput();
    while (output == 0)
      output = computer.readOutput();
    std::cout << "Result of puzzle 5a: " << output << std::endl;
  }
  {
    Computer computer(program);
    computer.writeInput({5});
    computer.calculate();

    auto output = computer.readOutput();
    std::cout << "Result of puzzle 5b: " << output << std::endl;
  }
}

void solve6() {
  std::ifstream input;
  getInput(input, 6);

  Orbit map;

  std::string entry;
  while (std::getline(input, entry))
    map.addOrbit(entry);

  std::cout << "Checksum: " << map.checksum() << std::endl;
  std::cout << "Minimum orbital transfer: "
            << map.minimumOrbitalTransfer("YOU", "SAN") << std::endl;
}

void solve7() {
  std::ifstream input;
  getInput(input, 7);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  std::cout << "Maximum thruster signal: "
            << AmplifierChain::maxThrusterSignal(program) << std::endl;

  FeedbackLoop loop(program);
  std::cout << "Maximum output signal: " << loop.maxOutputSignal() << std::endl;
}

void solve8() {
  std::ifstream input;
  getInput(input, 8);

  std::stringstream content;
  content << input.rdbuf();
  auto image = SpaceImage::fromDigitalSendingNetwork(25, 6, content.str());
  std::cout << "Image checksum: " << image.checksum() << std::endl;

  image.print();
}

void solve9() {
  std::ifstream input;
  getInput(input, 9);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  {
    Computer computer(program);
    computer.writeInput({1});
    computer.calculate();

    std::cout << "BOOST keycode: " << computer.readOutput() << std::endl;
  }
  {
    Computer computer(program);
    computer.writeInput({2});
    computer.calculate();

    std::cout << "Coordinates of distress signal: " << computer.readOutput()
              << std::endl;
  }
}

void solve10() {
  std::ifstream input;
  getInput(input, 10);

  Asteroids asteroids{input};

  auto station = asteroids.mostVisible();
  std::cout << "Maximum visible asteroids: " << station.first << std::endl;
  std::cout << "Coordinate: " << std::get<0>(station.second) << ","
            << std::get<1>(station.second) << std::endl;

  auto vaporized = asteroids.vaporized(station.second, 200);
  std::cout << "The 200th asteroid to be vaporized is at "
            << std::get<0>(vaporized) << "," << std::get<1>(vaporized)
            << std::endl;
}

void solve11() {
  std::ifstream input;
  getInput(input, 11);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  EmergencyHullPaintingRobot robot{program};
  auto img = robot.paint(Color::White);
  img.print();
}

void solve12() {
  std::ifstream input;
  getInput(input, 12);

  Motion simulation;
  std::string line{};
  while (std::getline(input, line))
    simulation.addMoon(line);

  {
    auto repeatSimulation = simulation;
    std::cout << "Number of iterations after time repeats: "
              << repeatSimulation.repeatingTime() << std::endl;
  }

  for (int i = 0; i < 1000; ++i) {
    simulation.timestep();
  }

  std::cout << "Total energy in system after 1000 steps: "
            << simulation.totalEnergy() << std::endl;
}

void solve13() {
  std::ifstream input;
  getInput(input, 13);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  program[0] = 2;
  ArcadeCabinet cabinet{program};
  cabinet.play();
}

void solve14() {
  std::ifstream input;
  getInput(input, 14);

  NanoFactory factory;
  std::string line{};
  while (std::getline(input, line))
    factory.addReaction(line);

  std::cout << "Amount of ORE needed to produce 1 FUEL: "
            << factory.necessaryORE() << std::endl;

  std::cout << "Amount of FUEL that can be produced: "
            << factory.maximumFuel(1000000000000) << std::endl;
}

void solve15() {
  std::ifstream input;
  getInput(input, 15);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  {
    Droid droid{program};
    std::cout << "Shortest path length: " << droid.shortestPath() << std::endl;
  }
  {
    Droid droid{program};
    std::cout << "Time to fill everything with oxygen: "
              << droid.fillWithOxygen() << std::endl;
  }
}

void solve16() {
  std::ifstream input;
  getInput(input, 16);

  std::string text{};
  std::getline(input, text);
  {
    auto signal = FFT::fromString(text, 1);
    for (int i = 0; i < 100; ++i)
      signal = FFT::outputSignal(signal);

    auto result = Signal{std::begin(signal), std::next(std::begin(signal), 8)};
    std::cout << "The first eight digits are: ";
    std::for_each(std::begin(result), std::end(result),
                  [](auto const &digit) { std::cout << digit; });
    std::cout << std::endl;
  }

  {
    auto offset = std::stol(
        std::string{std::begin(text), std::next(std::begin(text), 7)});

    auto signal = FFT::fromString(text, 10000);
    auto result = FFT::outputMessage(signal, 100, offset);

    std::cout << "The first eight digits at position '" << offset << "' are: ";
    std::for_each(std::begin(result), std::end(result),
                  [](auto const &digit) { std::cout << digit; });
    std::cout << std::endl;
  }
}

void solve17() {
  std::ifstream input;
  getInput(input, 17);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  ASCII ascii(program);

  std::cout << "The sum of all crossings is: " << ascii.findIntersections()
            << std::endl;
  std::cout << "The shortest path for vacuuming: " << std::endl;
  ascii.shortestPath();
  std::cout << "The collected amount of dust: " << ascii.searchRobots()
            << std::endl;
}

void solve18() {
  std::ifstream input;
  getInput(input, 18);

  Vault vault{input};
  std::cout << "The shortest path to all keys has " << vault.collectKeys()
            << " steps." << std::endl;

  vault.deployRobots();
  std::cout << "After deploying 4 robots, the shortest path has "
            << vault.collectKeys() << " steps." << std::endl;
}

void solve19() {
  std::ifstream input;
  getInput(input, 19);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));

  auto affected = TractorBeam::scan(program);
  std::cout << "The number of affected points is: " << affected << std::endl;

  auto closest = TractorBeam::minimumDistance(program);
  std::cout << "The closest point to the emitter is (" << closest.first << ","
            << closest.second << ") -> "
            << closest.first * 10000 + closest.second << std::endl;
}

void solve20() {
  std::ifstream input;
  getInput(input, 20);

  Maze maze{input};
  std::cout << "The shortest path is " << maze.shortestPath() << " steps."
            << std::endl;
  std::cout << "The shortest recursive path is " << maze.recursivePath()
            << " steps." << std::endl;
}

void solve21() {
  std::ifstream input;
  getInput(input, 21);

  Program program{};
  std::string line{};
  while (std::getline(input, line, ','))
    program.push_back(std::stol(line));
  
  {
    SpringScript script{"NOT A J", "NOT B T", "AND T J", "NOT C T", "AND T J",
                        "AND D J", "NOT J T", "OR B T",  "OR T J",  "NOT C T",
                        "AND T J", "AND D J", "NOT A T", "OR T J"};
    SpringDroid droid{program};
    auto damage = droid.walk(script);
    std::cout << "Reported hull damage: " << damage << std::endl;
  }
  {
    // (((!H & E) | !F | (!G & H)) & !C & D) | (!B & D) | !A
    SpringScript script{"NOT H T", "AND E T", "NOT F J", "OR J T",  "NOT G J", 
                        "AND H J", "OR J T",  "NOT C J", "AND J T", "AND D T", 
                        "NOT B J", "AND D J", "OR J T",  "NOT A J", "OR T J"};
    SpringDroid droid{program};

    auto damage = droid.run(script);
    std::cout << "Reported hull damage: " << damage << std::endl;
  }
}

void solve(int puzzleId, std::string const &) {
  if (puzzleId == 1)
    solve1();

  if (puzzleId == 2)
    solve2();

  if (puzzleId == 3)
    solve3();

  if (puzzleId == 4)
    solve4();

  if (puzzleId == 5)
    solve5();

  if (puzzleId == 6)
    solve6();

  if (puzzleId == 7)
    solve7();

  if (puzzleId == 8)
    solve8();

  if (puzzleId == 9)
    solve9();

  if (puzzleId == 10)
    solve10();

  if (puzzleId == 11)
    solve11();

  if (puzzleId == 12)
    solve12();

  if (puzzleId == 13)
    solve13();

  if (puzzleId == 14)
    solve14();

  if (puzzleId == 15)
    solve15();

  if (puzzleId == 16)
    solve16();

  if (puzzleId == 17)
    solve17();

  if (puzzleId == 18)
    solve18();

  if (puzzleId == 19)
    solve19();

  if (puzzleId == 20)
    solve20();

  if (puzzleId == 21)
    solve21();
}