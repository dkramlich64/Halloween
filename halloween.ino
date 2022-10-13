#include <Adafruit_NeoPixel.h>

#define LED_COUNT 300
#define LED_PIN    2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(50);
}


void loop() {
  for(int i = 0; i < 3; i++)
    fire(192, 63, 0, 255, 255, 255, false);
  for(int i = 0; i < 3; i++)
    fire(31, 0, 127, 0, 0, 0, false);
  //rainbow(10);
  theaterChase(strip.Color(255, 63, 0), strip.Color(63, 0, 255), 10, 20);
  // larson_scanner(255, 0, 0);
  double_larson_scanner(255, 31, 0, 63, 0, 255, 10);
  //larson_scanner_explode(255, 0, 0);
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}

void fire(int r1, int g1, int b1, int r2, int g2, int b2, boolean flash) {
  int flame_time = random(20, 300);
  float intensity;
  uint32_t color1;
  uint32_t color2;
  for(int i=0; i < flame_time; i++)
  {
    if(flash)
      intensity = random(0, 70) / 100.0 + 0.3;
    else
      intensity = 1;
    color1 = strip.Color((int)(intensity * r1), (int)(intensity * g1),(int)(intensity * b1));  
    for (int j = 0; j < LED_COUNT; j++) {
      strip.setPixelColor(j, color1);
    }
    for(int j=0; j < random(2, (int)LED_COUNT/5); j++) {        
      if(flash)
        intensity = random(0, 70) / 100.0 + 0.3;
      else
        intensity = 1;
      color2 = strip.Color((int)(intensity * r2), (int)(intensity * g2),(int)(intensity * b2));
      strip.setPixelColor(random(0, LED_COUNT-1), color2);
    }
    strip.show();
    delay(50);    
  }
}

void theaterChase(uint32_t color1, uint32_t color2, int size, int timeDelay) {
  int count = 0;
  int repeat = LED_COUNT * 10;
  if (LED_COUNT >= 100)
    repeat = LED_COUNT * 3;
  for (int i = 0; i < repeat; i++) {
    for (int j = 0; j < LED_COUNT; j++) {
      if ((j + count) % size >= 0 && (j + count) % size < (int)(size/2)) {
        strip.setPixelColor(j, color1);        
      }
      else {
        strip.setPixelColor(j, color2);
      } // else
    } // for j
    strip.show();
    delay(timeDelay);
    count++;
  }  // for i
}


 void larson_scanner(int red, int green, int blue) {
  uint32_t black = strip.Color(0, 0, 0);
  int index = 3, dir = 1;
  for(int j = 0; j < (LED_COUNT - 4) * 10; j++) {
    for(int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, black);
    }
    strip.setPixelColor(index, strip.Color(red, green, blue));
    strip.setPixelColor(index-1, strip.Color((int)(red*0.5), (int)(green*0.5), (int)(blue*0.5)));
    strip.setPixelColor(index+1, strip.Color((int)(red*0.5), (int)(green*0.5), (int)(blue*0.5)));
    strip.setPixelColor(index-2, strip.Color((int)(red*0.2), (int)(green*0.2), (int)(blue*0.2)));
    strip.setPixelColor(index+2, strip.Color((int)(red*0.2), (int)(green*0.2), (int)(blue*0.2)));
    strip.show();
    delay(10);
    if (index < 2) {
      dir *= -1;
    }
    if (index >= LED_COUNT-2) {
      dir *= -1;
    }
    index += dir;
  }
 }


 void double_larson_scanner(int red1, int green1, int blue1, int red2, int green2, int blue2, int count) {
  uint32_t black = strip.Color(0, 0, 0);
  int index1 = 3, dir1 = 1, index2 = LED_COUNT - 3, dir2 = -1;
  for(int j = 0; j < (LED_COUNT - 4) * count; j++) {
    for(int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, black);
    }
    strip.setPixelColor(index1, strip.Color(red1, green1, blue1));
    strip.setPixelColor(index1-1, strip.Color((int)(red1*0.5), (int)(green1*0.5), (int)(blue1*0.5)));
    strip.setPixelColor(index1+1, strip.Color((int)(red1*0.5), (int)(green1*0.5), (int)(blue1*0.5)));
    strip.setPixelColor(index1-2, strip.Color((int)(red1*0.2), (int)(green1*0.2), (int)(blue1*0.2)));
    strip.setPixelColor(index1+2, strip.Color((int)(red1*0.2), (int)(green1*0.2), (int)(blue1*0.2)));

    strip.setPixelColor(index2, strip.Color(red2, green2, blue2));
    strip.setPixelColor(index2-1, strip.Color((int)(red2*0.5), (int)(green2*0.5), (int)(blue2*0.5)));
    strip.setPixelColor(index2+1, strip.Color((int)(red2*0.5), (int)(green2*0.5), (int)(blue2*0.5)));
    strip.setPixelColor(index2-2, strip.Color((int)(red2*0.2), (int)(green2*0.2), (int)(blue2*0.2)));
    strip.setPixelColor(index2+2, strip.Color((int)(red2*0.2), (int)(green2*0.2), (int)(blue2*0.2)));    
    strip.show();
    delay(5);
    if (index1 < 2) {
      dir1 *= -1;
    }
    if (index2 < 2) {
      dir2 *= -1;
    }
    if (index1 >= LED_COUNT-2) {
      dir1 *= -1;
    }
     if (index2 >= LED_COUNT-2) {
      dir2 *= -1;
    }   
    index1 += dir1;
    index2 += dir2;
  }
 }

