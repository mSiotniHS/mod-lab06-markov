// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <random>
#include "textgen.h"
#include <gmock/gmock-matchers.h>

std::random_device rd;

TEST(test, table_genrates_correclty) {
    TextGenerator generator(2, rd());
    generator.analyze("hello there my dear friend");

    auto table = generator.getPrefixSuffixTable();

    ASSERT_THAT(table.size(), testing::Eq(3));

    prefix testPrefix = {"hello", "there"};

    ASSERT_THAT(table[testPrefix], testing::ElementsAre("my"));
}
