/*
 * Copyright (C) 2021 Medusalix
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <sys/types.h>

#include <unistd.h>

#include <fstream>

#include "log.h"
#include "pid_file.h"

PidFile::PidFile(const std::string& pid_file_path):
        _pid_file_path(pid_file_path) {
    std::fstream file;

    file.open(_pid_file_path, std::ios::out | std::ios::trunc);
    if(!file.is_open()) {
        Log::error("Could not open pid file for writing %s", _pid_file_path);
    } else {
        file << getpid();
        file.close();
    }
}

PidFile::~PidFile() {
    unlink(_pid_file_path.c_str());
}
