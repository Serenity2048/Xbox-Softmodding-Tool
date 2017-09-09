/*
**********************************
**********************************
**      BROUGHT TO YOU BY:		**
**********************************
**********************************
**								**
**		  [TEAM ASSEMBLY]		**
**								**
**		www.team-assembly.com	**
**								**
******************************************************************************************************
* This is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
******************************************************************************************************
*
* Source modified by Rocky5.
* Used with the 2014/16 Softmod kit.
*
******************************************************************************************************
*/
#include "Xbox Softmod Tool Kit.h"
#include "ShadowC Header.h"
#include <d3d8.h>
#include "xkhdd.h"
#include "xkeeprom.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstdio>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shared paths
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PrepDir												"E:\\Prep\\"
#define NKPSDir												"E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\"
#define NKPDir												"C:\\NKPatcher\\"
#define NKPConfDir											"C:\\NKPatcher\\Configs\\"
#define NKPDirAlt											"S:\\NKPatcher\\"
#define NKPConfDirAlt										"S:\\NKPatcher\\Configs\\"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save path for the EEPROM files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Backup_Path											"E:\\Backups\\EEPROM\\"
#define Virtual_Full_Path				NKPConfDirAlt		"eeprom.bin"
//#define Backup_Path "D:\\"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create Directory paths
// Cant seem to create a dir structure with one path, so had to use two
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Backup_EEPROM_Save_Path1							"E:\\Backups"
#define Backup_EEPROM_Save_Path2							"E:\\Backups\\EEPROM"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Config files, or if you will enabler files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Virtual_Remove_File									"D:\\Virtual_EEPROM_Remove.bin"
#define Virtual_File										"D:\\Virtual_EEPROM_Backup.bin"
#define Reboot_File											"D:\\Reboot.bin"
#define Override_File										"D:\\Standalone_Mode.bin"
#define RNKP_File											"D:\\rnkp.bin"
#define Update_Font											"D:\\Update_Font.bin"
#define Restore_Font										"D:\\Restore_Font.bin"
#define NULLHDDKey_File										"D:\\NULL_HDD_Key.bin"
#define PatchNKP_File1										"D:\\NKP_6.bin"
#define PatchNKP_File2										"D:\\NKP_67.bin"
#define Region_File1										"D:\\NTSC.bin"
#define Region_File2										"D:\\PAL.bin"
#define NullChecksum3_File									"D:\\NullChecksum3.bin"
#define FactoryResetPAL_File								"D:\\FactoryResetPAL.bin"
#define FactoryResetNTSC_File								"D:\\FactoryResetNTSC.bin"
#define EnableControlledError16_File						"D:\\EnablePersistentSoftmodMode.bin"
#define DisableControlledError16_File						"D:\\DisablePersistentSoftmodMode.bin"
#define DecryptedEERPOM_File								"D:\\BackupDEEPROM"
#define LockHDD_File					PrepDir				"LockHDD.xbe"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dashboard Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RunDashboard										"C:\\Dashboard\\default.xbe"
#define DashboardXBE					NKPSDir				"configs\\alt xbe's\\dashboard.xbe"
#define DashboardXML					NKPSDir				"configs\\dash.xml"
#define DashboardSkinXML				NKPSDir				"Skins\\Dashboard\\skin.xml"
#define DashboardSkinwideXML			NKPSDir				"Skins\\Dashboard\\skinwide.xml"
#define DashboardSkinevoxXML			NKPSDir				"Skins\\Dashboard\\skinevox.xml"
#define DashboardSkinSplash				NKPSDir				"Skins\\Dashboard\\UXSplash.jpg"
#define UnleashXXBE						NKPSDir				"Unleashx.xbe"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enable/Disable files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EnabledPNG						NKPSDir				"toggles\\enabled.png"
#define Dummy_File						NKPSDir				"modules\\Xbox softmod tool kit\\dummy_file"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup Kernel selection for first run of softmod
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NKP_XBE							NKPDirAlt			"default.xbe"
#define Dashloader											"S:\\nkpatcher\\dashloader\\default.xbe"
#define Rescuedashloader									"S:\\nkpatcher\\rescuedash\\loader.xbe"
#define PrepUX							PrepDir				"unleashx.xbe"
#define PrepXBE							PrepDir				"default.xbe"
#define SecondRun											"D:\\secondrun.bin"
#define FirstRunBin											"D:\\firstrun.bin"
#define UpdateRunBin										"D:\\updaterun.bin"
#define Font_Path						NKPConfDir			"fonts\\"
#define Font_Path_Alt 					NKPConfDirAlt		"fonts\\"
#define Generic_Font_File				NKPConfDir			"Fonts\\generic.xtf"
#define Generic_Font_File_Alt			NKPConfDirAlt		"Fonts\\generic.xtf"
#define xbox_xtf_File										"C:\\xodash\\xbox.xtf"
#define xbox_xtf_File_Alt									"S:\\xodash\\xbox.xtf"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup ShadowC selection for first run of softmod
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ShadowC_Location				NKPDir				"shadowc\\shadowc.img"
#define ShadowC_Size										485
#define ShadowCOFF						NKPConfDir			"shadowc_off.bin"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup UnleashX for showing the ShadowC partition
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NKPatcherSettings				NKPSDir				"UnleashX.xbe"
#define ResoftmodDash					NKPSDir				"modules\\resoftmod dash\\default.xbe"
#define CRescueDash						NKPDir				"rescuedash\\unleashx.xbe"
#define DashSettings					NKPSDir				"modules\\dash settings\\default.xbe"
#define ERescueDash1										"E:\\TDATA\\Rescuedash\\default.xbe"
#define ERescueDash2										"E:\\UDATA\\Rescuedash\\default.xbe"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup modifications for the xbe files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NKPatcher default
#define NKPHabibi							"\x58\x42\x45\x48\x20\x9B\xC0\x0F\xF1\x4F\x4F\x58\x73\xB8\x9F\x3B\x3C\x91\xED\x16\xE9\x14\x3C\x33\x77\xD8\xA4\xF9\xAF\xA9\xBF\x3B\xA0\xDA\x5A\x5B\x30\x0A\x57\x99\x5E\x1E\x8D\x68\xCA\x3C\x44\xF2\xFE\x95\x5B\x0D\x1C\xB3\xD6\xC7\x92\x7D\xC1\x8C\x4D\x1E\x92\x59\x0D\x08\xEC\xA6\x40\x2E\x41\x55\x41\xEB\x7D\x18\xB4\x1E\xCE\xBB\xB7\x31\xB0\xD5\xE6\x44\xCB\xEF\x53\xB5\xC5\xD8\x67\xB7\x2F\x98\x21\x62\xF1\xE7\x15\x9E\x6B\x33\x0F\x01\x53\xBA\xB3\x56\xFA\x06\x7D\x5A\x9F\x80\x01\x07\xA4\x6A\x69\x4A\x47\xD9\xF5\xFF\xF0\x0D\xA2\x15\xE6\x97\xA3\xAB\xA0\x09\x9F\x82\x54\x41\x36\x58\xF2\xB5\x87\x44\x05\xB9\x81\xAC\xEF\x62\xCF\x81\xD1\x62\x01\x1C\x48\x4F\x88\x79\xB6\x7C\x3F\x57\xDD\x85\x35\x73\xE4\x92\x7E\x7F\x0C\xF9\xD8\x8D\xEE\xE3\xB8\xEB\xFC\x27\xB9\xC1\x58\xBF\x3D\xEF\xC8\x1F\xE2\x79\xA3\x69\x21\xDD\x2D\xA9\x3C\xA9\x24\x94\xA3\x59\x7D\x0B\xD1\x54\xA0\x28\x57\x34\x91\x2D\xDD\x64\x78\xDB\x83\x08\x79\xD3\xDE\x33\x8C\x2C\x64\x37\x99\xE8\xE9\xEE\x3A\x6A\xCB\x27\x89\x09\x95\xC8\x15\xEE\xB0\x4C\x64\x85\xDB\x5E\x8B\xB6\x82\xBF\xD2\x27\x87\xE2\x2F\x11"
#define NKPHash								"\x0B\x03\xB1\xB9\x09\x3E\x6F\xE5\x82\x26\xD1\x88\x06\x45\x89\xD0\xCF\x63\x08\x75"
#define NKPHabibialt						"\x58\x42\x45\x48\x34\x83\xEB\x76\x6C\xC2\xAA\x09\xCD\x18\x7F\xF1\xEC\x00\xB2\x1A\x61\x9B\x8B\x34\xBA\x35\xC2\x0B\xCF\x7B\xB9\x05\x26\xF6\x39\x0A\xB3\xC1\x79\x5E\x90\xA4\xAD\x71\x56\x34\x81\xDD\xE9\x79\xEB\x93\x6F\xC0\xC0\xE4\xFD\x77\x9E\x13\x99\xA5\x36\x5E\x32\xA1\xA9\x6C\xA9\xE5\x24\x6D\x01\xAB\x30\x37\x0D\x2B\x9F\x03\x43\x34\xEC\x92\x2E\x59\xDF\x72\x7D\xA8\xCA\x4B\x5D\xAD\x75\xF4\x22\xFE\x82\x75\xBA\xA1\xC5\x3E\xD0\x5D\x39\xE5\x66\x95\x18\x4C\x3C\x2F\xD1\xDB\xEB\xB7\x7E\x86\xD5\x19\x9B\x77\x9A\x24\x75\x5E\x69\xBD\x37\x64\x6B\x07\x9F\x85\x1B\xB2\x2C\xC7\xA5\xAE\x45\xB4\xFA\x55\x04\xA6\xDC\x35\xDC\xFB\xFE\x6B\x41\xC2\x9F\xD3\xD7\x3E\x64\x59\x09\x59\x77\xC8\x66\xC4\x28\x32\x19\x5E\x30\x7B\x50\xA7\xD0\x3A\x22\x7E\x56\x9A\xF9\xC7\x0C\x3B\x54\x94\x2E\x38\xFF\xF4\x16\xCF\xD9\xB3\xFD\x37\xFE\xD5\xD5\xCC\x30\x82\xF4\xE0\xF9\x5D\xBC\x76\xBB\x81\x57\xC4\xC7\x87\x37\x63\x8E\xB6\x2E\x13\xE6\x80\xCC\xCE\xCB\x38\x60\x8E\x05\x61\x11\xE0\x18\x2A\x06\x53\xB9\x42\xD3\x52\xDE\x51\xA7\x80\x8A\x54\x79\x23\x74\x0A\x44\x9D\x2C\xC0\x58\x37\x3C\x27"
#define NKPHashalt							"\x25\x27\x01\x3E\xA1\xF6\x7A\x8C\x0A\xBF\xA5\x28\x97\x47\x3E\x1C\xDC\x9C\x67\x13"
#define NKPValue1							"\x01"
#define NKPValue2							"\x02"
#define NKPValue1Size						1
// NKPatcher Settings
#define NKPSHabibi							"\x58\x42\x45\x48\x04\x5A\x64\x49\x69\x20\x13\x50\x01\x6E\x3D\x17\x0F\xD2\x96\x47\x97\xEE\xA6\xC7\x58\x21\x9D\x05\x6D\x2D\xB6\x3F\x50\xD9\x0A\xD6\x11\xE3\x79\xF6\x68\x9A\xA4\xF2\x1D\xB5\x99\x42\x78\xEA\x14\xC8\x64\xAB\x22\xBB\x47\xB6\x9A\x08\x29\x17\x56\xF2\x24\x46\x18\x77\x9B\xE8\x6F\xC2\xA1\xE3\xE9\x8F\xFB\xCF\x6D\x60\xA8\x35\xFE\x3D\x7A\x99\x18\x9B\xF7\xDE\x13\x99\x43\xE1\x7F\x57\x1A\x24\x9B\xAF\xA8\x21\xD4\xCB\x56\x21\x08\x34\x09\x84\x59\xF0\xF9\xE7\x56\x81\x6D\xB7\xD7\x91\x4F\x66\x25\x68\x6E\x78\x57\xF8\x04\xD2\x69\x5F\x1F\x6A\x03\x3F\x45\x91\x33\xFE\x88\x64\x40\xD5\x15\x5E\x38\x3B\x01\x22\x65\xA8\x0D\x9E\x2A\x1A\x83\x80\x59\x65\x49\xBB\xE4\x41\xA6\xB3\x92\x34\xB8\x9F\x50\x81\x69\x23\xA9\xED\xC3\x1E\x1C\xD0\xE6\x33\xB7\x99\x1A\x5A\x44\x53\x18\x30\x67\x94\xD3\x4C\x59\x13\x26\x10\x5A\x17\x98\x47\x2F\xCD\x0D\x5C\x65\x56\x0A\x13\xDC\xA7\x86\x2B\x58\xFE\x6A\x29\xC9\xE4\xE2\xF8\x36\x60\x46\x75\x55\x1E\xF5\xBB\x8A\x77\x9E\xE0\xA3\x8E\x33\x8E\xBE\x87\x42\x62\x43\x00\x23\x92\x95\xDB\x2E\xE6\x90\xFB\xBB\x25\x70\x42\x45\x7C\xCA\x54"
#define NKPSHash							"\xBA\xC6\x20\xBF\x8A\xC7\x5A\xEF\x79\xB7\x8A\xF3\xD2\x3E\x66\xD0\xC7\xB1\x80\x52"
#define NKPSLabel							"\x4E\x00\x4B\x00\x50\x00\x61\x00\x74\x00\x63\x00\x68\x00\x65\x00\x72\x00\x20\x00\x53\x00\x65\x00\x74\x00\x74\x00\x69\x00\x6E\x00\x67\x00\x73"
#define NKPSLabelSize						35
#define NKPSRemoveTitleImage				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define NKPSRemoveTitleImageSize			14
#define NKPSRemoveItemsXML					"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define NKPSRemoveItemsXMLSize				12
#define NKPSShadowCPartition				"\x31\x34"
#define NKPSShadowCPartitionSize			2
// Resoftmod dashboard
#define ResoftmodDashHabibi					"\x58\x42\x45\x48\x09\x51\xD4\xF7\xA3\xE7\x75\xE2\xA8\xDE\x37\x4E\xE5\x31\xBC\x14\xC7\xF7\x9A\x87\x66\x0A\x89\xF5\x65\xD5\x11\xE0\xCD\xE2\x6E\x89\x38\x72\x46\xD1\x04\x79\xCA\x17\x88\x76\x81\x7F\xD1\x32\x12\xE2\xC8\x23\x3A\x4A\xE8\x65\x04\x9A\x44\xC4\x9D\x8B\xF3\x07\xB3\x80\x32\x49\xC3\xAE\xDB\x60\xDE\x71\x50\x56\xDB\x46\xD4\xB2\xC5\xE9\x6A\xC2\x6F\xC0\x8D\x79\x0D\x01\xE0\xDE\xAB\x1F\x3A\x38\x12\x11\x1B\xCB\xD4\xEE\x15\x7C\x9E\x95\x23\x9B\x29\xA3\x13\x6C\x76\x54\xDC\xD2\xA7\x91\x2D\xBE\x4D\x54\xC0\xF9\xB8\x06\xC5\xFF\x15\x87\x68\x39\x4B\xBA\xCF\xAF\x60\x70\x9F\x82\x18\xE6\xE6\x07\xA4\x19\xD6\xC3\x34\xCF\x78\xB5\x56\x8D\x53\xC7\x8D\x1D\x2C\x93\xB9\xAE\xC5\xC5\x68\x0E\xB4\x50\x89\xD6\x2D\xAF\x65\xE1\x1D\x36\x0E\xC1\xCC\x40\x74\xAB\xBC\x11\x25\x1A\x15\xE0\x56\xBE\x75\xA1\x55\xE8\xC8\xB3\xEC\xD9\x74\x3C\x0F\xBB\xB3\x32\xD3\x96\xCB\x3F\xDC\x6F\x8A\x39\x83\x80\xD9\x53\xE2\xF2\xB8\x07\x04\xDB\xFF\x0F\xE8\x95\x56\xFB\xDB\x85\x4F\xDA\x9D\x01\x0D\x4D\x77\x75\x98\x54\x43\x02\x84\x09\xD9\x0D\x42\xCC\x15\x76\xFA\x78\xB1\x62\x0A\x3A\x91\x19"
#define ResoftmodDashHash					"\x19\x0B\x5F\xA8\xA6\x1D\xB7\x7E\xE7\xB0\xDF\x2C\x3C\x33\x74\xA7\x00\xCD\xB8\x5C"
#define ResoftmodDashLabel					"\x52\x00\x65\x00\x53\x00\x6F\x00\x66\x00\x74\x00\x6D\x00\x6F\x00\x64\x00\x20\x00\x44\x00\x61\x00\x73\x00\x68"
#define ResoftmodDashLabelSize				27
// C Rescue dashboard
#define CRescueDashHabibi					"\x58\x42\x45\x48\x49\xDB\x25\xEF\xF5\x12\x40\x27\x64\x56\xEF\xBD\x93\x07\x54\x12\x59\xB2\x50\xD9\xFE\x91\xFA\x06\x27\x1A\xC5\xA5\xF1\x1B\x6D\x4E\x9C\x53\x7A\x66\xAB\x28\x64\x8E\x7B\x05\x34\xA2\x89\x44\xFC\x39\x34\xEC\xCE\x07\xAC\x6B\x09\xA5\x9C\xAC\xA3\xCD\xE0\xE3\xE6\x21\x5D\x60\xE6\xE0\xC9\xFB\xE2\xD1\x26\xE2\xC2\x6F\x9D\x2B\xBC\x86\xFA\xE8\x65\x7C\xCB\x15\x9D\x22\xCB\x39\xEA\x81\x68\x8B\xA5\x5C\x7C\xC1\xCE\x99\x00\x16\x0E\xF1\x1F\xB7\x91\x8F\x7A\x0E\x5A\x99\x0A\x60\x45\x6C\x31\x52\x80\x6F\xF6\x84\x58\x33\x7E\x61\x72\xAB\xF7\xF5\x64\x78\xF6\x0C\x0B\x65\xF2\x5F\x47\x7B\xA5\xE7\x2F\xA7\x73\x32\x02\x1A\x84\x15\x30\xF2\xA3\x61\xC9\x49\x46\xB4\x9E\xD3\x13\xF4\xD5\x5D\xCA\xBD\xB5\x79\x5F\x02\xBD\xD7\x64\x80\x63\xE0\x15\x5C\xA1\x01\xB8\xF7\x80\xAA\xC7\xFA\x44\xA5\x6E\x0E\xA8\x62\x2D\x22\x47\x80\xFE\x70\xE6\xC9\x4E\xE8\x77\x83\x50\x21\xDC\x33\x48\x36\xE7\x6F\xD3\xBD\x73\x27\x9D\x42\xA1\xD4\xE5\x0A\xDC\xF6\x5E\xCB\xFE\xCD\x4B\x09\x6E\xC0\x8F\x1D\x83\x73\xE8\x87\x3A\x12\xA2\x53\x9E\x94\x83\xAA\x87\x55\x08\x74\xB5\xAD\x27\xDB\x23\x05"
#define CRescueDashHash						"\x19\xF7\x31\x0D\xC4\x1F\x52\xDE\x0C\x80\xB6\x82\x6C\xB9\xB6\x2F\x02\x6F\x77\x3B"
#define CRescueDashLabel					"\x43\x00\x20\x00\x52\x00\x65\x00\x63\x00\x6F\x00\x76\x00\x65\x00\x72\x00\x79\x00\x20\x00\x44\x00\x61\x00\x73\x00\x68\x00"
#define CRescueDashLabelSize				29
#define CRescueDashShadowCPartition			"\x31\x34"
#define CRescueDashShadowCPartitionSize		2
// E Rescue dashboard
#define ERescueDashHabibi					"\x58\x42\x45\x48\x06\x38\x5A\x0B\xC5\x16\x8D\x76\xE9\x42\x07\x7C\xFC\x1E\x0E\xD5\xE3\x57\xAA\x2F\xC2\x6F\x80\x87\xD1\x9F\x82\xDA\xB1\x75\xDA\x2C\x0E\x82\xA5\x54\x9A\x37\x0C\x86\x12\xA9\xD9\x45\x51\x3B\x24\xB6\x63\x7A\xCB\xE8\xAA\xAE\x26\x9B\xCA\xBC\x92\xB3\x3F\x18\xF2\x98\x43\x01\xA5\x3F\x41\xDE\xB2\x17\xB2\xDD\x97\xEB\x00\x9A\xED\x47\xA3\xC9\xDE\x70\x25\x4C\xB0\x35\xC6\x7B\xE5\xF1\x3D\xD5\xF9\x54\x75\x10\xC4\xAD\x58\x71\x61\xCC\x63\xA0\x41\x07\xF3\xC6\x83\xBB\x3F\x30\x70\x01\x4E\x11\x26\x55\xAE\x9A\xB3\x28\x43\x50\x23\x08\x1C\xAE\x63\x6C\x63\xC1\xC8\x7E\x78\xE3\x09\xF7\x83\xF5\x99\x5A\x61\x8E\xDF\xB2\x82\x57\xF7\x4E\xEF\x49\xA7\xAA\xE3\x45\x4F\x08\x8B\x32\xDB\x2A\xFA\x57\xA9\xE4\x1E\x40\x1B\xBB\x3F\x67\x19\xA0\x96\x1A\xA6\x41\x02\xBF\x85\xFB\x5E\x0B\x7A\xC2\x96\x61\x19\x17\x9D\x88\x89\x55\xD0\xFB\x75\x68\x19\xC5\x04\x35\x17\xCF\xEF\x87\xA5\x4D\x56\x4E\x38\x54\x40\x49\x1B\x72\xC6\xE3\x98\xB2\x3E\x19\x6D\x30\x1C\x8E\x2D\xDB\xB3\x6C\xD1\x84\x96\xBB\xF2\x05\xCF\xA0\x18\x25\x8C\xD9\x5E\x36\x96\xD4\x77\x22\x65\x44\x19\xB3\xB0\x4C"
#define ERescueDashHash						"\x19\x0B\x5F\xA8\xA6\x1D\xB7\x7E\xE7\xB0\xDF\x2C\x3C\x33\x74\xA7\x00\xCD\xB8\x5C"
#define ERescueDashLabel					"\x45\x00\x20\x00\x52\x00\x65\x00\x63\x00\x6F\x00\x76\x00\x65\x00\x72\x00\x79\x00\x20\x00\x44\x00\x61\x00\x73\x00\x68\x00"
#define ERescueDashLabelSize				29
// Dashboard Settings
#define DashSettingsHabibi					"\x58\x42\x45\x48\xCF\x77\x26\xD8\xD6\x28\x51\x26\xFF\x13\xDC\x34\x4F\x54\x6B\xAB\xFE\xD8\xB9\xB6\xB3\xC1\x09\xD8\x7A\xAF\xF2\xFE\x6E\x6E\x76\xAA\x53\x99\x49\xA5\xA7\xFF\x79\xC6\xEF\x11\x05\x32\xA6\x37\x5F\xDD\x0B\xFE\x48\x93\x4A\x28\x7C\x95\x86\xF3\xE4\x52\x56\xFF\x98\x92\x2B\xAE\xF8\x50\x3D\xF1\x40\x15\x53\xF3\x52\xA5\x01\xDF\x2A\xBB\x0D\xFE\x50\x8D\x1C\x19\xF2\x81\x54\x57\x82\x77\x91\xF4\xB6\x0F\x8A\xCC\xC4\x37\xF2\xFB\x80\x5A\x52\xC8\x69\xAE\x99\x00\x7A\x28\x73\x62\xD6\x53\xA7\x20\xBF\x10\x51\xE6\x1A\x86\x90\x2F\xF1\x0F\xD2\x6C\xBB\x1A\x14\x63\xA1\x36\xC9\xCA\xE7\x84\x98\x5F\x06\xE7\xC6\x5A\x42\x98\x6C\xAC\xB7\xD6\x44\x36\x1F\x40\x25\x76\x11\x14\x2F\x8C\x8C\x63\x95\x22\x4F\x51\x3F\x7E\x24\x5D\x4E\x2A\x17\x7D\x72\x8F\x46\xB4\x8E\x47\x45\xEC\x1F\xDD\x67\x5A\x1A\x41\xED\xDA\x4C\x01\x6C\x78\x1D\x78\xA3\x0A\xC8\xD2\x0E\x32\xFE\x56\x4A\x9A\xAF\xF2\x02\xB0\xA0\x18\x27\xCE\x1B\xAC\x99\x66\x98\x49\x44\xDF\x38\x12\x8D\x9A\x35\x94\x64\x91\x2C\x02\xA7\xAF\xB2\x35\xA4\x28\x75\xBE\x37\x3A\xED\x8D\x5F\x43\x55\x36\xF3\x29\x45\x2A\xD5\x86"
#define DashSettingsHash					"\x19\x0B\x5F\xA8\xA6\x1D\xB7\x7E\xE7\xB0\xDF\x2C\x3C\x33\x74\xA7\x00\xCD\xB8\x5C"
#define DashSettingsLabel					"\x42\x00\x61\x00\x63\x00\x6B\x00\x75\x00\x70\x00\x2C\x00\x20\x00\x52\x00\x65\x00\x73\x00\x74\x00\x6F\x00\x72\x00\x65\x00\x20\x00\x6F\x00\x72\x00\x20\x00\x4D\x00\x6F\x00\x76\x00\x65"
#define DashSettingsLabelSize				45
// All XBE files
#define RemoveRecentdat						"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define RemoveRecentdatSize					10
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Checksum3 length is 0x60 - do not NULL to FF or you will brick your Xbox
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CheckSum3NULL						"FFFFFFFF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LED Colours
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	LED_Orange							XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_GREEN|XKUtils::LED_REGISTER_CYCLE0_RED|XKUtils::LED_REGISTER_CYCLE1_GREEN|XKUtils::LED_REGISTER_CYCLE1_RED|XKUtils::LED_REGISTER_CYCLE2_GREEN|XKUtils::LED_REGISTER_CYCLE2_RED|XKUtils::LED_REGISTER_CYCLE3_GREEN|XKUtils::LED_REGISTER_CYCLE3_RED)
#define LED_Flash_Orange					XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_GREEN|XKUtils::LED_REGISTER_CYCLE0_RED|XKUtils::LED_REGISTER_CYCLE3_GREEN|XKUtils::LED_REGISTER_CYCLE3_RED)
#define LED_Green							XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_GREEN|XKUtils::LED_REGISTER_CYCLE1_GREEN|XKUtils::LED_REGISTER_CYCLE2_GREEN|XKUtils::LED_REGISTER_CYCLE3_GREEN)
#define LED_Flash_Green						XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_GREEN|XKUtils::LED_REGISTER_CYCLE3_GREEN)
#define LED_Flash_Green_Orange				XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_GREEN|XKUtils::LED_REGISTER_CYCLE0_RED|XKUtils::LED_REGISTER_CYCLE1_GREEN|XKUtils::LED_REGISTER_CYCLE1_RED|XKUtils::LED_REGISTER_CYCLE2_GREEN|XKUtils::LED_REGISTER_CYCLE3_GREEN)
#define LED_Flash_Red						XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_RED|XKUtils::LED_REGISTER_CYCLE3_RED)
#define LED_Flash_Red_Fast					XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_RED|XKUtils::LED_REGISTER_CYCLE2_RED)
#define LED_Flash_Red_Orange				XKUtils::SetXBOXLEDStatus(XKUtils::LED_REGISTER_CYCLE0_GREEN|XKUtils::LED_REGISTER_CYCLE0_RED|XKUtils::LED_REGISTER_CYCLE1_GREEN|XKUtils::LED_REGISTER_CYCLE1_RED|XKUtils::LED_REGISTER_CYCLE2_RED|XKUtils::LED_REGISTER_CYCLE3_RED)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Code
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigMagicApp::VirtualEEPROMRemoval()
{
	std::ifstream VEEPROMRemoval(Virtual_Remove_File);
	if (VEEPROMRemoval.good())
	{
		VEEPROMRemoval.close();
		Sleep(1000);
		remove(Virtual_Full_Path);
		remove("S:\\NKPatcher\\Configs\\EEPROM_off.bin");
		remove(Virtual_Remove_File);
		remove(RNKP_File);
		remove(PrepXBE);
		RemoveDirectory(PrepDir);
		XKUtils::LaunchXBE(NKPatcherSettings);
	}
}
	
