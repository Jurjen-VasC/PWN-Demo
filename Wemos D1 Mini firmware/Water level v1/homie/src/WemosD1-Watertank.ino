
/*
  18-09-2018   1.0.0 Initial version  Marco Verleun <marco@marcoach.nl>
*/
#include <Homie.h>

#define TRIGGER D6 // wit
#define ECHO D7 // oranje
#define RELAY_VALVE D2
#define RELAY_PUMP D1

#define min_distance 10
#define max_distance 55  // Lowest level

#define min_level 10      // Minimum percentage that should remain in tank

// Need to maintain status somewhere
int valve = 0;
int pump = 0;
int level = 0;
int previous_level = 0;

float current_distance;
float average_distance;
long duration;

// int  measurement_counter = 0;
float distances[5];

HomieNode levelNode("level", "level");
HomieNode valveNode("valve", "switch");
HomieNode pumpNode("pump", "switch");

bool valveHandler(HomieRange range, String value) {
  /*
  Code to execute when valve is switched on or off
  Publish the value 'on' or 'off' to the
  topic: devices/<controller-id>/valve/state/set to start
  an action. This is the desired state.
  */
  Homie.getLogger() << "valveHandler: " << value << endl;
  if (value != "on" && value != "off") return false;

  if (value == "on" and valve == 0 and level > min_level) {
    // Only open valve is there is enough water in tank.
    digitalWrite(RELAY_VALVE, LOW);
    valve = 1;
    valveNode.setProperty("state").send("on");
  } else {
    digitalWrite(RELAY_VALVE, HIGH);
    valve = 0;
    if (pump == 1) {
      pumpNode.setProperty("state/set").send("off");
    }
    valveNode.setProperty("state").send("off");
    //valveNode.setProperty("state/set").send("off");
  }

  return true;
}

bool pumpHandler(HomieRange range, String value) {
  /*
  Code to execute when pump is switched on or off
  Publish the value 'on' or 'off' to the
  topic: devices/<controller-id>/pump/state/set to start
  an action. This is the desired state.
  */
  Homie.getLogger() << "pumpHandler: " << value << endl;
  if (value != "on" && value != "off") return false;

  if (value == "on" and pump == 0 and valve == 1) {
    // Only turn on pump if valve is open
    digitalWrite(RELAY_PUMP, LOW);
    pump = 1;
    pumpNode.setProperty("state").send("on");
  } else {
    digitalWrite(RELAY_PUMP, HIGH);
    pump = 0;
    pumpNode.setProperty("state").send("off");
    //pumpNode.setProperty("state/set").send("off");
  }


  return true;
}
void setupHandler() {
  levelNode.setProperty("unit").send("cm");

  // Set the GPIO pins correctly
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  digitalWrite(RELAY_PUMP, HIGH);
  pump = 0;
  pumpNode.setProperty("state").send("off");

  digitalWrite(RELAY_VALVE, HIGH);
  valve = 0;
  valveNode.setProperty("state").send("off");
}

void loopHandler() {
  /*
  The following TRIGGER/ECHO cycle is used to determine the
  distance of the nearest object by bouncing soundwaves off of it.
  */

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  current_distance = duration/58.2;

  // Ignore distances > 2 meter
  if (current_distance < 200) {
    // Keep history of last 5 valid readings
    distances[0] = distances[1];
    distances[1] = distances[2];
    distances[2] = distances[3];
    distances[3] = distances[4];
    distances[4] = current_distance;
  }

  Homie.getLogger() << "level: " << average_distance << " cm" << endl;
  Homie.getLogger() << "level: " << level << " %" << endl;
  average_distance = (distances[0] + distances[1] + distances[2] + distances[3] + distances[4]) / 5;

  // Calculate the level in % based on the distance to the watersurface
  level = 100 - ((average_distance - min_distance) / (max_distance - min_distance) * 100);
  if (level != previous_level) {
    // Only publish if the level has changed.
    levelNode.setProperty("level").send(String(level));
    previous_level = level;
  }
  if (level <= min_level) { // Tank running empty
    valveNode.setProperty("state/set").send("off");
    pumpNode.setProperty("state/set").send("off");
  }

  // Delay between measurements.
  delay(1000);
}

void setup() {
  distances[0] = 0;
  distances[1] = 0;
  distances[2] = 0;
  distances[3] = 0;
  distances[4] = 0;

  Serial.begin(115200);
  Serial << endl << endl;

  pinMode(RELAY_VALVE, OUTPUT);
  pinMode(RELAY_PUMP, OUTPUT);
  digitalWrite(RELAY_VALVE, LOW);
  digitalWrite(RELAY_PUMP, LOW);

  Homie_setFirmware("wemos-d1-watertank", "1.0.0");
  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);

  levelNode.advertise("unit");
  levelNode.advertise("%");

  valveNode.advertise("state").settable(valveHandler);
  pumpNode.advertise("state").settable(pumpHandler);
  Homie.setup();
}

void loop() {
  Homie.loop();
}
