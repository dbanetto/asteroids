/*
 * Settings.cpp
 *
 *  Created on: 25/09/2013
 *      Author: drb
 */

#include "Settings.h"
#include <iostream>
#include <stdlib.h>

static const std::string& whitespace = " \t\0";

std::string trim (std::string str);

Settings::Settings() {
	// TODO Auto-generated constructor stub

}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
	if (this->fs.is_open()) {
		this->fs.close();
	}
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
	return  ( this->get(key) == "true" ? true : false );
}
bool  Settings::getBool (const char * key) {
	return  ( this->get(key) == "true" ? true : false );
}

int Settings::getInt (std::string  key) {
	return atoi( this->get(key).c_str() );
}
int Settings::getInt (const char * key) {
	return atoi( this->get(key).c_str() );
}


std::string trim (std::string str) {
	//Remove trailing whitespace
	int strBegin = str.find_first_not_of(whitespace);
	int strEnd = str.find_last_not_of(whitespace);
	return str.substr(strBegin,  strEnd - strBegin + 1);
}
