#pragma once

#include <math.h>

static inline float LerpAngle(float current, float target, float t) {
    float diff = fmodf(target - current + 540.0f, 360.0f) - 180.0f;
    return current + diff * t;
}