import processing.svg.*;

int radius = 400;
int center_x = 500;
int center_y = 600;
int start_angle = 225;
int end_angle = 315;
float step = 3.6;

void setup() {
  size(1000, 500);
  
  beginRecord(SVG, "scale.svg");

  background(255);
  
  // draw arc
  arc(center_x, center_y, radius * 2, radius * 2, 0.75 * -PI, 0.25 * -PI);

  // draw strokes
  // 1 degree
  drawStrokes(1.03, step);
  // 5 degree
  strokeWeight(2);
  drawStrokes(1.06, step * 5);
  // 10 degree
  strokeWeight(3);
  drawStrokes(1.1, step * 10);
  
  // draw numbers
  drawText(start_angle, 0.25 * step, "0", 1.15, 36);
  drawText(start_angle + step * 5, 0.25 * step, "5", 1.1, 30);
  drawText(start_angle + step * 10, 0.5 * step, "10", 1.15, 36);
  drawText(start_angle + step * 15, 0.5 * step, "15", 1.1, 30);
  drawText(start_angle + step * 20, 0.5 * step, "20", 1.15, 36);
  drawText(start_angle + step * 25, 0.5 * step, "25", 1.1, 30);
  
  endRecord();
}


/**
* float proportion: proportion of the line length compared to the radius
* float degrees: degrees between two strokes
*/
void drawStrokes(float proportion, float degrees) {
  for (float i = start_angle; i <= end_angle; i += degrees) {
    float arc_x = center_x + cos(radians(i)) * radius;
    float arc_y = center_y + sin(radians(i)) * radius;
    float x = center_x + cos(radians(i)) * radius * proportion;
    float y = center_y + sin(radians(i)) * radius * proportion;
    line(arc_x, arc_y, x, y);
  }
}

void drawText(float angle, float alignment, String text, float proportion, int font_size) {
  fill(0);
  PFont f = createFont("Karma",20,true);
  textFont(f, font_size);
  float text_angle = radians(angle + 90);
  float text_x = center_x + cos(radians(angle - alignment)) * radius * proportion;
  float text_y = center_y + sin(radians(angle - alignment)) * radius * proportion;
  translate(text_x, text_y);
  rotate(text_angle);
  text(text, 0, 0);
  
  // rollback
  rotate(-text_angle);
  translate(-text_x, -text_y);
}
