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

class Settings {
public:
	Settings();
	virtual ~Settings();

	// Open File
	bool open (std::string file);
	bool open (const char * file);

	//Close file
	void close ();

	//Clear stored settings
	void clear();

	// Load all the settings in the file
	void load (unsigned int flag);

	bool exists (std::string  setting);
	bool exists (const char * setting);

	std::string get (std::string  key);
	std::string get (const char * key);

	bool getBool (std::string  key);
	bool getBool (const char * key);

	int getInt (std::string  key);
	int getInt (const char * key);

private:
	std::fstream fs;
	std::map<std::string , std::string> stored_settings;
};

#endif /* Settings_H_ */
