#pragma once

namespace ae {
/**	Math utility class. */
class Math {
public:
    static const float PI;
    static const float TWO_PI;
    static const int MAX_INT;
    static const float MAX_FLOAT;
    static const double MAX_DOUBLE;

    /** Returns "x*x". */
    static float square(float x);
    /** Returns square root of "x". */
    static float sqrt(float x);
    /** Returns "base^exponent". */
    static float pow(float base, float exponent);
    /** Returns the absolute value of an int. */
    static int abs(int x);
    /** Returns the absolute value of a float. */
    static float abs(float x);

    /** Returns the rounded value of a float. */
    static int round(float x);
    /** Returns the value of decimal rounded down. */
    static int roundDown(float x);
    /** Returns the value of a decimal rounded up. */
    static int roundUp(float x);
    /** Returns the fractional part of a float. */
    static float fractionalPart(float x);
    /** Clamp the value of a float between min and max. */
    static float clamp(float min, float max, float x);
    /** Linear interpolation from between two float. Specified amount should
        be a value between 0.0 and 1.0. */
    static float lerp(float from, float to, float amount);
    /** Returns true if x is a prime number. */
    static int isPrime(int n);
    /** Returns whether n is an infinity value (either positive infinity or negative infinity). */
    static bool isInfinite(double n);


    /** Converts radians to degrees. */
    static float degrees(float radians);
    /** Converts degrees to radians. */
    static float radians(float degrees);
    /** Normalizes an angle in radians between -PI and PI. */
    static float normalizeAngle(float radians);

    /** Converts milliseconds to seconds. */
    static float seconds(float ms);
    /** Converts seconds to milliseconds. */
    static float milliseconds(float seconds);
};
}
