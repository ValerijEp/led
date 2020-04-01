#pragma once

#include "util/constants.h"

#include <atomic>

struct LED
{
    std::atomic<util::Color> color;
    std::atomic<util::State> state;
    std::atomic<util::Rate> rate;
};
