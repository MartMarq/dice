#include "Watchy_dice.h"

#define DARKMODE false
int X[16] = { 0, 50, 100, 150, 0, 50,100, 150, 0, 50, 100, 150, 0, 50, 100, 150 };
int Y[16] = { 0, 0, 0, 0, 50, 50, 50, 50, 100, 100, 100, 100, 150, 150, 150, 150 };


void Watchydice::drawWatchFace(){
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
   // display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawTime();
    }


void Watchydice::drawTime(){

    const uint8_t* wurfx[] = {xnull, xeins, xzwei, xdrei, xvier, xfunf, xsechs, xsieben, xacht, xneun};
    int anzeig = 0;
    int stundeA = currentTime.Hour;
    int minuteA = currentTime.Minute;
    int tagA = currentTime.Day;
    int monatA = currentTime.Month;
    int batLev = min <int> (100 - ((4.15 - getBatteryVoltage()) * 100), 99);
    uint32_t Schritt = sensor.getCounter();

    // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();   
          }
          
    //time adjustment start
    //if you don't need a time adjustment, just delete all lines between time adjustment start and end
    //my watchy runs too fast (15 seconds and 500 ms a day), this code set back time each day by 15 seconds and 500 ms
    
	if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15500);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);     
         }

    // time adjustment end
    
    for (int n = 0; n < 16; n++) {

       if (n == 0) { 
            anzeig = stundeA / 10;
        }

       if (n == 1) {
           anzeig = stundeA - anzeig *10;
       }

        if (n == 2) {
            anzeig = minuteA / 10;
        }

        if (n == 3) {
            anzeig = minuteA - anzeig * 10;
        }

        if (n == 4) {
            anzeig = tagA / 10;
        }

        if (n == 5) {
            anzeig = tagA - anzeig * 10;
        }

        if (n == 6) {
            anzeig = monatA / 10;
        }

        if (n == 7) {
            anzeig = monatA - anzeig * 10;
        }

        if (n == 8) {
            anzeig = 0;
        }

        if (n == 9) {
            anzeig = batLev / 10;
        }

        if (n == 10) {
            anzeig = batLev - anzeig * 10;
        }

        if (n == 11) {
            anzeig = 0;
        }

        if (n == 12) {
            anzeig = Schritt / 10000;
            Schritt = Schritt - anzeig * 10000;
        }

        if (n == 13) {
            anzeig = Schritt / 1000;
            Schritt = Schritt - anzeig * 1000;
        }
        if (n == 14) {
            anzeig = Schritt / 100;
            Schritt = Schritt - anzeig * 100;
        }
        if (n == 15) {
            anzeig = Schritt / 10;
            
        }

        display.drawBitmap(X[n], Y[n], wurfx[anzeig], 50, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
}
