#!/bin/bash

# key_rotation.sh - Script to automate the key rotation process for AES keys.
# This script is designed to handle key rotation, securely erase the old key,
# and save the new key to a specified file. It is modular and scalable for integration
# with other cryptographic systems and components.

# Exit on any error
set -e

# Variables
KEY_FILE="/path/to/aes_key_file"  # Path to the AES key file
KEY_SIZE=32                       # AES-256 key size in bytes (256 bits = 32 bytes)
BACKUP_DIR="/path/to/backup"      # Directory where backup keys will be stored
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")  # Timestamp for backups
BACKUP_FILE="$BACKUP_DIR/aes_key_backup_$TIMESTAMP"  # Backup file path

# Ensure OpenSSL or /dev/urandom is available for secure key generation
OPENSSL_CMD=$(which openssl || echo "/dev/urandom")
[[ ! -x "$OPENSSL_CMD" ]] && { echo "Error: OpenSSL or /dev/urandom not found."; exit 1; }

# Function: Generate a new AES-256 key
# Output: A new key is generated and printed to stdout
generate_new_key() {
    if [[ "$OPENSSL_CMD" == "/dev/urandom" ]]; then
        # Fallback: Generate a key using /dev/urandom
        dd if=/dev/urandom bs=1 count=$KEY_SIZE 2>/dev/null | xxd -p
    else
        # Preferred: Generate a key using OpenSSL
        openssl rand -hex $KEY_SIZE
    fi
}

# Function: Backup the current key
# Input: Takes the current key file as an argument
# Output: Backs up the current key to the backup directory with a timestamp
backup_current_key() {
    if [[ -f "$KEY_FILE" ]]; then
        echo "Backing up the current key to $BACKUP_FILE"
        cp "$KEY_FILE" "$BACKUP_FILE" || { echo "Error: Failed to backup current key."; exit 1; }
    else
        echo "Warning: No existing key file found, skipping backup."
    fi
}

# Function: Securely erase the current key file
# Input: Takes the current key file as an argument
# Output: The file is securely erased
secure_erase_key() {
    if [[ -f "$KEY_FILE" ]]; then
        echo "Securely erasing the current key file."
        # Overwrite the file with random data, sync, and then delete
        dd if=/dev/urandom of="$KEY_FILE" bs=1 count=$KEY_SIZE conv=notrunc 2>/dev/null
        sync
        rm -f "$KEY_FILE"
    fi
}

# Function: Save the new key to the key file
# Input: Takes the new key as an argument
# Output: The new key is saved to the specified key file
save_new_key() {
    local new_key=$1
    echo "Saving the new key to $KEY_FILE"
    echo "$new_key" | xxd -r -p > "$KEY_FILE" || { echo "Error: Failed to save new key."; exit 1; }
    chmod 600 "$KEY_FILE"  # Ensure the key file is only readable by the owner
}

# Function: Log the rotation event
# Output: Logs the key rotation event to syslog or a log file
log_rotation_event() {
    local status=$1
    logger -t key_rotation "Key rotation completed: $status"
}

# Main Function: Orchestrates the key rotation process
rotate_key() {
    echo "Starting key rotation process..."

    # Step 1: Backup the current key
    backup_current_key

    # Step 2: Generate a new key
    new_key=$(generate_new_key)
    if [[ -z "$new_key" ]]; then
        echo "Error: Failed to generate a new key."
        log_rotation_event "Failed"
        exit 1
    fi

    # Step 3: Securely erase the current key
    secure_erase_key

    # Step 4: Save the new key
    save_new_key "$new_key"

    # Step 5: Log the rotation event
    log_rotation_event "Success"

    echo "Key rotation successfully completed."
}

# Ensure the script is run as root for permission management
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root. Exiting."
    exit 1
fi

# Run the key rotation function
rotate_key
