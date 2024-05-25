void text(String s, int size, int cX, int cY, bool clear, bool inverse) {
  if (clear) {
    display.clearBuffer(); // Clear the buffer
  }
  
  // Set text color based on inverse flag
  if (inverse) {
    display.setColorIndex(0); // Set text color to black
  } else {
    display.setColorIndex(1); // Set text color to white
  }

  display.setFont(u8g2_font_ncenB10_tr); // Set font size
  display.setCursor(cX, cY); // Set text cursor position
  display.print(s); // Print the text
  display.sendBuffer(); // Send the buffer to the display
}

// Menu Screen
void menu() {
  text("Download", 2, 0, 20, true, selection);
  text("Ask Help", 2, 0, 40, false, selection);
}

// Downloads screen
void downloadsScreen() {
  text(textFile, 1, 0, scrollyDir, true, false);
  delay(250);
}

// Help screen
void HelpScreen() {
  text(fetchStringData(), 2, 0, 20, true, false);
  text(sentText, 1, 128 - (sentText.length() * 6), 40, false, false);
  text(dictionary[wordCount], 2, 0, 40, false, true);
  delay(250);
}

// This function tracks which screen is selected
void selectedScreen() {
  switch (currentScreen) {
    case MENU:
      menu();
      break;
    case DOWNLOADS:
      downloadsScreen();
      break;
    case ASK_HELP:
      HelpScreen();
      break;
    default:
      text("Something went wrong!", 1, 0, 20, true, false);
  }
}
