/*
  programmer: jonathan potter
  github: https://github.com/jonathan-potter
  repo: https://github.com/jonathan-potter/shadertoy-fractal
*/

const int MAX_ITERATIONS = 64;
const float ITERATIONS_PER_SECOND = 32.0;
const float pi = 3.14159;
    
float modulus(float number, float divisor) {
  float integerQuotient = floor(number / divisor);
    
  return number - (integerQuotient * divisor);
}

float rampFunction(float t) {
  float animationPeriod = float(MAX_ITERATIONS);
    
  return modulus(t, animationPeriod);
}

struct complex { 
  float real;
  float imaginary;
};

int fractal(complex c, complex z, int iterations) {
  for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
    if (iteration >= iterations) {return 0;}

    // z <- z^2 + c
    float real = z.real * z.real - z.imaginary * z.imaginary + c.real;
    float imaginary = 2.0 * z.real * z.imaginary + c.imaginary;

    z.real = real;
    z.imaginary = imaginary;

    if (z.real * z.real + z.imaginary * z.imaginary > 4.0) {
      return iteration;
    }
  }

  return 0;
}

int mandelbrot(vec2 coordinate, int iterations) {
  complex c = complex(coordinate.x, coordinate.y);
  complex z = complex(0.0, 0.0);

  return fractal(c, z, iterations);
}

vec2 fragCoordToXY(vec2 fragCoord) {
  vec2 relativePosition = fragCoord.xy / iResolution.xy;
  float aspectRatio = iResolution.x / iResolution.y;

  vec2 cartesianPosition = (relativePosition - 0.5) * 3.0;
  cartesianPosition.x *= aspectRatio;

  return cartesianPosition;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
  int iterations = int(floor(rampFunction((iGlobalTime * ITERATIONS_PER_SECOND))));
    
  vec2 coordinate = fragCoordToXY(fragCoord);

  int crossoverIteration = mandelbrot(coordinate, iterations);
    
  float color = 1.0 * float(crossoverIteration) / float(iterations);

  fragColor = vec4(color, color, color, 1.0);
}
