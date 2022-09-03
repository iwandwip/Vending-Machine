int checkRFID(String UID_rfid) {
  int a = 0;
  String httpRequestData = String(DOMAIN)
                           + String("/api/purchase/check_rfid.php?rfid=")
                           + String(UID_rfid);

  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    Serial.println("httpRequestData = " + String(httpRequestData) + "zz");
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print(httpRequestData);

    if (httpResponseCode == 200) {

      Serial.print("payload = " + String(payload));
      String Buff_Response = parseString(payload, "#", 0);
      a  = Buff_Response.toInt();
    }
    Serial.println("httpRes = " + String(httpResponseCode));
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}

int checkFinger(int fingerID) {
  int a = 0;
  String httpRequestData = String(DOMAIN)
                           + String("/api/purchase/check_finger.php?fingerid=")
                           + String(fingerID);

  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print("payload = " + String(payload));

    if (httpResponseCode == 200) {
      String Buff_Response = parseString(payload, "#", 0);
      a  = Buff_Response.toInt();
    }
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}

int getSaldo(String UID_rfid) {
  int a = 0;
  //  String httpRequestData = String(DOMAIN)
  //                           + String("/api/purchase/get_saldo.php");

  //  String httpRequestData = String(DOMAIN)
  //                           + String("/api/purchase/check_finger.php?fingerid=")
  //                           + String(fingerID);

  String httpRequestData = String(DOMAIN)
                           + String("/api/purchase/check_rfid.php?rfid=")
                           + String(UID_rfid);

  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print("payload = " + String(payload));

    if (httpResponseCode == 200) {
      String Buff_Response = parseString(payload, "#", 1);
      a  = Buff_Response.toInt();
    }
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}

int BeliRokok(String merk, int iDBoard) {
  int a = 0;
  String httpRequestData = String(DOMAIN)
                           + String("/api/purchase/beli_rokok.php?idboard=")
                           + String(iDBoard) + "&merk=" + String(merk);

  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print(httpRequestData);
    //    Serial.println("payload = " + String(payload));

    if (httpResponseCode == 200) {
      String Buff_Response = parseString(payload, "#", 0);
      a  = Buff_Response.toInt();
    }
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}

int UpdateRokokDanSaldo(String merk, int iDBoard, String UID_rfid) {
  int a = 0;
  String httpRequestData = String(DOMAIN)
                           + String("/api/purchase/update_rokok.php?idboard=")
                           + String(iDBoard) + "&merk=" + String(merk)
                           + "&rfid=" + String(UID_rfid);

  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print(httpRequestData);
    Serial.println("payload = " + String(payload));

    if (httpResponseCode == 200) {
      String Buff_Response = parseString(payload, "#", 0);
      a  = Buff_Response.toInt();
    }
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}

int getNewId() {
  int a = 0;

  String httpRequestData = String(DOMAIN)
                           + String("/api/register/register.php");

  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print("payload = " + String(payload));

    if (httpResponseCode == 200) {
      String Buff_Response = parseString(payload, "#", 0);
      a  = Buff_Response.toInt();
    }
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}

int insertData(String UID_rfid, int id_finger) {
  int a = 0;
  String httpRequestData = String(DOMAIN)
                           + String("/api/register/in_data.php?rfid=")
                           + String(UID_rfid) + "&fingerid="
                           + String(id_finger);

  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print(httpRequestData);
    Serial.println("payload = " + String(payload));

    if (httpResponseCode == 200) {
      String Buff_Response = parseString(payload, "#", 0);
      a  = Buff_Response.toInt();
    }
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}
