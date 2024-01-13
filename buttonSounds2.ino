#define mode2

#include <MD_YX5300.h>
#include "SoftwareSerial.h"
const uint8_t PLAY_FOLDER = 1; // tracks are all placed in this folder

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial MP3Stream(PIN_MP3_RX, PIN_MP3_TX);
#define Console Serial // command processor input/output stream
// Create t
// Define global variables
MD_YX5300 mp3(MP3Stream);

bool playerPause = true; // true if player is currently paused

int button1 = 9; // shooting sound
int button3 = 10;
int button4 = 11;
int button5 = 12;

int busyPin = 4;
int
    playing1,
    playing2,
    playing3,
    playing4,
    playing5 = 0;

int button2 = 9; // reset button plays reload sound
#define mode
#define LOOP_STATE_STOPPED 0
#define LOOP_STATE_STARTED 1
int loopState = LOOP_STATE_STOPPED;
int count = 0;
bool counter = false;

/*******************
    your setup code
 *******************/
void setup()
{
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini

  // resetbutton.setDebounceTime(50); // set debounce time to 50 milliseconds
  // countbutton.setDebounceTime(50); // set debounce time to 50 milliseconds
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(busyPin, INPUT);

  // initialize global libraries
  MP3Stream.begin(MD_YX5300::SERIAL_BPS);
  mp3.begin();
  mp3.setSynchronous(true);
  mp3.playFolderRepeat(PLAY_FOLDER);
  mp3.volume(mp3.volumeMax());
}
void loop()
{
  mp3.check(); // run the mp3 receiver
  while (digitalRead(button2) == LOW)
  {
    if (playing2 == 0)
    {
      Serial.println("button 2 pressed ");
      if (digitalRead(busyPin) == HIGH)
      { // not playing play track

        mp3.playTrack(2);
      }
      playing2 = 1;
    }
  }
  if (digitalRead(button2) == HIGH)
  {
    if (playing2 == 1)
    {
      // player.stop();
      mp3.playStop();
      playing2 = 0;
    }
  }
  while (digitalRead(button1) == LOW)
  {
    if (playing1 == 0)
    {
      Serial.println("button 1 pressed ");
      if (digitalRead(busyPin) == HIGH)
      {                   // not playing play track
        mp3.playTrack(1); // shooting sound
      }
      playing1 = 1;
    }
  }
  if (digitalRead(button1) == HIGH)
  {
    if (playing1 == 1)
    {
      mp3.playStop();
      playing1 = 0;
    }
  }
  while (digitalRead(button3) == LOW)
  {
    if (playing3 == 0)
    {
      Serial.println("button 3 pressed ");
      if (digitalRead(busyPin) == HIGH)
      {                   // not playing play track
        mp3.playTrack(3); // shooting sound
      }
      playing3 = 1;
    }
  }
  if (digitalRead(button3) == HIGH)
  {
    if (playing3 == 1)
    {
      mp3.playStop();
      playing3 = 0;
    }
  }
  while (digitalRead(button4) == LOW)
  {
    if (playing4 == 0)
    {
      Serial.println("button 4 pressed ");
      if (digitalRead(busyPin) == HIGH)
      {                   // not playing play track
        mp3.playTrack(4); // shooting sound
      }
      playing4 = 1;
    }
  }
  if (digitalRead(button4) == HIGH)
  {
    if (playing4 == 1)
    {
      mp3.playStop();
      playing4 = 0;
    }
  }
  while (digitalRead(button5) == LOW)
  {
    if (playing5 == 0)
    {
      Serial.println("button 5 pressed ");
      if (digitalRead(busyPin) == HIGH)
      {                   // not playing play track
        mp3.playTrack(5); // shooting sound
      }
      playing5 = 1;
    }
  }
  if (digitalRead(button5) == HIGH)
  {
    if (playing5 == 1)
    {
      mp3.playStop();
      // mp3.playSpecific(1,1);
      playing5 = 0;
    }
  }
}

void playTrack(uint8_t track, int button)
{
  mp3.playStop();
  delay(200);
  int file = mp3.queryFolderFiles(1);
  Serial.print("track : ");
  Serial.println(track);
  Serial.print("file : ");
  Serial.println(file);
  while (file != track)
  {
    mp3.playTrack(track);
    // delay(200);
    file = mp3.queryFile();
    if (digitalRead(button) == HIGH)
      file = file + 1;
    break;
  }
}
