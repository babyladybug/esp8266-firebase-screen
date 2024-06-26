//single tap for selection
void singleTapUp()
{
  if(selection)
      updateScreen = true;
    selection = false;
}

void singleTapDown()
{
  if(!selection)
       updateScreen = true;
     selection = true;
}

//multitap for going inside the menu and also to return back to menu
void doubleTapUp()
{
  if(currentScreen == MENU)
  {
    if(textFile == "")
       {
      if(wifiConnection())
      {
      fetchTextFile();
      writeDownloads();
      }
    }
    WiFi.disconnect();
    WiFi.softAPdisconnect(true); 
    currentScreen = DOWNLOADS;
    updateScreen = true;
  }
  else
  {
    currentScreen = MENU;
    updateScreen = true;  
  }
}

void doubleTapDown()
{
  if(currentScreen == MENU)
  {
    currentScreen = ASK_HELP;
    if(wifiConnection())
    {
      updateScreen = true;
    }
    else
    {
      text("NO INTERNET",1,0,0,true,true);   
      delay(1000);
      currentScreen = MENU;
      updateScreen = true; 
    }
  }
  else
  {
    WiFi.disconnect();
    WiFi.softAPdisconnect(true); 
    currentScreen = MENU;
    updateScreen = true; 
  }
}

//Long press for scrolling +y and -Y direction and also to cycle through text message
void longPressUp()
{
    if(currentScreen == ASK_HELP)
    {
      updateScreen = true; 
      if(wordCount < 10)
      {
        wordCount++;
        return;
      }
      wordCount = 0;  
    }
    else if(currentScreen == DOWNLOADS)
    {
      updateScreen = true; 
      scrollyDir += 6;  
    }
}

void longPressDown()
{
     if(currentScreen == ASK_HELP)
    {
      updateScreen = true; 
      if(wordCount > 0)
      {
        wordCount--;
        return;
      }
      wordCount = 9;
    }
    else if(currentScreen == DOWNLOADS)
    {
      updateScreen = true; 
      scrollyDir -= 6;  
    }
}

//To send the selected text to firebase in the chat

void longPressStopUp()
{
   if(currentScreen == ASK_HELP)
    {
      sentText = dictionary[wordCount];
      insertData(sentText);
      updateScreen = true;  
    }
}

void longPressStopDown()
{
   if(currentScreen == ASK_HELP)
    {
      sentText = dictionary[wordCount];
      insertData(sentText);
      updateScreen = true; 
    }
}
