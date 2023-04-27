// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <random>
#include "textgen.h"

using testing::Eq;
using testing::ElementsAre;
using testing::AnyOf;

std::random_device rd;

TEST(test, table_generates_correctly) {
    TextGenerator generator(2, rd());
    generator.analyze("hello there my dear friend");

    auto table = generator.getPrefixSuffixTable();

    ASSERT_THAT(table.size(), Eq(3));

    prefix testPrefix = {"hello", "there"};
    ASSERT_THAT(table[testPrefix], ElementsAre("my"));

    testPrefix = {"there", "my"};
    ASSERT_THAT(table[testPrefix], ElementsAre("dear"));

    testPrefix = {"my", "dear"};
    ASSERT_THAT(table[testPrefix], ElementsAre("friend"));
}

TEST(test, single_suffix_is_handled_correctly) {
    TextGenerator generator(2, rd());
    generator.analyze("hello there my");
    std::string text = generator.generateText(3, {"hello", "there"});

    ASSERT_THAT(text, Eq("hello there my"));
}

TEST(test, multiple_suffixes_are_handled_correctly) {
    TextGenerator generator(2, rd());
    generator.analyze("hello there sweetie hello there darling");
    std::string text = generator.generateText(3, {"hello", "there"});

    ASSERT_THAT(text, AnyOf(
            Eq("hello there sweetie"), Eq("hello there darling")));
}