void ConfigMagicApp::EnableVirtualEEPROM()
{
	std::ifstream EnableVEEPROM(Virtual_File);
	if (EnableVEEPROM.good())
	{
		EnableVEEPROM.close();
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("INSTALLING VIRTUAL EEPROM");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(1000);
		remove(Virtual_File);
		remove(Virtual_Full_Path);
		remove("S:\\NKPatcher\\Configs\\EEPROM_off.bin");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\veeprom\\disabled.png");
		CopyFile(EnabledPNG, "E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\veeprom\\enabled.png", NULL);
		//Create Full path for BIN File..
		CHAR tmpFileName[FILENAME_MAX];
		ZeroMemory(tmpFileName, FILENAME_MAX);
		strcat(tmpFileName, Virtual_Full_Path);
		V_Serial();
		m_pXKEEPROM->WriteToBINFile((LPCSTR)tmpFileName);
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
		Render();
		Sleep(1500);
		SetupRNKP();
		XKUtils::XBOXReset();
	}
}
	
void ConfigMagicApp::SetUpDashboard()
{
	std::ifstream DashPrep(SecondRun);
	if (DashPrep.good())
	{
		DashPrep.close();
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("INSTALLING DASHBOARD FILES");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(1000);
		remove(FirstRunBin);
		remove(SecondRun);
		remove(PrepXBE);
		RemoveDirectory(PrepDir);
		CreateDirectory("C:\\Dashboard", NULL);
		CreateDirectory("C:\\Dashboard\\Skins", NULL);
		CreateDirectory("C:\\Dashboard\\Skins\\Softmod", NULL);
		CreateDirectory("C:\\Dashboard\\Skins\\Softmod Wide", NULL);
		CreateDirectory("C:\\Dashboard\\Skins\\Softmod Evox", NULL);
		CopyFile(DashboardXBE, "C:\\Dashboard\\default.xbe", NULL);
		CopyFile(DashboardXML, "C:\\Dashboard\\config.xml", NULL);
		CopyFile(DashboardSkinXML, "C:\\Dashboard\\Skins\\Softmod\\skin.xml", NULL);
		CopyFile(DashboardSkinwideXML, "C:\\Dashboard\\Skins\\Softmod Wide\\skin.xml", NULL);
		CopyFile(DashboardSkinevoxXML, "C:\\Dashboard\\Skins\\Softmod Evox\\skin.xml", NULL);
		CopyFile(DashboardSkinSplash, "C:\\Dashboard\\Skins\\Softmod\\UXSplash.jpg", NULL);
		CopyFile(DashboardSkinSplash, "C:\\Dashboard\\Skins\\Softmod Wide\\UXSplash.jpg", NULL);
		CopyFile(DashboardSkinSplash, "C:\\Dashboard\\Skins\\Softmod Evox\\UXSplash.jpg", NULL);
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
		Render();
		Sleep(1000);
		std::ifstream IfDashExist(RunDashboard);
		if (IfDashExist.good())
		{
			IfDashExist.close();
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Loading Dashboard");
			Render();
			Sleep(1500);
			XKUtils::LaunchXBE(Dashloader);
		}
		else
		{
			IfDashExist.close();
			((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("ERROR !!");
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Loading Recovery Menu");
			Render();
			LED_Flash_Red;
			Sleep(3000);
			XKUtils::LaunchXBE(Rescuedashloader);
		}
	}
}

void ConfigMagicApp::Stage2OfInstallSoftmod()
{
	std::ifstream firstrun(FirstRunBin);
	if (firstrun.good())
	{	
		firstrun.close();
		CopyFile(FirstRunBin, SecondRun, NULL);
		remove(ShadowCOFF);
		remove(FirstRunBin);
		remove("E:\\UDATA\\9e115330\\0064122817A8\\recent.dat");
		CopyFile(EnabledPNG, "E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\generic.png", NULL);
		{
			((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("CREATING SHADOWC PARTITION");
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
			Render();
			Sleep(1500);
			/* Create ShadowC.img */
			int i;
			std::ofstream FatxHeaderFile(ShadowC_Location, std::ios::binary);
			for(i = 0; i < sizeof(fatxheader); i++)
			{
				FatxHeaderFile << fatxheader[i];
			}
			FatxHeaderFile.close();
			std::ofstream ofs(ShadowC_Location, std::ios::binary | std::ios::out);
			ofs.seekp((ShadowC_Size<<20) - 1);
			ofs.write("", 1);
			ofs.close();
		}
		ColdBootSoftmod();
		PatchXBEFiles();
		InstallKernelFont();
		CreateEEPROMBackup();
		XKUtils::XBOXReset();
	}
}
	
void ConfigMagicApp::Stage2OfUpdateSoftmod()
{
	std::ifstream UpdateRun(UpdateRunBin);
	if (UpdateRun.good())
	{
		UpdateRun.close();
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("UPDATING SOFTMOD");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(1500);
		remove(ShadowCOFF);
		remove(UpdateRunBin);
		remove(PrepXBE);
		RemoveDirectory(PrepDir);
		remove("E:\\UDATA\\9e115330\\0064122817A8\\recent.dat");
		CopyFile(EnabledPNG, "E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\generic.png", NULL);
		ColdBootSoftmod();
		PatchXBEFiles();
		InstallKernelFont();
		CreateEEPROMBackup();
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::InstallKernelFont()
{
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("INSTALLING KERNEL FONT");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	Sleep(1000);
	KernelFontInstall();
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
	Render();
	Sleep(1000);
}
	
void ConfigMagicApp::UpdateKernelFont()
{
	std::ifstream UpdateFont(Update_Font);
	if (UpdateFont.good())
	{
		UpdateFont.close();
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("UPDATING INSTALLED KERNEL FONT");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(1000);
		KernelFontInstall();
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
		Render();
		Sleep(1500);
		XKUtils::LaunchXBE(NKPatcherSettings);
	}
}
	
void ConfigMagicApp::RestoreKernelFont()
{
	std::ifstream restorefont(Restore_Font);
	if (restorefont.good())
	{
		restorefont.close();
		std::ifstream restorefontcheck(Generic_Font_File_Alt);
		if (restorefontcheck.good())
		{
			restorefontcheck.close();
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\generic.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.3944.1.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.4034.1.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.4627.1.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.4817.1.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5101.1.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5530.1.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5713.1.png");
			remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5838.1.png");
			remove(xbox_xtf_File_Alt);
			remove(Restore_Font);
			CopyFile(Generic_Font_File_Alt, xbox_xtf_File_Alt, 1);
			CopyFile(EnabledPNG, "E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\generic.png", NULL);
		}
		XKUtils::LaunchXBE(NKPatcherSettings);
	}
}

void ConfigMagicApp::ReloadNKPatcherSettings()
{
	std::ifstream rnkpfile(RNKP_File);
	if (rnkpfile.good())
	{
		rnkpfile.close();
		remove(PrepXBE);
		remove(RNKP_File);
		RemoveDirectory(PrepDir);
		XKUtils::LaunchXBE(NKPatcherSettings);
	}
}

void ConfigMagicApp::NullHardDriveKey()
{
	std::ifstream nullfile(NULLHDDKey_File);
	if (nullfile.good())
	{
		nullfile.close();
		remove(NULLHDDKey_File);
		UnLock_New_HDD();
		NULL_HDD_KEY();
		Write_XBOX_EEPROM();
		Lock_New_HDD();
		CreateEEPROMBackup();
		XKUtils::LaunchXBE(NKPatcherSettings);
	}
}

void ConfigMagicApp::LockHardDrive()
{
	std::ifstream lockfile(LockHDD_File);
	if (lockfile.good())
	{
		lockfile.close();
		CreateEEPROMBackup();
		Lock_New_HDD();
		XKUtils::LaunchXBE(PrepUX);
	}
}
void ConfigMagicApp::ChangeVideoRegionToNTSC()
{
	std::ifstream regionfile1(Region_File1);
	if (regionfile1.good())
	{
		regionfile1.close();
		remove(Region_File1);
		ChangeRegionNTSC();
		SetupRNKP();
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::ChangeVideoRegionToPAL()
{
	std::ifstream regionfile2(Region_File2);
	if (regionfile2.good())
	{
		regionfile2.close();
		remove(Region_File2);
		ChangeRegionPAL();
		SetupRNKP();
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::NULLEEPROMCheckSum3()
{
	std::ifstream nullchecksum3file(NullChecksum3_File);
	if (nullchecksum3file.good())
	{
		nullchecksum3file.close();
		remove(NullChecksum3_File);
		NULLChecksum3();
		XKUtils::XBOXPowerCycle();
	}
}

void ConfigMagicApp::NTSCResetToFactoryEEPROM()
{
	std::ifstream factoryresetntscfile(FactoryResetNTSC_File);
	if (factoryresetntscfile.good())
	{
		factoryresetntscfile.close();
		remove(FactoryResetNTSC_File);
		FactoryResetNTSC();
		remove(PrepXBE);
		RemoveDirectory(PrepDir);
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::PALResetToFactoryEEPROM()
{
	std::ifstream factoryresetpalfile(FactoryResetPAL_File);
	if (factoryresetpalfile.good())
	{
		factoryresetpalfile.close();
		remove(FactoryResetPAL_File);
		FactoryResetPAL();
		remove(PrepXBE);
		RemoveDirectory(PrepDir);
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::PatchNKPatcherToSupportFtakesAll()
{
	std::ifstream nkppatchfile(PatchNKP_File1);
	if (nkppatchfile.good())
	{
		nkppatchfile.close();
		remove(PatchNKP_File1);
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("ENABLING ONLY F PARTITION");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(1000);
		std::ofstream NKPDefault(NKP_XBE, std::ios::binary | std::ios::in | std::ios::out);
			// Habibi Signature
			NKPDefault.seekp(0);
			NKPDefault.write(NKPHabibi, 260);
			// XBE Hash
			NKPDefault.seekp(888);
			NKPDefault.write(NKPHash, 20);
			//
			NKPDefault.seekp(8027);
			NKPDefault.write(NKPValue1, NKPValue1Size);
			//
			NKPDefault.seekp(17080);
			NKPDefault.write(NKPValue1, NKPValue1Size);
			NKPDefault.close();
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
		Render();
		Sleep(1500);
		SetupRNKP();
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::PatchNKPatcherToSupportFAndG()
{
	std::ifstream nkppatchfilealt(PatchNKP_File2);
	if (nkppatchfilealt.good())
	{
		nkppatchfilealt.close();
		remove(PatchNKP_File2);
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("ENABLING F & G PARTITIONS");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(1000);
		std::ofstream NKPAlt(NKP_XBE, std::ios::binary | std::ios::in | std::ios::out);
			// Habibi Signature
			NKPAlt.seekp(0);
			NKPAlt.write(NKPHabibialt, 260);
			// XBE Hash
			NKPAlt.seekp(888);
			NKPAlt.write(NKPHashalt, 20);
			//
			NKPAlt.seekp(8027);
			NKPAlt.write(NKPValue2, NKPValue1Size);
			//
			NKPAlt.seekp(17080);
			NKPAlt.write(NKPValue2, NKPValue1Size);
			NKPAlt.close();
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
		Render();
		Sleep(1500);
		SetupRNKP();
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::DumpDecryptedEEPROM()
{
	std::ifstream deepromfile(DecryptedEERPOM_File);
	if (deepromfile.good())
	{
		deepromfile.close();
		CreateDecryptedEEPROMBackup();
		XKUtils::LaunchXBE(NKPatcherSettings);
	}
}

void ConfigMagicApp::EnablePersistentSoftmodState()
{
	std::ifstream EnablePSfile(EnableControlledError16_File);
	if (EnablePSfile.good())
	{
		EnablePSfile.close();
		remove(EnableControlledError16_File);
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("ENABLING PERSISTENT SOFTMOD");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(2000);
		EnableControlledError16State();
		XKUtils::XBOXReset();
	}
}

void ConfigMagicApp::DisablePersistentSoftmodState()
{
	std::ifstream DisablePSfile(DisableControlledError16_File);
	if (DisablePSfile.good())
	{
		DisablePSfile.close();
		remove(DisableControlledError16_File);
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("DISABLING THE PERSISTENT SOFTMOD");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		Sleep(2000);
		DisableControlledError16State();
		XKUtils::XBOXReset();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigMagicApp::PatchXBEFiles()
{
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("MOVING XBE FILES");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	// Copy UX xbe files to there right place
	remove(ResoftmodDash);
	remove(ERescueDash1);
	remove(ERescueDash2);
	remove(DashSettings);
	remove(CRescueDash);
	remove(DashboardXBE);
	CopyFile(UnleashXXBE, NKPatcherSettings, NULL);
	CopyFile(UnleashXXBE, ResoftmodDash, NULL);
	CopyFile(UnleashXXBE, ERescueDash1, NULL);
	CopyFile(UnleashXXBE, ERescueDash2, NULL);
	CopyFile(UnleashXXBE, DashSettings, NULL);
	CopyFile(UnleashXXBE, CRescueDash, NULL);
	CopyFile(UnleashXXBE, DashboardXBE, NULL);
	
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("PATCHING XBE FILES");
	Render();
	// Patch UnleashX to show unprotected C partition for NKPatcher Settings
	std::ofstream UnleashX_XBE1(NKPatcherSettings, std::ios::binary | std::ios::in | std::ios::out);
	// Habibi Signature
	UnleashX_XBE1.seekp(0);
	UnleashX_XBE1.write(NKPSHabibi, 260);
	// Change XBE Title ( NKPatcher Settings )
	UnleashX_XBE1.seekp(400);
	UnleashX_XBE1.write(NKPSLabel, NKPSLabelSize);
	// XBE Hash
	UnleashX_XBE1.seekp(1532);
	UnleashX_XBE1.write(NKPSHash, 20);
	// Remove recent.dat creation
	UnleashX_XBE1.seekp(2353004);
	UnleashX_XBE1.write(RemoveRecentdat, RemoveRecentdatSize);
	// Remove XBE TitleImage.xbx parsing
	UnleashX_XBE1.seekp(2353334);
	UnleashX_XBE1.write(NKPSRemoveTitleImage, NKPSRemoveTitleImageSize);
	// Remove Items.xml
	UnleashX_XBE1.seekp(2355128);
	UnleashX_XBE1.write(NKPSRemoveItemsXML, NKPSRemoveItemsXMLSize);
	// Change C partition number
	UnleashX_XBE1.seekp(2399875);
	UnleashX_XBE1.write(NKPSShadowCPartition, NKPSShadowCPartitionSize);
	UnleashX_XBE1.close();

	std::ofstream UnleashX_XBE2(ResoftmodDash, std::ios::binary | std::ios::in | std::ios::out);
	// Habibi Signature
	UnleashX_XBE2.seekp(0);
	UnleashX_XBE2.write(ResoftmodDashHabibi, 260);
	// Change XBE Title ( Resoftmod Dash )
	UnleashX_XBE2.seekp(400);
	UnleashX_XBE2.write(ResoftmodDashLabel, ResoftmodDashLabelSize);
	// XBE Hash
	UnleashX_XBE2.seekp(1532);
	UnleashX_XBE2.write(ResoftmodDashHash, 20);
	// Remove recent.dat creation
	UnleashX_XBE2.seekp(2353004);
	UnleashX_XBE2.write(RemoveRecentdat, RemoveRecentdatSize);
	UnleashX_XBE2.close();

	std::ofstream UnleashX_XBE3(CRescueDash, std::ios::binary | std::ios::in | std::ios::out);
	// Habibi Signature
	UnleashX_XBE3.seekp(0);
	UnleashX_XBE3.write(CRescueDashHabibi, 260);
	// Change XBE Title ( C Recovery Dash )
	UnleashX_XBE3.seekp(400);
	UnleashX_XBE3.write(CRescueDashLabel, CRescueDashLabelSize);
	// XBE Hash
	UnleashX_XBE3.seekp(1532);
	UnleashX_XBE3.write(CRescueDashHash, 20);
	// Remove recent.dat creation
	UnleashX_XBE3.seekp(2353004);
	UnleashX_XBE3.write(RemoveRecentdat, RemoveRecentdatSize);
	// Change C partition number
	UnleashX_XBE3.seekp(2399875);
	UnleashX_XBE3.write(CRescueDashShadowCPartition, CRescueDashShadowCPartitionSize);
	UnleashX_XBE3.close();

	std::ofstream UnleashX_XBE5(ERescueDash1, std::ios::binary | std::ios::in | std::ios::out);
	// Habibi Signature
	UnleashX_XBE5.seekp(0);
	UnleashX_XBE5.write(ERescueDashHabibi, 260);
	// Change XBE Title ( E Recovery Dash )
	UnleashX_XBE5.seekp(400);
	UnleashX_XBE5.write(ERescueDashLabel, ERescueDashLabelSize);
	// XBE Hash
	UnleashX_XBE5.seekp(1532);
	UnleashX_XBE5.write(ERescueDashHash, 20);
	// Remove recent.dat creation
	UnleashX_XBE5.seekp(2353004);
	UnleashX_XBE5.write(RemoveRecentdat, RemoveRecentdatSize);
	UnleashX_XBE5.close();

	std::ofstream UnleashX_XBE6(ERescueDash2, std::ios::binary | std::ios::in | std::ios::out);
	// Habibi Signature
	UnleashX_XBE6.seekp(0);
	UnleashX_XBE6.write(ERescueDashHabibi, 260);
	// Change XBE Title ( E Recovery Dash )
	UnleashX_XBE6.seekp(400);
	UnleashX_XBE6.write(ERescueDashLabel, ERescueDashLabelSize);
	// XBE Hash
	UnleashX_XBE6.seekp(1532);
	UnleashX_XBE6.write(ERescueDashHash, 20);
	// Remove recent.dat creation
	UnleashX_XBE6.seekp(2353004);
	UnleashX_XBE6.write(RemoveRecentdat, RemoveRecentdatSize);
	UnleashX_XBE6.close();

	std::ofstream UnleashX_XBE7(DashSettings, std::ios::binary | std::ios::in | std::ios::out);
	// Habibi Signature
	UnleashX_XBE7.seekp(0);
	UnleashX_XBE7.write(DashSettingsHabibi, 260);
	// Change XBE Title ( Backup, Restore or Move )
	UnleashX_XBE7.seekp(400);
	UnleashX_XBE7.write(DashSettingsLabel, DashSettingsLabelSize);
	// XBE Hash
	UnleashX_XBE7.seekp(1532);
	UnleashX_XBE7.write(DashSettingsHash, 20);
	// Remove recent.dat creation
	UnleashX_XBE7.seekp(2353004);
	UnleashX_XBE7.write(RemoveRecentdat, RemoveRecentdatSize);
	UnleashX_XBE7.close();
	
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
	Render();
	Sleep(1500);
}

void ConfigMagicApp::ColdBootSoftmod()
{
	//On Screen Text
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("PATCHING EEPROM DATA");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	//Refresh screen....
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	//m_pXKEEPROM->SetTimeZoneStdNameString("GMT"); // Set timezone to GMT
	//m_pXKEEPROM->SetTimeZoneDltNameString("BST"); // Set Daylight saving to BST ( YES )
	//m_pXKEEPROM->SetTimeZoneStdDateString("0A050002"); // Set timezone standard Date
	//m_pXKEEPROM->SetTimeZoneDltDateString("03050001"); // Set Daylight saving Date
	//m_pXKEEPROM->SetTimeZoneDltBiasString("C4FFFFFF"); // Set Daylight saving Bias
	m_pXKEEPROM->SetVideoFlagsString("00004A00"); // Set Videoflags to (0A) 480p, 720p or (4A) PAL60, 480p and 720p
	m_pXKEEPROM->SetLanguageString("00"); // invalid language set, this will force the xbox to boot xboxdash.xbe always
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::EnableControlledError16State()
{
	//On Screen Text
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("PATCHING EEPROM DATA");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	//Refresh screen....
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	m_pXKEEPROM->SetLanguageString("00"); // invalid language set, this will force the xbox to boot xboxdash.xbe always
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::DisableControlledError16State()
{
	//On Screen Text
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("PATCHING EEPROM DATA");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	//Refresh screen....
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	m_pXKEEPROM->SetLanguageString("01"); // sets language to ENGLISH and stops the persistent softmod effect
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::NULLChecksum3()
{
	//On Screen Text
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("NULLING CHECKSUM 3");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	//Refresh screen....
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	m_pXKEEPROM->SetNullChecksum3String(CheckSum3NULL);
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::FactoryResetPAL()
{
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("RESETTING EEPROM");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	m_pXKEEPROM->SetVideoStandardVal(XKEEPROM::PAL_I);
	//m_pXKEEPROM->SetVideoFlagsString("00004800"); // Set Videoflags to PAL 60
	m_pXKEEPROM->SetNullChecksum3String(CheckSum3NULL);
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::FactoryResetNTSC()
{
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("RESETTING EEPROM");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	m_pXKEEPROM->SetVideoStandardVal(XKEEPROM::NTSC_M);
	m_pXKEEPROM->SetNullChecksum3String(CheckSum3NULL);
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::ChangeRegionNTSC()
{
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("CHANGING VIDEO REGION TO NTSC");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	//Re-Encrypt with correct Version...
	m_pXKEEPROM->SetVideoStandardVal(XKEEPROM::NTSC_M);
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::ChangeRegionPAL()
{
	//On Screen Text
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("CHANGING VIDEO REGION TO PAL");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	//Refresh screen....
	Render();
	Sleep(1000);
	m_pXKEEPROM->ReadFromXBOX();
	m_EnryptedRegionValid = TRUE;
	//Re-Encrypt with correct Version...
	m_pXKEEPROM->SetVideoStandardVal(XKEEPROM::PAL_I);
	Force_Write_XBOX_EEPROM();
}

void ConfigMagicApp::V_Serial()
{
	m_pXKEEPROM->ReadFromXBOX();
	m_pXKEEPROM->SetSerialNumberString("V-EEPROM ENB");
}

void ConfigMagicApp::NULL_HDD_KEY()
{	
	m_pXKEEPROM->ReadFromXBOX();
	std::ifstream nulltestfile("D:\\nulltestfile");
	if (nulltestfile.good())
	{
		m_pXKEEPROM->SetHDDKeyString("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	}
	else
	{
		m_pXKEEPROM->SetHDDKeyString("00000000000000000000000000000000");
	}
}

void ConfigMagicApp::CreateDecryptedEEPROMBackup()
{
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("BACKING UP DECRYPTED XBOX EEPROM");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		LED_Flash_Red_Fast;

		//Read XBOX EEPROM and save to disk..
		m_pXKEEPROM->ReadFromXBOX();
		m_pXKEEPROM->Decrypt();
		
		//incase path is on these drives..
		XKUtils::MountDiskE();
		CHAR tmpFileName[FILENAME_MAX];
		
		//Create Full path for BIN File..
		ZeroMemory(tmpFileName, FILENAME_MAX);
		strcat(tmpFileName, "D:\\Decrypted_EEPROM.bin");
		remove((LPCSTR)tmpFileName);
		m_pXKEEPROM->DWriteToBINFile((LPCSTR)tmpFileName);

		XKUtils::UnMountDiskE();
		//On Screen Text
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
		//Refresh screen....
		Render();
		Sleep(1500);

}

void ConfigMagicApp::SetupRNKP()
{
		CreateDirectory(PrepDir, NULL);
		CopyFile("D:\\default.xbe", "E:\\Prep\\default.xbe", NULL);
		CopyFile(Dummy_File, "E:\\Prep\\rnkp.bin", NULL);
}

void ConfigMagicApp::KernelFontInstall()
{
	LPSTR Install_Font_Partition = new CHAR[2048];
	ZeroMemory(Install_Font_Partition, 2048);
	CHAR tmpFileName[FILENAME_MAX];
	CHAR tmpFileName2[FILENAME_MAX];
	CHAR tmpData[256];
	LPSTR tmpFileStr = new CHAR[2048];
	LPSTR tmpFileStr2 = new CHAR[2048];
	DWORD tmpSize = 256;
	ZeroMemory(tmpData, tmpSize);
	ZeroMemory(tmpFileStr, 2048);
	ZeroMemory(tmpFileStr2, 2048);
	tmpSize = 256;
	ZeroMemory(tmpData, tmpSize);
	sprintf(tmpData, "K.%d.%d.%d.%d", *((USHORT*)XboxKrnlVersion),*((USHORT*)XboxKrnlVersion+1),*((USHORT*)XboxKrnlVersion+2),*((USHORT*)XboxKrnlVersion+3));
	strcat(tmpFileStr, tmpData);
	strcat(tmpFileStr2, "Installing " );
	strcat(tmpFileStr2, tmpData );
	strcat(tmpFileStr2, " Font" );
	ZeroMemory(tmpFileName, FILENAME_MAX);
	std::ifstream FontPath(Update_Font);
	if (FontPath.good())
	{
		FontPath.close();
		strcat(tmpFileName, Font_Path_Alt);
		Install_Font_Partition = xbox_xtf_File_Alt;
	}
	else
	{
		FontPath.close();
		strcat(tmpFileName, Font_Path);
		Install_Font_Partition = xbox_xtf_File;
	}
	strcat(tmpFileName, tmpFileStr);
	ZeroMemory(tmpFileName2, FILENAME_MAX);
	strcat(tmpFileName2, "E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\");
	strcat(tmpFileName2, tmpFileStr);
	strcat(tmpFileName2, ".png");
	std::ifstream updatefontcheck(tmpFileName);
	if (updatefontcheck.good())
	{
		updatefontcheck.close();
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText(tmpFileStr2);
		Render();
		Sleep(1000);
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\generic.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.3944.1.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.4034.1.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.4627.1.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.4817.1.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5101.1.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5530.1.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5713.1.png");
		remove("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\toggles\\font\\K.1.0.5838.1.png");
		remove(Install_Font_Partition);
		CopyFile(tmpFileName, Install_Font_Partition, 1);
		CopyFile(EnabledPNG, tmpFileName2, 1);
		remove(Update_Font);
	}
	else
	{
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("No Compatible Font Found");
		Render();
		Sleep(1000);
		remove(Update_Font);
	}
}

void ConfigMagicApp::CreateEEPROMBackup()
{		
		//Create E:\Backups\EEPROM directory
		CreateDirectory(Backup_EEPROM_Save_Path1, NULL);
		CreateDirectory(Backup_EEPROM_Save_Path2, NULL);
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("BACKING UP XBOX EEPROM");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
		Render();
		//save current eeprom context..
		XKEEPROM::EEPROMDATA currentEEPROM;
		m_pXKEEPROM->GetEEPROMData(&currentEEPROM);
		BOOL EncryptedState = m_pXKEEPROM->IsEncrypted();

		//Read XBOX EEPROM and save to disk..
		m_pXKEEPROM->ReadFromXBOX();
		//incase path is on these drives..
		XKUtils::MountDiskE();
		CHAR tmpFileName[FILENAME_MAX];
		
		//Create Full path for BIN File..
		ZeroMemory(tmpFileName, FILENAME_MAX);
		strcat(tmpFileName, Backup_Path);
		strcat(tmpFileName, "eeprom.bin");
		remove((LPCSTR)tmpFileName);
		m_pXKEEPROM->WriteToBINFile((LPCSTR)tmpFileName);
		
		//Write XBOX Information into .TXT file...
		ZeroMemory(tmpFileName, FILENAME_MAX);
		strcat(tmpFileName, Backup_Path);
		strcat(tmpFileName, "eeprom.cfg");
		remove((LPCSTR)tmpFileName);
		m_pXKEEPROM->WriteToCFGFile((LPCSTR)tmpFileName);

		//Create Full path for TXT File..
		ZeroMemory(tmpFileName, FILENAME_MAX);
		strcat(tmpFileName, Backup_Path);
		strcat(tmpFileName, "xbox info.txt");
		remove(tmpFileName);
		WriteTXTInfoFile(tmpFileName);

		XKUtils::UnMountDiskE();

		//switch eeprom context Back to previous
		if (EncryptedState)
			m_pXKEEPROM->SetEncryptedEEPROMData(&currentEEPROM);
		else 
			m_pXKEEPROM->SetDecryptedEEPROMData(m_XBOX_Version, &currentEEPROM);
		
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Complete");
		Render();
		Sleep(1000);
}

void ConfigMagicApp::WriteTXTInfoFile(LPCSTR strFilename)
{
	
	BOOL retVal = FALSE;
	DWORD dwBytesWrote = 0;
	CHAR tmpData[256];
	LPSTR tmpFileStr = new CHAR[2048];
	DWORD tmpSize = 256;
	ZeroMemory(tmpData, tmpSize);
	ZeroMemory(tmpFileStr, 2048);
	
	HANDLE hf = CreateFile(strFilename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hf !=  INVALID_HANDLE_VALUE)
	{
		
		//Get Xbox version
		m_EnryptedRegionValid = TRUE;
		m_XBOX_EEPROM_Current = TRUE;
		m_XBOX_Version = m_pXKEEPROM->GetXBOXVersion();

		//Re-Encrypt with correct Version...
		m_pXKEEPROM->EncryptAndCalculateCRC(m_XBOX_Version);
		
		//Time code
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		
		//Write File Header..
		strcat(tmpFileStr, "*******  XBOX & EEPROM INFORMATION FILE\r\n");
		sprintf(tmpData, "*******  Backed up on: %s", asctime (timeinfo) );
		strcat(tmpFileStr, tmpData);

		if (m_XBOX_Version == XKEEPROM::V1_0)
			strcat(tmpFileStr, "\r\nXBOX Version:\t\t\tV1.0");
		if (m_XBOX_Version == XKEEPROM::V1_1)
			strcat(tmpFileStr, "\r\nXBOX Version:\t\t\tV1.1/2/3/4/5");
        if (m_XBOX_Version == XKEEPROM::V1_6) 
            strcat(tmpFileStr, "\r\nXBOX Version:\t\t\tV1.6");

		//Get Memory Status
		strcat(tmpFileStr, "\r\nXBOX RAM in MBytes:\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		MEMORYSTATUS stat;
		GlobalMemoryStatus( &stat );
		ltoa(stat.dwTotalPhys/1024/1024, tmpData, 10);
		strcat(tmpFileStr, tmpData);
		
		//Get Kernel Version
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		sprintf(tmpData, "\r\nKernel Version:\t\t\t%d.%d.%d.%d", *((USHORT*)XboxKrnlVersion),*((USHORT*)XboxKrnlVersion+1),*((USHORT*)XboxKrnlVersion+2),*((USHORT*)XboxKrnlVersion+3));
		strcat(tmpFileStr, tmpData);

		//Write Serial Number..
		strcat(tmpFileStr, "\r\n\r\nXBOX Serial Number:\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		m_pXKEEPROM->GetSerialNumberString(tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);

		//Write MAC Address..
		strcat(tmpFileStr, "\r\nXBOX MAC Address:\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		m_pXKEEPROM->GetMACAddressString(tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);

		//Write Online Key ..
		strcat(tmpFileStr, "\r\nXBOX Online Key:\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		m_pXKEEPROM->GetOnlineKeyString(tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);

		//Write VideoMode ..
		strcat(tmpFileStr, "\r\nXBOX Video Mode:\t\t");
		VIDEO_STANDARD vdo = m_pXKEEPROM->GetVideoStandardVal();
		if (vdo == XKEEPROM::VIDEO_STANDARD::PAL_I)
			strcat(tmpFileStr, "PAL");
		else
			strcat(tmpFileStr, "NTSC");

		//Write XBE Region..
		strcat(tmpFileStr, "\r\nXBOX XBE Region:\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		m_pXKEEPROM->GetXBERegionString(tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);

		//Write HDDKey..
		strcat(tmpFileStr, "\r\nXBOX HDD Key:\t\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		m_pXKEEPROM->GetHDDKeyString(tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);

		//Write Confounder..
		strcat(tmpFileStr, "\r\nXBOX Confounder:\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		m_pXKEEPROM->GetConfounderString(tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);

		//GET HDD Info...
		//Query ATA IDENTIFY
		XKHDD::ATA_COMMAND_OBJ cmdObj;
		ZeroMemory(&cmdObj, sizeof(XKHDD::ATA_COMMAND_OBJ));
		cmdObj.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
		cmdObj.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
		XKHDD::SendATACommand(IDE_PRIMARY_PORT, &cmdObj, IDE_COMMAND_READ);
		
		//Write HDD Model
		strcat(tmpFileStr, "\r\n\r\nXBOX HDD Model:\t\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		XKHDD::GetIDEModel(cmdObj.DATA_BUFFER, (LPSTR)tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);

		//Write HDD Serial..
		strcat(tmpFileStr, "\r\nXBOX HDD Serial:\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		XKHDD::GetIDESerial(cmdObj.DATA_BUFFER, (LPSTR)tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);
		
		//Write HDD Password..
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		strcat(tmpFileStr, "\r\n\r\nXBOX HDD Password:\t\t");

		//Need decrypted HDD Key to calculate password !!
		BOOL OldState = m_pXKEEPROM->IsEncrypted();
		if (OldState)
			m_pXKEEPROM->Decrypt();
		XKEEPROM::EEPROMDATA tmptEEP;
		m_pXKEEPROM->GetEEPROMData(&tmptEEP);
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		BYTE HDDpwd[20];ZeroMemory(HDDpwd, 20);
		XKHDD::GenerateHDDPwd((UCHAR*)&tmptEEP.HDDKkey, cmdObj.DATA_BUFFER, (UCHAR*)&HDDpwd);
		XKGeneral::BytesToHexStr(HDDpwd, 20, tmpData);
		strcat(tmpFileStr, tmpData);
		if (OldState)
			m_pXKEEPROM->EncryptAndCalculateCRC(m_XBOX_Version);

		//Query ATAPI IDENTIFY
		ZeroMemory(&cmdObj, sizeof(XKHDD::ATA_COMMAND_OBJ));
		cmdObj.IPReg.bCommandReg = IDE_ATAPI_IDENTIFY;
		cmdObj.IPReg.bDriveHeadReg = IDE_DEVICE_SLAVE;
		XKHDD::SendATACommand(IDE_PRIMARY_PORT, &cmdObj, IDE_COMMAND_READ);
		
		//Write DVD Model
		strcat(tmpFileStr, "\r\n\r\nXBOX DVD Model:\t\t\t");
		tmpSize = 256;
		ZeroMemory(tmpData, tmpSize);
		XKHDD::GetIDEModel(cmdObj.DATA_BUFFER, (LPSTR)tmpData, &tmpSize);
		strcat(tmpFileStr, tmpData);
		strupr(tmpFileStr);
		WriteFile(hf, tmpFileStr, (DWORD)strlen(tmpFileStr), &dwBytesWrote, NULL);
	}
	delete[] tmpFileStr;
	CloseHandle(hf);
}

void ConfigMagicApp::UnLock_New_HDD()
{	
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("UNLOCKING HARD DRIVE");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	m_pXKEEPROM->ReadFromXBOX();
	m_XBOX_EEPROM_Current = TRUE;
	//ATA Command Structure..
	XKHDD::ATA_COMMAND_OBJ hddcommand;
	UCHAR HddPass[32];
	//Dont Lock if the EEPROM data was NOT read from XBOX
	if(m_XBOX_EEPROM_Current)
	{
		//Decrypting EEPROM, if it fails.. Display fail message!
		if (m_pXKEEPROM->Decrypt())
		{
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Checking HDD");
			Render();
			//Get IDE_ATA_IDENTIFY Data for HDD ..
			ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
			hddcommand.DATA_BUFFSIZE = 0;
			hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
			hddcommand.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
			XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_READ);

			XKEEPROM::EEPROMDATA tmpData;
			m_pXKEEPROM->GetEEPROMData(&tmpData);
			XKHDD::GenerateHDDPwd(tmpData.HDDKkey, hddcommand.DATA_BUFFER, HddPass);
			
			//Get ATA Locked State
			DWORD SecStatus = XKHDD::GetIDESecurityStatus(hddcommand.DATA_BUFFER);
			//Check if Disk is Reall locked..
			if ((SecStatus & IDE_SECURITY_SUPPORTED) && (SecStatus & IDE_SECURITY_ENABLED))
			{
				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Unlocking HDD");
				Render();
				//Execute HDD Unlock..
				ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
				hddcommand.DATA_BUFFSIZE = 512;
				hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
				hddcommand.IPReg.bCommandReg = IDE_ATA_SECURITY_UNLOCK;
				LPBYTE HDDP = (LPBYTE)&hddcommand.DATA_BUFFER;
				memcpy(HDDP+2, HddPass, 20);
				XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_WRITE);

				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Checking HDD");
				Render();
				//Query HDD To see if we succeeded..
				ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
				hddcommand.DATA_BUFFSIZE = 512;
				hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
				hddcommand.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
				XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_READ);

				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Disable HDD Password");
				Render();
				//Execute HDD Lock Disable
				ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
				hddcommand.DATA_BUFFSIZE = 512;
				hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
				hddcommand.IPReg.bCommandReg = IDE_ATA_SECURITY_DISABLE;
				memcpy(HDDP+2, HddPass, 20);
				XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_WRITE);

				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Checking HDD");
				Render();

				//We Found That sometimes that by the first query it hasnt unlocked yet.. so we query three times if needed..
				int retrycnt = 0;
				do
				{
					//Query HDD To see if we succeeded..
					ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
					hddcommand.DATA_BUFFSIZE = 512;
					hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
					hddcommand.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
					XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_READ);
					SecStatus = XKHDD::GetIDESecurityStatus(hddcommand.DATA_BUFFER);
					
					retrycnt++;
				
				} while (!((SecStatus & IDE_SECURITY_SUPPORTED) && !(SecStatus & IDE_SECURITY_ENABLED)) && (retrycnt < 3));

				if ((SecStatus & IDE_SECURITY_SUPPORTED) && !(SecStatus & IDE_SECURITY_ENABLED))
				{
					((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Xbox HDD is now unlocked");
					Render();
					Sleep(1500);
				}
				else
				{
					((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("FAILED TO UNLOCK XBOX HDD !!");
					Render();
					LED_Flash_Red_Fast;
					Sleep(5000);
					XKUtils::LaunchXBE(NKPatcherSettings);
				}				
			}
			else
			{
				((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("XBOX HDD IS NOT LOCKED ??");
				Render();
				LED_Flash_Red_Fast;
				Sleep(3000);
			}
			//Re Encrypt EEPROM with Current XBOX Version
			m_pXKEEPROM->EncryptAndCalculateCRC(m_XBOX_Version);
		}
		else
		{
			//Encrypted Region is Invalid.. DONT Allow Locking/Unlocking..
			m_EnryptedRegionValid = FALSE;
			((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("EEPROM ENCRYPTED REGION INVALID");
			Render();
			LED_Flash_Red_Fast;
			Sleep(5000);
			XKUtils::LaunchXBE(NKPatcherSettings);
		}
	}
}

void ConfigMagicApp::Write_XBOX_EEPROM()
{
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("UPDATING EEPROM");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	//ATA Command Structure..
	XKHDD::ATA_COMMAND_OBJ hddcommand;
	//Decrypting EEPROM, if it fails.. Display fail message!
	if (m_pXKEEPROM->Decrypt())
	{
		//Re-Encrypt with correct Version...
		m_EnryptedRegionValid = TRUE;
		m_XBOX_Version = m_pXKEEPROM->GetXBOXVersion();
		m_pXKEEPROM->EncryptAndCalculateCRC(m_XBOX_Version);
	
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Checking HDD");
		Render();
		//Get IDE_ATA_IDENTIFY Data for HDD ..
		ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
		hddcommand.DATA_BUFFSIZE = 0;
		hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
		hddcommand.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
		XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_READ);

		//Get ATA Locked State
		DWORD SecStatus = XKHDD::GetIDESecurityStatus(hddcommand.DATA_BUFFER);
		//Check if Disk is locked..
		if (!(SecStatus & IDE_SECURITY_ENABLED))
		{
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Writing EEPROM Data to XBOX");
			Render();
			if (m_pXKEEPROM->IsEncrypted())
			{
				m_pXKEEPROM->WriteToXBOX();
				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("EEPROM Has Been Updated");
				Render();
				Sleep(1000);
			}
			else
			{
				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatusMsg"))->SetText("EEPROM NOT ENCRYPTED");
				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("EEPROM Has Not Been Updated");
				Render();
				LED_Flash_Red_Fast;
				Sleep(5000);
			}
		}
		else
		{
			((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("UNLOCK FAILED TO UNLOCK");
			Render();
			LED_Flash_Red_Orange;
			Sleep(5000);
			XKUtils::LaunchXBE(NKPatcherSettings);
		}
	}
	else
	{
		//Encrypted Region is Invalid.. DONT Allow EEPROM Update..
		m_EnryptedRegionValid = FALSE;
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("EEPROM ENCRYPTED REGION INVALID !!");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("EEPROM Has Not Been Updated");
		Render();
		LED_Flash_Red;
		Sleep(5000);
	}
}

void ConfigMagicApp::Lock_New_HDD()
{
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("LOCKING XBOX HDD");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	Render();
	m_pXKEEPROM->ReadFromXBOX();
	m_XBOX_EEPROM_Current = TRUE;
	//ATA Command Structure..
	XKHDD::ATA_COMMAND_OBJ hddcommand;
	UCHAR HddPass[32];
	UCHAR MasterPassword[13] = "TEAMASSEMBLY";
	
	//Dont Lock if the EEPROM data was NOT read from XBOX
	if(m_XBOX_EEPROM_Current)
	{
		//Decrypting EEPROM, if it fails.. Display fail message!
		if (m_pXKEEPROM->Decrypt())
		{

			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Checking HDD");
			Render();
			//Get IDE_ATA_IDENTIFY Data for HDD ..
			ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
			hddcommand.DATA_BUFFSIZE = 0;
			hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
			hddcommand.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
			XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_READ);

			XKEEPROM::EEPROMDATA tmpData;
			m_pXKEEPROM->GetEEPROMData(&tmpData);
			XKHDD::GenerateHDDPwd(tmpData.HDDKkey, hddcommand.DATA_BUFFER, HddPass);

			//Get ATA Locked State
			DWORD SecStatus = XKHDD::GetIDESecurityStatus(hddcommand.DATA_BUFFER);
			//Check if Disk is already locked..
			if ((SecStatus & IDE_SECURITY_SUPPORTED) && !(SecStatus & IDE_SECURITY_ENABLED))
			{

				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Setting Master Password");
				Render();
				//Execute HDD Unlock..
				ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
				hddcommand.DATA_BUFFSIZE = 512;
				hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
				hddcommand.IPReg.bCommandReg = IDE_ATA_SECURITY_SETPASSWORD;
				LPBYTE HDDP = (LPBYTE)&hddcommand.DATA_BUFFER;
				LPDWORD pMastr = (LPDWORD) HDDP;
				*pMastr = 0x0001; //Set Master Pwd..
				memcpy(HDDP+2, MasterPassword, 13);
				XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_WRITE);
				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Master Password is TEAMASSEMBLY");
				Render();
				Sleep(2000);
				
				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Checking HDD");
				Render();
				//Query HDD To see if we succeeded..
				ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
				hddcommand.DATA_BUFFSIZE = 512;
				hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
				hddcommand.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
				XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_READ);
				SecStatus = XKHDD::GetIDESecurityStatus(hddcommand.DATA_BUFFER);

				((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Locking HDD");
				Render();
				//Execute HDD Unlock..
				ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
				hddcommand.DATA_BUFFSIZE = 512;
				hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
				hddcommand.IPReg.bCommandReg = IDE_ATA_SECURITY_SETPASSWORD;
				memcpy(HDDP+2, HddPass, 20);
				XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_WRITE);

				//We Found That sometimes that by the first query it hasnt locked yet.. so we query twice if needed..
				int retrycnt = 0;
				do
				{
					((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Checking HDD");
					Render();
					//Query HDD To see if we succeeded..
					ZeroMemory(&hddcommand, sizeof(XKHDD::ATA_COMMAND_OBJ));
					hddcommand.DATA_BUFFSIZE = 512;
					hddcommand.IPReg.bDriveHeadReg = IDE_DEVICE_MASTER;
					hddcommand.IPReg.bCommandReg = IDE_ATA_IDENTIFY;
					XKHDD::SendATACommand(IDE_PRIMARY_PORT, &hddcommand, IDE_COMMAND_READ);
					SecStatus = XKHDD::GetIDESecurityStatus(hddcommand.DATA_BUFFER);

					retrycnt++;

				} while (!((SecStatus & IDE_SECURITY_SUPPORTED) && (SecStatus & IDE_SECURITY_ENABLED)) && (retrycnt < 3));

				if ((SecStatus & IDE_SECURITY_SUPPORTED) && (SecStatus & IDE_SECURITY_ENABLED))
				{
					((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("HDD locked successfully");
					Render();
					Sleep(1000);
				}
				else
				{
					((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("FAILED TO LOCK XBOX HDD !!");
					Render();
					LED_Flash_Red_Fast;
					Sleep(5000);
					XKUtils::LaunchXBE(NKPatcherSettings);
				}
			}
			else
			{
				if (!(SecStatus & IDE_SECURITY_SUPPORTED))
					((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("HDD DOES NOT SUPPORT LOCKING !");
				else
					((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("XBOX HDD IS ALREADY LOCKED ??");

				Render();
				LED_Flash_Red_Fast;
				Sleep(5000);
				XKUtils::LaunchXBE(NKPatcherSettings);
			}
			// Re-Encrypt EEPROM with current XBOX Version..
			m_pXKEEPROM->EncryptAndCalculateCRC(m_XBOX_Version);
		}
		else
		{
			//Encrypted Region is Invalid.. DONT Allow Locking/Unlocking..
			m_EnryptedRegionValid = FALSE;
			((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("EEPROM ENCRYPTED REGION INVALID");
			Render();
			LED_Flash_Red_Fast;
			Sleep(5000);
			XKUtils::LaunchXBE(NKPatcherSettings);
		}
	}
	else
	{
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("LOAD XBOX EEPROM TO LOCK !!");
		Render();
		LED_Flash_Red_Fast;
		Sleep(5000);
		XKUtils::LaunchXBE(NKPatcherSettings);
	}
}

void ConfigMagicApp::Force_Write_XBOX_EEPROM()
{
	//Decrypting EEPROM, if it fails.. Display fail message!
	if (m_pXKEEPROM->Decrypt())
	{
		//Re-Encrypt with correct Version...
		m_EnryptedRegionValid = TRUE;
		m_XBOX_Version = m_pXKEEPROM->GetXBOXVersion();
		m_pXKEEPROM->EncryptAndCalculateCRC(m_XBOX_Version);
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Writing EEPROM Data to XBOX");
		Render();
		if (m_pXKEEPROM->IsEncrypted())
		{
			m_pXKEEPROM->WriteToXBOX();
			LED_Flash_Orange;
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("EEPROM Has Been Updated");
			Render();
			LED_Orange;
			Sleep(1000);
		}
		else
		{
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatusMsg"))->SetText("EEPROM NOT ENCRYPTED");
			((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("EEPROM Has Not Been Updated");
			Render();
			LED_Flash_Red_Fast;
			Sleep(5000);
		}
	}
	else
	{
		//Encrypted Region is Invalid.. DONT Allow EEPROM Update..
		m_EnryptedRegionValid = FALSE;
		((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("EEPROM ENCRYPTED REGION INVALID !!");
		((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("EEPROM Has Not Been Updated");
		Render();
		LED_Flash_Red;
		Sleep(5000);
	}
}

HRESULT ConfigMagicApp::Initialize()
{
	HRESULT retVal = S_OK;
	m_pXKEEPROM = new XKEEPROM();
	m_EnryptedRegionValid = FALSE;
	m_XBOX_EEPROM_Current = FALSE;
	//incase path is on these drives..
	XKUtils::MountDiskC();
	XKUtils::MountDiskE();
	XKUtils::MountDiskS();
	// Check for font files
	std::ifstream font1exist("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\modules\\Xbox softmod tool kit\\Media\\Font_Message.xpr"); // Size 24
	if (font1exist.good())
	{
		retVal = m_XBFont1.Create(m_pd3dDevice, "E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\modules\\Xbox softmod tool kit\\Media\\Font_Message.xpr");
	}
	else
	{
		retVal = m_XBFont1.Create(m_pd3dDevice, "D:\\Media\\Font_Message.xpr");
	}
	std::ifstream font2exist("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\modules\\Xbox softmod tool kit\\Media\\Font_Status.xpr"); // Size 20
	if (font2exist.good())
	{
		retVal = m_XBFont2.Create(m_pd3dDevice, "E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\modules\\Xbox softmod tool kit\\Media\\Font_Status.xpr");
	}
	else
	{
		retVal = m_XBFont2.Create(m_pd3dDevice, "D:\\Media\\Font_Status.xpr");
	}
	//Load Settings from Config File.. 
	LoadSettings();
	//Initialise the display.
	m_MenuXOffset = 0;
	m_MenuYOffset = 24;
	ScreenWidth = 640 - XImgCorrection;
	ScreenHeight = 480 - YImgCorrection;
	D3DXCreateSprite(m_pd3dDevice, &m_bgSprite);
	InitScreen();
	m_ActiveForm = m_pFrmStatus;
	((LPXKControl_TextBox) m_pFrmStatus->GetControl("txtStatusMsg"))->SetText("INITIALISING");
	((LPXKControl_TextBox) m_ActiveForm->GetControl("txtStatus"))->SetText("Please Wait");
	std::ifstream rnkpfileexist(RNKP_File);
	if (rnkpfileexist.good())
	{
		rnkpfileexist.close();
		Sleep(0);
	}
	else
	{
		rnkpfileexist.close();
		Render();
		Sleep(2000);
	}
	// Factory reset
	NTSCResetToFactoryEEPROM();
	PALResetToFactoryEEPROM();
	// Create dummy_file
	std::ofstream CreateDummy(Dummy_File, std::ios::binary | std::ios::out);
	CreateDummy.write("", 0);
	CreateDummy.close();
	//Functions ( These check for specific files )
	VirtualEEPROMRemoval();
	EnableVirtualEEPROM();
	SetUpDashboard();
	Stage2OfInstallSoftmod();
	Stage2OfUpdateSoftmod();
	UpdateKernelFont();
	RestoreKernelFont();
	ReloadNKPatcherSettings();
	NullHardDriveKey();
	LockHardDrive();
	ChangeVideoRegionToNTSC();
	ChangeVideoRegionToPAL();
	NULLEEPROMCheckSum3();
	PatchNKPatcherToSupportFtakesAll();
	PatchNKPatcherToSupportFAndG();
	DumpDecryptedEEPROM();
	EnablePersistentSoftmodState();
	DisablePersistentSoftmodState();
	//Default mode
	Sleep(100);
	LED_Flash_Green_Orange;
	CreateEEPROMBackup();
	LED_Orange;
	XKUtils::LaunchXBE(NKPatcherSettings);
	return retVal;
}

void ConfigMagicApp::InitScreen()
{
	m_pFrmStatus = new XKControl_Panel("Status", m_bgSprite, XOffset, YOffset, ScreenWidth,ScreenHeight);
	// Check for image file
	std::ifstream imageexist("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\modules\\Xbox softmod tool kit\\Media\\Status.png");
	if (imageexist.good())
	{
		m_pFrmStatus->LoadImage("E:\\UDATA\\21585554\\000000000000\\nkpatcher settings\\modules\\Xbox softmod tool kit\\Media\\Status.png");
	}
	else
	{	
		m_pFrmStatus->LoadImage("D:\\Media\\Status.png");
	}
	txtStatusMsg = new XKControl_TextBox("txtStatusMsg", m_bgSprite);
	txtStatusMsg->SetBitmapFont(&m_XBFont1);
	txtStatusMsg->SetTextColor(m_clrMessageTextColor);
	txtStatusMsg->SetTextCentered(TRUE);
	txtStatusMsg->SetTextShadow(FALSE);
	txtStatus = new XKControl_TextBox("txtStatus", m_bgSprite);
	txtStatus->SetBitmapFont(&m_XBFont2);
	txtStatus->SetTextColor(m_clrStatusTextColor);
	txtStatus->SetTextCentered(TRUE);
	txtStatus->SetTextShadow(FALSE);
	m_pFrmStatus->AddControl(txtStatusMsg,  0, 180,  ScreenWidth, 30);
	m_pFrmStatus->AddControl(txtStatus,		0, 400,  ScreenWidth, 30);
}

void ConfigMagicApp::ResetLocations(LONG xoffset, LONG yoffset)
{
	XOffset = (xoffset<=0)?0:xoffset;
	YOffset = (yoffset<=0)?0:yoffset;
	m_pFrmInfo->SetPosition(XOffset, YOffset);
	m_pFrmStatus->SetPosition(XOffset, YOffset);
	txtStatus->SetPosition(XOffset, YOffset+405);
}

HRESULT ConfigMagicApp::Render()
{
	//Clear screen..
    m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE); //some reason rendergradientbg doesn't wrok if this is false...
	RenderGradientBackground(0, 0);
	//Render Background Image..
	if (m_ActiveForm->IsImageLoaded())
		m_ActiveForm->Render();
	//Present Data
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}

void ConfigMagicApp::LoadSettings()
{
	//*************************** READ SCREEN SIZE, OFFSETS & COLOURS *****************************************
	XOffset = 25;
	YOffset = 20;
	XImgCorrection = 45;
	YImgCorrection = 40;
	m_clrMessageTextColor		= 0xffaee239;
	m_clrStatusTextColor		= 0xff626473;
}

//Application start point
void main()
{
	LED_Orange;
    ConfigMagicApp xbapp;
    xbapp.Create();
	xbapp.SetAppTitle("Xbox Softmod Tool Kit");
    xbapp.Run();
}