/*
1.0.0  25-08-2018 Initial version

Based on https://github.com/latonita/esp8266-mqtt-pulsecounter
*/
#include <Homie.h>

const char CompileDate[] = __DATE__ " " __TIME__;

HomieNode pulseNode("flow", "liters");
//HomieNode pulse1Node("pulse1", "interval");


#define PULSE_PIN1 D2   // P1


#define SAMPLE_MINUTES 0.1

#define DEBOUNCE_MS 20 //debouncing for interrupts

volatile unsigned int Pulses1 = 0;
volatile unsigned int PulsesLast1 = 0;
volatile unsigned int PulsesKept1 = 0;


volatile unsigned int PulsesPeriods = 0;

volatile unsigned long LastMicros1;
void pulseHandler() {
  if((long)(micros() - LastMicros1) >= DEBOUNCE_MS * 1000) {
    // Pulse counts only if it debounced properly
    Pulses1++;
    LastMicros1 = micros();
    Serial.print('.');
  }
}

// TIMER
os_timer_t myTimer;
bool tickOccured;

void timerCallback(void *pArg) {
  // If no pulses are counted don't do anything
  if (Pulses1 > 0) {
    PulsesLast1 = Pulses1;
    PulsesKept1 += Pulses1;
    Pulses1 = 0;

    PulsesPeriods++;
  }
  tickOccured = true;
}

void timerInit(void) {
  os_timer_setfn(&myTimer, timerCallback, NULL);
  os_timer_arm(&myTimer, 1000 * 60 * SAMPLE_MINUTES, true);
}

void setupHandler() {
  pulseNode.setProperty("unit").send("liter/min");

  // Pulses arrive at random intervals. Hence we use interrupts to count them
  pinMode(PULSE_PIN1, INPUT);
  attachInterrupt(PULSE_PIN1, pulseHandler, RISING);

  // Start a timer to periodicly report the number of pulses counted.
  tickOccured = false;
  timerInit();
}

bool broadcastHandler(const String& level, const String& value) {
  Serial << "Received broadcast level " << level << ": " << value << endl;
  return true;
}

void loopHandler() {
  if (tickOccured == true and PulsesKept1 > 0) {
    Serial.print("Tick occured. Pulses kept so far: ");
    
    String payload = "{";
    payload += "\"P1\":";
    payload += PulsesKept1;
    payload += ",\"Sec\":";
    payload += PulsesPeriods * 60 * SAMPLE_MINUTES;
    payload += ",\"Per\":";
    payload += PulsesPeriods;
    payload += ",\"Up\":";
    payload += ((unsigned long)millis()/1000);
    payload += "}";

    Serial.println(payload);

    if (PulsesKept1 > 0) {
      pulseNode.setProperty("pulses").send(String(PulsesKept1));
      pulseNode.setProperty("interval").send(String(PulsesPeriods));
      PulsesKept1 = 0;
      PulsesPeriods = 0;
    }

  }
  tickOccured = false;
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;


  Homie_setFirmware("wemos-d1-pulsecounter", "1.0.0");
  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);
  Homie.setBroadcastHandler(broadcastHandler); // before Homie.setup()

  pulseNode.advertise("pulses");
  pulseNode.advertise("interval");
  Homie.setup();
}

void loop() {
  Homie.loop();
}
