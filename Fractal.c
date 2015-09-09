/* jonathan potter */
/* github.com/jonathan-potter */

const int MAX_ITERATIONS = 64;

struct complex { 
  float real;
  float imaginary;
};

int fractal(complex c, complex z) {
  int crossoverIteration = 0;
  for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
    float real = z.real * z.real - z.imaginary * z.imaginary + c.real;
    float imaginary = 2.0 * z.real * z.imaginary + c.imaginary;

    z.real = real;
    z.imaginary = imaginary;

    if (z.real * z.real + z.imaginary + z.imaginary > 4.0 && crossoverIteration == 0) {
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
  complex c = complex(-0.835 * cos(iGlobalTime * 0.25), 0.2321);
  complex z = complex(x, y);

  return fractal(c, z);
}

vec2 fragCoordToXY(vec2 fragCoord) {
  vec2 relativePosition = fragCoord.xy / iResolution.xy;
  float aspectRatio = iResolution.x / iResolution.y;

  vec2 cartesianPosition = (relativePosition - 0.5) * 4.0;
  cartesianPosition.x *= aspectRatio;

  return cartesianPosition;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
  vec2 coordinate = fragCoordToXY(fragCoord);

  int crossoverIteration = animatedJulia(float(coordinate.x), float(coordinate.y));
    
  float color = float(crossoverIteration) / float(MAX_ITERATIONS);

  fragColor = vec4(color, color, color, 1.0);
}
