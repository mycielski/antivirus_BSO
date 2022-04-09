% antivirus_BSO(1) avbso 1.0.0
% Tomasz Mycielski
% April 2022

# NAME
antivirus_BSO - write this to pass this class

# SYNOPSIS
**antivirus_BSO** <file_with_hashes> <path_to_scan>

# DESCRIPTION
**antivirus_BSO** scans files and calculates their SHA256 checksums. If a file's digest matches one found in the hashes database (passed as the first cli argument of the program) that file is flagged as malicious and moved to quarantine. Malicious files have their x permission unset. You can exit the program while it is running by passing a SIGINT (Ctrl+C). It will exit gracefully.

# HASHING ALGORITHM
File digest is generated with the SHA 256 algorithm provided by OpenSSL. The choice to use this algorithm comes from my experience with VirusTotal, as it is the type of hash VT accepts for lookups.

# OPTIONS
**antivirus_BSO** does not take any options.

# BUGS
No known bugs.
