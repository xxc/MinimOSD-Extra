/* ******************************************************************/
/* *********************** GENERAL FUNCTIONS ********************** */

//Extract functions (get bits from the positioning bytes
//#define ISa(whichBit) getBit(panA_REG, whichBit)
//#define ISb(whichBit) getBit(panB_REG, whichBit)
//#define ISc(whichBit) getBit(panC_REG, whichBit)
//#define ISd(whichBit) getBit(panD_REG, whichBit)
#define ISa(panel, whichBit) getBit(panA_REG[panel], whichBit)
#define ISb(panel, whichBit) getBit(panB_REG[panel], whichBit)
#define ISc(panel, whichBit) getBit(panC_REG[panel], whichBit)
#define ISd(panel, whichBit) getBit(panD_REG[panel], whichBit)
 

boolean getBit(byte Reg, byte whichBit) {
  boolean State;
  State = Reg & (1 << whichBit);
  return State;
}

byte setBit(byte &Reg, byte whichBit, boolean stat) {
  if (stat) {
    Reg = Reg | (1 << whichBit);
  } 
  else {
    Reg = Reg & ~(1 << whichBit);
  }
  return Reg;
}

// EEPROM reader/writers
// Utilities for writing and reading from the EEPROM
byte readEEPROM(int address) {

  return EEPROM.read(address);
}

void writeEEPROM(byte value, int address) {
  EEPROM.write(address, value);
}


void InitializeOSD() {
  
  loadBar();
  delay(500);

  writeEEPROM(42, CHK1);
  writeEEPROM(VER-42,CHK2);
  writeSettings();
  
  osd.setPanel(4,9);
  osd.openPanel();
  osd.printf_P(PSTR("OSD Initialized, reboot")); 
  osd.closePanel();
 
  // run for ever so user resets 
  for(;;) {}
   
}

