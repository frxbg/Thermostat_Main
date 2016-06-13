/* ===================================================================== *
 *                                                                       *
   DISPLAY SYSTEM
 *                                                                       *
   =====================================================================
   every "disp menu function" needs three functions
   - void LCDML_DISP_setup(func_name)
   - void LCDML_DISP_loop(func_name)
   - void LCDML_DISP_loop_end(func_name)

   EXAMPLE CODE:
    void LCDML_DISP_setup(..menu_func_name..)
    {
      // setup
      // is called only if it is started

      // starts a trigger event for the loop function every 100 millisecounds
      LCDML_DISP_triggerMenu(100);
    }

    void LCDML_DISP_loop(..menu_func_name..)
    {
      // loop
      // is called when it is triggert
      // - with LCDML_DISP_triggerMenu( millisecounds )
      // - with every button status change

      // check if any button is presed (enter, up, down, left, right)
      if(LCDML_BUTTON_checkAny()) {
        LCDML_DISP_funcend();
      }
    }

    void LCDML_DISP_loop_end(..menu_func_name..)
    {
      // loop end
      // this functions is ever called when a DISP function is quit
      // you can here reset some global vars or do nothing
    }
   =====================================================================
*/

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_initscreen)
// *********************************************************************
{
  // setup function

}

void LCDML_DISP_loop(LCDML_FUNC_initscreen)
{

  lcd.setCursor(0, 0);
  lcd.print("Act: ");
  lcd.print(Input);
  lcd.setCursor(12, 0);
  lcd.print("Pos.");
  lcd.setCursor(0, 1);
  lcd.print("Set: ");
  lcd.print(Setpoint);
  lcd.setCursor(12, 1);
  lcd.print(Position);
  lcd.println("%    ");

  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
    // LCDML_DISP_funcend calls the loop_end function
    LCDML_DISP_funcend();
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_initscreen)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}



// *********************************************************************
double g_button_value1 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_Set)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Setpoint:       "));
  // Reset Button Value
  g_button_value1 = Setpoint;
  lcd.setCursor(10, 1); // set cursor
  lcd.print(g_button_value1); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_Set)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value1 = g_button_value1 + 0.1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value1); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value1 = g_button_value1 - 0.1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value1); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      Setpoint = g_button_value1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_Set)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}
int g_button_value2 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_tuneP)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Tune P:         "));
  // Reset Button Value
  g_button_value2 = kp;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value2); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_tuneP)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value2++;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value2); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value2--;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value2); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      kp = g_button_value2;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_tuneP)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}
int g_button_value3 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_tuneI)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Tune I:         "));
  // Reset Button Value
  g_button_value3 = ki;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value3); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_tuneI)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value3++;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value3); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value3--;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value3); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      ki = g_button_value3;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();

    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_tuneI)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

int g_button_value4 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_tuneD)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Tune D:         "));
  // Reset Button Value
  g_button_value4 = kd;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value4); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_tuneD)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value4++;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value4); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value4--;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value4); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      kd = g_button_value4;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value4 >= 53) {
  // end function for callback
  //   LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_tuneD)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
int g_button_value5 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_SampleTime)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("STime:          "));
  // Reset Button Value
  g_button_value5 = SampleTime;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value5); // print change content

}

void LCDML_DISP_loop(LCDML_FUNC_SampleTime)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value5 = g_button_value5 + 100;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value5); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value5 = g_button_value5 - 100;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value5); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      SampleTime = g_button_value5;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  //  if (g_button_value1 >= 53) {
  // end function for callback
  //    LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_SampleTime)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}
// *********************************************************************
uint8_t g_button_value6 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_outMin)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("outMin:         "));
  // Reset Button Value
  g_button_value6 = outMin;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value6); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_outMin)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value6++;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value6); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value6--;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value6); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      outMin = g_button_value6;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }

  // check if button count is three
  // if (g_button_value6 >= 53) {
  // end function for callback
  //   LCDML_DISP_funcend();
  //  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_outMin)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
byte buttonpress; // button value counter (global variable)
byte change3 = 0;
void LCDML_DISP_setup(LCDML_FUNC_Calibrate)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Enable:         "));
  buttonpress = 1;
  lcd.setCursor(11, 1); // set cursor
  lcd.print("Yes "); // print change content
  // Reset Button Value
}

