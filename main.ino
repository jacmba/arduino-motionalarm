const int PIR = 2;
const int LED = 10;
const int BUZZ = 44;

int cont = 0;
int total = 0;
bool alarm = false;
bool initialized = false;

void setup () {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
}

void loop () {
  if(!initialized) {
    Serial.println("Initializing alarm");
    digitalWrite(LED, HIGH);
    delay(60000);
    initialized = true;
    digitalWrite(LED, LOW);
    Serial.println("Alarm initialized");
  }

  int motion = digitalRead(PIR);
  Serial.println(motion);

  if(motion) {
    alarm = true;
  }

  if(alarm) {
    if(cont == 1) {
      digitalWrite(LED, HIGH);
      digitalWrite(BUZZ, HIGH);
    } else if(cont == 5) {
      digitalWrite(LED, LOW);
      digitalWrite(BUZZ, LOW);
    } else if(cont > 6) {
      total++;
      cont = 0;
    }

    cont++;

    if(total > 10 && !motion) {
      total = 0;
      alarm = false;
    }
  } else {
    cont = 0;
    total = 0;
  }

  delay(100);
}