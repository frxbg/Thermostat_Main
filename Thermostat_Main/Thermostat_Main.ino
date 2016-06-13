// ============================================================
// Термостат за регулиране на моторна задвижка за термоглава по PID закон
//
// ============================================================

/*working variables*/
#include <PID_v1.h>
#include <EEPROM.h>
#include <math.h>

// ************************************************
// PID Variables and constants
// ************************************************

double Setpoint;
double Input;
double Output;

//volatile long onTime = 0;

// pid tuning parameters
double kp;
double ki;
double kd;
double SampleTime;
double outMin;
double P1;
double P2;
int Mode = 1;


// EEPROM addresses for persisted data
const int SpAddress = 0;
const int KpAddress = 8;
const int KiAddress = 16;
const int KdAddress = 24;
const int STAddress = 32;
const int MinAddress = 64;
const int P1Address = 80;
const int WinterProtectEnableAddress = 96;
const int SwitchExtAddress = 112;
const int minOutTempAddress = 128;
const int maxOutTempAddress = 142;
const int minWinterOutAddress = 164;
const int SwTimeAddress = 186;
const int FrostTempAddress = 200;
const int CaliTimeAddress = 256;


//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

#define _LCDML_DISP_cfg_initscreen                 1
#define _LCDML_DISP_cfg_initscreen_time            10000

unsigned long time;
unsigned long time1;
unsigned long Up;
unsigned long Down;
unsigned long CaliTime;
unsigned long Open;
unsigned long Close;
unsigned long TimeToCali;
unsigned long OpeningTime;
unsigned long ClosingTime;

int ADC1;
int ADC2;
int current;
int Position;
int NewPosSET;
int MovingOpen;
int MovingClose;
int calibrating;
double minOutTemp;
double maxOutTemp;
double OutTemp;
double SwTime;
double FrostTemp;
byte minWinterOut;
byte WinterProtectEnable;
byte SwitchExt;
#define key 10


// include libs
#include <LiquidCrystal.h>
#include <LCDMenuLib.h>

// lib config
#define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
#define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
#define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol 

// *********************************************************************
// LCDML TYPE SELECT
// *********************************************************************
// settings for lcd
#define _LCDML_DISP_cols             16
#define _LCDML_DISP_rows             2

// lcd object
// liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const uint8_t scroll_bar[5][8] = {
  {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
  {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
  {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
  {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
  {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
};

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
// create menu
// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt    19

// LCDML_root        => layer 0
// LCDML_root_X      => layer 1
// LCDML_root_X_X    => layer 2
// LCDML_root_X_X_X  => layer 3
// LCDML_root_... 	 => layer ...

// LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
LCDML_DISP_init(_LCDML_DISP_cnt);
LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Init screen"        , LCDML_FUNC_initscreen);
LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "ControlSettings"    , LCDML_FUNC);
LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root_2      , 1  , "Setpoint"           , LCDML_FUNC_Set);
LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_2      , 2  , "Tune P"             , LCDML_FUNC_tuneP);
LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_2      , 3  , "Tune I"             , LCDML_FUNC_tuneI);
LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root_2      , 4  , "Tune D"             , LCDML_FUNC_tuneD);
LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root_2      , 5  , "SampleTime"         , LCDML_FUNC_SampleTime);
LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_2      , 6  , "Minimum output"     , LCDML_FUNC_outMin);
LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_2      , 7  , "Probe 1 adjust"     , LCDML_FUNC_P1);
LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root        , 5  , "Calibrate"          , LCDML_FUNC_Calibrate);
LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root        , 3  , "Input switch"       , LCDML_FUNC);
LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_3      , 1  , "Switch enable"      , LCDML_FUNC_SwitchExt);
LCDML_DISP_add      (18 , _LCDML_G1  , LCDML_root_3      , 2  , "Switch time "       , LCDML_FUNC_SwTime);
LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root        , 4  , "Winter protect"     , LCDML_FUNC);
LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root_4      , 1  , "Protect enable"     , LCDML_FUNC_WinterProtectEnable);
LCDML_DISP_add      (14 , _LCDML_G1  , LCDML_root_4      , 2  , "Min. out temp"      , LCDML_FUNC_minOutTemp);
LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_4      , 3  , "Max. out temp"      , LCDML_FUNC_maxOutTemp);
LCDML_DISP_add      (16 , _LCDML_G1  , LCDML_root_4      , 4  , "Winter out min. "   , LCDML_FUNC_WinterOutput);
LCDML_DISP_add      (17 , _LCDML_G1  , LCDML_root_4      , 5  , "Outside temp.   "   , LCDML_FUNC_OutTemp);
LCDML_DISP_add      (19 , _LCDML_G1  , LCDML_root        , 6  , "Frost protect"      , LCDML_FUNC_FrostTemp);



LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// *********************************************************************
// LCDML BACKEND (core of the menu, do not change here anything yet)
// *********************************************************************
// define backend function
#define _LCDML_BACK_cnt    1  // last backend function id

LCDML_BACK_init(_LCDML_BACK_cnt);
LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
LCDML_BACK_create();


// *********************************************************************
// SETUP
// *********************************************************************
void setup()
{
  // Set VREF to Vcc
  ADMUX |= (0 << REFS1) | (1 << REFS0);

  pinMode(11, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(key, INPUT);
  // serial init; only be needed if serial control is used
  while (!Serial);                   // wait until serial ready
  Serial.begin(9600);                // start serial
  Serial.println(F(_LCDML_VERSION)); // only for examples

  // LCD Begin
  lcd.begin(_LCDML_DISP_cols, _LCDML_DISP_rows);
  // set special chars for scrollbar
  lcd.createChar(0, (uint8_t*)scroll_bar[0]);
  lcd.createChar(1, (uint8_t*)scroll_bar[1]);
  lcd.createChar(2, (uint8_t*)scroll_bar[2]);
  lcd.createChar(3, (uint8_t*)scroll_bar[3]);
  lcd.createChar(4, (uint8_t*)scroll_bar[4]);

  // Enable all items with _LCDML_G1
  LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1

  // LCDMenu Setup
  LCDML_setup(_LCDML_BACK_cnt);

  LoadParameters();

  myPID.SetTunings(kp, ki, kd);

  LCDML_DISP_jumpToFunc(LCDML_FUNC_Calibrate);

}

// *********************************************************************
// LOOP
// *********************************************************************
void loop()
{
  GetTemp();
  if (Input <= FrostTemp - 30000) {
    digitalWrite(11, HIGH);
    myPID.SetMode(MANUAL);
    Output = 100;
    lcd.setCursor(0, 0);
    lcd.print(F("Frost  protection"));
    lcd.setCursor(0, 1);
    lcd.print(F("   PLEASE WAIT..."));
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    time = millis() + 630000;
    while (millis() <= time) {
      int RawADC;
      RawADC = analogRead(3);
      double Temp;
      Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
      Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
      Temp = Temp - 273.15;
      Input = Temp + (P1);

      if (Input >= 7 && (time - millis()) >= CaliTime ) {
        Position = 100;
        digitalWrite(2, LOW);
        break;
      }
    }
  }

  if (calibrating == 1) {
    LCDML_DISP_jumpToFunc(LCDML_FUNC_Calibrate);
  }


  //TimeToCali = millis();
  //if (TimeToCali - Down > 43200000) {
  //  LCDML_DISP_jumpToFunc(LCDML_FUNC_Calibrate);
  //}

  unsigned long currentMillis2 = millis();
  time1 = currentMillis2;
  if (SwitchExt == 1 && key == LOW) {
    unsigned long currentMillis2 = millis();
    if (currentMillis2 >= (time1 + SwTime)) {
      myPID.SetMode(MANUAL);
      time1 = currentMillis2;
      if (OutTemp <= minOutTemp && WinterProtectEnable == 1) {
        Output = minWinterOut;
      }
    }
  }
  else if (SwitchExt == 1 && key == HIGH) {
    myPID.SetMode(AUTOMATIC);
  }

  if (SwitchExt == 0) {
    myPID.SetMode(AUTOMATIC);
  }
  // myPID.SetMode(AUTOMATIC);


  if (OutTemp <= minOutTemp && WinterProtectEnable == 1) {
    myPID.SetOutputLimits(minWinterOut, 100);
  }
  else if (OutTemp >= maxOutTemp || WinterProtectEnable == 0) {
    myPID.SetOutputLimits(outMin, 100);
  }
  // myPID.SetOutputLimits(outMin, 100);


  myPID.SetSampleTime(SampleTime);

  if (Serial.available() > 0) {
    // read the incoming byte:
    Setpoint = Serial.parseInt();
    Serial.print("Setpoint: ");
    Serial.println(Setpoint);
  }


  if (MovingOpen == 0 && MovingClose == 0)
  {
    myPID.Compute();
    Serial.println("Output");
    Serial.println(Output);
    NewPosSET = Output;
    unsigned long currentMillis1 = millis();
    ClosingTime = currentMillis1;
    unsigned long currentMillis = millis();
    OpeningTime = currentMillis;
  }

  Closing();
  Opening();
  SaveParameters();




#if (_LCDML_DISP_cfg_initscreen == 1)
  if ((millis() - g_lcdml_initscreen) >= _LCDML_DISP_cfg_initscreen_time) {
    g_lcdml_initscreen = millis(); // reset init screen time
    LCDML_DISP_jumpToFunc(LCDML_FUNC_initscreen); // jump to initscreen
  }
#endif

  // this function must called here, do not delete it
  LCDML_run(_LCDML_priority);
}


// *********************************************************************
// Opening
// *********************************************************************
void Opening() {

  if (NewPosSET > Position && MovingClose == 0) {
    Open = NewPosSET - Position;
    Serial.println("Open");
    Serial.println(Open);
    Open = (CaliTime * Open) / 100;
    Serial.println("Position");
    Serial.println(Position);
    Serial.println("Open");
    Serial.println(Open);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    MovingOpen = 1;
    unsigned long currentMillis = millis();
    Serial.print("currentMillis");
    Serial.print(currentMillis - OpeningTime);
    if (currentMillis >= (OpeningTime + Open)) {
      digitalWrite(2, LOW);
      Open = 0;
      Position = NewPosSET;
      Serial.print("New Position is:");
      Serial.print(Position);
      Serial.println("%     Open");
      MovingOpen = 0;
      OpeningTime = currentMillis;
    }
  }
}

// *********************************************************************
// Closing
// *********************************************************************
void Closing() {

  if (NewPosSET < Position && MovingOpen == 0) {
    Close = Position - NewPosSET;
    Serial.println("Close");
    Serial.println(Close);
    Close = (CaliTime * Close) / 100;
    Serial.println("Position");
    Serial.println(Position);
    Serial.println("Close");
    Serial.println(Close);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    MovingClose = 1;
    unsigned long currentMillis1 = millis();
    Serial.print("currentMillis");
    Serial.print(currentMillis1 - ClosingTime);
    if (currentMillis1 >= (ClosingTime + Close)) {
      digitalWrite(3, LOW);
      Close = 0;
      Position = NewPosSET;
      Serial.print("New Position 2 is:");
      Serial.print(Position);
      Serial.println("%     Open");
      MovingClose = 0;
      ClosingTime = currentMillis1;
    }
  }
}

// *********************************************************************
// GetTemp
// *********************************************************************
void GetTemp() {

  int RawADC;
  RawADC = analogRead(3);
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;
  Input = Temp + (P1);
}

// *********************************************************************
// GetOutsideTemp
// *********************************************************************
void GetOutsideTemp() {

  int RawADC;
  RawADC = analogRead(2);
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;
  OutTemp = Temp + (P2);
}

// ************************************************
// Save any parameter changes to EEPROM
// ************************************************
void SaveParameters()
{
  if (Setpoint != EEPROM_readDouble(SpAddress))
  {
    EEPROM_writeDouble(SpAddress, Setpoint);
  }
  if (kp != EEPROM_readDouble(KpAddress))
  {
    EEPROM_writeDouble(KpAddress, kp);
  }
  if (ki != EEPROM_readDouble(KiAddress))
  {
    EEPROM_writeDouble(KiAddress, ki);
  }
  if (kd != EEPROM_readDouble(KdAddress))
  {
    EEPROM_writeDouble(KdAddress, kd);
  }
  if (SampleTime != EEPROM_readDouble(STAddress))
  {
    EEPROM_writeDouble(STAddress, SampleTime);
  }
  if (outMin != EEPROM_readDouble(MinAddress))
  {
    EEPROM_writeDouble(MinAddress, outMin);
  }
  if (P1 != EEPROM_readDouble(P1Address))
  {
    EEPROM_writeDouble(P1Address, P1);
  }
  if (WinterProtectEnable != EEPROM.read(WinterProtectEnableAddress))
  {
    EEPROM.write(WinterProtectEnableAddress, WinterProtectEnable);
  }
  if (SwitchExt != EEPROM.read(SwitchExtAddress))
  {
    EEPROM.write(SwitchExtAddress, SwitchExt);
  }
  if (minOutTemp != EEPROM_readDouble(minOutTempAddress))
  {
    EEPROM_writeDouble(minOutTempAddress, minOutTemp);
  }
  if (maxOutTemp != EEPROM_readDouble(maxOutTempAddress))
  {
    EEPROM_writeDouble(maxOutTempAddress, maxOutTemp);
  }
  if (minWinterOut != EEPROM.read(minWinterOutAddress))
  {
    EEPROM.write(minWinterOutAddress, minWinterOut);
  }
  if (CaliTime != EEPROM_readDouble(CaliTimeAddress))
  {
    EEPROM_writeDouble(CaliTimeAddress, CaliTime);
  }
  if (SwTime != EEPROM_readDouble(SwTimeAddress))
  {
    EEPROM_writeDouble(SwTimeAddress, SwTime);
  }
  if (FrostTemp != EEPROM_readDouble(FrostTempAddress))
  {
    EEPROM_writeDouble(FrostTempAddress, FrostTemp);
  }
}

// ************************************************
// Load parameters from EEPROM
// ************************************************
void LoadParameters()
{
  // Load from EEPROM
  Setpoint = EEPROM_readDouble(SpAddress);
  kp = EEPROM_readDouble(KpAddress);
  ki = EEPROM_readDouble(KiAddress);
  kd = EEPROM_readDouble(KdAddress);
  SampleTime = EEPROM_readDouble(STAddress);
  outMin = EEPROM_readDouble(MinAddress);
  P1 = EEPROM_readDouble(P1Address);
  WinterProtectEnable = EEPROM.read(WinterProtectEnableAddress);
  SwitchExt = EEPROM.read(SwitchExtAddress);
  minOutTemp = EEPROM_readDouble(minOutTempAddress);
  maxOutTemp = EEPROM_readDouble(maxOutTempAddress);
  minWinterOut = EEPROM.read(minWinterOutAddress);
  CaliTime = EEPROM_readDouble(CaliTimeAddress);
  SwTime = EEPROM_readDouble(SwTimeAddress);
  SwTime = EEPROM_readDouble(FrostTempAddress);


  // Use defaults if EEPROM values are invalid
  if (isnan(Setpoint))
  {
    Setpoint = 6;
  }
  if (isnan(kp))
  {
    kp = 85;
  }
  if (isnan(ki))
  {
    ki = 0.5;
  }
  if (isnan(kd))
  {
    kd = 0;
  }
  if (isnan(SampleTime))
  {
    SampleTime = 1000;
  }
  if (isnan(outMin))
  {
    outMin = 0;
  }
  if (isnan(P1))
  {
    P1 = 0;
  }
  if (isnan(WinterProtectEnable))
  {
    WinterProtectEnable = 1;
  }
  if (isnan(SwitchExt))
  {
    SwitchExt = 1;
  }
  if (isnan(minOutTemp))
  {
    minOutTemp = -5;
  }
  if (isnan(maxOutTemp))
  {
    maxOutTemp = 3;
  }
  if (isnan(minWinterOut))
  {
    minWinterOut = 20;
  }
  if (isnan(SwTime))
  {
    SwTime = 15000;
  }
  if (isnan(FrostTemp))
  {
    FrostTemp = 3;
  }
}

// ************************************************
// Write floating point values to EEPROM
// ************************************************
void EEPROM_writeDouble(int address, double value)
{
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
  {
    EEPROM.write(address++, *p++);
  }
}

// ************************************************
// Read floating point values from EEPROM
// ************************************************
double EEPROM_readDouble(int address)
{
  double value = 0.0;
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
  {
    *p++ = EEPROM.read(address++);
  }
  return value;
}

// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