void LCDML_DISP_loop(LCDML_FUNC_Calibrate)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (buttonpress == 1 && change3 == 0) {
        change3 = 1;
        buttonpress = 0;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("No "); // print change content
      }
      else if (buttonpress == 0 && change3 == 0) {
        change3 = 1;
        buttonpress = 1;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("Yes"); // print change content
      }
      change3 = 0;
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (buttonpress == 1 && change3 == 0) {
        change3 = 1;
        buttonpress = 0;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("No "); // print change content
      }
      else if (buttonpress == 0 && change3 == 0) {
        change3 = 1;
        buttonpress = 1;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("Yes"); // print change content
      }
      change3 = 0;
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      if (buttonpress == 1) {
        delay(1000);
        lcd.setCursor(0, 0);
        lcd.print(F("Calibrating     "));
        lcd.setCursor(0, 1);
        lcd.print(F("Please wait...  "));
        digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
        delay(2000);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(1000);
        Serial.println("mA");
        time = millis() + 60000;
        while (millis() < time) {
          ADC1 = analogRead(A5) / 0.204;
          ADC2 = analogRead(A4) / 0.204;
          /*Serial.print(ADC2);
            Serial.println("mV");
            Serial.print(ADC1);
            Serial.println("mV");*/
          current = (ADC2 - ADC1) / 150;
          Serial.print(current);
          Serial.println("mA");
          if (current <= -20) {
            digitalWrite(2, LOW);
            break;
          }
        }
        Up = millis();


        digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
        delay(1000);
        ADC1 = analogRead(A5) / 0.204;
        time = millis() + 60000;
        while (millis() < time) {
          ADC1 = analogRead(A5) / 0.204;
          ADC2 = analogRead(A4) / 0.204;
          /*Serial.print(ADC2);
            Serial.println("mV");
            Serial.print(ADC1);
            Serial.println("mV");*/
          current = (ADC2 - ADC1) / 150;
          Serial.print(current);
          Serial.println("mA");
          if (current >= 20) {
            digitalWrite(3, LOW);
            break;
          }
        }
        Down = millis();
        CaliTime = (Down - Up) - 1000;
        if (CaliTime != EEPROM_readDouble(CaliTimeAddress))
        {
          EEPROM_writeDouble(CaliTimeAddress, CaliTime);
        }
        lcd.setCursor(0, 1);
        lcd.print("Complete        ");
        Serial.print(CaliTime);
        Serial.println(" msec.");
        Position = 0;
        delay(3000);
        LCDML_DISP_funcend();
      }
      if (buttonpress == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Loading settings");
        lcd.setCursor(0, 1);
        lcd.print("Please wait...  ");
        delay(2000);
        lcd.setCursor(0, 0);
        lcd.print("    CaliTime    ");
        lcd.setCursor(0, 1);
        lcd.print(CaliTime);
        lcd.println("ms.             ");
        delay(2000);
        CaliTime = EEPROM_readDouble(CaliTimeAddress);
      }
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_Calibrate)
{

  CaliTime = EEPROM_readDouble(CaliTimeAddress);
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

double g_button_value7 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_P1)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("P1:             "));
  // Reset Button Value
  g_button_value7 = P1;
  lcd.setCursor(9, 1); // set cursor
  lcd.print(g_button_value7); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_P1)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value7 = g_button_value7 + 0.1;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value7); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value7 = g_button_value7 - 0.1;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print(g_button_value7); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      P1 = g_button_value7;

      // update lcd content
      lcd.setCursor(9, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_P1)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

byte g_button_value8 = 0; // button value counter (global variable)
byte change = 0;
void LCDML_DISP_setup(LCDML_FUNC_WinterProtectEnable)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Enable:      "));
  // Reset Button Value
  g_button_value8 = WinterProtectEnable;
  lcd.setCursor(11, 1); // set cursor

  if (g_button_value8 == 1) {
    lcd.print("Yes"); // print change content
  }
  if (g_button_value8 == 0) {
    lcd.print("No "); // print change content
  }
}

void LCDML_DISP_loop(LCDML_FUNC_WinterProtectEnable)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value8 == 1 && change == 0) {
        change = 1;
        g_button_value8 = 0;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("No "); // print change content
      }
      else if (g_button_value8 == 0 && change == 0) {
        change = 1;
        g_button_value8 = 1;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("Yes"); // print change content
      }
      change = 0;
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value8 == 1 && change == 0) {
        change = 1;
        g_button_value8 = 0;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("No "); // print change content
      }
      else if (g_button_value8 == 0 && change == 0) {
        change = 1;
        g_button_value8 = 1;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("Yes"); // print change content
      }
      change = 0;
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      WinterProtectEnable = g_button_value8;

      // update lcd content
      lcd.setCursor(0, 1); // set cursor
      lcd.print("     Saved      "); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_WinterProtectEnable)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

byte g_button_value9 = 0; // button value counter (global variable)
byte change1 = 0;
void LCDML_DISP_setup(LCDML_FUNC_SwitchExt)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Enable:         "));
  // Reset Button Value
  g_button_value9 = SwitchExt;
  lcd.setCursor(11, 1); // set cursor

  if (SwitchExt == 1) {
    lcd.print("Yes"); // print change content
  }
  if (SwitchExt == 0) {
    lcd.print("No "); // print change content
  }
}

