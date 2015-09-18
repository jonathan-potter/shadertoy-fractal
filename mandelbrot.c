/*
  programmer: jonathan potter
  github: https://github.com/jonathan-potter
  repo: https://github.com/jonathan-potter/shadertoy-fractal
*/

const int MAX_ITERATIONS = 512;
const float pi = 3.14159;

struct complex { 
  float real;
  float imaginary;
};
    
float modulus(float number, float divisor) {
  float integerQuotient = floor(number / divisor);
    
  return number - (integerQuotient * divisor);
}

float rampFunction(float t) {
  float animationPeriod = 5.0;
    
  return modulus(t, animationPeriod);
}

int fractal(complex c, complex z) {
  for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {

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

int mandelbrot(vec2 coordinate) {
  complex c = complex(coordinate.x, coordinate.y);
  complex z = complex(0.0, 0.0);

  return fractal(c, z);
}

int animatedJulia(vec2 coordinate) {
  float animationOffset = 0.055 * cos(iGlobalTime * 2.0);

  complex c = complex(-0.795 + animationOffset, 0.2321);
  complex z = complex(coordinate.x, coordinate.y);

  return fractal(c, z);
}

vec2 fragCoordToXY(vec2 fragCoord) {
  vec2 relativePosition = fragCoord.xy / iResolution.xy;
  float aspectRatio = iResolution.x / iResolution.y;

  vec2 cartesianPosition = (relativePosition - 0.5) * 10.0;
  cartesianPosition.x *= aspectRatio;
    
  float zoomLevel = pow(1.3, 10.0 * rampFunction(iGlobalTime));
  cartesianPosition.x /= zoomLevel;
  cartesianPosition.y /= zoomLevel;
    
  cartesianPosition.x += -0.22614245999608962;
  cartesianPosition.y += 0.8115717941462461;

  return cartesianPosition;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
  vec2 coordinate = fragCoordToXY(fragCoord);

  int crossoverIteration = mandelbrot(coordinate);
    
  float color = 1.0 * float(crossoverIteration) / float(MAX_ITERATIONS);

  fragColor = vec4(color, color, color, 1.0);
}
