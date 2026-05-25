#include "U8glib.h"
// for above library go to sketch->manage libraries ->search for "u8glib" by oliver.
// this is for 1.3 inch i2c oled 128X64 display
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
//pins
#define JOY_Y_PIN   A1
#define JOY_SW_PIN   9
#define JOY_CENTER  512
#define JOY_THRESH  150
#define BUZZ_PIN    A0

// X-Wing bitmap 16x16
const uint8_t PROGMEM dioda16[] = {
  0x00,0x00,0x00,0x00,0x1C,0x00,0x3F,0xF0,
  0x3C,0x00,0x3C,0x00,0xFF,0x00,0x7F,0xFF,
  0x7F,0xFF,0xFF,0x00,0x3C,0x00,0x3C,0x00,
  0x1F,0xF0,0x1C,0x00,0x00,0x00,0x00,0x00
};

// Heart bitmap 7x6
const uint8_t PROGMEM heartBmp[] = {
  0x6C,0x80,  // 0110 1100 1
  0xFE,0x80,  // 1111 1110 1
  0xFE,0x80,  // 1111 1110 1
  0x7D,0x00,  // 0111 1101 0
  0x3E,0x00,  // 0011 1110 0
  0x1C,0x00   // 0001 1100 0
};

const uint8_t STAR_X[] = {50,30,60,55,25,100,117,14,24,78,80,107,5,8,70,10,70};
const uint8_t STAR_Y[] = {30,17,18,16,43, 43, 52,49,24,36,57, 11,5,7,12,56,25};
#define NUM_STARS 17

int  metx=0,  mety=0;
int  postoji=0;
int  nep=8;
int  smjer=0;
int  go=0;
int  rx=95,  ry=0;
int  rx2=95, ry2=0;
int  rx3=95, ry3=0;
int  rx4=95, ry4=0;
int  bodovi=0;
int  brzina=3;
int  bkugle=1;
int  promjer=10;
int  zivoti=3;
int  poc=0;
int  ispaljeno=0;
int  nivo=1;
int  centar=95;
int  poz=24;
int  najmanja=600, najveca=1200;

unsigned long pocetno=0, odabrano=0, trenutno=0, nivovrije=0;

int  joyY = 512;
bool fire  = false;
bool lastFire = false;

void resetGame() {
  metx=0; mety=0; postoji=0;
  nep=8;  smjer=0; go=0;
  rx=95;  ry=0;
  rx2=95; ry2=0;
  rx3=95; ry3=0;
  rx4=95; ry4=0;
  bodovi=0; brzina=3; bkugle=1;
  najmanja=600; najveca=1200; promjer=10;
  zivoti=3; poc=0; ispaljeno=0; nivo=1;
  pocetno=0; odabrano=0; trenutno=0; nivovrije=0;
  poz=24;
}

// Draw hearts for lives
void drawHearts(int lives) {
  for (int i = 0; i < lives; i++) {
    u8g.drawBitmapP(i * 9, 0, 1, 6, heartBmp);
  }
}

void drawGame() {
  u8g.setFont(u8g_font_6x10);

  // Stars
  for (uint8_t i = 0; i < NUM_STARS; i++)
    u8g.drawPixel(STAR_X[i], STAR_Y[i]);

  // X-Wing
  u8g.drawBitmapP(4, poz, 2, 16, dioda16);

  // Death Star
  u8g.drawDisc(centar, nep, promjer);
  u8g.drawCircle(centar+2, nep+3, promjer/3);

  // Player bullet
  if (postoji == 1)
    u8g.drawLine(metx, mety, metx+4, mety);

  // Enemy bullets
  if (ispaljeno > 0) u8g.drawCircle(rx,  ry,  2);
  if (ispaljeno > 1) u8g.drawCircle(rx2, ry2, 1);
  if (ispaljeno > 2) u8g.drawCircle(rx3, ry3, 3);
  if (ispaljeno > 3) u8g.drawCircle(rx4, ry4, 2);

  // Hearts (top left)
  drawHearts(zivoti);

  // Score (bottom left)
  char buf[16];
  u8g.drawStr(0, 63, "score:");
  itoa(bodovi, buf, 10);
  u8g.drawStr(38, 63, buf);

  // Level (top right)
  u8g.drawStr(98, 8, "L:");
  itoa(nivo, buf, 10);
  u8g.drawStr(112, 8, buf);
}

void drawSplash() {
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(20, 16, "DEATH STAR");
  u8g.drawStr(30, 28, "vs X-Wing");
  u8g.drawStr(8,  44, "Joystick = move");
  u8g.drawStr(8,  56, "SW btn  = fire");
}

void drawGameOver() {
  char buf[12];
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(10, 12, "GAME  OVER!");
  u8g.drawStr(4,  26, "score:");
  itoa(bodovi, buf, 10);
  u8g.drawStr(42, 26, buf);
  u8g.drawStr(4,  38, "level:");
  itoa(nivo, buf, 10);
  u8g.drawStr(42, 38, buf);
  u8g.drawStr(4,  52, "SW btn = retry");
}

void beepNote(int note, int dur) {
  tone(BUZZ_PIN, note, dur);
  delay(dur);
  noTone(BUZZ_PIN);
  delay(50);
}

void playIntro() {
  beepNote(440, 500);
  beepNote(440, 500);
  beepNote(440, 500);
  beepNote(349, 350);
  beepNote(523, 150);
  beepNote(440, 500);
  beepNote(349, 350);
  beepNote(523, 150);
  beepNote(440, 650);
}

