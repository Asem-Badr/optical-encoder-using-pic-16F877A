#include <LiquidCrystal.h>
int pot_input;
int motor_signal;
float temp;
const int fsr = 5; //voltage Full scale resulation
int ad_result;    // Analog to Digital conversion Result
float v_out;
float port_read; //Read value from the port
float rps;       // Round per Second
float rpm;     // Round per Minute
float adc_resulation; // Analog to Digital conversion Resluation
const int rs = A4 , en = 13 , d4 = 12, d5 = 11, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  DDRD = B00000000;     //Port direction initialization
  PORTD = B00000000;    //port initial value
  pinMode(A0, INPUT);   //potenimeter input
  pinMode(A1, INPUT);   //motor enable switch
  pinMode(11, OUTPUT);  // Motor output
  pinMode(A5, OUTPUT);  // Fan output

  lcd.begin(16, 2);

}

void loop() {

  Motor_Drive(); // motor drive
  Temp_calc();
  Encoder_Rpm();
  Display();
  
}

void Motor_Drive() {
  pot_input = analogRead(A0);
  int switch_digital_value ;
  switch_digital_value = digitalRead(A1);
  if (switch_digital_value == HIGH) {
    motor_signal = map(pot_input, 0, 1023, 70, 255); // 70 first value the motor begins
    analogWrite(10, motor_signal);
  }
  else
  {
    digitalWrite(10, LOW);
  }
}

void Temp_calc() {
  ad_result = analogRead(A3); // Temperature sensor Input
  adc_resulation = fsr / (1023.0);
  v_out = adc_resulation * ad_result;
  temp = v_out * 100.0;
  if (temp >= 25) {
    digitalWrite(A5, HIGH); // Turning of Fan
  }
  else {
    digitalWrite(A5, LOW);
  }
}
void Encoder_Rpm() {
  port_read = PIND;
  rps = (port_read * 4.0) / 22.0;
  rpm = rps * 60.0;
}
void Display() {
  lcd.setCursor(0, 0);
  lcd.print("Rps:");
  lcd.print(rps);
  lcd.print(" T:");
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("Rpm:");
  lcd.print(rpm);
  lcd.print(" UIV:"); // user input voltage
  lcd.print((float)pot_input * 5.0 / 1023);
}
