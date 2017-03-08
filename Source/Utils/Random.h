#pragma once

namespace ae {
/// Randomization utility class.
class Random {
public:
    /// Sets an arbitrary random seed which will be used to generate
    /// randomized values.
    static void initSeed();
    /// Specifies the "seed" randomized values will be generated from. Identical
    /// seeds will generate an identical succession of numbers.
    static void setSeed(int seed);
    /// Returns a randomized "int" N, such that 0 <= N < max.
    static int next(int max);
    /// Returns a randomized "int" N, such that min <= N <= max.
    static int next(int min, int max);
    /// Returns a randomized "bool" with equal chance of being either true or false.
    static bool nextBool();
    /// Returns a randomized "float" F, such that 0.0f <= F <= 1.0f.
    static float nextFloat();
    /// Returns a uniform randomized "float" F, such that min <= F <= max.
    static float nextFloat(float min, float max);
    /// Returns a randomized "double" D, such that 0.0 <= D <= 1.0.
    static double nextDouble();
    /// Returns a uniform randomized "double" D, such that min <= D <= max.
    static double nextDouble(double min, double max);
};
}
