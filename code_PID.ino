#include <LiquidCrystal.h>
//động cơ 1
#define PWMA 3
#define INA 4
#define INB 5
//động cơ 2
#define PWMB 9
#define IND 8
#define INC 7

//do line
#define line_1 A0
#define line_2 A1
#define line_3 A2
#define line_4 A3
#define line_5 A4
#define line_6 A5
#define line_7 A6
#define line_8 A7

//LCD
#define RS_LCD 2
#define EN_LCD 13
#define D4_LCD 6
#define D5_LCD 10
#define D6_LCD 11
#define D7_LCD 12

// khai bao lcd
LiquidCrystal lcd(RS_LCD, EN_LCD, D4_LCD, D5_LCD, D6_LCD, D7_LCD);

int a[5];
int last_error = 0;

int integral = 0;

int expected = 2;

int mode = 0;
int speedA = 150, speedB = 150;
uint16_t analog_test[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int readline();
void PID();
void set_motors(int pid);
void move(int val);

void setup()
{

  // in ra phan khoi dau
  lcd.begin(16, 2);
  lcd.print("Line Follower");
  lcd.setCursor(0, 1);
  lcd.print("Runing.......");

  // thiet lap input output
  pinMode(PWMA, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INC, OUTPUT);
  pinMode(IND, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  Serial.begin(9600);

  //dung dong co
  digitalWrite(PWMA, 0);
  digitalWrite(PWMB, 0);
  digitalWrite(INA, 1);
  digitalWrite(INB, 0);
  digitalWrite(INC, 0);
  digitalWrite(IND, 1);
}

void loop()
{
  PID();
}

int readline()
{
  analog_test[0] = analogRead(A0);
  analog_test[1] = analogRead(A1);
  analog_test[2] = analogRead(A2);
  analog_test[3] = analogRead(A3);
  analog_test[4] = analogRead(A4);
  analog_test[5] = analogRead(A5);
  analog_test[6] = analogRead(A6);
  analog_test[7] = analogRead(A7);
  a[0] = ((analog_test[1] < 800) ? 0 : 1);
  a[1] = ((analog_test[2] < 800) ? 0 : 1);
  a[2] = (((analog_test[3] < 800) && (analog_test[4] < 800)) ? 0 : 1);
  a[3] = ((analog_test[5] < 800) ? 0 : 1);
  a[4] = ((analog_test[6] < 800) ? 0 : 1);

  bool blackspace = a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0 && a[4] == 0;
  bool whitespace = a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1;
  if (blackspace || whitespace)
  {
    return 10;
  }

  if (a[0] == a[4])
  {
    mode = a[0];
  }

  for (int i = 0; i < 5; i++)
  {
    if (a[i] != mode)
    {
      return i;
    }
  }

  return 10;
}

void move(int val)
{
  analogWrite(PWMA, speedA - val);
  analogWrite(PWMB, speedB + val);
}

void PID()
{
  int i; // Control function
  int power_difference = 0;
  float Kp, Ki, Kd;
  unsigned int position;
  int derivative, error;

  position = readline();

  if (position == 10)
  {
    move(0);
    return;
  }

  error = ((int)position - expected); // 0, 1, 2, 3, 4

  derivative = error - last_error;
  if (error == 0)
    integral = 0;
  else
    integral = integral + error;
  last_error = error;

  Kp = 350;
  Ki = 0.0001;
  Kd = 10;

  power_difference = error * Kp + integral * Ki + derivative * Kd;

  move(power_difference);

}