void setup() {
  pinMode(JOY_SW_PIN, INPUT_PULLUP);
  pinMode(BUZZ_PIN,   OUTPUT);

  u8g.firstPage();
  do { drawSplash(); } while (u8g.nextPage());

  playIntro();
  delay(500);
}

void loop() {
  joyY = analogRead(JOY_Y_PIN);
  bool rawFire = (digitalRead(JOY_SW_PIN) == LOW);
  fire = rawFire && !lastFire;
  lastFire = rawFire;

  if (go == 0) {

    // Movement
    if (joyY < JOY_CENTER - JOY_THRESH && poz > 2)   poz -= 2;
    if (joyY > JOY_CENTER + JOY_THRESH && poz < 46)  poz += 2;

    // Fire
    if (fire && postoji == 0) {
      postoji = 1;
      metx = 20;
      mety = poz + 8;
      tone(BUZZ_PIN, 1200, 20);
    }

    // Level up
    trenutno = millis();
    if ((trenutno - nivovrije) > 50000UL) {
      nivovrije = trenutno;
      nivo++;
      brzina++;
      if (nivo % 2 == 0) { bkugle++; if (promjer > 4) promjer--; }
      if (najmanja > 250) najmanja -= 50;
      if (najveca  > 300) najveca  -= 50;
    }

    // Enemy fire timer
    if (poc == 0) {
      pocetno  = millis();
      odabrano = random((int)najmanja, (int)najveca);
      poc = 1;
    }
    if ((pocetno + odabrano) < trenutno) {
      poc = 0;
      ispaljeno++;
      if (ispaljeno > 4) ispaljeno = 4;
      switch (ispaljeno) {
        case 1: rx =centar; ry =nep; break;
        case 2: rx2=centar; ry2=nep; break;
        case 3: rx3=centar; ry3=nep; break;
        case 4: rx4=centar; ry4=nep; break;
      }
    }

    // Move player bullet
    if (postoji == 1) metx += 8;
    if (metx > 128)   postoji = 0;

    // Move enemy bullets left
    if (ispaljeno > 0) rx  -= brzina;
    if (ispaljeno > 1) rx2 -= brzina;
    if (ispaljeno > 2) rx3 -= brzina;
    if (ispaljeno > 3) rx4 -= brzina;

    // Death Star bounce
    if (smjer == 0) nep += bkugle; else nep -= bkugle;
    if (nep >= (64 - promjer)) smjer = 1;
    if (nep <= promjer)        smjer = 0;

    // ── Hit: player bullet → Death Star ──────────────────────────────────
    if (postoji && mety >= nep - promjer && mety <= nep + promjer &&
        metx > (centar - promjer) && metx < (centar + promjer)) {
      tone(BUZZ_PIN, 500, 30);
      bodovi++;
      postoji = 0;
      metx = -20;
    }

    // ── Hit: enemy bullets → X-Wing ──────────────────────────────────────
    // X-Wing occupies x=4..20, y=poz..poz+16, centre poz+8
    int xw_left  = 4;
    int xw_right = 20;
    int xw_top   = poz;
    int xw_bot   = poz + 16;

    // bullet 1 (radius 2)
    if (ispaljeno > 0 &&
        rx + 2 >= xw_left && rx - 2 <= xw_right &&
        ry + 2 >= xw_top  && ry - 2 <= xw_bot) {
      rx = -50; ry = -50;
      tone(BUZZ_PIN, 150, 150);
      zivoti--;
    }

    // bullet 2 (radius 1)
    if (ispaljeno > 1 &&
        rx2 + 1 >= xw_left && rx2 - 1 <= xw_right &&
        ry2 + 1 >= xw_top  && ry2 - 1 <= xw_bot) {
      rx2 = -50; ry2 = -50;
      tone(BUZZ_PIN, 150, 150);
      zivoti--;
    }

    // bullet 3 (radius 3)
    if (ispaljeno > 2 &&
        rx3 + 3 >= xw_left && rx3 - 3 <= xw_right &&
        ry3 + 3 >= xw_top  && ry3 - 3 <= xw_bot) {
      rx3 = -50; ry3 = -50;
      tone(BUZZ_PIN, 150, 150);
      zivoti--;
    }

    // bullet 4 (radius 2)
    if (ispaljeno > 3 &&
        rx4 + 2 >= xw_left && rx4 - 2 <= xw_right &&
        ry4 + 2 >= xw_top  && ry4 - 2 <= xw_bot) {
      rx4 = -50; ry4 = -50;
      ispaljeno = 0;
      tone(BUZZ_PIN, 150, 150);
      zivoti--;
    }

    // Reset bullet 4 off-screen
    if (rx4 < 0) { ispaljeno = 0; rx4 = 200; }

    if (zivoti <= 0) { zivoti = 0; go = 1; }

    // Draw
    u8g.firstPage();
    do { drawGame(); } while (u8g.nextPage());
  }

  // ── Game Over ─────────────────────────────────────────────────────────────
  if (go == 1) {
    tone(BUZZ_PIN, 200, 300); delay(300);
    tone(BUZZ_PIN, 250, 200); delay(200);
    tone(BUZZ_PIN, 300, 300); delay(300);

    // Wait for button release then show screen
    while (digitalRead(JOY_SW_PIN) == LOW) {}

    bool shown = false;
    while (true) {
      if (!shown) {
        u8g.firstPage();
        do { drawGameOver(); } while (u8g.nextPage());
        shown = true;
      }
      bool r = (digitalRead(JOY_SW_PIN) == LOW);
      if (r) {
        tone(BUZZ_PIN, 370, 200); delay(300);
        resetGame();
        return;
      }
    }
  }
}
