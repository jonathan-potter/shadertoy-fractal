/*
  programmer: jonathan potter
  github: https://github.com/jonathan-potter
  repo: https://github.com/jonathan-potter/shadertoy-fractal
*/

const int MAX_ITERATIONS = 256;

struct complex { 
  float real;
  float imaginary;
};

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

int mandelbrot(vec2 coordinate) {
  complex c = complex(coordinate.x, coordinate.y);
  complex z = complex(0.0, 0.0);

  return fractal(c, z);
}

int julia(vec2 coordinate, vec2 offset) {
  complex c = complex(offset.x, offset.y);
  complex z = complex(coordinate.x, coordinate.y);

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
  vec2 coordinate    = fragCoordToXY(fragCoord);
  vec2 clickPosition = fragCoordToXY(vec2(iMouse.x, iMouse.y));

  int julia = julia(coordinate, clickPosition);
  int mandelbrot = mandelbrot(coordinate);
    
  float point;  
  if(length(clickPosition - coordinate) < 0.05){
    point = 1.0;
  } else {
    point = 0.0;
  }
    
  float juliaColor      = 5.0 * float(julia) / float(MAX_ITERATIONS);
  float mandelbrotColor = 5.0 * float(mandelbrot) / float(MAX_ITERATIONS);

  fragColor = vec4(mandelbrotColor, juliaColor, point, 1.0);
}