// Write our latest FACTORY settings to EEPROM
void writeSettings() {
 // Writing all default parameters to EEPROM, ON = panel enabled  
 // All panels have 3 values:
 //  - Enable/Disable
 //  - X coordinate on screen
 //  - Y coordinate on screen
 writeEEPROM(off, panCenter_en_ADDR);
 writeEEPROM(13, panCenter_x_ADDR);
 writeEEPROM(7,  panCenter_y_ADDR);
 writeEEPROM(on, panPitch_en_ADDR);
 writeEEPROM(22, panPitch_x_ADDR);
 writeEEPROM(9,  panPitch_y_ADDR);
 writeEEPROM(on, panRoll_en_ADDR);
 writeEEPROM(11, panRoll_x_ADDR);
 writeEEPROM(1,  panRoll_y_ADDR);
 writeEEPROM(on, panBatt_A_en_ADDR);
 writeEEPROM(21, panBatt_A_x_ADDR);
 writeEEPROM(1,  panBatt_A_y_ADDR);
 //writeEEPROM(on, panBatt_B_en_ADDR);
 //writeEEPROM(21, panBatt_B_x_ADDR);
 //writeEEPROM(3,  panBatt_B_y_ADDR);
 writeEEPROM(on, panGPSats_en_ADDR);
 writeEEPROM(2,  panGPSats_x_ADDR);
 writeEEPROM(13, panGPSats_y_ADDR);
 writeEEPROM(on, panGPL_en_ADDR);
 writeEEPROM(5,  panGPL_x_ADDR);
 writeEEPROM(13, panGPL_y_ADDR);
 writeEEPROM(on, panGPS_en_ADDR);
 writeEEPROM(2,  panGPS_x_ADDR);
 writeEEPROM(14, panGPS_y_ADDR);
 writeEEPROM(on, panRose_en_ADDR);
 writeEEPROM(16, panRose_x_ADDR);
 writeEEPROM(14, panRose_y_ADDR);
 writeEEPROM(on, panHeading_en_ADDR);
 writeEEPROM(24, panHeading_x_ADDR);
 writeEEPROM(13, panHeading_y_ADDR);
 writeEEPROM(on, panMavBeat_en_ADDR);
 writeEEPROM(2,  panMavBeat_x_ADDR);
 writeEEPROM(9, panMavBeat_y_ADDR);
 writeEEPROM(on, panHomeDir_en_ADDR);
 writeEEPROM(14, panHomeDir_x_ADDR);
 writeEEPROM(3,  panHomeDir_y_ADDR);
 writeEEPROM(on, panHomeDis_en_ADDR);
 writeEEPROM(2,  panHomeDis_x_ADDR);
 writeEEPROM(1,  panHomeDis_y_ADDR);
// writeEEPROM(off,panWPDir_en_ADDR);
// writeEEPROM(0,  panWPDir_x_ADDR);
// writeEEPROM(0,  panWPDir_y_ADDR);
// writeEEPROM(off,panWPDis_en_ADDR);
// writeEEPROM(0,  panWPDis_x_ADDR);
// writeEEPROM(0,  panWPDis_y_ADDR);
 writeEEPROM(on, panRSSI_en_ADDR);
 writeEEPROM(21, panRSSI_x_ADDR);
 writeEEPROM(5,  panRSSI_y_ADDR);
 
 writeEEPROM(on, panCur_A_en_ADDR);
 writeEEPROM(21, panCur_A_x_ADDR);
 writeEEPROM(2,  panCur_A_y_ADDR);
 //writeEEPROM(on, panCur_B_en_ADDR);
 //writeEEPROM(21, panCur_B_x_ADDR);
 //writeEEPROM(4,  panCur_B_y_ADDR);
 writeEEPROM(on, panAlt_en_ADDR);
 writeEEPROM(2,  panAlt_x_ADDR);
 writeEEPROM(2,  panAlt_y_ADDR);
 writeEEPROM(on, panHomeAlt_en_ADDR);
 writeEEPROM(2,  panHomeAlt_x_ADDR);
 writeEEPROM(5,  panHomeAlt_y_ADDR);
 writeEEPROM(on, panVel_en_ADDR);
 writeEEPROM(2,  panVel_x_ADDR);
 writeEEPROM(3,  panVel_y_ADDR);
 writeEEPROM(on, panAirSpeed_en_ADDR);
 writeEEPROM(2,  panAirSpeed_x_ADDR);
 writeEEPROM(3,  panAirSpeed_y_ADDR); 
 writeEEPROM(on, panBattery_A_Percent_en_ADDR);
 writeEEPROM(2,  panBattery_A_Percent_x_ADDR);
 writeEEPROM(3,  panBattery_A_Percent_y_ADDR); 
 writeEEPROM(on, panTime_en_ADDR);
 writeEEPROM(2,  panTime_x_ADDR);
 writeEEPROM(3,  panTime_y_ADDR);
 writeEEPROM(on, panThr_en_ADDR);
 writeEEPROM(2,  panThr_x_ADDR);
 writeEEPROM(4,  panThr_y_ADDR);
 writeEEPROM(on, panFMod_en_ADDR);
 writeEEPROM(17, panFMod_x_ADDR);
 writeEEPROM(13, panFMod_y_ADDR);
 writeEEPROM(on, panHorizon_en_ADDR);
 writeEEPROM(8,  panHorizon_x_ADDR);
 writeEEPROM(7,  panHorizon_y_ADDR);
 writeEEPROM(on, panWarn_en_ADDR);
 writeEEPROM(10, panWarn_x_ADDR);
 writeEEPROM(4,  panWarn_y_ADDR);
// writeEEPROM(on, panOff_en_ADDR);
// writeEEPROM(10, panOff_x_ADDR);
// writeEEPROM(4,  panOff_y_ADDR);
 writeEEPROM(on, panWindSpeed_en_ADDR);
 writeEEPROM(10, panWindSpeed_x_ADDR);
 writeEEPROM(4,  panWindSpeed_y_ADDR);
 writeEEPROM(on, panClimb_en_ADDR);
 writeEEPROM(10, panClimb_x_ADDR);
 writeEEPROM(4,  panClimb_y_ADDR);
// writeEEPROM(on, panTune_en_ADDR);
// writeEEPROM(10, panTune_x_ADDR);
// writeEEPROM(4,  panTune_y_ADDR);
// writeEEPROM(on, panSetup_en_ADDR);
// writeEEPROM(10, panSetup_x_ADDR);
// writeEEPROM(4,  panSetup_y_ADDR);

writeEEPROM(0, measure_ADDR);
writeEEPROM(50, overspeed_ADDR);
writeEEPROM(30, stall_ADDR);
writeEEPROM(106, battv_ADDR);
writeEEPROM(10, battp_ADDR);
writeEEPROM(400, overalt_ADDR);

writeEEPROM(0, OSD_Toggle_ADDR);

}

