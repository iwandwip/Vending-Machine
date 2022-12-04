#include "Pins.h"

void lcd_Init() {
        lcd.init();  // initialize the lcd
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
                        lcd.print("C. Check ID         ");

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

                                        lcd.setCursor(0, 0);
                                        lcd.print("    PURCHASING      ");
                                        lcd.setCursor(0, 1);
                                        lcd.print("                    ");
                                        lcd.setCursor(0, 2);
                                        lcd.print("   CHECKING E-KTP   ");
                                        lcd.setCursor(0, 3);
                                        lcd.print("      LOADING...    ");

                                        if (checkRFID(uidRFID)) {
                                                Serial.println("Check Umur");
                                                if (ageCheck(uidRFID) != -1) {
                                                        Serial.print("Umur Valid");
                                                        validate = 1;
                                                } else {
                                                        Serial.print("Umur Tidak Valid");
                                                        validate = -1;
                                                }
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
                                                if (getSaldo(uidRFID) >= 21000) {
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
                                                if (getSaldo(uidRFID) >= 26000) {
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
                                                if (getSaldo(uidRFID) >= 24000) {
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

                                delay(3000);
                                ESP.restart();

                        } else if (validate == 3) {
                                lcd.setCursor(0, 0);
                                lcd.print("    PURCHASING      ");
                                lcd.setCursor(0, 1);
                                lcd.print("       SURYA        ");
                                lcd.setCursor(0, 2);
                                lcd.print("     BERHASIL!!     ");
                                lcd.setCursor(0, 3);
                                lcd.print("   MOHON DITUNGGU   ");

                                Motor_Buka(1);
                                delay(300);
                                mh_digital_val = true;
                                if (mh_digital_val) {
                                        UpdateRokokDanSaldo("surya", ID_BOARD, uidRFID);
                                        Motor_Tutup(1);
                                        mh_digital_val = false;
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

                                Motor_Buka(2);
                                delay(300);
                                mh_digital_val = true;
                                if (mh_digital_val) {
                                        UpdateRokokDanSaldo("camel", ID_BOARD, uidRFID);
                                        Motor_Tutup(2);
                                        mh_digital_val = false;
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

                                Motor_Buka(3);
                                delay(1200);
                                mh_digital_val = true;
                                if (mh_digital_val) {
                                        UpdateRokokDanSaldo("marlboro", ID_BOARD, uidRFID);
                                        Motor_Tutup(3);
                                        mh_digital_val = false;
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

                                        lcd.setCursor(0, 0);
                                        lcd.print("     REGISTER       ");
                                        lcd.setCursor(0, 1);
                                        lcd.print("                    ");
                                        lcd.setCursor(0, 2);
                                        lcd.print("   CHECKING E-KTP   ");
                                        lcd.setCursor(0, 3);
                                        lcd.print("      LOADING...    ");

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
                                lcd.print("UID=" + String(uidRFID) + "    ");
                                lcd.setCursor(0, 2);
                                lcd.print("     ID ANDA = " + String(id) + "   ");
                                lcd.setCursor(0, 3);
                                lcd.print("  *  Untuk Kembali ");
                        }

                        break;

                case 'C':
                        if (umur_valid == 0) {
                                lcd.setCursor(0, 0);
                                lcd.print("     CHECK ID       ");
                                lcd.setCursor(0, 1);
                                lcd.print("                    ");
                                lcd.setCursor(0, 2);
                                lcd.print(" LETAKAN E-KTP ANDA ");
                                lcd.setCursor(0, 3);
                                lcd.print("                    ");

                                if (uidRFID != "") {

                                        lcd.setCursor(0, 0);
                                        lcd.print("     CHECK ID       ");
                                        lcd.setCursor(0, 1);
                                        lcd.print("                    ");
                                        lcd.setCursor(0, 2);
                                        lcd.print("   CHECKING E-KTP   ");
                                        lcd.setCursor(0, 3);
                                        lcd.print("      LOADING...    ");

                                        if (checkRFID(uidRFID)) {
                                                if (ageCheck(uidRFID) != -1) {
                                                        umur_valid = 1;
                                                } else {
                                                        umur_valid = -1;
                                                }
                                        } else {
                                                umur_valid = -1;
                                        }
                                }
                        } else if (umur_valid == 1) {
                                lcd.setCursor(0, 0);
                                lcd.print("     CHECK ID       ");
                                lcd.setCursor(0, 1);
                                lcd.print("                    ");
                                lcd.setCursor(0, 2);
                                lcd.print(" LETAKAN JARI ANDA  ");
                                lcd.setCursor(0, 3);
                                lcd.print("                    ");

                                if (fingerID != -1) {
                                        if (checkFinger(fingerID)) {
                                                umur_valid = 2;
                                        } else {
                                                umur_valid = -1;
                                        }
                                }
                        } else if (umur_valid == 2) {
                                lcd.setCursor(0, 0);
                                lcd.print("      ID ANDA      ");
                                lcd.setCursor(0, 1);
                                lcd.print("UID=" + String(uidRFID) + "    ");
                                lcd.setCursor(0, 2);
                                lcd.print("     ID ANDA = " + String(GetID(uidRFID)) + "       ");
                                lcd.setCursor(0, 3);
                                lcd.print("  *  Untuk Kembali ");

                        } else if (umur_valid == -1) {
                                lcd.setCursor(0, 0);
                                lcd.print("     CHECK ID       ");
                                lcd.setCursor(0, 1);
                                lcd.print("                    ");
                                lcd.setCursor(0, 2);
                                lcd.print("     GAGAL !!!      ");
                                lcd.setCursor(0, 3);
                                lcd.print("                    ");
                        }
                        break;
        }
}