void LCDML_DISP_loop(LCDML_FUNC_SwitchExt)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value9 == 1 && change1 == 0) {
        change1 = 1;
        g_button_value9 = 0;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("No "); // print change content
      }
      else if (g_button_value9 == 0 && change1 == 0) {
        change1 = 1;
        g_button_value9 = 1;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("Yes"); // print change content
      }
      change1 = 0;
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value9 == 1 && change1 == 0) {
        change1 = 1;
        g_button_value9 = 0;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("No "); // print change content
      }
      else if (g_button_value9 == 0 && change1 == 0) {
        change1 = 1;
        g_button_value9 = 1;
        lcd.setCursor(11, 1); // set cursor
        lcd.print("Yes"); // print change content
      }
      change1 = 0;
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      SwitchExt = g_button_value9;

      // update lcd content
      lcd.setCursor(0, 1); // set cursor
      lcd.print("     Saved      "); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_SwitchExt)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

double g_button_value10 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_minOutTemp)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Min temp:       "));
  // Reset Button Value
  g_button_value10 = minOutTemp;
  lcd.setCursor(10, 1); // set cursor
  lcd.print(g_button_value10); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_minOutTemp)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value10 = g_button_value10 + 1;

      if (g_button_value10 >= maxOutTemp) {
        g_button_value10 = maxOutTemp - 1;
      }

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value10); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value10 = g_button_value10 - 1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value10); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      minOutTemp = g_button_value10;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_minOutTemp)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

double g_button_value11 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_maxOutTemp)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Min temp:       "));
  // Reset Button Value
  g_button_value11 = maxOutTemp;
  lcd.setCursor(10, 1); // set cursor
  lcd.print(g_button_value11); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_maxOutTemp)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value11 = g_button_value11 + 1;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value11); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value11 = g_button_value11 - 1;

      if (g_button_value11 <= minOutTemp) {
        g_button_value11 = minOutTemp + 1;
      }

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print(g_button_value11); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      maxOutTemp = g_button_value11;

      // update lcd content
      lcd.setCursor(10, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_maxOutTemp)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

byte g_button_value12 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_WinterOutput)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("Min output:     "));
  // Reset Button Value
  g_button_value12 = minWinterOut;
  lcd.setCursor(12, 1); // set cursor
  lcd.print(g_button_value12); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_WinterOutput)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value12 = g_button_value12 + 1;

      // update lcd content
      lcd.setCursor(12, 1); // set cursor
      lcd.print(g_button_value12); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value12 = g_button_value12 - 1;

      // update lcd content
      lcd.setCursor(12, 1); // set cursor
      lcd.print(g_button_value12); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      minWinterOut = g_button_value12;

      // update lcd content
      lcd.setCursor(12, 1); // set cursor
      lcd.print("Saved"); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_WinterOutput)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}


// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_OutTemp)
// *********************************************************************
{
  // setup function

}

void LCDML_DISP_loop(LCDML_FUNC_OutTemp)
{

  GetOutsideTemp();
  lcd.setCursor(0, 0);
  lcd.print(" Outside temp. ");
  lcd.setCursor(4, 1);
  lcd.print(OutTemp);

  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
    // LCDML_DISP_funcend calls the loop_end function
    LCDML_DISP_funcend();
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_OutTemp)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

double g_button_value13 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_SwTime)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("SwTime:         "));
  // Reset Button Value
  g_button_value13 = SwTime;
  lcd.setCursor(8, 1); // set cursor
  lcd.print(g_button_value13); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_SwTime)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value13 = g_button_value13 + 1000;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value13); // print change content
      lcd.println("ms.       "); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value13 = g_button_value13 - 1000;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print(g_button_value13); // print change content
      lcd.println("ms.       "); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      SwTime = g_button_value13;

      // update lcd content
      lcd.setCursor(8, 1); // set cursor
      lcd.print("Saved      "); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_SwTime)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

double g_button_value14 = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_FrostTemp)
// *********************************************************************
{
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press up or down"));
  lcd.setCursor(0, 1);
  lcd.print(F("FrostTemp:         "));
  // Reset Button Value
  g_button_value14 = FrostTemp;
  lcd.setCursor(11, 1); // set cursor
  lcd.print(g_button_value14); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_FrostTemp)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value14 = g_button_value14 + 1;

      // update lcd content
      lcd.setCursor(11, 1); // set cursor
      lcd.print(g_button_value14); // print change content
    }

    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      g_button_value14 = g_button_value14 - 1;

      if (g_button_value14 <= 0) {
        lcd.setCursor(0, 1);
        lcd.print("     WARNING    ");
        delay(3000);
        lcd.setCursor(0, 1);
        lcd.print(F("FrostTemp:         "));
        lcd.setCursor(11, 1); // set cursor
        lcd.print(g_button_value14); // print change content
      }

      // update lcd content
      lcd.setCursor(11, 1); // set cursor
      lcd.print(g_button_value14); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      FrostTemp = g_button_value14;

      // update lcd content
      lcd.setCursor(11, 1); // set cursor
      lcd.print("Saved      "); // print change content
      delay(1000);
      LCDML_DISP_funcend();
    }
  }
}
void LCDML_DISP_loop_end(LCDML_FUNC_FrostTemp)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