void larson_scanner_explode(int red, int green, int blue) {
  uint32_t black = strip.Color(0, 0, 0);
  int index1 = 3, dir1 = 1, index2 = LED_COUNT - 3, dir2 = -1;
  for(int j = 0; j < (LED_COUNT - 2) / 2; j++) {
    for(int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, black);
    }
    strip.setPixelColor(index1, strip.Color(255-red, 255-green, 255-blue));
    strip.setPixelColor(index1-1, strip.Color((int)(red*0.5), (int)(green*0.5), (int)(blue*0.5)));
    strip.setPixelColor(index1+1, strip.Color((int)(red*0.5), (int)(green*0.5), (int)(blue*0.5)));
    strip.setPixelColor(index1-2, strip.Color((int)(red*0.2), (int)(green*0.2), (int)(blue*0.2)));
    strip.setPixelColor(index1+2, strip.Color((int)(red*0.2), (int)(green*0.2), (int)(blue*0.2)));

    strip.setPixelColor(index2, strip.Color(red, green, blue));
    strip.setPixelColor(index2-1, strip.Color((int)((255-red)*0.5), (int)((255-green)*0.5), (int)((255-blue)*0.5)));
    strip.setPixelColor(index2+1, strip.Color((int)((255-red)*0.5), (int)((255-green)*0.5), (int)((255-blue)*0.5)));
    strip.setPixelColor(index2-2, strip.Color((int)((255-red)*0.2), (int)((255-green)*0.2), (int)((255-blue)*0.2)));
    strip.setPixelColor(index2+2, strip.Color((int)((255-red)*0.2), (int)((255-green)*0.2), (int)((255-blue)*0.2)));    
    strip.show();
    delay(5);
    if (index1 < 2) {
      dir1 *= -1;
    }
    if (index2 < 2) {
      dir2 *= -1;
    }
    if (index1 >= LED_COUNT-2) {
      dir1 *= -1;
    }
     if (index2 >= LED_COUNT-2) {
      dir2 *= -1;
    }   
    index1 += dir1;
    index2 += dir2;
  }
  rainbow_half_display();
}


void rainbow_half_display() {
  int rainbow[strip.numPixels()];
  for(int i=0; i<strip.numPixels(); i++) { 
    int pixelHue = (i * 65536L / strip.numPixels());
    rainbow[i] = strip.gamma32(strip.ColorHSV(pixelHue));
  }
  int half = strip.numPixels() / 2;
  for(int i=0; i < half; i++) {
    strip.setPixelColor(half+i, rainbow[half+i]);
    strip.setPixelColor(half-i, rainbow[half-i]);
    strip.show();
    delay(8);
  }    
}
