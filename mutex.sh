#!/bin/bash

lockfile="/tmp/mylockfile.lock"

# Fungsi untuk critical section yang terkunci
critical_section() {
    flock -n 200 || { echo "Cannot lock the file."; exit 1; }
    for i in {1..5}; do
        echo "Critical Section - Iterasi $i"
        sleep 1
    done
}

# Membuka file descriptor 200 dan mengunci file
exec 200>"$lockfile"
critical_section 200

# Menutup file descriptor
exec 200>&-
