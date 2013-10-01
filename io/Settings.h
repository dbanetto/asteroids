/*
 * Settings.h
 *
 *  Created on: 25/09/2013
 *      Author: drb
 */

#ifndef Settings_H_
#define Settings_H_

#define SETTINGS_OVERRIDE_DUPLICATES 1
#define SETTINGS_IGNORE_DUPLICATES   0

#include <string>
#include <fstream>
#include <map>
#include "../util/env.h"

enum SettingsSplits
{
    SETTING_SPLIT_STARTSWITH= 0
                              ,SETTING_SPLIT_ENDSWITH  = 1
#ifdef SETTINGS_REGEX_ENABLED
                                      ,SETTING_SPLIT_REGEX     = 4
#endif
};

class Settings
{
public:
    Settings();
    Settings( Settings& settings );
    Settings(const std::map<std::string , std::string> settings);
    virtual ~Settings();

    // Open File
    bool open (std::string  file);
    bool open (const char * file);

    //Close file
    void close ();

    //Clear stored settings
    void clear();

    // Load all the settings in the file
    void load (unsigned int flag);
    void load ( std::string  file , unsigned int flag);
    void load ( std::fstream&  file , unsigned int flag);

    bool exists (std::string  setting);
    bool exists (const char * setting);

    std::string get (std::string  key);
    std::string get (const char * key);

    bool getBool (std::string  key);
    bool getBool (const char * key);

    int getInt (std::string  key);
    int getInt (const char * key);

    //Implies Overriding pre-existing is NOT ok
    // @return false : If Setting already exists
    // @return true  : If settings was added
    bool add (std::string key , std::string value);

    //Implies overriding is OK
    void set (std::string key , std::string value);

    std::map<std::string , std::string> split ( std::string key , SettingsSplits splittype );

private:
    std::fstream fs;
    std::map<std::string , std::string> stored_settings;
};

#endif /* Settings_H_ */
