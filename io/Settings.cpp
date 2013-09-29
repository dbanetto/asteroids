/*
 * Settings.cpp
 *
 *  Created on: 25/09/2013
 *      Author: drb
 */

#include "Settings.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <regex>
#include <regex.h>

typedef std::map<std::string , std::string>::iterator map_ss_itr;

static const std::string& whitespace = " \t\0";

std::string trim (std::string str);
bool endswith (std::string str,std::string  suffix);
bool startswith (std::string str,std::string  prefix);


Settings::Settings() {
	// TODO Auto-generated constructor stub
}

Settings::Settings(const std::map<std::string , std::string> settings) {
	this->stored_settings = settings;
}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
	if (this->fs.is_open()) {
		this->fs.close();
	}
	this->stored_settings.clear();
}


bool Settings::open(const char * file) {
	this->fs.open( file , std::fstream::in | std::fstream::out);

	return this->fs.is_open();
}

bool Settings::open(std::string file) {
	this->fs.open( file.c_str() , std::fstream::in | std::fstream::out);

	return this->fs.is_open();
}

void Settings::close() {
	if (fs.is_open()) {
		this->fs.close();
	}
}

void Settings::clear() {
	this->stored_settings.clear();
}

bool Settings::exists (std::string  setting) {
	if(this->stored_settings.find(setting) == this->stored_settings.end() ) {
		return false;
	} else {
		return true;
	}
}
bool Settings::exists (const char * setting) {
	if(this->stored_settings.find(setting) == this->stored_settings.end() ) {
		return false;
	} else {
		return true;
	}
}

void Settings::load(unsigned int flag) {
	//Check if the file is open
	if (!this->fs.is_open()) {
		return;
	}

	//Seek to the beginning of the file
	this->fs.seekg( 0 , this->fs.beg );
	std::string line;
	while ( ! this->fs.eof() ) {
		//Get the current line
		std::getline ( this->fs, line );
		//Treat lines starting with # as comments and do not process
		if (line[0] == '#' || line.length() == 0) {
			continue;
		}
		//Find the equal part of the line
		std::size_t equal_pos = line.find_first_of('=', 0);

		std::string key = trim ( line.substr( 0 , equal_pos ) );
		std::string value = trim ( line.substr( equal_pos + 1  , line.length() - 1 ) );



		if (this->stored_settings.count( key ) > 0 ) {
			//There is another copy of the key, check if it is OK to override
			if (flag == SETTINGS_OVERRIDE_DUPLICATES) {
				this->stored_settings[key] = value;
			}
		} else {
			this->stored_settings[key] = value;
		}
	}
}

std::string Settings::get (std::string  setting) {
	if (this->exists(setting)) {
			return this->stored_settings[setting];
		} else {
			return "";
		}
}
std::string Settings::get (const char * setting) {
	if (this->exists(setting)) {
	return this->stored_settings[setting];
	} else {
		return "";
	}
}

bool  Settings::getBool (std::string  key) {
	std::string b = this->get(key);
	if (b != "") {
		return  ( b == "true" ? true : false );
	} else {
		return false;
	}
}
bool  Settings::getBool (const char * key) {
	std::string b = this->get(key);
	if (b != "") {
		return  ( b == "true" ? true : false );
	} else {
		return false;
	}
}

int Settings::getInt (std::string  key) {
	std::string b = this->get(key);
	if (b != "") {
		return atoi( this->get(key).c_str() );
	} else {
		return -1;
	}
}

int Settings::getInt (const char * key) {
	std::string b = this->get(key);
	if (b != "") {
		return atoi( this->get(key).c_str() );
	} else {
		return -1;
	}
}

bool Settings::add (std::string key , std::string value) {
	if (!this->exists(key)) {
	this->stored_settings[key] = value;
		return true;
	} else {
		return false;
	}
}

void Settings::set (std::string key , std::string value) {
	this->stored_settings[key] = value;
}

std::map<std::string , std::string> Settings::split ( std::string key , SettingsSplits splittype ) {
	std::map<std::string , std::string> output;

	for (map_ss_itr iterator = this->stored_settings.begin(); iterator != this->stored_settings.end(); iterator++ ) {
		switch (splittype) {
			case (SETTING_SPLIT_ENDSWITH) :
				if ( endswith( iterator->first , key )  ) {
					output[iterator->first] = iterator->second;
				}
				break;
			case (SETTING_SPLIT_STARTSWITH):
				if ( startswith( iterator->first , key )  ) {
					output[iterator->first] = iterator->second;
				}
				break;
			case (SETTING_SPLIT_REGEX):
				std::regex regx (key);

				if (std::regex_search (iterator->first.begin() , iterator->first.end() , regx)) {
					output[iterator->first] = iterator->second;
				}

				break;
		}
	}

	return output;
}


std::string trim (std::string str) {
	//Remove trailing whitespace
	int strBegin = str.find_first_not_of(whitespace);
	int strEnd = str.find_last_not_of(whitespace);
	return str.substr(strBegin,  strEnd - strBegin + 1);
}

bool endswith (std::string str,std::string  suffix) {
	if( str == "" || suffix == "" )
	    return false;

	  if(suffix.length() > str.length())
	    return false;

	  return 0 == strncmp( str.c_str() + str.length() - suffix.length(), suffix.c_str() , suffix.length() );
}
bool startswith (std::string str,std::string  prefix) {
	if( str == "" || prefix == "" )
		return false;

	if(prefix.length() > str.length())
		return false;

	return 0 == strncmp( str.c_str(), prefix.c_str() , prefix.length() );
}
