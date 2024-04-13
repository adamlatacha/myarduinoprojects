/*
Copyright (C) AC SOFTWARE SP. Z O.O.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <SuplaDevice.h>

#include <supla/control/relay.h>
#include <supla/control/virtual_relay.h>
#include <supla/control/button.h>
#include <supla/control/action_trigger.h>
#include <supla/sensor/binary.h>
#include <supla/sensor/virtual_binary.h>

// Choose proper network interface for your card:
#ifdef ARDUINO_ARCH_AVR
  // Arduino Mega with EthernetShield W5100:
  #include <supla/network/ethernet_shield.h>
  // Ethernet MAC address
  uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  Supla::EthernetShield ethernet(mac);

  // Arduino Mega with ENC28J60:
  // #include <supla/network/ENC28J60.h>
  // Supla::ENC28J60 ethernet(mac);
#elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
  // ESP8266 and ESP32 based board:
  #include <supla/network/esp_wifi.h>
  Supla::ESPWifi wifi("network", "88888888");
#endif

  Supla::Control::VirtualRelay *trigger_on_off = nullptr;
  Supla::Control::VirtualRelay *trigger_home = nullptr;
  Supla::Control::VirtualRelay *trigger_start = nullptr;

  int pin_power = 12;
  int pin_up = 14;
  int pin_down = 4;
  int pin_ok = 5;

  int delay1 = 4000;
  int delay2 = 500;
  int delay3 = 300;

void setup() {

  Serial.begin(115200);

  // Replace the falowing GUID with value that you can retrieve from https://www.supla.org/arduino/get-guid
  char GUID[SUPLA_GUID_SIZE] = {0x0D,0x5A,0xF4,0xF6,0xC0,0xE8,0xB7,0x7A,0xA9,0x70,0x06,0x6E,0xF5,0xC7,0x28,0x05};

  // Replace the following AUTHKEY with value that you can retrieve from: https://www.supla.org/arduino/get-authkey
  char AUTHKEY[SUPLA_AUTHKEY_SIZE] = {0x3C,0x0C,0xB9,0x0C,0x9B,0xFE,0x81,0xA7,0x51,0xC1,0x60,0xD8,0xE2,0x1E,0x3C,0xE8};

  /*
   * Having your device already registered at cloud.supla.org,
   * you want to change CHANNEL sequence or remove any of them,
   * then you must also remove the device itself from cloud.supla.org.
   * Otherwise you will get "Channel conflict!" error.
   */



  trigger_on_off = new Supla::Control::VirtualRelay();
  trigger_home = new Supla::Control::VirtualRelay();
  trigger_start = new Supla::Control::VirtualRelay();

  

  /*
  auto button_start = new Supla::Control::Button(0, true, false); //pin D3
  auto button_home = new Supla::Control::Button(2, true, false); //pin D3
  auto action_trigger = new Supla::Control::ActionTrigger();
  */
  
  pinMode (5 ,OUTPUT) ; //D1
  pinMode (4 ,OUTPUT) ; //D2
  pinMode (14 ,OUTPUT) ; //D5
  pinMode (12 ,OUTPUT) ; //D6
  
  /*
  button->setHoldTime(1000);
  button->setMulticlickTime(400);
  action_trigger->attach(button_start);
  action_trigger->attach(button_home);
  */


  

  /*
   * SuplaDevice Initialization.
   * Server address is available at https://cloud.supla.org 
   * If you do not have an account, you can create it at https://cloud.supla.org/account/create
   * SUPLA and SUPLA CLOUD are free of charge
   * 
   */

  SuplaDevice.begin(GUID,              // Global Unique Identifier 
                    "svr5.supla.org",  // SUPLA server address
                    "adam.latacha@gmail.com",   // Email address used to login to Supla Cloud
                    AUTHKEY);          // Authorization key
    
}

void loop() {

 SuplaDevice.iterate(); 


bool on_off = trigger_on_off->isOn();
bool home = trigger_home->isOn();
bool start = trigger_start->isOn();

 if (on_off == 1) { //Jeśli przekaznik włączono
    digitalWrite(pin_power, HIGH); //Włącz obwód przycisku POWER
    delay(delay1);
    digitalWrite(pin_power, LOW);
    delay(delay2);
    digitalWrite(pin_ok, HIGH);
    delay(delay3);
    digitalWrite(pin_ok, LOW);
    delay(delay2);
    digitalWrite(pin_ok, HIGH);
    delay(delay3);
    digitalWrite(pin_ok, LOW);
    delay(delay2);
    digitalWrite(pin_up, HIGH);
    delay(delay3);
    digitalWrite(pin_up, LOW);
    delay(delay2);
    digitalWrite(pin_up, HIGH);
    delay(delay3);
    digitalWrite(pin_up, LOW);
    delay(delay2);
    digitalWrite(pin_ok, HIGH);
    delay(delay3);
    digitalWrite(pin_ok, LOW);
    delay(delay2);
    digitalWrite(pin_down, HIGH);
    delay(delay3);
    digitalWrite(pin_down, LOW);
    delay(delay2);
    digitalWrite(pin_down, HIGH);
    delay(delay3);
    digitalWrite(pin_down, LOW);
    delay(delay2);
    digitalWrite(pin_ok, HIGH);
    delay(delay3);
    digitalWrite(pin_ok, LOW);
    delay(delay2);
    trigger_on_off->turnOff();
 }

 if (home == 1) { //Jeśli przekaznik włączono
    digitalWrite(pin_down, HIGH);
    delay(delay3);
    digitalWrite(pin_down, LOW);
    delay(delay2);
    digitalWrite(pin_ok, HIGH);
    delay(delay3);
    digitalWrite(pin_ok, LOW);
    delay(delay2);
    trigger_home->turnOff();
 }

 if (start == 1) { //Jeśli przekaznik włączono
    digitalWrite(pin_up, HIGH);
    delay(delay3);
    digitalWrite(pin_up, LOW);
    delay(delay2);
    digitalWrite(pin_ok, HIGH);
    delay(delay3);
    digitalWrite(pin_ok, LOW);
    delay(delay2);
    trigger_start->turnOff();
 }

 
}
