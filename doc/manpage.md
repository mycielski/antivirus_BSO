% AVBSO(1)
% Tomasz Mycielski
% April 2022

# NAME
**avbso** - write this to pass this class

# SYNOPSIS
**avbso** [file_with_hashes] [path_to_scan]

# DESCRIPTION
**avbso** scans files and calculates their SHA256 checksums. If a file's digest matches one found in the hashes database (passed as the first cli argument of the program) that file is flagged as malicious and moved to quarantine. Malicious files have their x permission unset. You can exit the program while it is running by passing a SIGINT (Ctrl+C). It will exit gracefully.

# HASHING ALGORITHM
File digest is generated with the SHA 256 algorithm provided by the OpenSSL library. The choice to use this algorithm comes from my experience with VirusTotal, as it is the type of hash VT accepts for lookups.

# DIRECTORY TRAVERSAL
The program can take a path of a file to scan but also a path to a directory. If the latter is the case then the program will recursively search through the directory and its subdirectories to find all files in them. There are limitations to this however. Anything in /proc, /dev will be skipped, and so will a /swapfile, if it exists. **Warning:** the program *does not* follow symlinks!

# OPTIONS
**avbso** does not take any options.

# BUGS
No known bugs.
