void doReboot() {
    // send reboot command
    SCB_AIRCR = 0x05FA0004;
}

void checkReboot() {
    if(digitalRead(rebootButton) == LOW){
        Serial.print("reboot");
        doReboot();
    }
}