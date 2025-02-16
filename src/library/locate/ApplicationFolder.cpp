/*
 * ApplicationFolder.cpp
 *
 *  Created on: Oct 12, 2019
 *      Author: Gabriele Contini
 */
#include <fstream>
#include <sstream>
#include <string>

#include <build_properties.h>

#include "../base/logger.h"
#include "../api/datatypes.h"
#include "../base/base.h"
#include "../base/EventRegistry.h"
#include "../base/FileUtils.hpp"
#include "../os/os.h"
#include "ApplicationFolder.hpp"
#include <iostream>

namespace license {
namespace locate {
using namespace std;

ApplicationFolder::ApplicationFolder() :
		LocatorStrategy("ApplicationFolder") {
}

ApplicationFolder::~ApplicationFolder() {
}

const vector<string> ApplicationFolder::license_locations(
		EventRegistry &eventRegistry) {
	vector<string> diskFiles;
	char fname[MAX_PATH] = { 0 };
	const FUNCTION_RETURN fret = getModuleName(fname);
	if (fret == FUNC_RET_OK) {
		const string module_name = remove_extension(fname);
		const string temptativeLicense = string(module_name) + ".lic";
		ifstream f(temptativeLicense.c_str());
		if (f.good()) {
			diskFiles.push_back(temptativeLicense);
			eventRegistry.addEvent(LICENSE_FOUND, temptativeLicense.c_str());
		} else {
			eventRegistry.addEvent(LICENSE_FILE_NOT_FOUND, temptativeLicense.c_str());
		}
		f.close();
	} else {
		LOG_WARN("Error determining module name.");
	}
	return diskFiles;
}

}
} /* namespace license */
