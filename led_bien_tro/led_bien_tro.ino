void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once: 
  for (int i=2; i<=11; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // cau 5
  traiSangPhaiBienTro();
}

void traiSangPhai() {
  for (int i = 2; i <=11; i++) {
    if (i > 2) 
      digitalWrite(i - 1, LOW);
    
    digitalWrite(i, HIGH);
    delay(500);
    if (i == 11)
      digitalWrite(11, LOW);
  }

  delay(300);

  for (int i = 11; i >=2; i--) {
    if (i < 11) 
      digitalWrite(i + 1, LOW);
    
    digitalWrite(i, HIGH);
    delay(500);
    if (i == 2)
      digitalWrite(2, LOW);
  }

  delay(300); 
}

void haiBenVaoTrong() {
    int j = 9;
    for (int i = 2; i <= 6; i++) {
      if (i > 2) {
        digitalWrite((i - 1), LOW);
        digitalWrite((i + j + 1), LOW);        
      }
      
      digitalWrite(i, HIGH);
      digitalWrite((i + j), HIGH);
      delay(500);
      if (i == 6) {
        digitalWrite(i, LOW);
        digitalWrite((i + j), LOW);
      }
      j -= 2;                
    }

    delay(400);
    int k = 1;

    for (int i = 6; i >=2 ; i--) {
      if (i < 6) {
        digitalWrite((i + 1), LOW);
        digitalWrite((i + k - 1), LOW);        
      }
      
      digitalWrite(i, HIGH);
      digitalWrite((i + k), HIGH);
      delay(500);
      if (i == 2) {
        digitalWrite(i, LOW);
        digitalWrite((i + k), LOW);
      }
      k += 2;                
    }
    delay(500);    
}

void chanLe() {
  for (int i = 3; i <= 11; i += 2) {
    if (i > 3)  {
      digitalWrite(i - 2, LOW);
    }
    digitalWrite(i, HIGH);
    delay(500);
    if (i == 11)
      digitalWrite(i, LOW);
  }

  delay(300);

  for (int i = 2; i <= 10; i += 2) {
    if (i > 1)  {
      digitalWrite(i - 2, LOW);
    }
    digitalWrite(i, HIGH);
    delay(500);
    if (i == 10)
      digitalWrite(i, LOW);
  }

  delay(300);
}

void traiSangPhaiBienTro() {
  int st;
  st = analogRead(0);
  int st1 = st/2;
  for (int i = 2; i <=11; i++) {

    if (i > 2) 
      digitalWrite(i - 1, LOW);
    
    digitalWrite(i, HIGH); 
    st = analogRead(0);
    st1 = st/2;   
    delay(st1);
    if (i == 11)
      digitalWrite(11, LOW);
  }

  st = analogRead(0);
  st1 = st/2;
  delay(st1);

  for (int i = 11; i >=2; i--) {
    if (i < 11) 
      digitalWrite(i + 1, LOW);
    
    digitalWrite(i, HIGH);
    st = analogRead(0);
    st1 = st/2;
    delay(st1);
    if (i == 2)
      digitalWrite(2, LOW);
  }

  st = analogRead(0);
  st1 = st/2;
  delay(st1);   
}

void bienTro() {
  int st;
  st = analogRead(0);
  int st1 = st/4;
  analogWrite(3, st1);
  analogWrite(5, st1);
  analogWrite(6, st1);
  analogWrite(9, st1);
  analogWrite(10, st1);
}
