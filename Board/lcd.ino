void lcd_Init()
{
  lcd.init(); // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
}

void lcd_main() {

  switch (_mode) {
    case 'E':
      lcd.setCursor(0, 0);
      lcd.print("     MAIN MENU      ");
      lcd.setCursor(0, 1);
      lcd.print("A. Purchase         ");
      lcd.setCursor(0, 2);
      lcd.print("B. Register         ");
      lcd.setCursor(0, 3);
      lcd.print("                    ");

      validate = 0;
      regist = 0;

      break;

    case 'A':
      if (validate == 0) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print(" LETAKAN E-KTP ANDA ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");

        if (uidRFID != "") {
          if (checkRFID(uidRFID)) {
            validate = 1;
          } else {
            validate = -1;
          }
        }

      } else if (validate == 1) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print(" LETAKAN JARI ANDA  ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");

        if (fingerID != -1) {
          if (checkFinger(fingerID)) {
            validate = 2;
          } else {
            validate = -1;
          }
        }

      } else if (validate == 2) {
        lcd.setCursor(0, 0);
        lcd.print("SALDO = " + String(getSaldo(uidRFID)) + "      ");
        lcd.setCursor(0, 1);
        lcd.print("1. Surya     Rp21000");
        lcd.setCursor(0, 2);
        lcd.print("2. Camel     Rp26000");
        lcd.setCursor(0, 3);
        lcd.print("3. Marlboro  Rp24000");

        /* -------------------------------------------------------*/

        if (beli_roko[0] == 1) {
          lcd.setCursor(0, 0);
          lcd.print("    PURCHASING      ");
          lcd.setCursor(0, 1);
          lcd.print("       SURYA        ");
          lcd.setCursor(0, 2);
          lcd.print(" SEDANG DIPROSES!!  ");
          lcd.setCursor(0, 3);
          lcd.print("                    ");

          delay(2000);

          if (BeliRokok("surya", ID_BOARD) == 1) {
            if (!getSaldo(uidRFID) < 0) {
              validate = 3;
            } else {
              validate = 7;
            }
          } else if (BeliRokok("surya", ID_BOARD) == -1) {
            validate = 6;
          }

        }

        /* -------------------------------------------------------*/

        if (beli_roko[1] == 1) {
          lcd.setCursor(0, 0);
          lcd.print("    PURCHASING      ");
          lcd.setCursor(0, 1);
          lcd.print("       CAMEL        ");
          lcd.setCursor(0, 2);
          lcd.print(" SEDANG DIPROSES!!  ");
          lcd.setCursor(0, 3);
          lcd.print("                    ");

          delay(2000);

          if (BeliRokok("camel", ID_BOARD) == 1) {
            if (!getSaldo(uidRFID) < 0) {
              validate = 4;
            } else {
              validate = 7;
            }

          } else if (BeliRokok("camel", ID_BOARD) == -1) {
            validate = 6;
          }
        }

        /* -------------------------------------------------------*/

        if (beli_roko[2] == 1) {
          lcd.setCursor(0, 0);
          lcd.print("    PURCHASING      ");
          lcd.setCursor(0, 1);
          lcd.print("     MARLBORO       ");
          lcd.setCursor(0, 2);
          lcd.print(" SEDANG DIPROSES!!  ");
          lcd.setCursor(0, 3);
          lcd.print("                    ");

          delay(2000);
          if (BeliRokok("marlboro", ID_BOARD) == 1) {
            if (!getSaldo(uidRFID) < 0) {
              validate = 5;
            } else {
              validate = 7;
            }
          } else if (BeliRokok("marlboro", ID_BOARD) == -1) {
            validate = 6;
          }
        }

      } else if (validate == -1) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print("     GAGAL !!!      ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");

      } else if (validate == 3) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("       SURYA        ");
        lcd.setCursor(0, 2);
        lcd.print("     BERHASIL!!     ");
        lcd.setCursor(0, 3);
        lcd.print("   MOHON DITUNGGU   ");

        servoBuka();

        if (mh_digital_val) {
          UpdateRokokDanSaldo("surya", ID_BOARD, uidRFID);
          servoTutup();
          validate = 2;
          beli_roko[0] = 0;
        }
      } else if (validate == 4) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("       CAMEL        ");
        lcd.setCursor(0, 2);
        lcd.print("     BERHASIL!!     ");
        lcd.setCursor(0, 3);
        lcd.print("   MOHON DITUNGGU   ");

        if (mh_digital_val) {
          UpdateRokokDanSaldo("camel", ID_BOARD, uidRFID);
          validate = 2;
          beli_roko[1] = 0;
        }

      } else if (validate == 5) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("     MARLBORO       ");
        lcd.setCursor(0, 2);
        lcd.print("     BERHASIL!!     ");
        lcd.setCursor(0, 3);
        lcd.print("   MOHON DITUNGGU   ");

        if (mh_digital_val) {
          UpdateRokokDanSaldo("marlboro", ID_BOARD, uidRFID);
          validate = 2;
          beli_roko[2] = 0;
        }

      } else if (validate == 6) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print("      GAGAL!!       ");
        lcd.setCursor(0, 3);
        lcd.print("   ROKOK HABIS!!    ");
        delay(3000);
        validate = 2;
        beli_roko[0] = 0;
        beli_roko[1] = 0;
        beli_roko[2] = 0;
      } else if (validate == 7) {
        lcd.setCursor(0, 0);
        lcd.print("    PURCHASING      ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print("      GAGAL!!       ");
        lcd.setCursor(0, 3);
        lcd.print("   SALDO HABIS!!    ");
        delay(3000);
        validate = 2;
        beli_roko[0] = 0;
        beli_roko[1] = 0;
        beli_roko[2] = 0;
      }
      break;

    case 'B':
      if (regist == 0) {
        lcd.setCursor(0, 0);
        lcd.print("     REGISTER       ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print(" LETAKAN E-KTP ANDA ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");

        if (uidRFID != "") {
          regist = 1;
        }

      } else if (regist == 1) {
        id = getNewId();

        lcd.setCursor(0, 0);
        lcd.print("     REGISTER       ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print(" LETAKAN JARI ANDA  ");
        lcd.setCursor(0, 3);
        lcd.print("     ID ANDA = " + String(id) + "   ");


        if (getFingerprintEnroll()) {
          insertData(uidRFID, id);
          regist = 2;
        }
      } else if (regist == 2) {
        lcd.setCursor(0, 0);
        lcd.print(" BERHASIL REGISTER  ");
        lcd.setCursor(0, 1);
        lcd.print("UID = " + String(uidRFID) + "  ");
        lcd.setCursor(0, 2);
        lcd.print("     ID ANDA = " + String(id) + "   ");
        lcd.setCursor(0, 3);
        lcd.print("  *  Untuk Kembali " );
      }

      break;
  }
}
