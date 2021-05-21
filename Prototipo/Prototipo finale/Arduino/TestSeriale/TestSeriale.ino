bool starttemp = false;
bool starthr = false;
bool startreflex = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    String tmp = Serial.readStringUntil(';');
    if (tmp == "battito") {
      starthr = true;
    }
    else if (tmp == "temperatura"){
      starttemp = true;
    }
    else if (tmp == "riflessi"){
      startreflex = true;
    }
  };
  if (starthr == true) {
    int tmp = random(100, 200);
    Serial.print("H");
    Serial.println(tmp);
    tmp = random(100, 200);
    Serial.print("S");
    Serial.println(tmp);
  }
  if (starttemp == true) {
    int tmp = random(100, 200);
    Serial.print("T");
    Serial.println(tmp);
  }
  if (startreflex == true) {
    Serial.println("Rtest");
    startreflex = false;
  }
  delay(1000);
}
