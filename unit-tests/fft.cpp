#include "doctest.h"

#include <fft.h>

#include <iostream>

using namespace AdventOfCode;

TEST_CASE("Convert from string to Signal") {
  std::string const input{"12345678"};
  Signal signal = FFT::fromString(input, 1);

  Signal expected{1, 2, 3, 4, 5, 6, 7, 8};
  REQUIRE(expected == signal);
}

TEST_CASE("FFT simple input") {
  Signal input{1, 2, 3, 4, 5, 6, 7, 8};

  Signal phase_1 = FFT::outputSignal(input);
  Signal expected_1{4, 8, 2, 2, 6, 1, 5, 8};

  REQUIRE(phase_1 == expected_1);

  Signal phase_2 = FFT::outputSignal(phase_1);
  Signal expected_2{3, 4, 0, 4, 0, 4, 3, 8};

  REQUIRE(phase_2 == expected_2);

  Signal phase_3 = FFT::outputSignal(phase_2);
  Signal expected_3{0, 3, 4, 1, 5, 5, 1, 8};

  REQUIRE(phase_3 == expected_3);

  Signal phase_4 = FFT::outputSignal(phase_3);
  Signal expected_4{0, 1, 0, 2, 9, 4, 9, 8};

  REQUIRE(phase_4 == expected_4);
}

TEST_CASE("FFT longer input") {
  auto signal = FFT::fromString("80871224585914546619083218645595", 1);
  for (int i = 0; i < 100; ++i)
    signal = FFT::outputSignal(signal);
  ;

  auto result = Signal{std::begin(signal), std::next(std::begin(signal), 8)};
  auto expected = FFT::fromString("24176176", 1);

  REQUIRE(expected == result);
}

TEST_CASE("FFT longer input with many repetitions 1") {
  std::string const input{"03036732577212944063491565474664"};
  auto signal = FFT::fromString(input, 10000);
  auto offset = std::stoi(
      std::string{std::begin(input), std::next(std::begin(input), 7)});

  auto result = FFT::outputMessage(signal, 100, offset);
  auto expected = FFT::fromString("84462026", 1);

  REQUIRE(expected == result);
}

TEST_CASE("FFT longer input with many repetitions 2") {
  std::string const input{"02935109699940807407585447034323"};
  auto signal = FFT::fromString(input, 10000);
  auto offset = std::stoi(
      std::string{std::begin(input), std::next(std::begin(input), 7)});

  auto result = FFT::outputMessage(signal, 100, offset);
  auto expected = FFT::fromString("78725270", 1);

  REQUIRE(expected == result);
}

TEST_CASE("FFT longer input with many repetitions 3") {
  std::string const input{"03081770884921959731165446850517"};
  auto signal = FFT::fromString(input, 10000);
  auto offset = std::stoi(
      std::string{std::begin(input), std::next(std::begin(input), 7)});

  auto result = FFT::outputMessage(signal, 100, offset);
  auto expected = FFT::fromString("53553731", 1);

  REQUIRE(expected == result);
}