void readSettings() {
  
  overspeed = EEPROM.read(overspeed_ADDR);
  stall = EEPROM.read(stall_ADDR);
  battv = EEPROM.read(battv_ADDR);
  battp = EEPROM.read(battp_ADDR);
  overalt = EEPROM.read(overalt_ADDR);
  user_rssi_high = EEPROM.read(OSD_HIGH_ADDR);
  user_rssi_low = EEPROM.read(OSD_LOW_ADDR);
  osd_toggle_chan = EEPROM.read(OSD_Toggle_ADDR);
  if (osd_toggle_chan > 4) osd_toggle_chan = 0;
  osd_toggle_temp = osd_toggle_chan;
  
  do_converts();
  
  
  for (panel = 0; panel < npanels; panel++)
  {
  
    uint16_t offset = 200 * panel;
    
    //****** First set of 8 Panels ******
    
    setBit(panA_REG[panel], Cen_BIT, readEEPROM(panCenter_en_ADDR + offset));
    panCenter_XY[0][panel] = readEEPROM(panCenter_x_ADDR + offset);
    panCenter_XY[1][panel] = checkPAL(readEEPROM(panCenter_y_ADDR + offset));
    
    setBit(panA_REG[panel], Bp_BIT, readEEPROM(panBattery_A_Percent_en_ADDR + offset));
    panBattery_A_Percent_XY[0][panel] = readEEPROM(panBattery_A_Percent_x_ADDR + offset);
    panBattery_A_Percent_XY[1][panel] = checkPAL(readEEPROM(panBattery_A_Percent_y_ADDR + offset));
    
    setBit(panA_REG[panel], Pit_BIT, readEEPROM(panPitch_en_ADDR + offset));
    panPitch_XY[0][panel] = readEEPROM(panPitch_x_ADDR + offset);
    panPitch_XY[1][panel] = checkPAL(readEEPROM(panPitch_y_ADDR + offset));
    
    setBit(panA_REG[panel], Rol_BIT, readEEPROM(panRoll_en_ADDR + offset));
    panRoll_XY[0][panel] = readEEPROM(panRoll_x_ADDR + offset);
    panRoll_XY[1][panel] = checkPAL(readEEPROM(panRoll_y_ADDR + offset));
    
    setBit(panA_REG[panel], BatA_BIT, readEEPROM(panBatt_A_en_ADDR + offset));
    panBatt_A_XY[0][panel] = readEEPROM(panBatt_A_x_ADDR + offset);
    panBatt_A_XY[1][panel] = checkPAL(readEEPROM(panBatt_A_y_ADDR + offset));
  
    //setBit(panA_REG[panel], BatB_BIT, readEEPROM(panBatt_B_en_ADDR));
    //panBatt_B_XY[0][panel] = readEEPROM(panBatt_B_x_ADDR);
    //panBatt_B_XY[1][panel] = checkPAL(readEEPROM(panBatt_B_y_ADDR));
    
    setBit(panA_REG[panel], GPSats_BIT, readEEPROM(panGPSats_en_ADDR + offset));
    panGPSats_XY[0][panel] = readEEPROM(panGPSats_x_ADDR + offset);
    panGPSats_XY[1][panel] = checkPAL(readEEPROM(panGPSats_y_ADDR + offset));
  
    setBit(panA_REG[panel], GPL_BIT, readEEPROM(panGPL_en_ADDR + offset));
    panGPL_XY[0][panel] = readEEPROM(panGPL_x_ADDR + offset);
    panGPL_XY[1][panel] = checkPAL(readEEPROM(panGPL_y_ADDR + offset));
    
    setBit(panA_REG[panel], GPS_BIT, readEEPROM(panGPS_en_ADDR + offset));
    panGPS_XY[0][panel] = readEEPROM(panGPS_x_ADDR + offset);
    panGPS_XY[1][panel] = checkPAL(readEEPROM(panGPS_y_ADDR + offset));
  
    //****** Second set of 8 Panels ******
    
    setBit(panB_REG[panel], Rose_BIT, readEEPROM(panRose_en_ADDR + offset));
    panRose_XY[0][panel] = readEEPROM(panRose_x_ADDR + offset);
    panRose_XY[1][panel] = checkPAL(readEEPROM(panRose_y_ADDR + offset));
  
    setBit(panB_REG[panel], Head_BIT, readEEPROM(panHeading_en_ADDR + offset));
    panHeading_XY[0][panel] = readEEPROM(panHeading_x_ADDR + offset);
    panHeading_XY[1][panel] = checkPAL(readEEPROM(panHeading_y_ADDR + offset));
  
    setBit(panB_REG[panel], MavB_BIT, readEEPROM(panMavBeat_en_ADDR + offset));
    panMavBeat_XY[0][panel] = readEEPROM(panMavBeat_x_ADDR + offset);
    panMavBeat_XY[1][panel] = checkPAL(readEEPROM(panMavBeat_y_ADDR + offset));
  
    setBit(panB_REG[panel], HDis_BIT, readEEPROM(panHomeDis_en_ADDR + offset));
    panHomeDis_XY[0][panel] = readEEPROM(panHomeDis_x_ADDR + offset);
    panHomeDis_XY[1][panel] = checkPAL(readEEPROM(panHomeDis_y_ADDR + offset));
  
    setBit(panB_REG[panel], HDir_BIT, readEEPROM(panHomeDir_en_ADDR + offset));
    panHomeDir_XY[0][panel] = readEEPROM(panHomeDir_x_ADDR + offset);
    panHomeDir_XY[1][panel] = checkPAL(readEEPROM(panHomeDir_y_ADDR + offset));
  
    setBit(panB_REG[panel], Time_BIT, readEEPROM(panTime_en_ADDR + offset));
    panTime_XY[0][panel] = readEEPROM(panTime_x_ADDR + offset);
    panTime_XY[1][panel] = checkPAL(readEEPROM(panTime_y_ADDR + offset));
  
    //****** Third set of 8 Panels ******
  
    setBit(panC_REG[panel], CurA_BIT, readEEPROM(panCur_A_en_ADDR + offset));
    panCur_A_XY[0][panel] = readEEPROM(panCur_A_x_ADDR + offset);
    panCur_A_XY[1][panel] = checkPAL(readEEPROM(panCur_A_y_ADDR + offset));
  
    //setBit(panC_REG[panel], CurB_BIT, readEEPROM(panCur_B_en_ADDR + offset));
    //panCur_B_XY[0][panel] = readEEPROM(panCur_B_x_ADDR + offset);
    //panCur_B_XY[1][panel] = checkPAL(readEEPROM(panCur_B_y_ADDR + offset));
  
    setBit(panC_REG[panel], Alt_BIT, readEEPROM(panAlt_en_ADDR + offset));
    panAlt_XY[0][panel] = readEEPROM(panAlt_x_ADDR + offset);
    panAlt_XY[1][panel] = checkPAL(readEEPROM(panAlt_y_ADDR + offset));
  
    setBit(panC_REG[panel], Halt_BIT, readEEPROM(panHomeAlt_en_ADDR + offset));
    panHomeAlt_XY[0][panel] = readEEPROM(panHomeAlt_x_ADDR + offset);
    panHomeAlt_XY[1][panel] = checkPAL(readEEPROM(panHomeAlt_y_ADDR + offset));
    
    setBit(panC_REG[panel], As_BIT, readEEPROM(panAirSpeed_en_ADDR + offset));
    panAirSpeed_XY[0][panel] = readEEPROM(panAirSpeed_x_ADDR + offset);
    panAirSpeed_XY[1][panel] = checkPAL(readEEPROM(panAirSpeed_y_ADDR + offset));
  
    setBit(panC_REG[panel], Vel_BIT, readEEPROM(panVel_en_ADDR + offset));
    panVel_XY[0][panel] = readEEPROM(panVel_x_ADDR + offset);
    panVel_XY[1][panel] = checkPAL(readEEPROM(panVel_y_ADDR + offset));
  
    setBit(panC_REG[panel], Thr_BIT, readEEPROM(panThr_en_ADDR + offset));
    panThr_XY[0][panel] = readEEPROM(panThr_x_ADDR + offset);
    panThr_XY[1][panel] = checkPAL(readEEPROM(panThr_y_ADDR + offset));
  
    setBit(panC_REG[panel], FMod_BIT, readEEPROM(panFMod_en_ADDR + offset));
    panFMod_XY[0][panel] = readEEPROM(panFMod_x_ADDR + offset);
    panFMod_XY[1][panel] = checkPAL(readEEPROM(panFMod_y_ADDR + offset));
  
    setBit(panC_REG[panel], Hor_BIT, readEEPROM(panHorizon_en_ADDR + offset));
    panHorizon_XY[0][panel] = readEEPROM(panHorizon_x_ADDR + offset);
    panHorizon_XY[1][panel] = checkPAL(readEEPROM(panHorizon_y_ADDR + offset));
  
    //****** Fourth set of 8 Panels ******
  
    setBit(panD_REG[panel], Warn_BIT, readEEPROM(panWarn_en_ADDR + offset));
    panWarn_XY[0][panel] = readEEPROM(panWarn_x_ADDR + offset);
    panWarn_XY[1][panel] = checkPAL(readEEPROM(panWarn_y_ADDR + offset));
    
    setBit(panD_REG[panel], WindS_BIT, readEEPROM(panWindSpeed_en_ADDR + offset));
    panWindSpeed_XY[0][panel] = readEEPROM(panWindSpeed_x_ADDR + offset);
    panWindSpeed_XY[1][panel] = checkPAL(readEEPROM(panWindSpeed_y_ADDR + offset));
    
    setBit(panD_REG[panel], Climb_BIT, readEEPROM(panClimb_en_ADDR + offset));
    panClimb_XY[0][panel] = readEEPROM(panClimb_x_ADDR + offset);
    panClimb_XY[1][panel] = checkPAL(readEEPROM(panClimb_y_ADDR + offset));
    
  //  setBit(panD_REG[panel], Tune_BIT, readEEPROM(panTune_en_ADDR + offset));
  //  panTune_XY[0][panel] = readEEPROM(panTune_x_ADDR + offset);
  //  panTune_XY[1][panel] = checkPAL(readEEPROM(panTune_y_ADDR + offset));
    
    setBit(panD_REG[panel], RSSI_BIT, readEEPROM(panRSSI_en_ADDR + offset));
    panRSSI_XY[0][panel] = readEEPROM(panRSSI_x_ADDR + offset);
    panRSSI_XY[1][panel] = checkPAL(readEEPROM(panRSSI_y_ADDR + offset));
    
  }
  panel = 0; // set back to first panel after for loop
}

int checkPAL(int line){
  if(line >= osd.getCenter() && osd.getMode() == 0){
    line -= 3;//Cutting lines offset after center if NTSC
  }
  return line;
}

void updateSettings(byte panel, byte panel_x, byte panel_y, byte panel_s ) {
  if(panel >= 1 && panel <= 32) {
    
    writeEEPROM(panel_s, (6 * panel) - 6 + 0);
    if(panel_s != 0) {
      writeEEPROM(panel_x, (6 * panel) - 6 + 2);
      writeEEPROM(panel_y, (6 * panel) - 6 + 4);
    }
    osd.clear();
    readSettings();
  } 
}

