// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
using namespace esphome;
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void setup() {
  // ===== DO NOT EDIT ANYTHING BELOW THIS LINE =====
  // ========== AUTO GENERATED CODE BEGIN ===========
  App.set_name("controller_5");
  App.set_compilation_datetime(__DATE__ ", " __TIME__);
  LogComponent *logcomponent = App.init_log(115200, 512, UART_SELECTION_UART0);
  WiFiComponent *wificomponent = App.init_wifi();
  wificomponent->set_use_address("controller_5.local");
  WiFiAP wifiap = WiFiAP();
  wifiap.set_ssid("PWN-IoT");
  wifiap.set_password("DrinkWater");
  wificomponent->add_sta(wifiap);
  OTAComponent *otacomponent = App.init_ota();
  otacomponent->set_auth_password("PWN");
  otacomponent->start_safe_mode();
  mqtt::MQTTClientComponent *mqtt_mqttclientcomponent = App.init_mqtt("192.168.42.254", 1883, "", "");
  mqtt_mqttclientcomponent->set_topic_prefix("devices/controller_5");
  WebServer *webserver = App.init_web_server(80);
  sensor::UptimeSensor *sensor_uptimesensor = App.make_uptime_sensor("Uptime Sensor controller_5");
  sensor::WiFiSignalSensor *sensor_wifisignalsensor = App.make_wifi_signal_sensor("WiFi Signal Sensor controller_5", 10000);
  switch_::RestartSwitch *switch__restartswitch = App.make_restart_switch("Restart controller controller_5");
  StatusLEDComponent *statusledcomponent = App.make_status_led(GPIOOutputPin(2, OUTPUT, false));
  output::GPIOBinaryOutputComponent *pomp_uitvoer = App.make_gpio_output(5);
  output::GPIOBinaryOutputComponent *klep_uitvoer = App.make_gpio_output(4);
  sensor::UltrasonicSensorComponent *sensor_ultrasonicsensorcomponent = App.make_ultrasonic_sensor("Niveau Tank 3", 12, 13, 2000);
  switch_::OutputSwitch *switch__outputswitch = App.make_output_switch("Pomp 3", pomp_uitvoer);
  switch_::OutputSwitch *switch__outputswitch_2 = App.make_output_switch("Klep 3", klep_uitvoer);
  sensor_ultrasonicsensorcomponent->set_unit_of_measurement("%");
  switch__outputswitch->set_icon("mdi:skip-next");
  sensor_ultrasonicsensorcomponent->set_filters({new sensor::FilterOutNANFilter(), new sensor::SlidingWindowMovingAverageFilter(5, 1), new sensor::LambdaFilter([=](float x) -> optional<float> {
        return (100 - (((x * 100) - 10) / (55 - 10) * 100));
  }), new sensor::UniqueFilter()});
  // =========== AUTO GENERATED CODE END ============
  // ========= YOU CAN EDIT AFTER THIS LINE =========
  App.setup();
}

void loop() {
  App.loop();
}
