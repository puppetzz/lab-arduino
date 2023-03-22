// red chan 3
// green chan 5
// blue chan 6

int  r, g, b;

void setup() {
  Serial.begin(9600);
}

void loop() {
  run();
}

void run() {
  while (Serial.available()) {
    String val = Serial.readString();
    int rindex = val.indexOf('R');
    int gindex = val.indexOf('G');
    int bindex = val.indexOf('B');
    int dindex = val.indexOf('D');

    if (rindex > -1) {
      if (gindex > -1) {
        r = val.substring(rindex + 1, gindex).toInt();
        if (r > 255)
          r = 255;
      } else if (bindex > -1) {
        r = val.substring(rindex + 1, bindex).toInt();
        if (r > 255)
          r = 255;
      } else if (dindex > -1) {
        r = val.substring(rindex + 1, dindex).toInt();
        if (r > 255)
          r = 255;
      } else {
        r = val.substring(rindex + 1).toInt();
        if (r > 255)
          r = 255;
      }
    }
    if (gindex > -1) {
      if (bindex > -1) {
        g = val.substring(gindex + 1, bindex).toInt();
        if (r > 255)
          g = 255;
      } else if (dindex > -1) {
        g = val.substring(gindex + 1, dindex).toInt();
        if (g > 255)
          g = 255;
      } else {
        g = val.substring(gindex + 1).toInt();
        if (g > 255)
          g = 255;
      }
    }
    if (bindex > -1) {
      if (dindex > -1) {
        b = val.substring(bindex + 1, dindex).toInt();
        if (b > 255)
          b = 255;
      } else {
        b = val.substring(bindex + 1).toInt();
        if (b > 255)
          b = 255;
      }
    }
    
    int d = 0;
    if (dindex > -1) {
      d = val.substring(dindex + 1).toInt();
    }
    analogWrite(3, r);
    analogWrite(5, g);
    analogWrite(6, b);
    if (d > 0) {
      delay(d);
      analogWrite(3, 0);
      analogWrite(5, 0);
      analogWrite(6, 0);
      r = 0;
      g = 0;
      b = 0;
    }
  }
}
