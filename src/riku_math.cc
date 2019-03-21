#include <math.h> // C module
#include <riku/math.h>

#if PLATFORM_ANDROID // Android support for log2 and log2f
extern "C"
{
    inline float log2f(float x)
    {
        return (logf(x) / 0.693147180559945f);
    }

    inline double log2(double x)
    {
        return (log(x) / 0.693147180559945);
    }
}
#endif

namespace math
{
    /* Computes cosine
     */
    float cos(float x)
    {
        return ::cosf(x);
    }

    /* Computes sine
     */
    float sin(float x)
    {
        return ::sinf(x);
    }

    /* Computes tangent
     */
    float tan(float x)
    {
        return ::tanf(x);
    }

    /* Computes hyperbolic cosine
     */
    float cosh(float x)
    {
        return ::coshf(x);
    }

    /* Computes hyperbolic sine
     */
    float sinh(float x)
    {
        return ::sinhf(x);
    }

    /* Computes hyperbolic tangent
     */
    float tanh(float x)
    {
        return ::tanhf(x);
    }

    /* Computes inverse cosine
     */
    float acos(float x)
    {
        return ::acosf(x);
    }

    /* Computes inverse sine
     */
    float asin(float x)
    {
        return ::asinf(x);
    }

    /* Computes inverse tangent
     */
    float atan(float x)
    {
        return ::atanf(x);
    }

    /* Computes inverse tangent with 2 args
     */
    float atan2(float y, float x)
    {
        return ::atan2f(y, x);
    }

    /* Computes Euler number raised to the power 'x'
     */
    float exp(float x)
    {
        return ::expf(x);
    }

    /* Computes 2 raised to the power 'x'
     */
    float exp2(float x)
    {
        return ::exp2f(x);
    }

    /* Computes the base Euler number logarithm
     */
    float log(float x)
    {
        return ::logf(x);
    }

    /* Computes the base 2 logarithm
     */
    float log2(float x)
    {
        return ::log2f(x);
    }

    /* Computes the base 10 logarithm
     */
    float log10(float x)
    {
        return ::log10f(x);
    }

    /* Computes the value of base raised to the power exponent
     */
    float pow(float x, float y)
    {
        return ::powf(x, y);
    }

    /* Computes the floating-point remainder of the division operation x/y
     */
    float fmod(float x, float y)
    {
        return ::fmodf(x, y);
    }

    /* Computes the smallest integer value not less than 'x'
     */
    float ceil(float x)
    {
        return ::ceilf(x);
    }

    /* Computes the largest integer value not greater than 'x'
     */
    float floor(float x)
    {
        return ::floorf(x);
    }

    /* Computes the nearest integer value
     */
    float round(float x)
    {
        return ::roundf(x);
    }

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    float trunc(float x)
    {
        return ::truncf(x);
    }

    /* Get the fractal part of floating point
    */
    float frac(float x)
    {
        return ::modff(x, 0);
    }

    /* Computes square root of 'x'.
     */
    float sqrt(float x)
    {
        return ::sqrtf(x);
    }
}