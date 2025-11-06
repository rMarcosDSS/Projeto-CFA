#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

#include <WiFi.h>
#include <WebServer.h>

void iniciarWiFi(const char* ssid, const char* password, IPAddress local_ip, IPAddress gateway, IPAddress subnet);
void configurarRotas(WebServer &server);

#endif
