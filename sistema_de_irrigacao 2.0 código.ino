#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C PCF8574
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensor_solo = 0;
int umidade = 0;

void setup()
{
  pinMode(A0, INPUT);

  pinMode(7, OUTPUT); // Relé
  pinMode(8, OUTPUT); // LED Vermelho
  pinMode(9, OUTPUT); // LED Verde

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Sistema de");
  lcd.setCursor(0, 1);
  lcd.print("Irrigacao");

  delay(2000);
  lcd.clear();
}

void loop()
{
  sensor_solo = analogRead(A0);

  // Conversão para porcentagem
  // Ajuste os valores 0 e 876 se necessário
  umidade = map(sensor_solo, 0, 876, 0, 100);
  umidade = constrain(umidade, 0, 100);

  // Exibe porcentagem
  lcd.setCursor(0, 0);
  lcd.print("Umidade:      ");

  lcd.setCursor(9, 0);
  lcd.print("    "); // limpa números antigos
  lcd.setCursor(9, 0);
  lcd.print(umidade);
  lcd.print("%");

  // Lógica da irrigação
  if (umidade < 30)
  {
    // Solo seco
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);

    lcd.setCursor(0, 1);
    lcd.print("IRRIGANDO...  ");
  }
  else
  {
    // Solo úmido
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("SOLO UMIDO    ");
  }

  Serial.print("Sensor: ");
  Serial.print(sensor_solo);
  Serial.print(" | Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  delay(500);
}