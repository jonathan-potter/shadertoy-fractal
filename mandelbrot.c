/*
  programmer: jonathan potter
  github: https://github.com/jonathan-potter
  repo: https://github.com/jonathan-potter/shadertoy-fractal
*/

const int MAX_ITERATIONS = 2048;
const float pi = 3.14159;

struct complex { 
  float real;
  float imaginary;
};

float rampFunction(float t) {
  // this is here because modulus doesn't work and i wanted a smooth
  // waveform to base zooming on. obviously still needs work 
  float sum = 0.0;
  float f = 0.05; // ramp frequency
    
  float positiveNegative = 5.0;  
  for (float k = 1.0; k < 600.0; k++) {
    sum += 2.0 / pi * positiveNegative * sin(2.0 * pi * k * f * t) / k;
    
    positiveNegative *= -1.0; 
  }
    
  return sum + 2.0;
}

int fractal(complex c, complex z) {
  for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {

    // z <- z^2 + c
    float real = z.real * z.real - z.imaginary * z.imaginary + c.real;
    float imaginary = 2.0 * z.real * z.imaginary + c.imaginary;

    z.real = real;
    z.imaginary = imaginary;

    if (z.real * z.real + z.imaginary + z.imaginary > 4.0) {
      return iteration;
    }
  }

  return 0;
}

int mandelbrot(float x, float y) {
  complex c = complex(x, y);
  complex z = complex(0.0, 0.0);

  return fractal(c, z);
}

int animatedJulia(float x, float y) {
  float animationOffset = 0.055 * cos(iGlobalTime * 2.0);

  complex c = complex(-0.795 + animationOffset, 0.2321);
  complex z = complex(x, y);

  return fractal(c, z);
}

vec2 fragCoordToXY(vec2 fragCoord) {
  vec2 relativePosition = fragCoord.xy / iResolution.xy;
  float aspectRatio = iResolution.x / iResolution.y;

  vec2 cartesianPosition = (relativePosition - 0.5) * 3.0;
  cartesianPosition.x *= aspectRatio;
    
  float zoomLevel = pow(1.2, 10.0 * rampFunction(iGlobalTime));
  cartesianPosition.x /= zoomLevel;
  cartesianPosition.y /= zoomLevel;
    
  cartesianPosition.x += -0.22614245999608962;
  cartesianPosition.y += 0.8115717941462461;

  return cartesianPosition;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
  vec2 coordinate = fragCoordToXY(fragCoord);

  int crossoverIteration = mandelbrot(float(coordinate.x), float(coordinate.y));
    
  float color = 5.0 * float(crossoverIteration) / float(MAX_ITERATIONS);

  fragColor = vec4(color, color, color, 1.0);
}
