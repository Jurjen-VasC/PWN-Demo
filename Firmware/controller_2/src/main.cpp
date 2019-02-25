// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
using namespace esphome;
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void setup() {
  // ===== DO NOT EDIT ANYTHING BELOW THIS LINE =====
  // ========== AUTO GENERATED CODE BEGIN ===========
  App.set_name("controller_2");
  App.set_compilation_datetime(__DATE__ ", " __TIME__);
  LogComponent *logcomponent = App.init_log(115200, 512, UART_SELECTION_UART0);
  WiFiComponent *wificomponent = App.init_wifi();
  wificomponent->set_use_address("controller_2.local");
  WiFiAP wifiap = WiFiAP();
  wifiap.set_ssid("PWN-IoT");
  wifiap.set_password("DrinkWater");
  wificomponent->add_sta(wifiap);
  OTAComponent *otacomponent = App.init_ota();
  otacomponent->set_auth_password("PWN");
  otacomponent->start_safe_mode();
  mqtt::MQTTClientComponent *mqtt_mqttclientcomponent = App.init_mqtt("192.168.42.254", 1883, "", "");
  mqtt_mqttclientcomponent->set_topic_prefix("devices/controller_2");
  WebServer *webserver = App.init_web_server(80);
  sensor::UptimeSensor *sensor_uptimesensor = App.make_uptime_sensor("Uptime Sensor controller_2");
  sensor::WiFiSignalSensor *sensor_wifisignalsensor = App.make_wifi_signal_sensor("WiFi Signal Sensor controller_2", 10000);
  switch_::RestartSwitch *switch__restartswitch = App.make_restart_switch("Restart controller controller_2");
  StatusLEDComponent *statusledcomponent = App.make_status_led(GPIOOutputPin(2, OUTPUT, false));
  sensor::PulseCounterSensorComponent *sensor_pulsecountersensorcomponent = App.make_pulse_counter_sensor("Flow door sensor controller_2", 4, 2000);
  sensor_pulsecountersensorcomponent->set_unit_of_measurement("l/m");
  sensor_pulsecountersensorcomponent->set_filters({new sensor::FilterOutNANFilter(), new sensor::SlidingWindowMovingAverageFilter(5, 1), new sensor::LambdaFilter([=](float x) -> optional<float> {
        return ( x / 100 );
  }), new sensor::UniqueFilter()});
  // =========== AUTO GENERATED CODE END ============
  // ========= YOU CAN EDIT AFTER THIS LINE =========
  App.setup();
}

void loop() {
  App.loop();
}
