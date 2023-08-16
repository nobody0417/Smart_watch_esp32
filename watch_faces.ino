int cx = SCREEN_WIDTH / 2;
int cy = SCREEN_HEIGHT / 2;
int size = min(SCREEN_WIDTH, SCREEN_HEIGHT);
/*
timeinfo.tm_sec
timeinfo.tm_min
timeinfo.tm_hour
*/

void drawHourHand(int cx, int cy, int size, int hour, int minute) {
  float hour_angle = radians((hour + minute / 60.0) * 30 - 90);
  int hour_hand_length = size * 0.3;
  int hour_x = cx + hour_hand_length * cos(hour_angle);
  int hour_y = cy + hour_hand_length * sin(hour_angle);
  display.drawLine(cx, cy, hour_x, hour_y, SH110X_WHITE);
}

void drawMinuteHand(int cx, int cy, int size, int minute, int second) {
  float minute_angle = radians((minute + second / 60.0) * 6 - 90);
  int minute_hand_length = size * 0.4;
  int minute_x = cx + minute_hand_length * cos(minute_angle);
  int minute_y = cy + minute_hand_length * sin(minute_angle);
  display.drawLine(cx, cy, minute_x, minute_y, SH110X_WHITE);
}

void drawSecondHand(int cx, int cy, int size, int second) {
  float second_angle = radians(second * 6 - 90);
  int second_hand_length = size * 0.45;
  int second_x = cx + second_hand_length * cos(second_angle);
  int second_y = cy + second_hand_length * sin(second_angle);
  display.drawLine(cx, cy, second_x, second_y, SH110X_WHITE);
}

void drawAnalogClockFace(int cx, int cy, int size) {
  int clock_radius = (size / 2) - 1;
  display.drawCircle(cx, cy, clock_radius, SH110X_WHITE);
}


void oled_display1() {
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  if (watch_face == 1) {
    display.println(&timeinfo, "%H:%M:%S");
    display.println(&timeinfo, "%m %d %Y");
    display.println(&timeinfo, "%A");
    display.drawBitmap(90, 2, darkcloudy, 30, 30, 1);
  } else if (watch_face == 2) {
    drawAnalogClockFace(cx, cy, size);
    drawHourHand(cx, cy, size, timeinfo.tm_hour % 12, timeinfo.tm_min);
    drawMinuteHand(cx, cy, size, timeinfo.tm_min, timeinfo.tm_sec);
    drawSecondHand(cx, cy, size, timeinfo.tm_sec);
  } else if (watch_face == 3) {
    drawAnalogClockFace(cx - 33, cy, size);
    drawHourHand(cx - 33, cy, size, timeinfo.tm_hour % 12, timeinfo.tm_min);
    drawMinuteHand(cx - 33, cy, size, timeinfo.tm_min, timeinfo.tm_sec);
    drawSecondHand(cx - 33, cy, size, timeinfo.tm_sec);
  } else if (watch_face == 4) {
    display.setTextSize(2);
    display.setCursor(16, 3);
    display.println(&timeinfo, "%H:%M:%S");
    display.setCursor(1, 23);
    display.println(&timeinfo, "%m %d %Y");
    display.setCursor(14, 43);
    display.println(&timeinfo, "%A");
  } else if (watch_face == 5) {
    display.println(&timeinfo, "%H:%M");
    display.println(&timeinfo, "%m %d %Y");
    display.println(&timeinfo, "%A");
    display.drawBitmap(90, 2, darkcloudy, 30, 30, 1);
    display.drawRect(0, 26, 60, 5, SH110X_WHITE);//for bar graph
    display.fillRect(0, 26, timeinfo.tm_sec + 1, 5, SH110X_WHITE);
  } else if (watch_face == 6) {
    display.setTextSize(3);
    display.println("updating soon");
  }
  display.display();
}