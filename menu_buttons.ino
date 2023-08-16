bool getInverted = 0;
const int numMenus = 7;
const int numOptions = 8;



const char* mainMenuItems[numMenus] = {
  "Brightness",
  "Backlight On/Off",
  "Set Watch Faces",
  "Set Time Zone",
  "Invert Screen",
  "Option 6",
  "Option 7",

};

int currentMenu = 0;
int currentOption = 0;

bool backlightOn = true;
int brightnessLevel = 50;  // Initial brightness level

void showMainMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(mainMenuItems[currentMenu]);
  display.display();
}

void showOptionMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(mainMenuItems[currentMenu]);
  display.println(" Option " + String(currentOption + 1));
  display.display();
}


void adjustBrightness() {
/*
  if (currentOption == 0) {
    if (brightnessLevel < 255) {
      brightnessLevel += 10;
    } else {
      brightnessLevel = 1;
    }
  }
*/


  if (currentOption == 0) {
    if (brightnessLevel > 250) {
      brightnessLevel = 1;
    }
  } else {
    if (brightnessLevel < 255) {
      brightnessLevel += 10;
    } else {
      brightnessLevel = 1;
    }
  }


  Serial.println(brightnessLevel);
  display.drawRect(0, 26, 100, 5, SH110X_WHITE);//for bar graph
  display.fillRect(0, 26, brightnessLevel/5, 5, SH110X_WHITE);

  display.setContrast(brightnessLevel);
    display.display();
}


void toggleBacklight() {
  backlightOn = !backlightOn;
  // display.ssd1306_command(SSD1306_DISPLAYONOFF | backlightOn);
}

void setWatchFace() {
  if (currentOption == 2) {
    if (watch_face > 6) {
      watch_face = 0;
    }
    watch_face++;
  }
}

/*
void setWatchFace() {
  // Add code to set wallpaper here
    if (currentOption == 0) {
    if (watch_face > 0) {
      watch_face -= 1;
    }
  } else {
    if (watch_face < 10) {
      watch_face += 1;
    }
    else{
      watch_face = 1;
    }
  }
  //watch_face=
}
*/
void setTimeZone() {
  // Add code to set time zone here
}

void invertScreen() {
  getInverted = !getInverted;
  display.invertDisplay(getInverted);
  //  display.invertDisplay(!display.getInverted());
}

void performOptionAction() {
  switch (currentMenu) {
    case 0:  // Brightness
      adjustBrightness();
      break;

    case 1:  // Backlight On/Off
      toggleBacklight();
      break;

    case 2:  // Set Wallpaper
      setWatchFace();
      break;

    case 3:  // Set Time Zone
      setTimeZone();
      break;

    case 4:  // Invert Screen
      invertScreen();
      break;


    case 5:  // Invert home page
             //  home = true;
             // x = 0;
      break;


      // Add more cases for additional options
    default:
      returnToHomeScreen();
      break;
  }
}

void gotTouch1() {
  home = false;
  // Serial.println("in  touch 1");
  // Serial.println(home);
  touchValue = touchRead(T4);
  // Serial.println(touchValue);
  if (touchValue < TOUCH_THRESHOLD) {
    lastTouchTime = millis();  // Reset the timeout timer
    currentOption = (currentOption + 1) % numOptions;
    showOptionMenu();
    performOptionAction();
    delay(300);  // Debounce delay
  }
}


void gotTouch2() {
  home = false;
  // Serial.println("in  touch 2");
  // Serial.println(home);
  touchValue = touchRead(T5);
  // Serial.println(touchValue);
  if (touchValue < TOUCH_THRESHOLD) {
    lastTouchTime = millis();  // Reset the timeout timer
    currentMenu = (currentMenu + 1) % numMenus;
    currentOption = 0;
    showMainMenu();
    delay(300);  // Debounce delay
  }
}



void touch1() {
  x = 1;
}

void touch2() {
  x = 2;
}
