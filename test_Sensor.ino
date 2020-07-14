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

// khai bao bien line den
unsigned int black_line1 = 747;
unsigned int black_line2 = 739;

unsigned int black_line3 = 732;
unsigned int black_line4 = 718;

unsigned int black_line5 = 762;
unsigned int black_line6 = 732;

unsigned int black_line7 = 763;
unsigned int black_line8 = 767;

// cac bien loi hien tai (Err), loi truoc (pre_Err), he so dieu chinh toc do k (he so nay tu chon, he so nao xe chay muot nhat thi lay so do)
int Err = 0, pre_Err = 0, k = 11;

//toc do mac dinh ban dau
int speedA = 100, speedB = 100;

// bien luu gia tri test nen san nha
uint16_t analog_test[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint16_t min_analog = 0;

void setup()
{

  // in ra phan khoi dau
  

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

  //kiem tra nen, neu la nen sang (mau trang hoac cac mau sang thi cac gia tri black line giu nguyen,
  // neu mau nen la mau toi (mau nau hay mau xam, thi cong them gia tri black line)
  // lay mau 60 lan
  for (int i = 0; i < 8; i++)
  {
    analog_test[0] = analogRead(A0);
    analog_test[1] += analogRead(A1);
    analog_test[2] += analogRead(A2);
    analog_test[3] += analogRead(A3);
    analog_test[4] += analogRead(A4);
    analog_test[5] += analogRead(A5);
    analog_test[6] += analogRead(A6);
    analog_test[7] += analogRead(A7);
  }

  // lay gia tri trung binh

  // lay gia tri nho nhat cua nen de so sanh
  for (int i = 0; i <= 6; i++)
  {
    min_analog = analog_test[0];
    if (analog_test[i + 1] <= min_analog)
      min_analog = analog_test[i + 1];
  }

  // neu la nen  toi thi cong them 65 vao gia tri bat line
  if (min_analog >= 620)
  { // con so 620 la con  so kinh nghiem, doi voi nen toi mau)
    black_line1 = black_line1 + 65;
    black_line2 = black_line2 + 65;
    black_line3 = black_line3 + 65;
    black_line4 = black_line4 + 65;
    black_line5 = black_line5 + 65;
    black_line6 = black_line6 + 65;
    black_line7 = black_line7 + 65;
    black_line8 = black_line8 + 65;
  }

}

void loop()
{

  // print loi
  
  for (int i = 0; i < 8; i++)
  {
    analog_test[0] = analogRead(A0);
    analog_test[1] = analogRead(A1);
    analog_test[2] = analogRead(A2);
    analog_test[3] = analogRead(A3);
    analog_test[4] = analogRead(A4);
    analog_test[5] = analogRead(A5);
    analog_test[6] = analogRead(A6);
    analog_test[7] = analogRead(A7);
  }
 for(int i=0;i<8;i++)
  {
    Serial.print(analog_test[i]);
    Serial.print(" ");
  }  
  Serial.print("\n");
  delay(1000);
}
