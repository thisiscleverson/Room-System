#include <Arduino.h>
#ifndef CONNECTWIFI_H
#define CONNECTWIFI_H


/**
 * @brief Conecta-se a uma rede Wi-Fi usando o SSID e senha fornecidos.
 * 
 * Esta função tenta conectar o dispositivo a uma rede Wi-Fi especificada pelo SSID e senha. 
 * A função aguarda até que a conexão seja estabelecida ou até que um tempo limite seja atingido.
 * 
 * @param ssid O SSID (nome) da rede Wi-Fi à qual se conectar.
 * @param password A senha da rede Wi-Fi.
 * @return `true` se a conexão foi bem-sucedida, `false` se a conexão falhou.
 * 
 */
boolean connectWifi(const char* ssid, const char* password);

#endif  // CONNECTWIFI_H
