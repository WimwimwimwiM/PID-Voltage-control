const int analogPin = A0;
float Vout = 0.0;
const float R1 = 10000.0;
const float R2 = 5100.0;

// PID parameter
float Kp = 2.0;
float Ki = 0.3;
float Kd = 1.0;

float setpoint = 14.8;
float input = 0;
float output = 0;

float error = 0;
float previous_error = 0;
float integral = 0;
float derivative = 0;

unsigned long previous_time = 0;
float dt = 0.1;
void setup() {
  Serial.begin(9600);

}

void loop() {
  unsigned long current_time = millis();
  if (current_time - previous_time >= dt * 1000) {
    dt = (current_time - previous_time)/1000.0;
    previous_time = current_time;
    
  float raw = analogRead(analogPin);
  Vout = raw *5.0 / 1023;
  input = Vout * ((R1+R2)/R2);
    
    error = setpoint - input;

    integral += error * dt;
    derivative = (error - previous_error) / dt;
    
    output = Kp * error + Ki * integral + Kd * derivative;
    previous_error = error;


    Serial.print("Input V = ");
    Serial.print(input, 2);
    Serial.print(" V\tPID Output = ");
    Serial.print(output, 2);
    Serial.print("  \tDuty Cycle = ");
    Serial.print(output/255*100, 2);
    Serial.print(" %\tset = ");
    Serial.print(((output/255*100)*setpoint)/100, 2);
    Serial.println(" v");
  }
}
